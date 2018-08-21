#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;

//冒泡排序 稳定
void pop(vector<int> &nums) {
	int s = 0;
	for (int i = 0; i < nums.size(); i++) {
		for (int j = 0; j < nums.size() - i - 1; j++) {
			if (nums[j] > nums[j + 1]) {
				swap(nums[j], nums[j + 1]);
				s = 1;
			}
		} 
		if (!s) break; //遍历一次没有交换，说明已经是有序的，则停止算法，复杂度降到O(n);
	}
}

//选择排序 不稳定
void select(vector<int> &nums) {
	for (int i = 0; i < nums.size(); i++) {
		int m = i;
		for (int j = i + 1; j < nums.size(); j++)
			m = nums[j] < nums[m] ? j : m;
		if (m != i) swap(nums[m], nums[i]);
	}
}

//插入排序 稳定
void insert(vector<int> &nums) {
	for (int i = 1; i < nums.size(); i++) 
		for (int j = i; j > 0; j--) 
			if (nums[j - 1] > nums[j]) 
				swap(nums[j],nums[j - 1]);
			else break;
}

//快速排序 不稳定
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
	int begin = 0;
	int end = nums.size() - 1;
	q_sort(nums, begin, end);
}

//堆排序 稳定
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
	for (int i = nums.size() / 2 - 1; i >= 0; i--)  // 从最后一个不是叶子的节点开始，建立一个大顶堆
		make_heap(nums, i, nums.size());
	for (int i = nums.size() - 1; i >= 0; i--) {
		swap(nums[0], nums[i]);
		make_heap(nums, 0, i);
	}
	
}

//归并排序 稳定
void _merge(vector<int> &nums, int begin, int end, int mid) {
	int i = begin;
	int j = mid + 1;
	vector<int> tmp(end - begin + 1, 0);
	int k = 0;
	while (i <= mid && j <= end) {
		if (nums[i] < nums[j]) 
			tmp[k++] = nums[i++];
		else
			tmp[k++] = nums[j++];
	}
	
	if (i > mid) 
		while (j <= end) tmp[k++] = nums[j++];
	else 
		while (i <= mid) tmp[k++] = nums[i++];
	
	for (int i = 0; i < tmp.size(); i++)
		nums[begin + i] = tmp[i];
}
void m_sort(vector<int> &nums, int begin, int end) {
	int mid = (end + begin) / 2 ;
	if (end - begin > 1) {
		m_sort(nums, begin, mid);
		m_sort(nums, mid + 1, end);
	}
	_merge(nums, begin, end, mid);
}
void merge(vector<int> &nums) {
	m_sort(nums, 0, nums.size() - 1);
}

//基数排序 稳定
void r_sort(vector<int> &nums, int pos) {
	vector<queue<int>> queues;
	for (int i = 0; i < 10; i++) {
		queue<int> q;
		queues.push_back(q);
	}

	for (auto n : nums) {
		int idx = (n / (int)pow(10, pos)) % 10;
		queues[idx].push(n);
	}
	
	int k = 0;
	for (int i = 0; i < 10; i++) 
		while (!queues[i].empty()) {
			int n = queues[i].front();
			nums[k++] = n;
			queues[i].pop();
		}
}
void radix(vector<int> &nums) {
	int len = to_string(*max_element(nums.begin(), nums.end())).size();
	for (int i = 0; i < len; i++) //从个位开始
		r_sort(nums, i);
}

//希尔排序 不稳定
void shell(vector<int> &nums) {
	for (int gap = nums.size() / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < nums.size(); i++)  // 插入排序
			for (int j = i; j - gap >= 0; j -= gap) {
				if (nums[j] < nums[j - gap]) 
					swap(nums[j], nums[j - gap]);
				else break;
			
		}
	}
}

int main()
{
	vector<int> nums = { 213,22212,34,343,44 };
	auto cmp = [](int a, int b) {
		string sa = to_string(a);
		string sb = to_string(b);
		return sa + sb < sb + sa;
	}
	sort(nusm.begin(), nums.end(),cmp);
	
	//pop(nums);
	//select(nums);
	//insert(nums);
	//quick(nums);
	//heap(nums);
	//merge(nums);
	//radix(nums);
	//shell(nums);
	for (auto n : nums) 
		cout << n << " ";
	return 0;
}

