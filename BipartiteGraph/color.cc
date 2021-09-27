#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <cstring>
using namespace std;
unordered_map<int, unordered_map<int, int>> g;
const int N = 2e4 + 10;
int n, m;
int color[N];

bool dfs(int node, int col, int limit) {
    color[node] = col;
    for (auto next : g[node]) {
        int ne = next.first, we = next.second;
        if (we <= limit) continue;
        if (color[ne] == col) return false;
        if (color[ne] == 0){
            if (!dfs(ne, 3 - col, limit)) return false;
        }
    }
    return true;
}

bool check(int cur) {
    memset(color, 0, sizeof color);
    for (int i = 1; i <= n; ++i) {
        if (color[i] == 0 && !dfs(i, 1, cur)) return false;  // 染色
    }
    return true;
}

// 关押罪犯
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int a, b, c; cin >> a >> b >> c;
        g[a][b] = g[b][a] = c;
    }
    
    int l = 0, r = 1000000009;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    
    cout << r << endl;
    return 0;
}

