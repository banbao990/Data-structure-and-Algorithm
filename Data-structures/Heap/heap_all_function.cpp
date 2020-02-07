/**********************************************************************
 * author:      banbao                                                *
 * language:    c++/c                                                 *
 **********************************************************************/
#include <stdio.h>
#include <iostream>
using namespace std;

const int MAXN = 1010;

// heap-sort
int a[MAXN];
int current;

void make_heap_sift_down(int N);
void make_heap_sift_up(int N);
int top_heap();
void pop_heap();
void sift_down(int x = 0);
void heap_sort(int N);
void sift_up(int x);
void make_heap_sift_up(int N);
bool del_heap(int x = 0);
bool insert_heap(int value);

/* MAX ROOT HEAP */

int main() {
    //input
    int N;
    //int b[MAXN];//for test1
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> a[i];
    //for (int i = 0; i < N; ++i) cin >> b[i];
    //sort
    heap_sort(N);
    /*
        //test1 (insert) start
            current = 0;
            for (int i = 0; i < N; ++i) insert_heap(b[i]);
            int count = current;
            while (--count) pop_heap();
        //test1 end
    */
    //output
    for (int i = 0; i < N; ++i) cout << a[i] << endl;
    //end
    system("pause");
    return 0;
}

// O(log(depth))
void sift_down(int x) {
    int f = x;//father
    int f_v = a[x];//father-value
    int s = (f << 1) | 1;//left-son
    while (s < current) {
        if (s < current - 1 && a[s] < a[s + 1]) ++s;//找出大儿子
        if (a[s] > f_v) {
            a[f] = a[s];
            f = s;
            s = (f << 1) | 1;
        }
        else break; // end
    }
    a[f] = f_v;
    return;
}

// O(n)
void make_heap_sift_down(int N) {
    current = N;
    int last_node_has_leaf = (N >> 1) - 1;
    for (int i = last_node_has_leaf; i >= 0; --i) sift_down(i);
    return;
}

// O(logn)
void pop_heap() {
    int temp = a[0];
    a[0] = a[--current];
    a[current] = temp;
    sift_down();
    return;
}

int top_heap() {
    return a[0];
}

void heap_sort(int N) {
    make_heap_sift_down(N);
    //make_heap_sift_up(N);
    int count = current;
    while (--count) pop_heap();
    //while (--count) del();
    return;
}

void sift_up(int x) {
    int s = x;
    int s_v = a[x];
    int f = (s - 1) >> 1;
    while (s > 0) {
        if (a[f] < s_v) {
            a[s] = a[f];
            s = f;
            f = (s - 1) >> 1;
        }
        else break;
    }
    a[s] = s_v;
}

void make_heap_sift_up(int N) {
    current = N;
    for (int i = 1; i < N; ++i) sift_up(i);
    return;
}

// O(lgn)
bool del_heap(int x) {
    // 异常处理
    if (x < 0 || x >= current) return false;
    int temp = a[x];
    a[x] = a[--current];
    a[current] = temp;//保全数组
    sift_up(x);
    sift_down(x);
    return true;
}

bool insert_heap(int value) {
    // overflow
    // return false; 
    a[current] = value;
    sift_up(current);
    ++current;
    return true;
}

