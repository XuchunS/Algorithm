// 最长公共上升子序列
// f[i][j] 代表 a 中前 i 个元素中，b中以第 j 个元素为结尾的 最长的公共上升子序列
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 3010;
int a[N], b[N];
int n;
int dp[N][N];

/**
for (int i = 1; i <= n; i ++ )
{
    for (int j = 1; j <= n; j ++ )
    {
        f[i][j] = f[i - 1][j];
        if (a[i] == b[j]) // 如果相等，则 查找 最长上升子序列
        {
            int maxv = 1;
            for (int k = 1; k < j; k ++ )
                if (a[i] > b[k])
                    maxv = max(maxv, f[i - 1][k] + 1);
            f[i][j] = max(f[i][j], maxv);
        }
    }
}
**/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    
    for (int i = 1; i <= n; ++i) {
        int maxv = 1;
        for (int j = 1; j <= n; ++j) {
            dp[i][j] = dp[i - 1][j];
            if (a[i] == b[j]) {
                dp[i][j] = max(dp[i][j], maxv);
            }
            if (a[i] > b[j]) maxv = max(maxv, dp[i - 1][j] + 1);
        }
    }
    
    int ans = 0;
    for (int i = 1; i <= n; ++i) ans = max(dp[n][i], ans);
    cout << ans << endl;
    return 0;
}