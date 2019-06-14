#include "2d-fft-cuda.hpp"
#include "fft-cuda.cuh"

void fft_2d(vector<pair<float, float> >& a, int n, int m, int threads) {
    for (int i = 0; i < n; ++i) {
        float2 b[m];
        for (int j = 0; j < m; ++j) {
            b[j].x = a[i * m + j].first;
            b[j].y = a[i * m + j].second;
        }
        fft(b, m, threads);
        for (int j = 0; j < m; ++j) {
            a[i * m + j].first = b[j].x;
            a[i * m + j].second = b[j].y;
        }
    }
    for (int j = 0; j < m; ++j) {
        float2 b[n];
        for (int i = 0; i < n; ++i) {
            b[i].x = a[i * m + j].first;
            b[i].y = a[i * m + j].second;
        }
        fft(b, n, threads);
        for (int i = 0; i < n; ++i) {
            a[i * m + j].first = b[i].x;
            a[i * m + j].second = b[i].y;
        }
    }
}
