﻿/**********************************************************************
 * author:      banbao                                                *
 * language:    c++/c                                                 *
 **********************************************************************/
#include <stdio.h>
#include <iostream>
using namespace std;
#pragma warning(disable:4996)

const int MAXN = 1010;

struct node {
    int key;
    int next;// -1 refer NULL
    node& operator = (const node& t) {
        key = t.key;
        next = t.next;
        return *this;
    }
};
template <class T>
void MySwap(T &a, T &b) {
    T temp;
    temp = a;
    a = b;
    b = temp;
    return;
}

struct StaticQueue {
    int head, tail;
    StaticQueue() :head(-1), tail(-1) {}
};

// radix-sort
// most significant digit first
// divide,divide,divide,...,merge
void radix_sort_MSD(int *a, int N, int radix);
// radix-sort
// least significant digit first
// divide,merge;divide,merge;...;divide,merge
// must be a stable sort function when bucket-sort(except first)
void radix_sort_LSD(node *a, int &first, int N);
void distribute(node *a, int first, int i, int r, StaticQueue* sq);
void collect(node *a, int& first, int r, StaticQueue* sq);

void addr_sort_index(node *a, int N, int first) {
    int index[MAXN];
    // the element should be put into the index[i]-th place
    int now = 0;
    while (first != -1) {
        index[first] = now++;
        first = a[first].next;
    }
    // index-sort version-2
    for (int i = 0; i < N - 1; i++){
        if (index[i] == i) continue;
        int j = i;
        while (index[j] != i) {
            MySwap(a[index[j]], a[i]);/* a[i] 作为temp */
            j = index[j];
        }
        // modify the index
        j = i;
        while (index[j] != i) {
            int b = index[j];
            index[j] = j;
            j = b;
        }
        index[i] = i;
        index[j] = j;
    }
}

int main() {
    freopen("D:\\Code\\C_plus_plus\\in.txt", "r", stdin);
    freopen("D:\\Code\\C_plus_plus\\out.txt", "w", stdout);
    node a[MAXN];
    int N;
    int MaxInputNumber = 0;
    // input
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> a[i].key;
    // init
    int first = 0;
    radix_sort_LSD(a, first, N);
    // index-sort
    addr_sort_index(a, N, first);
    // output
    for (int i = 0; i < N; ++i) cout << a[i].key << endl;
    // end
    return 0;
}


void radix_sort_MSD(int *a, int N, int radix) {}

void radix_sort_LSD(node *a, int &first, int N) {
    const int r = 10;
    const int d = 3;
    int radix = 1;
    StaticQueue *sq = new StaticQueue[r];
    // make initail array a link
    for (int i = 0; i < N - 1; ++i) a[i].next = i + 1;
    a[N - 1].next = -1;
    for (int i = 0; i < d; ++i) {
        distribute(a, first, i, r, sq);
        collect(a, first, r, sq);
    }
    delete[]sq;
}

void distribute(node *a, int first, int i, int r, StaticQueue* sq) {
    int cur = first;
    int key;//key
    int radix = 1;
    for (int k = 0; k < i; ++k) radix *= r;
    for (int j = 0; j < r; ++j) sq[j].head = -1;
    while (cur != -1) {
        key = a[cur].key;
        // obtian the i-th least significant key value
        key = key / radix % r;
        /*
         * sq[key].head = a[j]
         * while(a[j] != sq[key].tail ){
         *     link.push(a[j]);
         *     a[j] = a[j].next;
         * }
        */
        if (sq[key].head == -1) sq[key].head = cur;
        else a[sq[key].tail].next = cur;
        sq[key].tail = cur;
        cur = a[cur].next;
    }
}

void collect(node *a, int& first, int r, StaticQueue* sq) {
    int last;
    int key = 0;
    // find first non-empty group
    while (sq[key].head == -1) ++key;
    first = sq[key].head;
    last = sq[key].tail;
    // find others
    while (key < r - 1) {
        ++key;
        // find next non-empty group and add it to tail
        while (key < r - 1 && sq[key].tail == -1) ++key;
        // has next group
        if (sq[key].head != -1) {
            a[last].next = sq[key].head;
            last = sq[key].tail;
        }
    }
    // a[last].next = -1
    a[last].next = -1;
    /*
     * first = a[first].next
     * travel through
    */
}

