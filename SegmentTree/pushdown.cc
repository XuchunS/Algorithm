#include <iostream>
#include <algorithm>

using namespace std;
using LL = long long;
const int N = 1e5 + 10;
struct Node {
    int l, r;
    LL sum;
    int add;
} tr[N * 4];
int arr[N];
int n, m;

void pushup(int u) {
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void build(int u, int l, int r) {
    if (l == r) tr[u] = {l, r, arr[l], 0};
    else {
        tr[u] = {l, r};
        int mid = l + (r - l) / 2;
        build(u << 1, l, mid); build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

void pushdown(Node& root, Node& left, Node& right) {
    left.add += root.add; left.sum += (left.r - left.l + 1) * root.add;  // 这里也是一样，要先把新加的值计算进去。
    right.add += root.add; right.sum += (right.r - right.l + 1) * root.add;
    root.add = 0;
}

void pushdown(int u) {
    Node& root = tr[u]; Node& left = tr[u << 1]; Node& right = tr[u << 1 | 1];
    pushdown(root, left, right);
} 

void modify(int u, int l, int r, int d) {
    if (tr[u].l >= l && tr[u].r <= r) {
        tr[u].sum += (tr[u].r - tr[u].l + 1) * d;
        tr[u].add += d; // 这里是重点， 因为根节点 是正确的，所以这里要先 把根节点的值乘 d，而不是
                        // 先把add + d， 再乘add
    } else {
        pushdown(u);
        int mid = tr[u].l + (tr[u].r - tr[u].l) / 2;
        if (l <= mid) modify(u << 1, l, r, d);
        if (r > mid) modify(u << 1 | 1, l, r, d);
        pushup(u);
    }
}

LL query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].sum;
    else {
        pushdown(u);
        int mid = tr[u].l + (tr[u].r - tr[u].l) / 2;
        LL res = 0;
        if (l <= mid) res = query(u << 1, l, r);
        if (r > mid) res += query(u << 1 | 1, l, r);
        return res;
    }
}
// N 个数， 两种操作
// 查询区间 l, r 的总和
// 给区间 l， r的每个数加一个d
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    build(1, 1, n);
    
    for (int i = 1; i <= m; ++i) {
        string op;
        int l, r;
        cin >> op >> l >> r;
        if (op == "C") {
            int add; cin >> add;
            modify(1, l, r, add);
        } else {
            cout << query(1, l, r) << endl;
        }
    }
    
    return 0;
}