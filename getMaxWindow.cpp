#include <deque>
#include <vector>
using namespace std;
class getMax {
public:
	vector<int> getMaxWindow(vector<int> nums, int w) {
		vector<int> ans;
		if (!nums.size() || w < 1 || nums.size() < w)  return ans;

		deque<int> qmax;
		for (int i = 0; i < nums.size(); ++i) {
			while (!qmax.empty() && nums[i] >= nums[qmax[qmax.size() - 1]])
				qmax.pop_back();

			qmax.push_back(i);
			if (qmax[0] == i - w) qmax.pop_front();
			if (i >= w - 1)	ans.push_back(nums[qmax[0]]);
		}
		return ans;
	}
	
};