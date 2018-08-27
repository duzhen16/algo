#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Solution {
public:
    void flip(vector<int> &a, int low, int high) {
        for (int i = low, j = high; i <= j; i++, j--)
            swap(a[i], a[j]);
    }
    
    int flipPancake(vector<int> &nums) { //每次翻转的下表从0开始。
        int res = 0;
        int high = (int)nums.size() - 1;
        int cur_max_idx = 0;
        while (high != 0) {
            int m = -1;
            for (int i = 0; i <= high; i++) // 找到当前要寻找的最大的数
                if (m < nums[i]) {
                    m = nums[i];
                    cur_max_idx = i;
                }
            if (cur_max_idx == high) { //如果当前最大数已经在最后了，则不用翻转
                high--;
                continue;
            }
            if (cur_max_idx == 0) { //如果当前最大数在首位，则只需翻转一次，将其放置在最后
                flip(nums, 0, high);
                res += 1;
            } else {
                flip(nums, 0, cur_max_idx); //否则，先将最大的数翻转到首位
                flip(nums, 0, high); // 在将最大数翻转至最后位
                res += 2;
            }
            high --;
        }
        return res;
    }
    int flipPancake2(vector<int> &nums) { //可以不从数列首位开始翻转
        int res = 0;
        int high = (int)nums.size() - 1;
        int cur_max_idx = 0;
        while (high != 0) {
            int m = -1;
            for (int i = 0; i <= high; i++)
                if (m < nums[i]) {
                    m = nums[i];
                    cur_max_idx = i;
                }
            if (cur_max_idx == high) {
                high--;
                continue;
            }
            flip(nums,cur_max_idx,high);// 只需将从最大数到最后的数进行翻转，可以使得最大数放置在最后
            res += 1;
            high --;
        }
        return res;
    } 
    };
int main(int argc ,char* argv[])
{
    vector<int> n = {5,4,2,3,1};
    Solution sol;
    cout << sol.flipPancake(n) << endl;
    return 0;
}