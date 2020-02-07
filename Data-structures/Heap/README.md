# 堆( [$heap$](./heap_all_function.cpp) )

## 1. 实现方式

+ 实现的是**大根堆**

+ 使用数组实现
  + $a[0]$ 是树根
  + $a[2i+1]$ 是 $a[i]$ 的**左儿子**
  + $a[2i+2]$ 是 $a[i]$ 的**右儿子**

## 2. 函数

### 2.1 汇总

```C
void make_heap_sift_down(int N);
void make_heap_sift_up(int N);
int top_heap();
void pop_heap();
void sift_down(int x = 0);
void heap_sort(int N);
void sift_up(int x);
bool del_heap(int x = 0);
bool insert_heap(int value);
```

### 2.2 函数

---

```C
void sift_down(int x = 0);
```

+ 在结点 $a[x]$ 为树根的子树中除了 $a[i]$ 之外都满足堆的性质时, 调整 $a[i]$ 为树根的子树成为堆
+ 时间复杂度 : $O(log(n))$

---

```C
void make_heap_sift_down(int N);
```

+ 通过逐步对每个非叶子结点进行`sift_down`调整, 实现建堆
  + 深度大的优先
    + 满足`sift_down`的条件
  + 同层结点任意顺序
    + 实现的时候从右到左
+ 时间复杂度 : $O(n)$

---

```C
void pop_heap();
```

+ 将堆顶(树根)元素删除
  + 实现
    + 将堆顶元素与最后一个元素互换
    + 将堆元素个数减一
    + 对堆顶调用`sift_down`
+ 时间复杂度 : $O(logn)$

---

```C
int top_heap();
```

+ 返回堆顶元素
+ 时间复杂度 : $O(1)$

---

```C
void heap_sort(int N);
```

+ 调用`pop_heap`进行堆排序
+ 时间复杂度 : $O(nlogn)$

---

```C
void sift_up(int x);
```

+ 在 $a[i]$ 的祖先结点(除了父结点)都满足堆性质时,向上调整使得所有祖先结点都满足堆性质
+ 时间复杂度 : $O(logn)$

---

```C
void make_heap_sift_up(int N);
```

+ 通过依次对所有结点调用`sift_up`建堆
  + 深度小的优先
    + 满足`sift_up`的条件
  + 同层结点任意顺序
    + 实现的时候从左到右
+ 时间复杂度 : $O(nlogn)$

---

```C
bool del_heap(int x);
```

+ 删除结点 $a[x]$

+ 实现
  + 将 $a[x]$ 与最后一个元素交换
  + 对 $a[x]$ 依次调用 `sift_up`, `sift_down`
+ 时间复杂度 : $O(logn)$

---

```C
bool insert_heap(int value);
```

+ 实现
  + 最后增加一个元素 $value$, 对其调用`sift_up`

时间复杂度 : $O(logn)$