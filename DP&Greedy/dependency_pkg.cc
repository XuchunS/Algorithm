#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;
const int N = 110;
unordered_map<int, unordered_set<int>> g;
int n, m, root;
int v[N], w[N];
int dp[N][N];

void dfs(int u) {
    for (int i = v[u]; i <= m; ++i) dp[u][i] = w[u];
    for (auto iter = g[u].begin(); iter != g[u].end(); ++iter) {
        int son = *iter;
        dfs(son);
        
        for (int i = m; i >= v[u]; --i) { //这里不能从小到达枚举， 因为递归是从下边上来的，
                                          // 即大的容量需要利用小的容量（上一层（递归））来geng xin n
            for (int j = 0; j <= i - v[u]; ++j) {
                dp[u][i] = max(dp[u][i], dp[u][i - j] + dp[son][j]);
            }
        }
    }
}
// 有依赖的背包问题，即选择 物品 i 时， 必须要选择其以来的物品
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        int p;
        cin >> v[i] >> w[i] >> p; // p 是物品 i 以来的物品
        if (p == -1) root = i;
        else g[p].insert(i);
    }
    
    dfs(root);
    cout << dp[root][m] << endl;
    
    return 0;
}