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
    
    int flipPancake(vector<int> &nums) { //ÿ�η�ת���±��0��ʼ��
        int res = 0;
        int high = (int)nums.size() - 1;
        int cur_max_idx = 0;
        while (high != 0) {
            int m = -1;
            for (int i = 0; i <= high; i++) // �ҵ���ǰҪѰ�ҵ�������
                if (m < nums[i]) {
                    m = nums[i];
                    cur_max_idx = i;
                }
            if (cur_max_idx == high) { //�����ǰ������Ѿ�������ˣ����÷�ת
                high--;
                continue;
            }
            if (cur_max_idx == 0) { //�����ǰ���������λ����ֻ�跭תһ�Σ�������������
                flip(nums, 0, high);
                res += 1;
            } else {
                flip(nums, 0, cur_max_idx); //�����Ƚ���������ת����λ
                flip(nums, 0, high); // �ڽ��������ת�����λ
                res += 2;
            }
            high --;
        }
        return res;
    }
    int flipPancake2(vector<int> &nums) { //���Բ���������λ��ʼ��ת
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
            flip(nums,cur_max_idx,high);// ֻ�轫������������������з�ת������ʹ����������������
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