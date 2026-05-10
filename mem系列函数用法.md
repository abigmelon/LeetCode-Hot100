# mem 系列函数用法

`<string.h>` 头文件中的内存操作函数，直接操作原始内存（字节），不关心字符串的 `\0` 终止符。

---

## 一、memcpy — 内存拷贝

```c
void* memcpy(void* dest, const void* src, size_t n);
```

从 `src` 拷贝 `n` 个字节到 `dest`。**源和目标不能重叠。**

```c
int a[5] = {1, 2, 3, 4, 5};
int b[5];

// 正确：第三个参数是字节数！
memcpy(b, a, 5 * sizeof(int));   // 拷贝 20 字节（5 × 4）
//       ↑       ↑
//      目标    源     字节数 = 元素个数 × sizeof(类型)
```

### ⚠️ 常见错误

```c
int a[5] = {1, 2, 3, 4, 5};
int b[5];

memcpy(b, a, 5);   // ❌ 只拷贝了 5 个字节（1.25 个 int），不是 5 个 int！
memcpy(b, a, sizeof(a));  // ✅ 或者用 sizeof 算总字节数
```

### 手写实现

```c
void* my_memcpy(void* dest, const void* src, size_t n) {
    char* d = (char*)dest;
    const char* s = (const char*)src;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}
```

---

## 二、memmove — 安全内存拷贝

```c
void* memmove(void* dest, const void* src, size_t n);
```

与 `memcpy` 功能相同，但**允许源和目标区域重叠**。内部会用临时缓冲区或反向拷贝来保证正确性。

```c
char str[] = "abcdef";

// 想把 "abc" 往后移两位 → "abc" → "ababc"
// 源 [0,2] 和 目标 [2,4] 重叠了，必须用 memmove
memmove(str + 2, str, 3);   // str 变成 "ababc"

// 如果用 memcpy，结果不可预测（编译器优化可能导致错误）
```

| | memcpy | memmove |
|---|---|---|
| 重叠区域 | ❌ 未定义行为 | ✅ 安全 |
| 性能 | 更快 | 略慢（需处理重叠） |

---

## 三、memset — 内存填充

```c
void* memset(void* str, int c, size_t n);
```

把 `str` 的前 `n` 个字节都设为值 `c`（`c` 会被转为 `unsigned char`）。

```c
int arr[10];

memset(arr, 0, 10 * sizeof(int));   // 全部设为 0 ✅
memset(arr, -1, 10 * sizeof(int));  // 全部设为 -1 ✅
memset(arr, 1, 10 * sizeof(int));   // ❌ 不是把每个 int 设为 1！
```

### ⚠️ memset 只能逐字节设置

```c
int x;
memset(&x, 1, sizeof(int));  // x = 0x01010101 = 16843009，不是 1！
```

因为 `memset` 把每个 **字节** 都设为 `0x01`：

```
int 是 4 字节： 01 01 01 01
合起来就是 0x01010101 = 16843009
```

**只有设 0 和 -1 才是安全的：**

```c
memset(arr, 0, n * sizeof(int));   // 每个 int = 0  ✅
memset(arr, -1, n * sizeof(int));  // 每个 int = -1 ✅（0xFF FF FF FF = -1）
```

---

## 四、memcmp — 内存比较

```c
int memcmp(const void* ptr1, const void* ptr2, size_t n);
```

逐字节比较 `ptr1` 和 `ptr2` 的前 `n` 个字节。

| 返回值 | 含义 |
|--------|------|
| 0 | 前 n 个字节完全相同 |
| < 0 | ptr1 第一个不同的字节 < ptr2 |
| > 0 | ptr1 第一个不同的字节 > ptr2 |

```c
int a[] = {1, 2, 3};
int b[] = {1, 2, 3};
int c[] = {1, 2, 4};

memcmp(a, b, 3 * sizeof(int));   // 0（相等）
memcmp(a, c, 3 * sizeof(int));   // < 0（a < c，因为第三个 int 3 < 4）
```

---

## 五、memchr — 内存中查找字符

```c
void* memchr(const void* str, int c, size_t n);
```

在前 `n` 个字节中查找第一个值为 `c` 的字节（转为 `unsigned char`）。返回指向该位置的指针，没找到返回 `NULL`。

```c
char str[] = "hello world";
char* p = memchr(str, 'w', strlen(str));
if (p) printf("找到 'w'，位置：%ld\n", p - str);  // 输出：6
```

---

## 六、速查表

| 函数 | 作用 | 第三个参数是 |
|------|------|-------------|
| `memcpy(dst, src, n)` | 拷贝（不重叠） | **字节数** |
| `memmove(dst, src, n)` | 拷贝（可重叠） | **字节数** |
| `memset(ptr, val, n)` | 填充 | **字节数** |
| `memcmp(a, b, n)` | 比较 | **字节数** |
| `memchr(ptr, val, n)` | 查找字节 | **字节数** |

### 🔑 黄金法则

> **第三个参数永远是字节数，不是元素个数。**
>
> 字节数 = 元素个数 × `sizeof(类型)`

```c
int arr[100];
memset(arr, 0, 100 * sizeof(int));   // ✅
memset(arr, 0, sizeof(arr));         // ✅（sizeof(arr) = 100 × 4）
memset(arr, 0, 100);                 // ❌ 只操作了 100 字节，不是 100 个 int
```
