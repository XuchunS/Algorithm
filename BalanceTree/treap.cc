#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10;
const int INF = 1e8;
struct Node {
    int l, r; //左右儿子
    int key, val;
    int size, cnt;
} treap[N];
int root, idx;

int get_node(int key) {
    ++idx;
    treap[idx].key = key;
    treap[idx].val = rand();
    treap[idx].size = treap[idx].cnt = 1;
    
    return idx;
}

void pushup(int p) {
    treap[p].size = treap[treap[p].l].size + treap[p].cnt + treap[treap[p].r].size;
}

void left_rotate(int& p) {
    int x = treap[p].r;
    treap[p].r = treap[x].l;
    treap[x].l = p;
    p = x;  // 这里由于加了引用，所以 直接就替换了原来的根节点, 不必再 返回新的根节点 由外部将树修复
    pushup(treap[p].l);
    pushup(p);
}

void right_rotate(int& p) {
    int x = treap[p].l;
    treap[p].l = treap[x].r;
    treap[x].r = p;
    p = x;
    pushup(treap[p].r);
    pushup(p);
}

void build() {
    get_node(-INF);
    get_node(INF);
    root = 1; 
    treap[root].r = 2;
    pushup(root);
    
    if (treap[treap[root].r].val > treap[root].val) left_rotate(root);
}

void insert(int& p, int x) {
    if (!p) p = get_node(x);
    else if (treap[p].key == x) treap[p].cnt++;
    else if (treap[p].key < x) {
        insert(treap[p].r, x);
        if (treap[p].val < treap[treap[p].r].val) left_rotate(p);
    } else if (treap[p].key > x) {
        insert(treap[p].l, x);
        if (treap[p].val < treap[treap[p].l].val) right_rotate(p);
    }
    
    pushup(p);
}

void remove(int& p, int x) {
    if (!p) return;
    if (treap[p].key == x) {
        if (treap[p].cnt > 1) treap[p].cnt--;
        else if (treap[p].l || treap[p].r) {
            if (!treap[p].r || treap[treap[p].r].val < treap[treap[p].l].val) {
                right_rotate(p);
                remove(treap[p].r, x);
            } else {
                left_rotate(p);
                remove(treap[p].l, x);
            }
        } else {
            p = 0;
        }
    } else if (treap[p].key > x) remove(treap[p].l, x);
    else remove(treap[p].r, x);
    
    pushup(p);
}

int get_rank_by_key(int p, int key) {
    if (!p) return 0;
    if (treap[p].key == key) return treap[treap[p].l].size;
    else if (treap[p].key > key) return get_rank_by_key(treap[p].l, key);
    else return treap[treap[p].l].size + treap[p].cnt + get_rank_by_key(treap[p].r, key);
}

int get_key_by_rank(int p, int rank) {
    if (!p) return INF;
    if (treap[treap[p].l].size >= rank) return get_key_by_rank(treap[p].l, rank);
    else if (treap[treap[p].l].size + treap[p].cnt >= rank) return treap[p].key;
    return get_key_by_rank(treap[p].r, rank - treap[treap[p].l].size - treap[p].cnt);
}

int get_prev(int p, int key) {
    if (!p) return -INF;
    if (treap[p].key >= key) return get_prev(treap[p].l, key);
    return max(treap[p].key, get_prev(treap[p].r, key));
}

int get_next(int p, int key) {
    if (!p) return INF;
    if (treap[p].key <= key) return get_next(treap[p].r, key);
    return min(treap[p].key, get_next(treap[p].l, key));
}

int main() {
    int n;
    cin >> n;
    build();
    for (int i = 0; i < n; ++i) {
        int opt, x;
        scanf("%d%d", &opt, &x);
        
        if (opt == 1) insert(root, x);
        else if (opt == 2) remove(root, x);
        else if (opt == 3) printf("%d\n", get_rank_by_key(root, x));
        else if (opt == 4) printf("%d\n", get_key_by_rank(root, x + 1));
        else if (opt == 5) printf("%d\n", get_prev(root, x));
        else if (opt == 6) printf("%d\n", get_next(root, x));
    }
    
    return 0;
}