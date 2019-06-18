#include <iostream>
#include <cstdio>
#include <cstring>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "FFT/2d-fft-cuda.hpp"
using namespace std;
using namespace cv;
Mat image;
int cols, rows;
void readImg(vector<pair<float, float> >& mat) {
    image = imread("/home/ruki/Documents/lena.jpg", 0);
    rows = image.rows;
    cols = image.cols;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mat.push_back(make_pair(0, 0));
        }
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mat[i * cols + j].first = image.at<uchar>(i, j);
        }
    }
}
void saveResult(vector<pair<float, float> >& mat, string output_file) {
    Mat F = Mat(rows, cols, CV_8U, Scalar::all(0));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            F.at<uchar>(i, j) = mat[i * cols + j].first;
        }
    }
    imwrite(output_file, F);
}
int main() {
    vector<pair<float, float> > mat;
    // //float tmp[3][3] = {{1, 2, 5}, {3, 2, 5}, {5, 6, 4}};
    // float tmp[16] = {15, 32, 9, 222, 118, 151, 5, 7, 56, 233, 56, 121, 235, 89, 98, 111};
    // // for (int i = 0; i < 3; ++i) {
    // //     for (int j = 0; j < 3; ++j) {
    // //         mat.push_back(make_pair(tmp[i][j], 0));
    // //     }
    // // }
    // for (int i = 0; i < 16; ++i) {
    //     mat.push_back(make_pair(tmp[i], 0));
    // }
    // test_fft(mat, 16, 4, false);
    // for (int i = 0; i < 1; ++i) {
    //     for (int j = 0; j < 16; ++j) {
    //         cout<<mat[i * 16 + j].first<<" "<<mat[i*16+j].second<<endl;
    //     }
    // }
    readImg(mat);
    cout<<rows<<" "<<cols<<endl;
    fft_2d(mat, rows, cols, 1, false);
    saveResult(mat, "/home/ruki/Documents/lena_fft.jpg");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mat[i*cols+j].first = log(mat[i*cols+j].first);
            mat[i*cols+j].second = log(mat[i*cols+j].second);
        }
    }
    saveResult(mat, "/home/ruki/Documents/lena_fft_log.jpg");
    fft_2d(mat, rows, cols, 1, true);
    saveResult(mat, "/home/ruki/Documents/lena_fft_rev.jpg");
    return 0;
}

// https://blog.csdn.net/sac761/article/details/76525188
