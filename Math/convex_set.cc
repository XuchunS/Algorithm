#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
using PDD = pair<double, double>;
vector<PDD> points;

double cross(double x1, double y1, double x2, double y2) {
    return x1 * y2 - x2 * y1;
}

double area(int p1_idx, int p2_idx, int p3_idx) {
    PDD p1 = points[p1_idx], p2 = points[p2_idx], p3 = points[p3_idx];
    double x1 = p2.first - p1.first, y1 = p2.second - p1.second;
    double x2 = p3.first - p1.first, y2 = p3.second - p1.second;
    return cross(x1, y1, x2, y2);
}

double get_dist(int p1_idx, int p2_idx) {
    PDD p1 = points[p1_idx], p2 = points[p2_idx];
    double x = p1.first - p2.first;
    double y = p1.second - p2.second;
    return sqrt(x * x + y * y);
}

double andrew() {
    vector<int> stk;
    vector<bool> used(points.size(), false);
    sort(points.begin(), points.end());
    // 从左往右扫描， 确定 上边的边
    for (int i = 0; i < points.size(); ++i) {
        while (stk.size() >= 2 && area(stk[stk.size() - 2], stk[stk.size() - 1], i) > 0) {
            used[stk.back()] = false;
            stk.pop_back();
        }
        stk.push_back(i);
        used[i] = true;
    }
    
    // 从右往左扫描， 确定下边的边
    used[0] = false;
    for (int i = points.size() - 1; i >= 0; --i) {
        if (used[i]) continue;
        while (stk.size() > 2 && area(stk[stk.size() - 2], stk.back(), i) > 0) {
            used[stk.back()] = false;
            stk.pop_back();
        }
        stk.push_back(i);
        used[i] = true;
    }
    
    double ans = 0;
    for (int i = 1; i < stk.size(); ++i) {
        ans += get_dist(stk[i], stk[i - 1]);
    }
    
    return ans;
}
// 求 把 n 个点围起来的最小周长
// 求 n 个点的 凸包
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n; cin >> n;

    for (int i = 0; i < n; ++i) {
        double x, y; cin >> x >> y;
        points.push_back({x, y});
    }
    
    double res = andrew();
    
    printf("%.2f", res);
    return 0;
}
