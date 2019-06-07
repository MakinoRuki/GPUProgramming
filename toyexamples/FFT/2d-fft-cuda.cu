#include "fft-cuda.cuh"

void 2d_fft(Cplx* a, int n, int m, int threads) {
    for (int i = 0; i < n; ++i) {
        Cplx b[m];
        for (int j = 0; j < m; ++j) {
            b[j] = a[i * m + j];
        }
        fft(b, m, threads);
        for (int j = 0; j < m; ++j) {
            a[i * m + j] = b[j];
        }
    }
    for (int j = 0; j < m; ++j) {
        Cplx b[n];
        for (int i = 0; i < n; ++i) {
            b[i] = a[i * m + j];
        }
        fft(b, n, threads);
        for (int i = 0; i < n; ++i) {
            a[i * m + j] = b[i];
        }
    }
}