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
    //ָ��仯��ɣ�����height
    p->height = max(height(p->left), height(p->right)) + 1;
    node->height = max(height(node->left), height(node->right)) + 1;
    node = p;
}

void RR(AVLNode * node) {
    AVLNode * p = node->right;
    node->right = p->left;
    p->left = node;
    //ָ��仯��ɣ�����height
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
    if (root == nullptr)  //û�ҵ�Ԫ��
        return nullptr;
    else if(root->val > val)
        return search(root->left, val); //���������������
    else if(root->val < val)
        return search(root->right, val); //���������������
    else //���
        return root;
}


void leftBalance(AVLNode * node) {
    AVLNode * p = node->left;
    if (height(p->left) - height(p->right) == -1) // ���ӵ�����������
        LR(node);
    else
        LL(node);
}

void rightBalance(AVLNode * node) {
    AVLNode * p = node->right;
    if (height(p->right) - height(p->left) == -1) // �Һ��ӵ�����������
        RL(node);
    else
        RR(node);
}

void insert(AVLNode * root, int val) {
    if (root == nullptr)
        root = new AVLNode(val);
    // ���Һ��ʵ�λ��
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
    // �������ĸ߶�
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
    } else { // �ҵ���Ҫɾ�Ľڵ�
        if (root->left == nullptr) { // ������Ϊ�գ����Һ��Ӵ���֮
            AVLNode * p = root;
            root = root->right;
            delete p;
        } else if (root->right == nullptr) { // ������Ϊ�գ������Ӵ���֮
            AVLNode * p = root;
            root = root->left;
            delete p;
        }
        else { // ���Һ��Ӷ����գ���������ҵĽڵ����֮
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