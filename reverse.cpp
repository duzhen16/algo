#include <stack>
using namespace std;

class revStack {
public:
	int getLast(stack<int> &s) {
		int ans = s.top();
		s.pop();
		if (s.empty())	return ans;
		else {
			int last = getLast(s);
			s.push(ans);
			return last;
		}
	}
	void reverse(stack<int> &s) {
		if (s.empty()) return;
		int last = getLast(s);
		reverse(s);
		s.push(last);
	}
};
