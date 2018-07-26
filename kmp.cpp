#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
/* substr by kmp algo ,O(M + N)*/

//获取pattern字符串每一位的前缀后缀串相同的最长长度，以使得每次匹配失败后，不至于回退
//到pattern串的初始位置而重新进行搜索

vector<int> getNext(string pattern) {
	int pl = pattern.size();
	vector<int> next(pl, -1);
	int j = 0;
	int k = -1;
	while (j < pl - 1) {
		if (k == -1 || pattern[j] == pattern[k]) 
			if (pattern[k + 1] == pattern[j + 1])
				next[++j] = next[++k];	//optimaze
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
