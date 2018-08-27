#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;
	
class minPathSum_C {
public:
	int minPathSum(vector<vector<int>> &M) {
		// dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + M[i][j];
		//time :O (n^2)
		//mem  :O (m * n)
		int row = M.size();
		int col = M[0].size();
		vector<vector<int>> dp(row, vector<int>(col, 0));
		dp[0][0] = M[0][0];
		for (int i = 1; i < row; i++)    
			dp[i][0] = dp[i - 1][0] + M[i][0];
		for (int j = 1; j < col; j++)
			dp[0][j] = dp[0][j - 1] + M[0][j];
	
		for (int i = 1; i < row; i++)
			for (int j = 1; j < col; j++)
				dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + M[i][j];
		return dp[row - 1][col - 1];
	}
	int minPathSum2(vector<vector<int>> &M) {
		//time :O (n^2)
		//mem  :O (M[0].size())

		vector<int> dp(M[0].size(),0);
		dp[0] = M[0][0];
		for (int i = 1; i < dp.size(); i++) dp[i] = dp[i - 1] + M[0][i];
		for (int i = 1; i < M.size(); i++) {
			dp[0] = dp[0] + M[i][0];
			for (int j = 1; j < dp.size(); j++)
				dp[j] = min(dp[j], dp[j - 1]) + M[i][j];
		}
		return dp[dp.size() - 1];
	}
};

class minCoins_C {
public:
	int minCoins(vector<int> &Coins, int aim) {
		// greedy, „???????? -> 11;
		// time : O(NlogN) 
		// mem  : O(1)
		sort(Coins.begin(), Coins.end());
		int ans = 0;
		int d, r;
		for (int i = Coins.size() - 1; i > -1; i--) {
			d = aim / Coins[i];
			r = aim % Coins[i];
			ans += d;
			if (!r) return ans;
			aim -= d * Coins[i];
		}
		return -1;
	}
	
	int minCoins2(vector<int> &Coins, int aim) { // „????????
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
	int minCoins3(vector<int> &Coins, int aim) { // „??????????
		//DP dp[i][j] = min (dp[i - 1][j], dp[i - 1][j - Coins[i]] + 1}
		vector<vector<int>> dp(Coins.size(), vector<int>(aim + 1, 0));
		for (int i = 1; i <= aim; i++) dp[0][i] = INT_MAX;
		if (aim >= Coins[0]) dp[0][Coins[0]] = 1;
		int left;
		for (int i = 1; i < Coins.size(); i++) 
			for (int j = 1; j <= aim; j++) {
				left = INT_MAX;
				if (j - Coins[i] >= 0 && dp[i - 1][j - Coins[i]] != INT_MAX)
					left = dp[i - 1][j - Coins[i]] + 1;
				dp[i][j] = min(dp[i - 1][j], left);
			}
		return dp[Coins.size() - 1][aim] != INT_MAX ? dp[Coins.size() - 1][aim] : -1;
	}
	
};

class makeupCoins_C {
public:
	int help(vector<int> &coins, int idx,int aim) {
		int res = 0;
		if (idx == coins.size()) res = aim == 0 ? 1 : 0;
		else for (int i = 0; coins[idx] * i <= aim; i++)
			res += help(coins, idx + 1, aim - coins[idx] * i);
		return res;
	}
	int makeupCoins(vector<int> &coins, int aim) { //„??????
		//recursive
		if (aim < 0 || coins.size() == 0) return 0;
		return help(coins, 0, aim);
	}
	
	int makeupCoins2(vector<int> &coins, int aim) { //„????????
		//DP;
		// time : O(aim^2 * coins.size())
		// mem  : O(row * col);
		if (aim < 0 || coins.size() == 0) return 0;
		int row = coins.size();
		int col = aim + 1;
		vector<vector<int>> dp(row, vector<int>(col, 0));
		for (int i = 0; i < row; i++) dp[i][0] = 1;
		for (int i = 1; i * coins[0] <= aim; i++) dp[0][i * coins[0]] = 1;
		for (int i = 1; i < row; i++) {
			for (int j = 1; j < col; j++) {
				int num = 0;
				for (int k = 0; k * coins[i] <= j; k++) num += dp[i - 1][j - k * coins[i]];
				dp[i][j] = num;
			}
		}
		return dp[row - 1][col - 1];
	}

	int makeupCoins3(vector<int> &coins, int aim) { //„?????
		//DP; dp[i][j] = dp[i - 1][j] + dp[i][j - coins[i]];
		// time : O(aim * coins.size())
		// mem  : O(aim);
		if (aim < 0 || coins.size() == 0) return 0;
		vector<int> dp(aim + 1, 1);
		for (int i = 1; i < coins.size(); i++)
			for (int j = 1; j <= aim; j++)
				dp[j] += j - coins[i] >= 0 ? dp[j - coins[i]] : 0;
		return dp[aim];
	}

	int makeupCoins4(vector<int>& nums, int target) {//„???????
		vector<int> dp(target + 1, 0);
		dp[0] = 1;
		for (int i = 0; i < nums.size(); i++) {
			for (int j = target; j >= nums[i]; j--) {
				dp[j] += dp[j - nums[i]];
			}
		}
		return dp[target];
	}

};

int main()
{
	int i = log(12) / log(2);
	cout << i << endl;
	system("pause");
	return 0;
}


