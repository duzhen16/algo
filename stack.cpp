#include <iostream>
#include <stack>
using namespace std;

void sortStack(stack<int> &s)
{
	stack<int> help;
	if (s.empty()) {
		cout << "Stack is empty!\n";
		return ;
	}
	while (!s.empty()) {
		int cur = s.top();
		s.pop();	
		while (!help.empty() && help.top() < cur) {
			int ht = help.top();
			s.push(ht);
			help.pop();
		}
		help.push(cur);
	}
	while (!help.empty()) {
		s.push(help.top());
		help.pop();
	}
}
// 判断某个序列是否是按某次序入栈的一个出栈顺序
bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        stack<int> num;
        int push_idx = 0;
        int pop_idx = 0;
        int len = popV.size();
        while (push_idx < len) {
            while (num.empty() || popV[pop_idx] != num.top())
                num.push(pushV[push_idx++]);
            while (!num.empty() && popV[pop_idx] == num.top()) {
                num.pop();
                pop_idx++;
            }
        }
        if (!num.empty()) return false;
        else return true;
    }