/**********************************************************************
 * author:      banbao                                                *
 * language:    c++/c                                                 *
 **********************************************************************/
#include <stdio.h>
#include <iostream>
using namespace std;

const int MAXN = 1010;

// 查找时二分优化
//insert-sort
//data (0,N-1)
void insertion_sort(int *a, int N) {
    int i, j;
    for (i = 1; i < N; ++i) {
        int temp = a[i];
        for (j = i - 1; j >= 0; --j) {
            if (a[j] > temp) a[j + 1] = a[j];
            else break;
        }
        a[j + 1] = temp;
    }
}

int main() {
    int a[MAXN];
    int N;
    //input
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> a[i];
    //sort
    insertion_sort(a, N);
    //output
    for (int i = 0; i < N; ++i) cout << a[i] << endl;
    system("pause");
    return 0;
}