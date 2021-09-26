#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <cstring>
using namespace std;

const int N = 4e4 + 10;
unordered_map<int, unordered_map<int, int>> g;
int fa[N][16], depth[N];

void bfs(int root) {
    queue<int> q; 
    memset(depth, 0x3f, sizeof depth);
    q.push(root); depth[0] = 0; depth[root] = 1;
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        for (auto next : g[cur]) {
            int node = next.first;
            if (depth[node] > depth[cur] + 1) {
                depth[node] = depth[cur] + 1;
                fa[node][0] = cur;
                for (int i = 1; i <= 15; ++i) {
                    fa[node][i] = fa[fa[node][i - 1]][i - 1];
                }
                q.push(node);
            }
        }
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    for (int i = 15; i >= 0; --i) {
        if (depth[fa[a][i]] >= depth[b]) {  // 先跳到同一高度
            a = fa[a][i];
        }
    }
    if (a == b) return b;
    for (int i = 15; i >= 0; --i) {
        if (fa[a][i] != fa[b][i]) {  // 一起往上跳
            a = fa[a][i];
            b = fa[b][i];
        }
    }
    
    return fa[a][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n; 
    int root = 0;
    for (int i = 1; i <= n; ++i) {
        int a, b; cin >> a >> b;
        if (b == -1) root = a;
        else g[a][b] = g[b][a] = 1;
    }
    
    bfs(root);
    
    int m; cin >> m;
    while (m --) {
        int x, y; cin >> x >> y;
        int p = lca(x, y);
        //cout << "p = " << p << endl; 
        if (p == x) cout << 1 << endl;
        else if (p == y) cout << 2 << endl;
        else cout << 0 << endl;
    }
    
    return 0;
}