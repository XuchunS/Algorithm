#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;
using PII = pair<int, int>;
const int M = 2e4 + 10, N = 1e4 + 10;
int n, m;
unordered_map<int, unordered_map<int, int>> g;
unordered_map<int, vector<PII>> query;
int ans[M];
int dist[N];
int st[N];
int id[N];
int find(int p) {
    if (p == id[p]) return p;
    return id[p] = find(id[p]);
}
void dfs(int u, int fa) {
    for (auto node : g[u]) {
        int next = node.first;
        int w = node.second;
        if (next == fa) continue;
        dist[next] = dist[u] + w;
        dfs(next, u);
    }
}

void tarjan(int u) {
    st[u] = 1;   // 表明该点正在被访问
    
    for (auto node : g[u]) {
        if (st[node.first] == 0) {
            tarjan(node.first);
            id[node.first] = u;
        }
    }
    
    for (auto item : query[u]) {
        int another = item.first;
        if (st[another] == 2) {
            int anc = find(another);
            ans[item.second] = dist[u] + dist[another] - 2 * dist[anc];
        }
    }
    
    st[u] = 2;   // 该点已经回溯访问结束
}
// 询问 两点之间的距离
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n >> m;
    for (int i = 1; i <= n - 1; ++i) {
        int x, y, k; cin >> x >> y >> k;
        g[x][y] = g[y][x] = k;
    }
    
    for (int i = 1; i <= m; ++i) {
        int x, y; cin >> x >> y;
        query[x].push_back({y, i});
        query[y].push_back({x, i});
    }
    for (int i = 1; i <= N; ++i) id[i] = i;
    dfs(1, -1);
    tarjan(1);
    
    for (int i = 1; i <= m; ++i) cout << ans[i] << endl;
    
    return 0;
}

