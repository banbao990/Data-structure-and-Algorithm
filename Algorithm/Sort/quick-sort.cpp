/**********************************************************************
 * author:      banbao                                                *
 * language:    c++/c                                                 *
 **********************************************************************/
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

const int MAXN = 1010;

void MySwap(int &a, int &b) {
    a ^= b;
    b ^= a;
    a ^= b;
    return;
}

// quick-sort

int select_pivot(int left, int right) {
    //return  (left + right) >> 1;  //2 2 2 9 2 4
    return rand() % (right - left) + left;//2 4 3 3 2 6 //3 3 3 4 3 5 拉平
}

void quick_sort(int *a, int left, int right) {
    if (left >= right) return;
    //standard
    int pivot = select_pivot(left, right);
    int p_v = a[pivot];//pivot value
    int l = left, r = right;
    a[pivot] = a[r];//此时 a[r] 空
    while (l < r) {
        while (a[l] <= p_v && l < r) ++l;
        if (l < r) a[r--] = a[l];// a[l] 空
        while (a[r] >= p_v && l < r) --r;
        if (l < r) a[l++] = a[r];// a[r] 空
    }
    a[l] = p_v;
    quick_sort(a, left, l - 1);
    quick_sort(a, r + 1, right);
    return;
}

int main() {
    srand((unsigned)time(NULL));
    int a[MAXN];
    int N;
    //input
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> a[i];
    //sort
    quick_sort(a, 0, N - 1);
    //output
    for (int i = 0; i < N; ++i) cout << a[i] << endl;
    //end
    system("pause");
    return 0;
}

