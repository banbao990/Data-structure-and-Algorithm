/**********************************************************************
 * author:      banbao                                                *
 * language:    c++/c                                                 *
 **********************************************************************/
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
#pragma warning(disable:4996)

const int MAXN = 1010;
const int MAXNUMBER = 1000;//桶的个数

// bucket-sort
void bucket_sort(int *a, int n, int M) {
    int *bucket = new int[M+1];//桶
    for (int i = 0; i <= M; ++i) bucket[i] = 0;//置0
    int *b = new int[n];
    for (int i = 0; i < n; ++i) {
        b[i] = a[i];//copy
        ++bucket[a[i]];
    }
    for (int i = 1; i <= M; ++i) bucket[i] += bucket[i - 1];
    for (int i = n - 1; i>=0; --i) a[--bucket[b[i]]] = b[i];// -- 表示从0开始存
    delete b;
    delete bucket;
    return;
}

int main() {
    freopen("D:\\Code\\C_plus_plus\\in.txt", "r", stdin);
    freopen("D:\\Code\\C_plus_plus\\out.txt", "w", stdout);
    int a[MAXN];
    int N;
    //input
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> a[i];
    //sort
    bucket_sort(a, N, MAXNUMBER);
    //output
    for (int i = 0; i < N; ++i) cout << a[i] << endl;
    //end
    system("pause");
    return 0;
}

