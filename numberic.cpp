#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// ��������� ���ù�ʽ (n,m) = (n - 1, m - 1) + (n - 1, m)
#define N 100
vector<vector<long long>> combs(N + 1, vector<long long>(N + 1, 0));

void combination() {
    combs[1][0] = 1;
    combs[1][1] = 1;
    for (int i = 0; i <= N; ++i)
        combs[i][0] = 1;
    for (int i = 1; i <= N; ++i)
        combs[i][1] = i;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            combs[i][j] = combs[i - 1][j - 1] + combs[i - 1][j];
         // combs[i][j] = ( combs[i - 1][j - 1] % 1000000007 + combs[i - 1][j] % 1000000007 ) % 1000000007;
}

//������1�ĸ���    
int  NumberOf1(int n) {
     int cnt = 0;
     while (n) {
         cnt++;
         n = (n - 1) & n;
     }
     return cnt;
}
// ����pow����
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
//string ת int
int myAtoi(char* str) {
    int sign = 1, base = 0, i = 0;
    //ȥ����ͷ�Ŀհ��ַ�
    while (str[i] == ' ')  
        ++; 

    //�����+-�ţ��ж����ֵķ���
    if (str[i] == '-' || str[i] == '+') { 
        sign = 1 - 2 * (str[i++] == '-'); 
    }

    while (str[i] >= '0' && str[i] <= '9') {
        // �ж����
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

//�����г��ֳ���һ�����
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
// ����������ĺ����
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