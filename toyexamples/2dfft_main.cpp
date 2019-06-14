#include <iostream>
#include <cstdio>
#include <cstring>
#include "FFT/2d-fft-cuda.hpp"
using namespace std;
int main() {
    vector<pair<float, float> > mat;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            pair<float, float> num(i * 4.0 + j, 0);
            mat.push_back(num);
        }
    }
    fft_2d(mat, 4, 4, 1);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout<<i<<" "<<j<<" "<<mat[i * 4 + j].first<<" "<<mat[i * 4 + j].second<<endl;
        }
    }
    return 0;
}
