## 动态规划

### 背包问题

#### 0-1背包

#### 完全背包

#### 多重背包
- 二进制优化 转化 为0-1背包问题
- 单调队列优化

#### 分组背包
- 每组物品只能拿一个

#### 找到到最优解的路径
```c++
#include <iostream>
#include <algorithm>

using namespace std;
int val[20][20];
int dp[15][20];
int path[20];
int n, m;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) cin >> val[i][j];
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int k = 0; k <= m; ++k) {
                if (k <= j) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - k] + val[i][k]);
                }
            }
        }
    }
    cout << dp[n][m] << endl;
    // 找到到 最优解的路径
    int j = m;
    for (int i = n; i; --i) {
        for (int k = 0; k <= j; ++k) {
            if (dp[i][j] == dp[i - 1][j - k] + val[i][k]) {
                path[i] = k;
                j -= k;
                break;
            }
        }
    }
    
    for (int i = 1; i <= n; ++i) cout << i << " " << path[i] << endl;
    return 0;
}
```

#### 有依赖的背包问题
树状DP


#### 背包问题求具体方案