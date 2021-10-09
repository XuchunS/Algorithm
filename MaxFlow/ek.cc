#include <iostream>
#include <unordered_map>
#include <queue>
#include <cstring>
using namespace std;

const int N = 1010;
int n, m, S, T;
unordered_map<int, unordered_map<int, int>> g;
int pre[N];
bool marked[N];
bool bfs() {
    // 维护 每个点的前驱节点
    memset(pre, -1, sizeof pre);
    memset(marked, false, sizeof marked); // 标记是否访问过
    queue<int> q;
    q.push(S), pre[S] = S, marked[S] = true;
    
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        
        for (auto iter = g[cur].begin(); iter != g[cur].end(); ++iter) {
            int i = (*iter).first;
            if (g[cur][i] > 0 && !marked[i]) {
                pre[i] = cur;
                if (i == T) return true;
                q.push(i);
                marked[i] = true;
            }
        }
    }
    return false;  // 
}

int EK() {
    int flow = 0;
    // 找增广路
    while (bfs()) {  // 当到不了终点时 会返回false
        int d = 0x3f3f3f3f;
        // 维护残留网络
        // 找到 此条路  的 最小值
        for (int i = T; i != S; i = pre[i]) {
            if (g[pre[i]][i] < d) d = g[pre[i]][i];
        }
        // 这条 路径上 的每条边 都要 减去相应流量
        for (int i = T; i != S; i = pre[i]) {
            g[pre[i]][i] -= d;   // 正向边 减去 流量值
            g[i][pre[i]] += d;   // 反向边 加上 流量值
        }
        
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
    
    printf("%d", EK());
}