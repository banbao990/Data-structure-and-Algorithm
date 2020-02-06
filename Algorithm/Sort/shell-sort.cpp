/**********************************************************************
 * author:      banbao                                                *
 * language:    c++/c                                                 *
 **********************************************************************/
#include <stdio.h>
#include <iostream>
using namespace std;

const int MAXN = 1010;

// shell-sort
// 先对小序列进行插入排序,再整体
// delta 序列 n, n/2, n/4, ..., 1 由于不互质, 性能一般, O(n^2)
// delta 序列 n, n/3, n/9, ..., 1                   O(n^1.5)
// delta 序列 2^k - 1, 2^(k-1) - 1, ... , 1             O(n^1.5)
// delta 序列 2^p*3^q                               O(nlog(2,n))
    // 1 2 3 4 6 8 9 12
void s_insertion_sort(int *a, int N, int delta) {
    int i, j;
    for (i = delta; i < N; i += delta) {
        int temp = a[i];
        for (j = i - delta; j >= 0; j -= delta) {
            if (a[j] > temp) a[j + delta] = a[j];
            else break;
        }
        a[j + delta] = temp;
    }
}

void shell_sort(int *a, int N) {
    for (int delta = N >> 1; delta > 0; delta >>= 1) {
        for (int i = 0; i < delta; ++i) {
            s_insertion_sort(&a[i], N - i, delta);
        }
    }
    // 如果没有进行过 delta = 1 的插入排序, 还需要进行以下的调用
    // s_insertion_sort(a,N,1);
}

int main() {
    int a[MAXN];
    int N;
    //input
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> a[i];
    //sort
    shell_sort(a, N);
    //output
    for (int i = 0; i < N; ++i) cout << a[i] << endl;
    //end
    system("pause");
    return 0;
}