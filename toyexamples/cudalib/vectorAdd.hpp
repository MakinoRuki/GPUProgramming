#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
// Seems cuda.h can not in .hpp but should in .cuh
//#include <cuda.h>
//#include <cuda_runtime.h>
using namespace std;
//#include <helper_cuda.h>


#define RANDOM(x) (rand() % x)

#define MAX 100000

#define BLOCKSIZE 16

int vectorAddHello(int a, int b);