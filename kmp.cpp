#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
/* substr by kmp algo ,O(M + N)*/

//��ȡpattern�ַ���ÿһλ��ǰ׺��׺����ͬ������ȣ���ʹ��ÿ��ƥ��ʧ�ܺ󣬲����ڻ���
//��pattern���ĳ�ʼλ�ö����½�������

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
