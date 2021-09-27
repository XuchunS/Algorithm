#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
using PII = pair<int, int>;
const int N = 110;
bool g[N][N];
int n, t;
PII match[N][N];
bool st[N][N];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

bool find(int x, int y) {
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 1 || nx > n || ny < 1 || ny > n || g[nx][ny] || st[nx][ny]) continue;
        st[nx][ny] = true;
        auto tmp = match[nx][ny];
        if (tmp.first == 0 || find(tmp.first, tmp.second)) {
            match[nx][ny] = {x, y};
            return true;
        }
    }
    return false;
}
// 覆盖棋盘，即用长2宽1的木板盖住棋盘，最多能放多少块木板
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n >> t;
    for (int i = 1; i <= t; ++i) {
        int x, y; cin >> x >> y;
        g[x][y] = true;
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if ((i + j) % 2 && !g[i][j]) {  // 匈牙利算法
                memset(st, false, sizeof st);
                if (find(i, j)) ans ++;
            }
        }
    }
    
    cout << ans << endl;
    return 0;
}