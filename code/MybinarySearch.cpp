#include <iostream>
#include <vector>
using namespace std;
/*
* 二分法：
    1. 一个有序数组，寻找某个数num是否存在
    2. 在一个有序数组中，找>=某个数num最左侧的位置或<=某个数num最右侧的位置
    3. 数组无序，任何两个相邻数一定不相等，求局部最小值
*/

//一个有序数组，寻找某个数num是否存在
int binarySearch(vector<int>& nums, int target) {
    int low = 0;
    int high = nums.size() - 1;
    while(low <= high){
        //int mid = (low + high) / 2; 
        int mid = low + ((high - low) >> 1);
        if(nums[mid] == target){
            return mid; // find
        }
        else if(nums[mid] > target){
            high = mid - 1;
        }
        else{
            low = mid + 1; 
        }
    }
    return -1;  //not found
}

//在一个有序数组中，找>=某个数num最左侧的位置
int binarySearch_01(vector<int>& nums, int target){
    int low = 0;
    int high = nums.size() - 1;
    int index = -1;
    while (low <= high){
        //int mid = (low + high) / 2; 
        int mid = low + ((high - low) >> 1);
        if(nums[mid] >= target){
            index = mid;
            high = mid - 1;
        }
        else if(nums[mid] < target){
            low = mid + 1;
        }  
    }
    return index;
}

//数组无序，任何两个相邻数一定不相等，求局部最大值
int findPeakElement(vector<int>& nums) {
    int n = nums.size();
    if(n == 1){
        return 0;
    }
    //先判断两边情况
    if(nums[0] > nums[1]){
        return 0;
    }
    else if(nums[n - 1] > nums[n - 2]){
        return n - 1;
    }      
    int low = 0;
    int high = n - 1;
    while(low <= high){
        int mid = low + ((high - low) >> 1);
        // 当前为峰值
        if(mid >= 1 && mid < n - 1 && nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1]){
            return mid;
        }
        else if(mid >= 1 && nums[mid] < nums[mid - 1]){
            // 峰值在 mid 左侧
            high = mid - 1;
        }
        else if(mid < n - 1 && nums[mid] < nums[mid + 1]){
            // 峰值在 mid 右侧
            low = mid + 1;
        }
    }
    return -1;
}

int main()
{
    return 0;
}