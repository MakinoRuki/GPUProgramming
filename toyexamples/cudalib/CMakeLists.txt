cmake_minimum_required(VERSION 2.8)
find_package(CUDA QUIET REQUIRED)

# Specify binary name and source file to build it from
CUDA_ADD_LIBRARY(VectorAdd vectorAdd.hpp vectorAdd.cpp vectorAdd.cuh vectorAdd.cu)
