# 堆( $heap$ )

## 1. 实现方式

+ 实现的是**大根堆**

+ 使用数组实现
  + $a[0]$ 是树根
  + $a[2i+1]$ 是 $a[i]$ 的**左儿子**
  + $a[2i+2]$ 是 $a[i]$ 的**右儿子**

## 2. 函数

### 2.0 汇总

```C 
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
```

### 2.1 $void\ sift\_down(int\ x = 0)$;​

+ 在结点 $a[i]$ 为树根的子树中除了 $a[i]$ 之外都满足堆的性质时, 调整 $a[i]$ 为树根的子树成为堆

### 2.2 $void\ make\_heap\_sift\_down(int\ N)