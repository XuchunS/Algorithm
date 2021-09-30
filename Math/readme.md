## 数学相关

### 分解质因数
```c++
for (int i = 2; i * i <= num; ++i) {
    if (num % i == 0) {
        int s = 0;
        while (num % i == 0) {
            num /= i;
            s ++;
        }
        cout << i << " " << s << endl;
    }
}
if (num > 1) cout << num << " " << "1" << endl;
```

### 线性筛质数
```c++
// 线性时间筛出小于 n 的所有质数
void get_primes(int n)
{
    for (int i = 2; i <= n; i ++ )
    {
        if (!st[i]) primes[cnt ++ ] = i;
        for (int j = 0; primes[j] <= n / i; j ++ )
        {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}
```