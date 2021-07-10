# 左神数据结构算法（基础到高级篇）
## 基础
### 1.认识复杂度和简单排序算法
#### 1.1 异或运算
- 在一个整型数组中，只有一种数出现了奇数次，其他数都出现了偶数次，如何找到这一种数。
```cpp
void printOddTimesNum1(vector<int> & arr)
{
    int eor = 0;
    for(int cur : arr)
        eor ^= cur;
    cout << eor << endl;
}
```
- 有两种数出现了奇数次，其他数都出现了偶数次，如何找到这两种数。
```cpp
void printOddTimesNum2(vector<int> & arr)
{
    int eor = 0;
    for(int cur : arr)
        eor ^= cur;
    // eor = a^b;
    // eor != 0;    -->    eor 必然有一个位置上是1
    int rightOne = eor & (~eor + 1);    //提取出最右侧的1
    int onlyOne = 0;    // eor'
    for(int cur : arr){
        if(cur & rightOne == 0)
            onlyOne ^= cur;
    }
    cout << eor << "," << (eor ^ onlyOne) << endl;  
}
```
#### 1.2 二分法
- 一个有序数组，寻找某个数num是否存在。
```cpp
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
```
- 在一个有序数组中，找>=某个数num最左侧的位置。
```cpp
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
```
- 数组无序，任何两个相邻数一定不相等，求局部最小值
```cpp
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
```