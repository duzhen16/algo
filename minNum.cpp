#include <iostream>
#include <vector>
using namespace std;
/*
* 阿里云 三面 交叉面
* 有一个很大的数组，每次会给两个下标b和e，返回这个范围内的最小值，但是这个查询操作是非常频繁的
* 如果每次都是在b和e之间循环,开销很大,现在如何对其进行优化查询
*/
struct Node {
    int begin;
    int end;
    int min;
    Node * left;
    Node * right;
    Node(int b, int e, int m) : begin(b), end(e),min(m),left(nullptr), right(nullptr){}
};

vector<int> nums = {4,3,5,2,7,4,3};

Node * create(int begin, int end) {
    if (begin == end) {
        Node * p = new Node(begin, end, nums[begin]);
        return p;
    } else {
        int mid = (begin + end) >> 1;
        Node * left = create(begin, mid);
        Node * right = create(mid + 1, end);
        Node * p = new Node(begin, end, min(left->min, right->min));
        p->left = left;
        p->right = right;
        return p;
    }
}
void help(Node * root, int begin, int &end, int &min) {
    Node * p = root;
    if (!root) return ;
    else {
        while (p) {
            if (p->begin == begin && p->end <= end) {
                min = p->min;
                end = p->end;
                return ;
            }
            if (p->left->end >= begin && p->left->begin <= begin)
                p = p->left;
            else if (p->right->end >= begin && p->right->begin <= begin)
                p = p->right;
        }
    }
}

int minNum(Node * root, int idx1, int idx2) {
    if (idx1 <= 0 || idx2 >= (int)nums.size()) {
        cout << "Error input\n";
        return -1;
    }
    int res = INT_MAX;
    int pos1 = idx1;
    int pos2 = idx2;
    while (pos1 <= idx2) {
        int cur = INT_MAX;
        help(root, pos1, pos2, cur);
        res = min(res, cur);
        pos1 = pos2 + 1;
        pos2 = idx2;
    }
    return res;
}

int main()
{
    Node * root = create(0, (int)nums.size() - 1);
    int idx1, idx2;
    cin >> idx1 >> idx2;
    cout << minNum(root, idx1, idx2) << endl;
    cout << endl;
    return 0;
}








