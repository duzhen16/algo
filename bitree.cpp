#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct TreeNode {

	int val;
	struct TreeNode * left;
	struct TreeNode * right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void visit(TreeNode *p) { cout << p->val << " "; }

TreeNode * prev_construct(vector<int> nums, int &idx, int invalid)
{
	if (idx < nums.size() && nums[idx] != invalid) {
		TreeNode *r = new TreeNode(nums[idx]);
		r->left = construct(nums, ++idx, invalid);
		r->right = construct(nums, ++idx, invalid);
		return r;
	}
	else
		return nullptr;
}
/*
@prev : 前序遍历的结果数组
@in   : 中序遍历的结果数组
@p	  : 子树的在前序中的首节点下标
@i	  : 子树的左子树的首节点下标
@len  : 子树的长度
*/
TreeNode * construct_prev_in(vector<int> prev, vector<int> in, int p, int i, int len)
{
	if (len <= 0) return nullptr;
	TreeNode *r = new TreeNode(prev[p]);
	int m = find(in.begin(), in.end(),prev[p]) - in.begin();
	r->left = construct_prev_in(prev, in, p + 1, i, m - i);
	r->right = construct_prev_in(prev, in, p + (m - i) + 1, m + 1, len - (m - i) - 1);
	return r;
}

void R_pre_order(TreeNode * r)
{
	if (!r) return;
	visit(r);
	if (r->left) R_pre_order(r->left);
	if (r->right) R_pre_order(r->right);
}

void R_in_order(TreeNode * r)
{
	if (!r) return;
	if (r->left) R_in_order(r->left);
	visit(r);
	if (r->right) R_in_order(r->right);
}

void R_post_order(TreeNode *r)
{
	if (!r) return;
	if (r->left) R_post_order(r->left);
	if (r->right) R_post_order(r->right);
	visit(r);
}

void pre_order(TreeNode * root)
{
	cout << "pre_order without Recursive...\n";
	TreeNode * r = root;
	stack<TreeNode *> s;
	while (r || !s.empty()) {
		while (r) {
			visit(r);
			s.push(r);
			r = r->left;
		}
		if (!s.empty()) {
			r = s.top();
			s.pop();
			r = r->right;
		}
	}
}

void in_order(TreeNode * root)
{
	cout << "in_order without Recursive...\n";
	TreeNode * r = root;
	stack<TreeNode *> s;
	while (r || !s.empty()) {
		while (r) {
			s.push(r);
			r = r->left;
		}
		if (!s.empty()) {
			r = s.top();
			s.pop();
			visit(r);
			r = r->right;
		}
	}
}

void level_order(TreeNode * root)
{
	cout << "level order ...\n";
	TreeNode * r = root;
	queue<TreeNode *> q;
	if (r) q.push(r);
	while (r || !q.empty()) {
		if (r->left) q.push(r->left);
		if (r->right) q.push(r->right);
		if (!q.empty()) {
			r = q.front();
			visit(r);
			q.pop();
			if (q.empty()) r = nullptr;
			else r = q.front();
		}
	}
}
// 转换一棵BST为有序的双链表
void in_order_visit(TreeNode* root, TreeNode* &last) {
        if (!root) return ;
        in_order_visit(root->left, last);
        root->left = last;
        if (last) 
            last->right = root;
        last = root;
        in_order_visit(root->right, last);
} 
TreeNode* Convert(TreeNode* pRootOfTree)
{
    if (!pRootOfTree) return nullptr;
    TreeNode * last = nullptr;
    in_order_visit(pRootOfTree, last);
    while (last->left) 
        last = last->left;
    return last;
}
//判断一棵树是否为平衡二叉树
bool IsBalanced(TreeNode *pRoot, int &depth) {
    if (!pRoot) {
        depth = 0;
        return true;
    }
    int left, right;
    if (IsBalanced(pRoot->left, left) && IsBalanced(pRoot->right, right)) {
        if (abs(left - right) <= 1) {
            depth = max(left, right) + 1;
            return true;
        } 
    }
    return false;
} 



