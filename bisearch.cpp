#include <iostream>
#include <vector>
using namespace std;

int binarysearch(vector<int> nums, int target)
{
    int low = 0;
    int high = (int)nums.size() - 1;
    while (low <= high) {
        int mid = (low + high) >> 1;
        if (nums[mid] == target)
            return mid;
        else if (nums[mid] > target)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

// 旋转数组的最小值
int minNumberInRotateArray(vector<int> rotateArray) {
    int low = 0;
    int high = rotateArray.size() - 1;
    int mid = low;
    while (rotateArray[low] >= rotateArray[high]) {
        mid = (low + high) >> 1;
        if (high - low == 1) {
            mid = high;
            break;
        }
        if (rotateArray[mid] >= rotateArray[low])
            low = mid;
        else if (rotateArray[mid] <= rotateArray[high])
            high = mid;
    }
    return rotateArray[mid];
}

//旋转数组中进行二分查找
int rotatedSearch(vector<int> nums, int target)
{
    //二分查找找到最小的数，将原数组分为两部分，然后分别在两部分中进行原始的二分查找
    int minidx = minNumberInRotateArray(nums);
    int res1 = binarysearch(nums, 0, minidx - 1);
    int res2 = binarysearch(nums, minidx, nums.size() - 1);
    int ans;
    if (res1 == res2 == -1)
        ans = -1;
    else
        ans = (res1 == -1) ? res2 : res1;
    return ans;
}

//二维数组查找
bool search2Dmatrix(int target, vector<vector<int> > array) {
    int row = array.size();
    int col = array[0].size() - 1;
    int i = 0;
    int j = col;
    while ( i < row && j >= 0) {
        if (array[i][j] == target)
            return true;
        else if (array[i][j] > target)
            --j;
        else
            ++i;
    }
    return false;
}

//排序数组中数字出现的次数
int GetFirstK(vector<int> data, int k, int start, int end) {
    if (start > end) 
        return -1;
    int mid = (start + end) >> 1;
    int midval = data[mid];
    if (midval == k) {
        if ((mid > 0 && data[mid - 1] != k) || mid == 0) // mid is first;
            return mid;
        else 
               end = mid - 1;
    } else if (midval > k) 
        end = mid - 1;
    else
        start = mid + 1;
    return GetFirstK(data, k, start, end);
}
int GetLastK(vector<int> data, int k, int start, int end) {
    if (start > end)
        return -1;
    int mid = (start + end) >> 1;
    int midval = data[mid];
    if (midval == k) {
        if ((mid < data.size() - 1 && data[mid + 1] != k) || mid == data.size() - 1) // mid is last;
            return mid;
        else
            start = mid + 1;
    } else if (midval < k)
        start = mid + 1;
    else
        end = mid - 1;
    return GetLastK(data, k, start, end);
}

int GetNumberOfK(vector<int> data ,int k) {
    int res = 0;
    int first = GetFirstK(data, k, 0, data.size() - 1);
    int last = GetLastK(data, k, 0, data.size() - 1);
    if (first > -1 && last > -1)
        res = last - first + 1;
    return res;
}