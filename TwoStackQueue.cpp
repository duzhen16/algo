#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class TwoStackQueue {
private:
	stack<int> stack_push;
	stack<int> stack_pop;
public:
	void add(int n)
	{
		stack_push.push(n);
	}
	int poll()
	{
		if (stack_push.empty() && stack_pop.empty()) {
			cout << "Queue is empty!\n";
			return -1;
		}
		if (stack_pop.empty()) {
			while (!stack_push.empty()) {
				stack_pop.push(stack_push.top());
				stack_push.pop();
			}
		}
		int ans = stack_pop.top();
		stack_pop.pop();
		return ans;
	}
	int peek()
	{
		if (stack_push.empty() && stack_pop.empty()) {
			cout << "Queue is empty!\n";
			return -1;
		}
		if (stack_pop.empty()) {
			while (!stack_push.empty()) {
				stack_pop.push(stack_push.top());
				stack_push.pop();
			}
		}
		int ans = stack_pop.top();
		return ans;
	}
};