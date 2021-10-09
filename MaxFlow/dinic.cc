#include <iostream>
#include <unordered_map>
#include <queue>
#include <cstring>
using namespace std;

const int N = 10010;
int n, m, S, T;
unordered_map<int, unordered_map<int, int>> g;
int pre[N];
bool marked[N];
int depth[N];
bool bfs() {
    // 维护 每个点的前驱节点
    memset(depth, -1, sizeof depth);
    queue<int> q;
    q.push(S), depth[S] = 0;

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        for (auto iter = g[cur].begin(); iter != g[cur].end(); ++iter) {
            int i = (*iter).first;
            if (g[cur][i] > 0 && depth[i] == -1) {
                depth[i] = depth[cur] + 1;
                if (i == T) return true;
                q.push(i);
            }
        }
    }
    if (depth[T] == -1) return false;
    return true;
}

int dfs(int cur, int dist) {
    if (cur == T) return dist;
    int flow = 0;
    for (auto iter = g[cur].begin(); iter != g[cur].end() && flow < dist; ++iter) {
        int i = iter->first;
        if (depth[i] == depth[cur] + 1 && g[cur][i] > 0) {
            int di = dfs(i, min(g[cur][i], dist - flow));
            if (!di) depth[i] = -1; // 如果该点不可达终点，则将其移出
            g[cur][i] -= di;
            g[i][cur] += di;

            flow += di;
        }
    }
    
    return flow;
}

int Dinic() {
    int flow = 0;
    // 找增广路
    // bfs主要是标记所有增广路中的点的层数，避免环路 
    while (bfs()) {
        while (int d = dfs(S, 0x3f3f3f3f))
            flow += d;
    }

    return flow;
}

int main() {
    cin >> n >> m >> S >> T ;
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        g[u][v] += c;
    }

    printf("%d", Dinic());
    return 0;
}