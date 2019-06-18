#include "2d-fft-cuda.hpp"
#include "fft-cuda.cuh"

void test_fft(vector<pair<float, float> >& a, int n, int threads, bool isrev) {
    float2 b[n];
    for (int i = 0; i < n; ++i) {
        b[i].x = a[i].first;
        b[i].y = a[i].second;
    }
    fft(b, n, threads, isrev);
    for (int i = 0; i < n; ++i) {
        a[i].first = b[i].x;
        a[i].second = b[i].y;
    }
}

void fft_1d(vector<pair<float, float> >& a, int n, int m, int threads, bool isrev, bool byrow) {
    for (int i = 0; i < n; ++i) {
        float2 b[m];
        for (int j = 0; j < m; ++j) {
            int k = (byrow ? i * m + j : j * n + i);
            b[j].x = a[k].first;
            b[j].y = a[k].second;
        }
        fft(b, m, threads, isrev);
        for (int j = 0; j < m; ++j) {
            int k = (byrow ? i * m + j : j * n + i);
            a[k].first = b[j].x;
            a[k].second = b[j].y;
        }
    }
}

void fft_2d(vector<pair<float, float> >& a, int n, int m, int threads, bool isrev) {
    if (!isrev) {
        fft_1d(a, n, m, threads, isrev, true);
        fft_1d(a, m, n, threads, isrev, false);
    } else {
        fft_1d(a, m, n, threads, isrev, false);
        fft_1d(a, n, m, threads, isrev, true);
    }
}
