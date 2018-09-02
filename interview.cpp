/*
����ʵϰһ��
1. ��ת������
2. ��������������з�ת��Ȼ����в���ĳ��Ŀ��
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
// ��ת�������Сֵ,�������ҵ��������Ϊ�����������������
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
//���ֲ����ҵ���С��������ԭ�����Ϊ�����֣�Ȼ��ֱ����������н���ԭʼ�Ķ��ֲ���
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
��Ѷʵϰһ��
1. ���ַ����в����Ӵ�
2. ��Ǯ�����ٻ�������
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
�����Ʋ�����
1. һ����ֻ�����˳飬�������������У���˭������Ӯ
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
            // �Ż���һά
            dp[j] = max(nums[i] - dp[j], nums[j] - dp[j - 1]);
    int res = dp[len - 1];
    
    if (res > 0) return 1; // �ȳ���ʤ
    else if (res < 0) return 2; // �����ʤ
    else return 0; // ƽ��
}

/*
������һ��
1. ������
2 �ڴ�����unsigned int���������ҵ�ֻ����һ�ε���
*/
void make_heap(vector<int> &nums, int tar, int len) {  // �󶥶�
	int tmp = nums[tar];
	int j = 2 * tar + 1;
	while (j < len) {
		if (j + 1 < len && nums[j] < nums[j + 1]) j++; // j�Ǻ���������
		if (nums[j] <= tmp) break; // �Ѿ��Ǵ󶥶���
		else {
			nums[tar] = nums[j];
			tar = j;
			j = 2 * tar + 1;
		}
	}
	nums[tar] = tmp;
}
void heap(vector<int> &nums) { 
//������ �ȶ�
    for (int i = nums.size() / 2 - 1; i >= 0; i--)  // �����һ������Ҷ�ӵĽڵ㿪ʼ������һ���󶥶�
		make_heap(nums, i, nums.size());
	for (int i = nums.size() - 1; i >= 0; i--) {
		swap(nums[0], nums[i]);
		make_heap(nums, 0, i);
	}
}
vector<unsigned int> appearOnce(vector<unsigned int> &nums) {
//��Ҫ���Ǿ����ܵؽ���ʱ��ռ临�Ӷ�
    vector<bitset<2>> bits(UINT32_MAX, 0); // 00 --> ����0�Σ� 01 --> ����1�Σ� 11 --> ���ֶ��
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
�����ƶ���
1. ����
2. �������ַ����Ľ���
3. �����򣨽���˼·��
4. ������Ʊ���������
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
//�������� ���ȶ�
    int begin = 0;
	int end = nums.size() - 1;
	q_sort(nums, begin, end);
}
string intersect2strings(string& str1, string& str2) {
/* ������str�в������ظ��ַ���
1. ����str1�е��ַ�����str2�н��в��� 
   ʱ�临�Ӷ� O��n*n)
2. �ֱ��str1�� str2��������Ȼ��ʹ������ָ��ֱ�ָ�������ַ�������ͷ��ʼ���бȽ�
   ʱ�临�Ӷ� O(nlogn)
3. ʹ��λͼ���ֱ���������ַ���
   ʱ�临�Ӷ� O(n)
   �ռ临�Ӷ� O(1), �����ڴ� 128bit
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
�����ƴ����棺�����ַ�ת����
���������K
1->2->3->4->5->6->7->8->9
K = 3
��� 
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
�����ƽ�����
��һ���ܴ�����飬ÿ�λ�������±�b��e�����������Χ�ڵ���Сֵ�����������ѯ�����Ƿǳ�Ƶ����
���ÿ�ζ�����b��e֮��ѭ��,�����ܴ�,������ζ�������Ż���ѯ��ʹ���Ժ�Ĳ�ѯ���
˼·������һ�Ų�ѯ��������b,e�������е���Сֵ
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