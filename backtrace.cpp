#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;

vector<string> Permutation(string str) {
    if(str.size() == 0) return result;
    dfs(str,0);
    return result;
}

void dfs(string str,int begin){
    if(begin == str.size()){
        result.push_back(str);
        return ;
    }
    for(int i = begin; i < str.size(); i++){
        if(i != begin && str[begin]==str[i])
            continue;
        swap(str[begin], str[i]);
        dfs(str,begin + 1);
        swap(str[begin], str[i]);
    }
}

class Solution {
public:
	vector<vector<int>> ans;
	void bt(vector<bool> &visited, vector<int> &nums, vector<int> vec) {
		if (vec.size() == nums.size()) {
			ans.push_back(vec);
		}
		for (int i = 0; i < nums.size(); i++) {
			if (!visited[i]) {
				vec.push_back(nums[i]);
				visited[i] = true;
				bt(visited, nums, vec);
				visited[i] = false;
				vec.pop_back();
			}
		}
	}
	vector<vector<int>> permute(vector<int>& nums) {
		vector<int> vec;
		vector<bool> visited(nums.size(), false);
		bt(visited, nums, vec);
		return ans;
	}	
};

class Solution {
public:
    vector<vector<int>> ans;
	vector<int> last;
    void bt(vector<bool> &visited, vector<int> &nums, vector<int> &vec) {
        if (vec.size() == nums.size()) {
                ans.push_back(vec);
				return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (!visited[i]) {
				if (last.end() != find(last.begin(), last.end(), nums[i])) {
					vec.push_back(nums[i]);
					visited[i] = true;
                    bt(visited, nums, vec);
                    visited[i] = false;
                    last.push_back(nums[i]);
                    vec.pop_back();
                } else 
                    vec.pop_back();
               
            }
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<int> vec;
        vector<bool> visited(nums.size(), false);
        bt(visited, nums, vec);
        return ans;
    }
};

class Solution {
public:
	vector<vector<int>> ans;
	void bt(vector<int> &vec, int res, int idx, vector<int> nums) {
		if (res == 0) {
			ans.push_back(vec);
			return;
		}
		for (int i = idx + 1; i < nums.size(); i++) {
			if (res - nums[i] >= 0) {
				vec.push_back(nums[i]);
				bt(vec, res - nums[i], i, nums);
				vec.pop_back();
			}
		}
	}
	vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
		sort(candidates.begin(), candidates.end());
		vector<int> vec;
		bt(vec, target, 0, candidates);
		return ans;
	}
};

class Solution {
public:
	int findTargetSumWays(vector<int>& nums, int S) {
		int total = accumulate(nums.begin(), nums.end(), 0);
		if (S > total || (S + total) % 2 == 1) return 0;
		int target = (S + total) >> 1;
		vector<int> dp(target + 1, 0);
		dp[0] = 1;
		for (int i = 0; i < nums.size(); i++) {
			//dp[nums[i]] = 1;
			for (int j = target; j >= nums[i]; j--) {
				dp[j] += dp[j - nums[i]];
			}
		}
		return dp[target];
	}
};
