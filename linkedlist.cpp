
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