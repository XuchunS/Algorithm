#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
vector<string> pat;
string target;
struct Node {
    vector<int> exist;
    Node* fail;
    Node* child[26];
};
// 字典树插入
void insert(Node* root, string& ss) {
    Node* node = root;
    for (auto ch : ss) {
        if (node->child[ch - 'a'] == nullptr) node->child[ch - 'a'] = new Node();
        node = node->child[ch - 'a']; 
    }
    node->exist.push_back(ss.size());
}

void build(Node* root) {
    // 构建字典树
    for (auto ss : pat) {
        insert(root, ss);
    }

    // 初始化第一层节点的fail指针
    queue<Node*> que;
    for (int i = 0; i < 26; ++i) {
        if (root->child[i] != nullptr) {
            que.push(root->child[i]);
            root->child[i]->fail = root;
        }
    }

    while (!que.empty()) {
        Node* cur = que.front(); que.pop();
        
        for (int i = 0; i < 26; ++i) {
            if (cur->child[i] == nullptr) continue;
            Node* child = cur->child[i];
            Node* fafail = cur->fail;
            while (fafail && nullptr == fafail->child[i]) fafail = fafail->fail;
            if (fafail == nullptr) child->fail = root;
            else {
                child->fail = fafail->child[i];
            }

            if (child->fail->exist.size()) {
                vector<int>& tmp = child->fail->exist;
                for (auto num : tmp) {
                    child->exist.push_back(num);
                }
            }

            que.push(child);
        }
    }
}

void query(Node* root) {
    Node* node = root;
    for (int i = 0; i < target.size(); ++i) {
        int index = target[i] - 'a';
        while (nullptr == node->child[i] && node->fail != nullptr) node = node->fail;
        if (node->child[i]) {
            node = node->child[i];
        } else continue;

        if (node->exist.size() > 0) {
            vector<int>& tmp = node->exist;
            for (auto len : tmp) {
                cout << target.substr(i - len + 1, len);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        string tmp; cin >> tmp;
        pat.push_back(tmp);
    }
    cin >> target;
    Node* root = new Node();
    build(root);
    query(root);
}