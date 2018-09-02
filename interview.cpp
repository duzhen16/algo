/*
阿里实习一面
1. 反转单链表
2. 将以有序数组进行翻转，然后进行查找某个目标
*/
struct Node {
    int val;
    struct Node * next;
    Node(int v) : val(v), next(nullptr) {}
};
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

int minNumberInRotateArray(vector<int> rotateArray) {
// 旋转数组的最小值,即就是找到将数组分为两部分有序数组的轴
    int low = 0;
    int high = rotateArray.size() - 1;
    int mid = low;
    while (rotateArray[low] >= rotateArray[high]) {
        mid = (low + high) >> 1;
        if (high - low == 1) {
            mid = high;
            break;
        }
        if (rotateArray[mid] >= rotateArray[low])
            low = mid;
        else if (rotateArray[mid] <= rotateArray[high])
            high = mid;
    }
    return rotateArray[mid];
}
int rotatedSearch(vector<int> nums, int target)
{
//二分查找找到最小的数，将原数组分为两部分，然后分别在两部分中进行原始的二分查找
    int minidx = minNumberInRotateArray(nums);
    int res1 = binarysearch(nums, 0, minidx - 1);
    int res2 = binarysearch(nums, minidx, nums.size() - 1);
    int ans;
    if (res1 == res2 == -1)
        ans = -1;
    else
        ans = (res1 == -1) ? res2 : res1;
    return ans;
}

/*
腾讯实习一面
1. 在字符串中查找子串
2. 换钱的最少货币张数
*/
vector<int> getNext(string pattern) {
	int pl = pattern.size();
	vector<int> next(pl, -1);
	int j = 0;
	int k = -1;
	while (j < pl - 1) {
		if (k == -1 || pattern[j] == pattern[k]) 
			if (pattern[k + 1] == pattern[j + 1]) //optimaze
				next[++j] = next[++k];	
			else 
				next[++j] = ++k; // original
		else
			k = next[k];
	}
	return next;
}
int kmp_strStr(string text, string pattern) {
	vector<int> next = getNext(pattern);
	int i = 0;
	int j = 0;
	int len_text = text.size();
	int len_patt = pattern.size();
	while (i < len_text && j < len_patt) {
		if (j == -1 || text[i] == pattern[j]) {
			i++;
			j++;
		}
		else
			j = next[j];
	}
	return j == len_patt ? i - j : -1;
}

int minCoins2(vector<int> &Coins, int aim) { 
    // DP   dp[i][j] = min { dp[i - 1][j] , dp[i][j - Coins[i]] + 1}
    // time : (Coins.size() * aim)  
    // mem  : O(Coins.size() * aim) 
    vector<vector<int>> dp(Coins.size(), vector<int>(aim + 1, 0));
    for (int i = 1; i <= aim; i++) {
        dp[0][i] = INT_MAX;
        if (i - Coins[0] >= 0 && dp[0][i - Coins[0]] != INT_MAX)
            dp[0][i] = dp[0][i - Coins[0]] + 1;
    }
    int left;
    for (int i = 1; i < Coins.size(); i++) 
        for (int j = 1; j <= aim; j++) {
            left = INT_MAX;
            if (j - Coins[i] >= 0 && dp[i][j - Coins[i]] != INT_MAX)
                left = dp[i][j - Coins[i]] + 1;
            dp[i][j] = min(dp[i - 1][j], left);
        }
    return dp[Coins.size() - 1][aim] != INT_MAX ? dp[Coins.size() - 1][aim] : -1;
}

/*
阿里云测评题
1. 一副牌只在两端抽，两个人轮流进行，问谁最后可以赢
The dp[i][j] saves how much more scores that the first-in-action 
player will get from i to j than the second player. First-in-action
means whomever moves first. 
*/
int card(vector<int> &nums) {
// dp[i][j] = max(nums[i] - dp[i+1][j], nums[j] - dp[i][j-1]);
	int len = nums.size();
    vector<int> dp(len, 0);
    for (int i = len - 2; i >= 0; i--) 
        for (int j = i + 1; j < len; j++) 
            // 优化到一维
            dp[j] = max(nums[i] - dp[j], nums[j] - dp[j - 1]);
    int res = dp[len - 1];
    
    if (res > 0) return 1; // 先抽者胜
    else if (res < 0) return 2; // 后抽者胜
    else return 0; // 平局
}

/*
阿里云一面
1. 堆排序
2 在大量的unsigned int型数据中找到只出现一次的数
*/
void make_heap(vector<int> &nums, int tar, int len) {  // 大顶堆
	int tmp = nums[tar];
	int j = 2 * tar + 1;
	while (j < len) {
		if (j + 1 < len && nums[j] < nums[j + 1]) j++; // j是孩子中最大的
		if (nums[j] <= tmp) break; // 已经是大顶堆了
		else {
			nums[tar] = nums[j];
			tar = j;
			j = 2 * tar + 1;
		}
	}
	nums[tar] = tmp;
}
void heap(vector<int> &nums) { 
//堆排序 稳定
    for (int i = nums.size() / 2 - 1; i >= 0; i--)  // 从最后一个不是叶子的节点开始，建立一个大顶堆
		make_heap(nums, i, nums.size());
	for (int i = nums.size() - 1; i >= 0; i--) {
		swap(nums[0], nums[i]);
		make_heap(nums, 0, i);
	}
}
vector<unsigned int> appearOnce(vector<unsigned int> &nums) {
//需要考虑尽可能地降低时间空间复杂度
    vector<bitset<2>> bits(UINT32_MAX, 0); // 00 --> 出现0次； 01 --> 出现1次； 11 --> 出现多次
    for (auto n : nums) {
        if (bits[n] == 0)
            bits[n] |= 0b01;
        else if (bits[n] == 1)
            bits[n] |= 0b11;
    }
    vector<unsigned int> ans;
    for (auto i = 0; i < UINT32_MAX; ++i)
        if (bits[i] == 1)
            ans.push_back(i);
    return ans;
}
/*
阿里云二面
1. 快排
2. 求两个字符串的交集
3. 外排序（介绍思路）
4. 买卖股票的最大收益
*/
void q_sort(vector<int> &nums, int begin, int end) {
	int i = begin;
	int j = end;
	if (i >= j) return;
	int flag = nums[begin];
	while (i < j) {
		while (i < j && nums[j] >= flag)  j--;
		if (i < j) nums[i] = nums[j];
		
		while (i < j && nums[i] <= flag)  i++;
		if (i < j) nums[j] = nums[i];
	}
	nums[i] = flag;
	q_sort(nums, begin, i - 1);
	q_sort(nums, i + 1, end);
}
void quick(vector<int> &nums) {
//快速排序 不稳定
    int begin = 0;
	int end = nums.size() - 1;
	q_sort(nums, begin, end);
}
string intersect2strings(string& str1, string& str2) {
/* （假设str中不出现重复字符）
1. 遍历str1中的字符，在str2中进行查找 
   时间复杂度 O（n*n)
2. 分别对str1， str2进行排序，然后使用两个指针分别指向两个字符串，从头开始进行比较
   时间复杂度 O(nlogn)
3. 使用位图，分别遍历两个字符串
   时间复杂度 O(n)
   空间复杂度 O(1), 消耗内存 128bit
*/
    bitset<128> bits;
    string ans;
    for (auto c : str1) 
        bits[c - '0'] = 1;
    for (auto c : str2) 
        if (bits[c - '0'] == 1) 
            ans.push_back(c);
    return ans;
}
int maxProfit(vector<int>& prices) {
    int minPrice = INT_MAX;
    int maxProfit = 0;
    for (auto price : prices) {
        minPrice = min (minPrice, price);
        maxProfit = max (maxProfit, price - minPrice);
    }
    return maxProfit;
}
/*
阿里云代码面：按部分反转链表
输入链表和K
1->2->3->4->5->6->7->8->9
K = 3
输出 
7->8->9->4->5->6->1->2->3
*/
struct Pair {
    Node * begin;
    Node * end;
    Pair() : begin(nullptr), end(nullptr){}
};
Node * reverseListByK(Node * head, int k) {
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

/*
阿里云交叉面
有一个很大的数组，每次会给两个下标b和e，返回这个范围内的最小值，但是这个查询操作是非常频繁的
如果每次都是在b和e之间循环,开销很大,现在如何对其进行优化查询，使得以后的查询变快
思路：建立一颗查询树，输入b,e返回其中的最小值
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