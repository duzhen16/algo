#include <iostream>
#include <algorithm>
using namespace std;

struct AVLNode {
    int val;
    AVLNode * left;
    AVLNode * right;
    int height;
    AVLNode(int v) : val(v), left(nullptr), right(nullptr), height(0) {}
};

int height(AVLNode * node) {
    return (node == nullptr) ? -1 : node->height;
}

void LL(AVLNode * node) {
    AVLNode * p = node->left;
    node->left = p->right;
    p->right = node;
    //指针变化完成，更新height
    p->height = max(height(p->left), height(p->right)) + 1;
    node->height = max(height(node->left), height(node->right)) + 1;
    node = p;
}

void RR(AVLNode * node) {
    AVLNode * p = node->right;
    node->right = p->left;
    p->left = node;
    //指针变化完成，更新height
    p->height = max(height(p->left), height(p->right)) + 1;
    node->height = max(height(node->left), height(node->right)) + 1;
    node = p;
}

void LR(AVLNode * node) {
    RR(node->left);
    LL(node);
}

void RL(AVLNode * node) {
    LL(node->right);
    RR(node);
}

AVLNode * search(AVLNode * root, int val) {
    if (root == nullptr)  //没找到元素
        return nullptr;
    else if(root->val > val)
        return search(root->left, val); //在左子树里面查找
    else if(root->val < val)
        return search(root->right, val); //在右子树里面查找
    else //相等
        return root;
}


void leftBalance(AVLNode * node) {
    AVLNode * p = node->left;
    if (height(p->left) - height(p->right) == -1) // 左孩子的右子树过高
        LR(node);
    else
        LL(node);
}

void rightBalance(AVLNode * node) {
    AVLNode * p = node->right;
    if (height(p->right) - height(p->left) == -1) // 右孩子的左子树过高
        RL(node);
    else
        RR(node);
}

void insert(AVLNode * root, int val) {
    if (root == nullptr)
        root = new AVLNode(val);
    // 查找合适的位置
    else if (root->val > val) {
        insert(root->left, val);
        if (height(root->left) - height(root->right) == 2)
            leftBalance(root);
    }
    else if (root->val < val) {
        insert(root->right, val);
        if (height(root->right) - height(root->left) == 2)
            rightBalance(root);
    }
    // 更新树的高度
    root->height = max(height(root->left), height(root->right)) + 1;
}

void remove(AVLNode * root, int val) {
    if (root == nullptr)
        return ;
    else if (root->val > val) {
        remove(root->left, val);
        if (height(root->right) - height(root->left) == 2)
            rightBalance(root);
    } else if (root->val < val) {
        remove(root->right, val);
        if (height(root->left) - height(root->right) == 2)
            leftBalance(root);
    } else { // 找到了要删的节点
        if (root->left == nullptr) { // 左子树为空，用右孩子代替之
            AVLNode * p = root;
            root = root->right;
            delete p;
        } else if (root->right == nullptr) { // 右子树为空，用左孩子代替之
            AVLNode * p = root;
            root = root->left;
            delete p;
        }
        else { // 左右孩子都不空，找左边最右的节点代替之
            AVLNode * p = root->left;
            while (p->right) p = p->right;
            root->val = p->val;
            remove(root->left, p->val);
            if (height(root->right) - height(root->left) == 2)
                rightBalance(root);
        }
    }
    if (root)
        root->height = max(height(root->left), height(root->right)) + 1;
}

