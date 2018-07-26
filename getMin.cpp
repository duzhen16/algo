#include <iostream>
#include <stack>
using namespace std;

class MinStack
{
private:
	stack<int> nums;
	stack<int> order;
public:
	void push(int n)
	{
		nums.push(n);
		if (order.empty())
			order.push(n);
		else if (order.top() >= n)
			order.push(n);
	}
	int pop()
	{
		if (nums.empty()) {
			cout << "Stack is empty!\n";
			return -1;
		}
		int ans = nums.top();
		nums.pop();
		if (order.top() == ans)
			order.pop();
		return ans;
	}
	int getMin()
	{
		if (order.empty()) {
			cout << "Stack is empty!\n";
			return -1;
		}
		return order.top();
	}
};