/**********************************************************************
 * author:      banbao                                                *
 * language:    c++/c                                                 *
 **********************************************************************/
#include <stdio.h>
#include <iostream>
using namespace std;
#pragma warning(disable:4996)

const int MAXN = 1010;

void MySwap(int &a, int &b) {
    a ^= b;
    b ^= a;
    a ^= b;
    return;
}

// radix-sort
// most significant digit first
// divide,divide,divide,...,merge
void radix_sort_MSD(int *a, int N, int radix) {
    bool last = (radix == 1);
    const int r = 10;
    int *b = new int[N];
    int* next[r] = {};
    int count[r];
    // init
    for(int i = 0; i < N; ++i) b[i] = a[i];
    for(int i = 0; i < r; ++i) count[i] = 0;
    // bucket sort
    for(int i = 0; i < N; ++i) ++count[(b[i] / radix % r)];
    for(int i = 1; i < r; ++i) count[i] += count[i-1]; 
    for(int i = N-1; i >= 0;--i) a[--count[(b[i] / radix % r)]] = b[i];
    delete b;
    if(last) return;
    int* MAXINDEX = &a[N];
    int* last_i = a;
    int before = radix;
    int cnt;
    int *i = a;
    while(i < MAXINDEX){
        if(*i < before) ++i;
        else{
            before += radix;
            cnt = (int)(i - last_i);
            if(cnt > 1) radix_sort_MSD(last_i,cnt,radix/10);
            last_i = i;
        }
    }
    // last group
    cnt = (int)(i - last_i);
    if(cnt > 1) radix_sort_MSD(last_i,cnt,radix/10);
}

// radix-sort
// least significant digit first
// divide,merge;divide,merge;...;divide,merge
// must be a stable sort function when bucket-sort(except first)
void radix_sort_LSD(int *a, int N) {
    const int MAXRADIX = 1000;
    const int r = 10;
    int radix = 1;// must start from 1
    int *b = new int[N];
    int count[r];
    int num;
    while (radix < MAXRADIX) {
        for (int i = 0; i < N; ++i) b[i] = a[i];
        for (int i = 0; i < r; ++i) count[i] = 0;
        // bucket-sort
        for (int i = 0; i < N; ++i) {
            num = b[i] / radix % r;
            ++count[num];
        }
        for (int i = 1; i < r; ++i) count[i] += count[i - 1];
        for (int i = N - 1; i >= 0; --i) a[--count[(b[i] / radix % r)]] = b[i];
        radix *= r;
    }
    delete b;
}

int main() {
    freopen("D:\\Code\\C_plus_plus\\in.txt", "r", stdin);
    freopen("D:\\Code\\C_plus_plus\\out.txt", "w", stdout);
    int a[MAXN];
    int N;
    int MaxInputNumber = 0;
    //input
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> a[i];
        if(a[i] > MaxInputNumber) MaxInputNumber = a[i];
    }
    //sort
    //radix_sort_LSD(a, N);
    int MaxRadix = 1;
    while((MaxInputNumber /= 10) > 0) MaxRadix *= 10;
    radix_sort_MSD(a,N,MaxRadix);
    //output
    for (int i = 0; i < N; ++i) cout << a[i] << endl;
    //end
    system("pause");
    return 0;
}

