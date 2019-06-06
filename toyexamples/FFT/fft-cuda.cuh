#include <iostream>
#include <cstdio>
#include <cstring>
#include <cuda.h>
#include "cuda_runtime.h"
using namespace std;
struct Cplx {
    float x;
    float y;
    Cplx(float x, float y) : x(x), y(y) {}
};

void fft(Cplx* a, int n, int threads);