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
int binarySearch(const vector<int> & arr, const int & num)
{
    int low = 0;
    int high = arr.size() - 1;
    while (low < high){
        //int mid = (low + high) / 2; 
        int mid = low + (high - low) / 2;
        if(arr[mid] < num)
            low = mid + 1;
        else if(arr[mid] > num)
            high = mid - 1;
        else
            return mid; // find
    }
    return -1;  //not found
}

//在一个有序数组中，找>=某个数num最左侧的位置
int binarySearch_01(const vector<int> & arr, const int & num)
{
    int low = 0;
    int high = arr.size() - 1;
    int index = -1;
    while (low <= high){
        //int mid = (low + high) / 2; 
        int mid = low + (high - low) / 2;
        if(arr[mid] >= num){
            index = mid;
            high = mid - 1;
        }
        else if(arr[mid] < num)
            low = mid + 1;
    }
    return index;
}

//数组无序，任何两个相邻数一定不相等，求局部最小值
int binarySearch_02(const vector<int> & arr)
{
    if(arr.size() < 2)
        return -1; 
    int low = 0;
    int high = arr.size() - 1;

    //如果端点处为局部最小值
    if(arr[0] < arr[1])
        return 0;
    else if(arr[arr.size() - 1] < arr[arr.size() - 2])
        return arr.size()-1;

    while (low < high){
        //int mid = (low + high) / 2; 
        int mid = low + (high - low) / 2;
        //判断 mid 处是否为局部最小值
        if(arr[mid] < arr[mid + 1] && arr[mid] < arr[mid - 1])
            return mid;
        else if(arr[mid] > arr[mid + 1])
            low = mid + 1;
        else if(arr[mid] > arr[mid - 1])
            high = mid - 1;
    }
}

int main()
{
    vector<int> a;
    a.push_back(3);
    a.push_back(2);
    a.push_back(0);
    a.push_back(1);
    a.push_back(9);
    for (int i = 0; i < a.size(); i++)
        cout << a[i] << endl;
    
    cout << binarySearch_02(a);
    return 0;
}