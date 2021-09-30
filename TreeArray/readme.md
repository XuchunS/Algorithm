## 树状数组
### 特点
- 快速求前缀和 (logN)
- 修改某一个数 (logN)

### 操作
- 修改操作
```C++
for (int i = x; i <= n; i += lowbit(x)) tr[i] += c;
```

- 求前缀和
```C++
for (int i = x; i > 0; i -= lowbit(x)) res += tr[i];
```