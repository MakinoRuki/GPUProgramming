#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct cplx {
    float x, y;
};
// void bitrev(cplx* a, int n) {
//     cplx b[16];
//     int bits = log(n);
//     for (int i = 0; i < n; ++i) {
//         int ni = 0;
//         for (int j = 0; j < 32; ++j) {
//             ni |= (1<<(31-j));
//         }
//         b[ni >> (32 - bits)] = a[i];
//     }
//     for (int i = 0; i < n; ++i) {
//         a[i] = b[i];
//     }
// }

void bitrev(cplx *a, int n) {
    for(int i = 1, j = n / 2; i < n - 1; ++i) {
        if(i < j) swap(a[i], a[j]);
        int k = n / 2;
        while(j >= k) {
            j -= k;
            k >>= 1;
        }
        j += k;
    }
}
cplx CplxAdd(const cplx& a, const cplx& b) {
    cplx c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return c;
}
cplx CplxMinus(const cplx& a, const cplx& b) {
    cplx c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    return c;
}
cplx CplxMul(const cplx& a, const cplx& b) {
    cplx c;
    c.x = a.x * b.x - a.y * b.y;
    c.y = a.x * b.y + a.y * b.x;
    return c;
}
void fft(cplx* a, int n) {
    for (int i = 2; i <= n; i *= 2) {
        // cplx wn;
        // wn.x = cos((2.0 * M_PI) / (1.0 * i));
        // wn.y = sin((2.0 * M_PI) / (1.0 * i));
        for (int j = 0; j < n; j += i) {
            int i2 = i / 2;
            for (int k = j; k < j + i2; ++k) {
                cplx w;
                w.x = cos((2.0 * M_PI * (k - j)) / (1.0 * i));
                w.y = sin((2.0 * M_PI * (k - j)) / (1.0 * i));
                cplx u = a[k];
                cplx t = a[k + i2];
                a[k] = CplxAdd(u, CplxMul(w, t));
                a[k + i2] = CplxMinus(u, CplxMul(w, t));
                //w = CplxMul(w, wn);
            }
        }   
    }
}
int main() {
    float b[16] = {15, 32, 9, 222, 118, 151, 5, 7, 56, 233, 56, 121, 235, 89, 98, 111};
    cplx a[16];
    for (int i = 0; i < 16; ++i) {
        a[i].x = b[i];
        a[i].y = 0;
    }
    bitrev(a, 16);
    fft(a, 16);
    for (int i = 0; i < 16; ++i) {
        cout<<a[i].x<<" "<<a[i].y<<endl;
    }
    return 0;
}


/* #include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 16
using namespace std;

const double Pi = acos(-1.0);

struct complex {
    double r, i;
    complex(double r = 0, double i = 0):r(r), i(i) {}
    complex operator + (const complex &ot) const {
        return complex(r + ot.r, i + ot.i);
    }
    complex operator - (const complex &ot) const {
        return complex(r - ot.r, i - ot.i);
    }
    complex operator * (const complex &ot) const {
        return complex(r * ot.r - i * ot.i, r * ot.i + i * ot.r);
    }
}x1[N], x2[N];

void change(complex *y, int len) {
    for(int i = 1, j = len / 2; i < len - 1; ++i) {
        if(i < j) swap(y[i], y[j]);
        int k = len / 2;
        while(j >= k) {
            j -= k;
            k >>= 1;
        }
        j += k;
    }
}

void FFT(complex *y, int len, int on) {
    change(y, len);
    for(int h = 2; h <= len; h <<= 1) {
        complex wn = complex(cos(on * 2 * Pi / h), sin(on * 2 * Pi / h));
        for(int j = 0; j < len; j += h) {
            complex w = complex(1, 0);
            for(int k = j; k < j + h / 2; ++k) {
                complex u = y[k];
                complex t = y[k+h/2] * w;
                y[k] = u + t;
                y[k+h/2] = u - t;
                w = w * wn;
            }
        }
    }
    if(on == -1) {
        for(int i = 0; i < len; ++i)
            y[i].r /= len;
    }
}
int main() {
    float a[16] = {15, 32, 9, 222, 118, 151, 5, 7, 56, 233, 56, 121, 235, 89, 98, 111};
    complex b[16];
    for (int i = 0; i < 16; ++i) {
        b[i] = complex(a[i], 0);
    }
    FFT(b, 16, 1);
    for (int i = 0; i < 16; ++i) {
        cout<<b[i].r<<" "<<b[i].i<<endl;
    }
    return 0;
} */
