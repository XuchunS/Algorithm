#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

struct Node {
    vector<int> exists;
    Node* fail;
    Node* child[26];
};

void insert(Node* root, string& ss) {
    Node* tmp = root;
    for (auto ch : ss) {
        if (tmp->child[ch - 'a'] == nullptr) tmp->child[ch - 'a'] = new Node();
        tmp = tmp->child[ch - 'a'];
    }
    tmp->exists.push_back(ss.size());
}

void build(Node* root, vector<string>& pat) {
    for (auto ss : pat) insert(root, ss);
    
    queue<Node*> que;
    for (int i = 0; i < 26; ++i) {
        if (root->child[i]) {
            root->child[i]->fail = root;
            que.push(root->child[i]);
        }
    }
    
    while (!que.empty()) {
        Node* cur = que.front(); que.pop();
        
        for (int i = 0; i < 26; ++i) {
            if (cur->child[i] == nullptr) continue;
            Node* next = cur->child[i];
            Node* fafail = cur->fail;
            while (fafail && fafail->child[i] == nullptr) fafail = fafail->fail;
            if (fafail == nullptr) next->fail = root;
            else next->fail = fafail->child[i];
            
            que.push(next);
        }
    }
}

int query(Node* root, string& ss) {
    Node* tmp = root;
    int ans = 0;

    for (int i = 0; i < ss.size(); ++i) {
        int index = ss[i] - 'a';
        while (nullptr == tmp->child[index] && tmp->fail) tmp = tmp->fail;
        if (tmp->child[index]) {
            tmp = tmp->child[index];
        } else continue;
        
        // 这里为了统计正确，必须把当前节点的所有fail指针的 全部统计，然后将其清空， 避免重复统计。
        Node* atmp = tmp;
        while (atmp) {
            ans += atmp->exists.size();
            atmp->exists.resize(0);
            atmp = atmp->fail;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int T; cin >> T;
    while (T --) {
        vector<string> pat;
        string ss;
        int n; cin >> n;
        for (int i = 1; i <= n; ++i) {
            string tmp; cin >> tmp;
            pat.push_back(tmp);
        }
        cin >> ss;
        Node* root = new Node();
        build(root, pat);
        cout << query(root, ss) << endl;
    }
    return 0;
}