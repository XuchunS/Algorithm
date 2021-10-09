#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
using namespace std;
unordered_map<int, unordered_map<int, int>> g;
int n, m;
vector<int> depth;
vector<bool> s_vis;
vector<bool> vis_t;
bool bfs() {
    vector<int> tmp(n + 1, -1);
    std::swap(depth, tmp);
    queue<int> que; que.push(0); depth[0] = 0;
    
    while (!que.empty()) {
        int node = que.front(); que.pop();
        
        for (auto ne : g[node]) {
            int nenod = ne.first;
            if (ne.second > 0 && depth[nenod] == -1) {
                depth[nenod] = depth[node] + 1;
                if (nenod == n - 1) return true;
                que.push(nenod);
            }
        }
    }
    return false;
}

int dfs(int cur, int dist) {
    if (cur == n - 1) return dist;
    int flow = 0;
    for (auto iter = g[cur].begin(); iter != g[cur].end() && flow < dist; ++iter) {
        int ne = (*iter).first;
        if (g[cur][ne] > 0 && depth[ne] == depth[cur] + 1) {
            int di = dfs(ne, min((*iter).second, dist - flow));
            if (di == 0) {
                depth[ne] = -1;
                continue;
            }
            
            g[cur][ne] -= di;
            g[ne][cur] += di;
            
            flow += di;
        }
    }
    return flow;
}

int dinic() {
    int d, flow = 0;
    while (bfs()) while (d = dfs(0, 0x3f3f3f3f)) flow += d;
    return flow;
}

void check_front(int cur, vector<bool>& v) {
    v[cur] = true;
    for (auto ne : g[cur]) {
        int nenod = ne.first;
        if (ne.second > 0 && !v[nenod]) check_front(nenod, v);
    }
}

void check_back(int cur, vector<bool>& v) {
    v[cur] = true;
    for (auto ne : g[cur]) {
        int nenod = ne.first;
        if (g[nenod][cur] > 0 && !v[nenod]) check_back(nenod, v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    vector<pair<int, int>> edges;  // 记录正向边
    cin >> n >> m;
    depth.resize(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b, c; cin >> a >> b >> c;
        g[a][b] += c;
        g[b][a] += 0;
        edges.push_back({a, b});
    }
    
    dinic();  // 找到最大流
    s_vis.resize(n + 1);  
    vis_t.resize(n + 1);  
    check_front(0, s_vis);  // 标记从源点可以到达的点
    check_back(n - 1, vis_t);  // 标记哪些点可以到达终点
    int ans = 0;
    for (auto edge : edges) {  // 遍历正向边，
        int a = edge.first, b = edge.second;
        if (g[a][b] == 0 && s_vis[a] && vis_t[b]) ans ++;
    }
    
    cout << ans << endl;
    return 0;
}
