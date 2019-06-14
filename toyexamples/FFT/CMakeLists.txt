cmake_minimum_required(VERSION 2.8)
find_package(CUDA QUIET REQUIRED)

# Specify binary name and source file to build it from
CUDA_ADD_LIBRARY(2DFFT 2d-fft-cuda.cpp 2d-fft-cuda.hpp fft-cuda.cu fft-cuda.cuh)
