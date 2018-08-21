
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
            val(x), next(NULL) {
};

//反转单链表
ListNode* reverseList(ListNode* head) {
    ListNode *prev = nullptr;
    ListNode *next = nullptr;
    while (head) {
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}
//递归反转单链表 
Node * reverseList_R(Node * head) {
    if (head == nullptr || head->next == nullptr)
        return head;
    Node * next = head->next;
    Node * res = reverseList_R(next);
    head->next = nullptr;
    next->next = head;
    return res;
}

//倒数第K个节点
ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
    if (!pListHead || !k) return nullptr;
    ListNode * p, *q;
    p = q = pListHead;
    while (k > 1 && p->next) {
        p = p->next;
        k--;
    }
    while (p->next) {
        p = p->next;
        q = q->next;
    } 
    if (k > 1) return nullptr;
    return q;
}
//合并两个排序的链表
ListNode* Merge(ListNode* pHead1, ListNode* pHead2) {
    if (!pHead1) return pHead2;
    if (!pHead2) return pHead1;
    ListNode *pMerge = nullptr;
    if (pHead1->val < pHead2->val) {
        pMerge = pHead1;
        pMerge->next = Merge(pHead1->next, pHead2);
    }else {
        pMerge = pHead2;
        pMerge->next = Merge(pHead1, pHead2->next);
    }
    return pMerge;
}
//两个链表的第一个交点
ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
    int len1, len2;
    len1 = len2 = 0;
    ListNode *p = pHead1;
    while(p) {
        len1++;
        p = p->next;
    }
    p = pHead2;
    while(p) {
        len2++;
        p = p->next;
    }
    int diff = len1 - len2;
    if (diff > 0) {
        int d = diff;
        while (d--) pHead1 = pHead1->next;
    } else if (diff < 0) {
        int d = -diff;
        while (d--) pHead2 = pHead2->next;
    }
    while (pHead1 != pHead2) {
        pHead1 = pHead1->next;
        pHead2 = pHead2->next;
    }
    return pHead1;
}


struct Node {
    int val;
    Node * next;
    Node(int v) : val(v), next(nullptr){}
};

struct Pair {
    Node * begin;
    Node * end;
    Pair() : begin(nullptr), end(nullptr){}
};

Node * reverseListByK(Node * head, int k) {
    //得到链表长度。
    int len = 0;
    Node *p = head;
    while (p) {
        len++;
        p = p->next;
    }
    if (k < 0 || k >= len) return head;
    
    int cnt = len / k;
    int mod = len % k;
    if (mod != 0) cnt += 1;
    vector<Pair *> pairs;
    p = head;
    while (cnt > 0 && p) {
        Pair * pr = new Pair;
        pr->begin = p;
        int i = 0;
        while (i < k - 1 && p->next) {
            p = p->next;
            i++;
        }
        if (p)
            pr->end = p;
        pairs.push_back(pr);
        p = p->next;
        cnt--;
    }
    cnt = pairs.size() - 1;
    Node * nh = pairs[cnt]->begin;
    for (int i = pairs.size() - 1; i > 0; i--) {
        pairs[i]->end->next = pairs[i - 1]->begin;
    }
    pairs[0]->end->next = nullptr;
    return nh;
}