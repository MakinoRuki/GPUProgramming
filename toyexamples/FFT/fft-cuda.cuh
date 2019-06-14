#include <iostream>
#include <cstdio>
#include <cstring>
#include <cuda.h>
#include "cuda_runtime.h"
using namespace std;
//struct float2 {
//    float x;
//    float y;
//    float2(float x, float y) : x(x), y(y) {}
//};

void fft(float2* a, int n, int threads);
