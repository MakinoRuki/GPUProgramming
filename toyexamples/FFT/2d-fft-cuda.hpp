#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <vector>
#include <opencv2/opencv.hpp>
// Seems cuda.h can not in .hpp but should in .cuh
//#include <cuda.h>
//#include <cuda_runtime.h>
using namespace std;


#define RANDOM(x) (rand() % x)

//#define MAX 100000

#define BLOCKSIZE 16

void test_fft(vector<pair<float, float> >& a, int n, int threads, bool isrev);

void fft_2d(vector<pair<float, float> >& a, int n, int m, int threads, bool isrev);
