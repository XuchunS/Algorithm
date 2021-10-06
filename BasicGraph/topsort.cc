//N  个点 M 条边的有向无环图，分别统计从每个点出发能够到达的点的数量
// 每个点可以到达的点等于 其所有可达点的并集
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <queue>
#include <bitset>
using namespace std;

unordered_map<int, unordered_multiset<int>> g;
int n, m;
vector<int> d;
vector<int> res;
bitset<30010> f[30010];
void topsort() {
    queue<int> que;
    for (int i = 1; i <= n; ++i) if (d[i] == 0) {
        que.push(i);
    }
    int cnt = 0;
    while (!que.empty()) {
        int cur = que.front(); que.pop();
        res[++ cnt] = cur;
        for (auto ne : g[cur]) {
            if (-- d[ne] == 0) que.push(ne);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n >> m;
    d.resize(n + 1);
    res.resize(n + 1);
    for (int i = 0; i < m; ++i) {
        int x, y; cin >> x >> y;
        g[x].insert(y); d[y]++;
    }
    
    topsort();

    for (int i = n; i > 0; --i) {
        int cur = res[i];
        f[cur][cur] = 1;
        for (auto ne : g[cur]) f[cur] |= f[ne];
    }
    
    for (int i = 1; i <= n; ++i) cout << f[i].count() << endl;
    
    return 0;
}