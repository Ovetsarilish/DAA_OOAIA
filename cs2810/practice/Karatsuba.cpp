#include <bits/stdc++.h>
using namespace std;

int64_t karatsuba(int64_t x, int64_t y, int size){
    if(size <= 1){
        return x * y;
    }
    int m = size / 2;
    int64_t pow10 = int(pow(10, m));
    int64_t a = x / pow10;
    int64_t b = x % pow10;
    int64_t c = y / pow10;
    int64_t d = y % pow10;

    int64_t e = karatsuba(a, c, m);
    int64_t f = karatsuba(b, d, m);
    int64_t g = karatsuba(a - b, c - d, m);

    return int(pow(10, 2 * m)) * e + pow10 * (e + f - g) + f;
}

int main(){
    int64_t a = 10;
    int64_t b = 20;

    // cout << karatsuba(a, b) << "\n";
}
