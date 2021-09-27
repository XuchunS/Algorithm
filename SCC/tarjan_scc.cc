#include <iostream>
#include <algorithm>
#include <stack>
#include <unordered_map>
#include <vector>
#include <cstring>
using namespace std;
const int N = 1e4 + 10;
unordered_map<int, unordered_map<int, int>> g;
int n, m;
int dfn[N], low[N];
stack<int> stac;
int time_stamp = 1;
bool st[N];
vector<int> res;
int id[N], siz[N], ssc_id;
int d_out[N];
void dfs(int cur) {
    stac.push(cur); st[cur] = true;   // 入栈
    dfn[cur] = low[cur] = time_stamp ++;  // 第一次访问到的时间戳
    for (auto pa : g[cur]) {
        int next = pa.first;
        if (dfn[next] == 0) {
            dfs(next);
            low[cur] = min(low[cur], low[next]);  // 更新可以回溯到的最早的时间点。
        } else if (st[next]) {
            low[cur] = min(low[cur], low[next]);
        }
    }
    
    if (dfn[cur] == low[cur]) {  // 如果该点首次被访问到的时间点 等于 可以最早回溯到的时间点，则表明找到了一个强连通分量
        ssc_id ++;
        while (stac.top() != cur)
        {
            int tmp = stac.top(); stac.pop();
            st[tmp] = false;
            id[tmp] = ssc_id; siz[ssc_id] ++;
        } 
        int tmp = stac.top(); stac.pop();
        st[tmp] = false;
        id[tmp] = ssc_id; siz[ssc_id] ++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n >> m;
    //memset(st, false, sizeof st);
    for (int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        g[a][b] = 1;
    }
    
    for (int i = 1; i <= n; ++i) {
        if (dfn[i] == 0) dfs(i);
    }
    
    for (int i = 1; i <= n; ++i) {
        for (auto pa : g[i]) {
            int next = pa.first;
            if (id[i] != id[next]) d_out[id[i]] ++;
        }
    }
    
    int zeros = 0, ans = 0;
    for (int i = 1; i <= ssc_id; ++i) {
        if (d_out[i] == 0) {
            zeros ++;
            ans = siz[i];
            if (zeros > 1) {
                ans = 0;
                break;
            }
        }
    }
    cout << ans << endl;
    
    return 0;
}
