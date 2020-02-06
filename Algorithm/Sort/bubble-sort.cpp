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

// bubble-sort
void bubble_sort(int *a,int N) {
    for (int i = 0; i < N - 1; ++i) {
        bool swap = false;//没有交换说明成功, 优化
        for (int j = N - 1; j > i; --j) {
            if (a[j - 1] > a[j]) MySwap(a[j - 1], a[j]);
        }
        if (swap) break;
    }
}

int main() {
    freopen("D:\\Code\\C_plus_plus\\in.txt", "r", stdin);
    freopen("D:\\Code\\C_plus_plus\\out_s.txt", "w", stdout);
    int a[MAXN];
    int N;
    //input
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> a[i];
    //sort
    bubble_sort(a, N);
    //output
    for (int i = 0; i < N; ++i) cout << a[i] << endl;
    //end
    system("pause");
    return 0;
}

