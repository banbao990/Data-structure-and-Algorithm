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
int *b;

// merge-sort

// 2 2 2 3 2 4
void merge(int *a, int left, int right) {
    int m = (left + right) >> 1;
    int l = left, r = m + 1, k = l;
    while (l <= m && r <= right) {
        // = 保证稳定性
        if (a[l] <= a[r]) b[k++] = a[l++];
        else b[k++] = a[r++];
    }
    while (l <= m) b[k++] = a[l++];
    while (r <= right) b[k++] = a[r++];
    for (k = left; k <= right; ++k) a[k] = b[k];
    return;
}

// 2 2 2 3 2 4
void Sedgewick_merge(int *a, int left, int right) {
    int m = (left + right) >> 1;
    int l, r, k = left;
    for (int i = left; i <= m; ++i) b[k++] = a[i];
    for (int i = right; i > m; --i) b[k++] = a[i];//back to back
    l = left; r = right;
    // 循环代替了边界判断 2判断 -> 1判断
    for (k = left; k <= right; ++k) {
        // 一点也不稳定 (1,2,3,4)(2',3',4',4'') -> (1,2,3,4)(4'',4',3',2') -> (1,2,2',3,3',4,4'',4')
        if (b[l] <= b[r]) a[k] = b[l++];
        else a[k] = b[r--];
    }
    return;
}

void divide(int *a, int l, int r) {
    if (l >= r) return;
    int m = (l + r) >> 1;
    divide(a, l, m);
    divide(a, m + 1, r);
    Sedgewick_merge(a, l, r);
    return;
}

void merge_sort(int *a, int n) {
    b = new int[n];
    divide(a, 0, n - 1);
    delete b;
}

int main() {
    int a[MAXN];
    int N;
    //input
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> a[i];
    //sort
    merge_sort(a, N);
    //output
    for (int i = 0; i < N; ++i) cout << a[i] << endl;
    //end
    system("pause");
    return 0;
}

