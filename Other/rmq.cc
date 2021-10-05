// RMQ 算法
// f[i][j] 表示以 i 为起点，区间长度为 2^j 的区间的最大值

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
const int N = 2e5 + 10;
int a[N];
int n, m;
int dp[N][18];

void init() {
    for (int i = 0; i < n; ++i) dp[i][0] = a[i];
    for (int j = 1; j < 18; ++j) {
        for (int i = 0; i + (1 << j) - 1 < n; ++i) { // 计算时要不重不漏
            dp[i][j] = max(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int check(int a, int b) {
    int len = b - a + 1;
    int k = log(len) / log(2);
    return max(dp[a][k], dp[b - (1 << k) + 1][k]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    init();
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        cout << check(a - 1, b - 1) << endl;
    }
    
    return 0;
}