/**********************************************************************
 * author:      banbao                                                *
 * language:    c++/c                                                 *
 **********************************************************************/
#include <stdio.h>
#include <iostream>
using namespace std;

const int MAXN = 1010;

// select-sort
void selection_sort(int *a, int N) {
    int temp, index;
    for (int i = 0; i < N - 1; ++i) {
        index = i;// 最小值
        for (int j = i + 1; j < N; ++j) if (a[j] < a[index]) index = j;
        temp = a[i];
        a[i] = a[index];
        a[index] = temp;
    }
}

int main() {
    int a[MAXN];
    int N;
    //input
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> a[i];
    //sort
    selection_sort(a, N);
    //output
    for (int i = 0; i < N; ++i) cout << a[i] << endl;
    //end
    system("pause");
    return 0;
}