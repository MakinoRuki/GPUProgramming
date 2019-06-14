#include "fft-cuda.cuh"

static __device__ __host__ inline float2 CplxAdd(float2 a, float2 b) {
    float2 c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return c;
}

static __device__ __host__ inline float2 CplxMul(float2 a, float2 b) {
    float2 c;
    c.x = a.x * b.x - a.y * b.y;
    c.y = a.x * b.y + a.y * b.x;
    return c;
}

static __device__ __host__ inline float2 CplxInv(float2 a) {
    float2 c;
    c.x = -a.x;
    c.y = -a.y;
    return c;
}

__global__ void bit_reorder(float2* da, float2* ra, int n, int s, int threads) {
    int id = blockIdx.x * threads + threadIdx.x;
    ra[id] = da[__brev(id) >> (32 - s)];
}

// __global__ void calc_fft(float2* ra, int k, int k_2, int start, int threads) {
//     int tid = blockIdx.x * threads + threadIdx.x;
//     int id = start * k_2 + tid;
//     int id2 = id + k;
//     float2 c;
//     c.x = __cosf((2.0 * M_PI * tid) / (1.0 * k_2));
//     c.y = -__sinf((2.0 * M_PI * tid) / (1.0 * k_2));
//     float2 u, t;
//     u = float2Add(ra[id], float2Mul(c, ra[id2]));
//     t = float2Add(ra[id], float2Inv(float2Mul(c, ra[id2])));
//     ra[id] = u;
//     ra[id2] = t;
// }

__global__ void calc_fft(float2* ra, int m, int threads) {
    int tid = blockIdx.x * threads + threadIdx.x;
    if (tid % m < m / 2) {
    	int id = tid;
	    int id2 = id + m / 2;
	    float2 c;
	    c.x = __cosf((2.0 * M_PI * (tid % m)) / (1.0 * m));
	    c.y = -__sinf((2.0 * M_PI * (tid % m)) / (1.0 * m));
	    float2 u, t;
	    u = CplxAdd(ra[id], CplxMul(c, ra[id2]));
	    t = CplxAdd(ra[id], CplxInv(CplxMul(c, ra[id2])));
	    ra[id] = u;
	    ra[id2] = t;
    }
}

void fft(float2* a, int n, int threads) {
    size_t data_size = n * sizeof(float2);
    float2* ra;
    float2* da;
    cudaMalloc((void**)&ra, data_size);
    cudaMalloc((void**)&da, data_size);
    cudaMemcpy(da, a, data_size, cudaMemcpyHostToDevice);

    cudaDeviceSynchronize();

    int s = log2((float)n);
    bit_reorder<<<n/threads, threads>>>(da, ra, n, s, threads);

    // for (int i = 2; i < n; i *= 2) {
    //     for (int j = 0; j < n; j += i) {
    //         int k = i / 2;
    //         calc_fft<<<ceil(k/threads), threads>>>(ra, k, i, j, threads);
    //     }
    // }
    for (int i = 2; i < n; i *= 2) {
    	calc_fft<<<ceil(n/threads), threads>>>(ra, i, threads);
    }

    // float2* result;
    // result = (float2*)malloc(data_size);
    cudaMemcpy(a, ra, data_size, cudaMemcpyDeviceToHost);
    cudaFree(da);
    cudaFree(ra);
}
