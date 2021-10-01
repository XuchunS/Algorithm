## 平衡树

### Treap
结合了搜索树和堆，保证树平衡

### Splay

### RBTree


### 删除一个节点
一般是将需要删除的节点往下旋转到叶子节点删除
```c++
// TreeNode*& 
// 这里 不加 引用的话，导致值拷贝，使得 旋转操作后 该节点的父节点 没有得到修正
// 不加 引用，可以多传 一个 父节点以及左或右儿子 两个参数 来修正 父节点的指向
void remove(TreeNode*& root, int key) {
        if (root == nullptr) return;
        if (root->val == key) {
            if (root->left || root->right) {
                if (!root->right) {
                    zag(root);
                    remove(root->right, key);
                } else {
                    zig(root);
                    remove(root->left, key);
                }
            } else {
                root = nullptr;
            }
        } else if (root->val > key) remove(root->left, key);
        else remove(root->right, key);
    }
```