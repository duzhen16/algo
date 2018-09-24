#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;



int main()
{
 int n,m;
 cin >> n >> m;
 vector<int> price;

 for(int i = 0;i < n;i++)
 {
  int p;
  cin >> p;
  price.push_back(p);
 }

 vector<int> v1,v2,v3;
 for(int j = 0;j < m;j++)
 {
  int p,r;
  cin >> p >> r;
  v1.push_back(p);
  v2.push_back(r);
  v3.push_back(1);
 }
 int sum = 0;
 sort(price.begin(),price.end());
 for(int i = 0;i < n;i++)
 {
  int pri = price[i];
  int max = -1,maxindex = -1;
  for(int j = 0;j < v1.size();j++)
  {
   if(v1[j] <= pri && v2[j] > max && v3[j] == 1)
   {
    max = v2[j];
    maxindex = j;
   }
  }

  sum += pri;
  if(max != -1)
  {
   sum -= v2[maxindex];
   v3[maxindex] = 0;
  }
 }
 cout << sum;
}