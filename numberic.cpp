#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//数字中1的个数    
int  NumberOf1(int n) {
     int cnt = 0;
     while (n) {
         cnt++;
         n = (n - 1) & n;
     }
     return cnt;
}
// 计算pow函数
double Power(double base, int exponent) {
    double res = 1;
    int absexp = abs(exponent);
    while (absexp > 0) {
        if (absexp & 1 == 1) res *= base;
        base *= base;
        absexp >>= 1;
    }
    if (exponent < 0) res = 1 / res;
    return res;
}
//string 转 int
int myAtoi(char* str) {
    int sign = 1, base = 0, i = 0;
    //去除开头的空白字符
    while (str[i] == ' ')  
        ++; 

    //如果有+-号，判断数字的符号
    if (str[i] == '-' || str[i] == '+') { 
        sign = 1 - 2 * (str[i++] == '-'); 
    }

    while (str[i] >= '0' && str[i] <= '9') {
        // 判断溢出
        if (base >  INT_MAX / 10 || (base == INT_MAX / 10 && str[i] - '0' > 7)) {
            if (sign == 1) 
                return INT_MAX;
            else 
                return INT_MIN;
        }
        base  = 10 * base + (str[i++] - '0');
    }
    return base * sign;
}

//数组中出现超过一半的数
int MoreThanHalfNum_Solution(vector<int> numbers) {
    int ans = numbers[0];
    int cnt = 1;
    for (int i = 1; i < numbers.size(); i++) {
         if (cnt == 0) {
            ans = numbers[i];
            cnt = 1;
        }
        else if (ans == numbers[i]) 
            cnt++;
        else 
            cnt--;
    } 
    cnt = 0;
    for (auto n : numbers) 
        if (ans == n)
            cnt++;
    ans = cnt > numbers.size() / 2 ? ans : 0;
    return ans;
}
// 连续子数组的和最大
int FindGreatestSumOfSubArray(vector<int> array) {
    if (array.size() == 0 ) return 0;
    int ans = INT_MIN;
    int sum = 0;
    for (int i = 0; i < array.size(); i++) {
        sum += array[i];
        sum = max(array[i], sum);
        ans = max(sum, ans);
    }
    return ans;
}