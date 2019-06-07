#include "fft-cuda.cuh"

static __device__ __host__ inline Cplx CplxAdd(Cplx& a, Cplx& b) {
    Cplx c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return c;
}

static __device__ __host__ inline Cplx CplxMul(Cplx& a, Cplx& b) {
    Cplx c;
    c.x = a.x * b.x - a.y * b.y;
    c.y = a.x * b.y + a.y * b.x;
    return c;
}

static __device__ __host__ inline Cplx CplxInv(Cplx& a) {
    Cplx c(-a.x, -a.y);
    return c;
}

__global__ void bit_reorder(Cplx* da, Cplx* ra, int n, int s, int threads) {
    int id = blockIdx.x * threads + threadIdx.x;
    ra[id] = da[__brev(id) >> (32 - s)];
}

// __global__ void calc_fft(Cplx* ra, int k, int k_2, int start, int threads) {
//     int tid = blockIdx.x * threads + threadIdx.x;
//     int id = start * k_2 + tid;
//     int id2 = id + k;
//     Cplx c;
//     c.x = __cosf((2.0 * M_PI * tid) / (1.0 * k_2));
//     c.y = -__sinf((2.0 * M_PI * tid) / (1.0 * k_2));
//     Cplx u, t;
//     u = CplxAdd(ra[id], CplxMul(c, ra[id2]));
//     t = CplxAdd(ra[id], CplxInv(CplxMul(c, ra[id2])));
//     ra[id] = u;
//     ra[id2] = t;
// }

__global__ void calc_fft(Cplx* ra, int m, int threads) {
    int tid = blockIdx.x * threads + threadIdx.x;
    if (tid % m < m / 2) {
    	int id = tid;
	    int id2 = id + m / 2;
	    Cplx c;
	    c.x = __cosf((2.0 * M_PI * (tid % m)) / (1.0 * m));
	    c.y = -__sinf((2.0 * M_PI * (tid % m)) / (1.0 * m));
	    Cplx u, t;
	    u = CplxAdd(ra[id], CplxMul(c, ra[id2]));
	    t = CplxAdd(ra[id], CplxInv(CplxMul(c, ra[id2])));
	    ra[id] = u;
	    ra[id2] = t;
    }
}

void fft(Cplx* a, int n, int threads) {
    size_t data_size = n * sizeof(Cplx);
    Cplx* ra, da;
    cudaMalloc((void**)&ra, data_size);
    cudaMalloc((void**)&da, data_size);
    cudaMemcpy(da, a, data_size, cudaMemcpyHostToDevice);

    cudaDeviceSynchronize();

    int s = log2(n);
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

    Cplx* result;
    result = (Cplx*)malloc(data_size);
    cudaMemcpy(result, ra, data_size, cudaMemcpyDeviceToHost);
    cudaFree(da);
    cudaFree(ra);
}
