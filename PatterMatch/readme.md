## 模式匹配

### AC自动机
多模匹配
- fail指针，每个节点的fail指针指向其最长后缀
```c++
struct Node {
    vector<int> exists;
    Node* fail;
    Node* child[26];
}
```