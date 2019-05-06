#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <cuda.h>
#include "cuda_runtime.h"
using namespace std;


#define RANDOM(x) (rand() % x)

#define MAX 100000

#define BLOCKSIZE 16

int vectorAdd(int a, int b);