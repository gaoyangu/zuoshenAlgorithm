#include <iostream>
#include <vector>
#include <cstdlib> 
#include <algorithm> 
#include <climits>
#include <queue>
#include <time.h>
using namespace std;

void swap(vector<int>& arr, int i, int j){
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp; 
}

// 选择排序
void selectSort(vector<int>& arr){
    if( arr.size() < 2){
        return;
    }
    for (int i = 0; i < arr.size() - 1; i++){   // i ~ N-1
        int minIndex = i;
        for (int j = i + 1; j < arr.size(); j++){
            minIndex = arr[j] < arr[minIndex] ? j : minIndex;
        }
        swap(arr, i, minIndex);
    }
}


// 冒泡排序
void bubbleSort(vector<int> & arr){
    if( arr.size() < 2){
        return;
    } 
    for(int i = arr.size() - 1; i > 0; i--){
        for (int j = 0; j < i; j++){
            if(arr[j] > arr[j+1]){
                swap(arr, j, j+1);  
            }    
        }
    }
}


//插入排序
void insertionSort(vector<int> & arr){
    if (arr.size() < 2){
        return;
    }
    for(int i = 1; i < arr.size(); i++){ //0~i做到有序
        for(int j = i-1; j >= 0 && arr[j] > arr[j+1]; j--){ // 0~i-1 已经有序, j 当前位置的前一个位置
            swap(arr, j, j+1);
        }
    }
}


//归并排序
vector<int> mergeSort(vector<int>& nums) {
    process(nums, 0, nums.size() - 1);
    return nums;
}
void process(vector<int>& nums, int L, int R){
    if(L == R){
        return;
    }
    int mid = L + ((R - L) >> 1);
    process(nums, L, mid);
    process(nums, mid + 1, R);
    merge(nums, L, mid, R);
}
void merge(vector<int>& nums, int L, int M, int R){
    vector<int> help;   //！额外空间复杂度
    int p1 = L;
    int p2 = M + 1;
    while(p1 <= M && p2 <= R){
        help.push_back(nums[p1] <= nums[p2] ? nums[p1++] : nums[p2++]);
    }
    while(p1 <= M){
        help.push_back(nums[p1++]);
    }
    while(p2 <= R){
        help.push_back(nums[p2++]);
    }
    for(int i = 0; i < help.size(); i++){
        nums[L + i] = help[i];
    }
}


//快速排序
void quickSort(vector<int>& nums, int L, int R){
    if(L < R){
        srand((unsigned)time(NULL));
        swap(nums, L + rand()%(R - L + 1), R);  //在数组中随机选择一个数，与最后一个数交换作为划分值num
        vector<int> p = partition(nums, L, R);  //根据实际的数据状况决定
        quickSort(nums, L, p[0] - 1);
        quickSort(nums, p[1] + 1, R);
    }
}
//返回值：等于区域的左边界和右边界
vector<int> partition(vector<int>& nums, int L, int R){
    int less = L - 1;   // <区右边界
    int more = R;       // >区左边界
    while(L < more){
        if(nums[L] < nums[R]){      //当前值 < 划分值
            swap(nums, ++less, L++);
        }
        else if(nums[L] > nums[R]){ //当前值 > 划分值
            swap(nums, --more, L);
        }
        else{
            L++;
        }
    }
    swap(nums, more, R);
    return {less + 1, more};
}


//堆排序
// 某个数现在处在index位置，往上继续移动
void heapInsert(vector<int> & arr, int index){
    while (arr[index] > arr[(index - 1) / 2]){  //当前的数大于父位置的数
        swap(arr, index, (index - 1) / 2);
        index = (index - 1) / 2;
    }
}
//某个数在index位置，能否往下移动
void heapify(vector<int> & arr, int index, int heapSize){
    int left = index * 2 + 1;   //左孩子的下标
    while (left < heapSize){
        //两个孩子中，谁的值大，把下标给largest
        int largest = left + 1 < heapSize && arr[left + 1] > arr[left] ? left + 1 : left;
        //父和较大的孩子之间，谁的值大，把下标给largest
        largest = arr[largest] > arr[index] ? largest : index;
        if(largest == index){
            break;
        }
        swap(arr, largest, index);
        index = largest;
        left = index * 2 + 1;
    }
}
void heapSort(vector<int> & arr){
    if(arr.size() < 2){
        return;
    }
    // 用户一次只给一个数: O(NlogN)
    for (int i = 0; i < arr.size(); i++){   //O(N)
        heapInsert(arr, i); //O(logN)
    }
    // 用户一次给出所有的数: O(N)
    // for (int i = arr.size() - 1; i >= 0; i--){
    //     heapify(arr, i, arr.size());
    // }
    int heapSize = arr.size();
    swap(arr, 0, --heapSize);       //0位置的数与堆上最后一个数做交换
    while (heapSize > 0){           //O(N)
        heapify(arr, 0, heapSize);  //O(logN)
        swap(arr, 0, --heapSize);   //O(1)
    }
}

//小根堆的应用
void sortedArrDistanceLessK(vector<int>& arr, int k){
    // 默认大根堆，greater -> 小根堆
    priority_queue<int, vector<int>, greater<int>> q;
    int index = 0;
    for(; index <= min((int)arr.size(), k); index++){
        q.push(arr[index]);
    }
    int i = 0;
    for(; index < arr.size(); i++, index++){
        q.push(arr[index]);
        arr[i] = q.top();
        q.pop();
    }
    while (!q.empty()){
        arr[i++] = q.top();
        q.pop();
    }
}

//基数排序
void radixSort(vector<int>& arr){
    if(arr.size() < 2){
        return;
    }
    radixSort(arr, 0, arr.size() - 1, maxbits(arr));
}
//digit：最大值有几个十进制位
void radixSort(vector<int>& arr, int L, int R, int digit){
    const int radix = 10;
    int i = 0, j = 0;
    vector<int> bucket; //R-L+1
    for (int d = 1; d <= digit; d++){   //有多少个十进制位，就入桶出桶多少次
        // 10个空间
        // count[0] 当前位(d位)是0的数字有多少个
        // count[1] 当前位(d位)是(0和1)的数字有多少个
        // count[2] 当前位(d位)是(0、1和2)的数字有多少个
        // count[i] 当前位(d位)是(0~i)的数字有多少个
        vector<int> count;  //词频表，长度为10
        for(i = L; i <= R; i++){    //个位数字 等于2 的有多少个
            j = getDigit(arr[i], d);
            count[j]++;
        }
        for(i = 1; i < radix; i++){ //前缀和 数组：个位数字 小于等于2 的有多少个
            count[i] += count[i-1];
        }
        for(i = R; i >= L; i--){    //从右往左，先入桶的先出桶 
            j = getDigit(arr[i], d);
            bucket[count[j] - 1] = arr[i];
            count[j]--;
        }
        for(i = L, j = 0; i <= R; i++, j++){
            arr[i] = bucket[j];
        }
    }
}
int maxbits(vector<int>& arr){
    int maxNum = INT_MIN;
    for(int i = 0; i < arr.size(); i++){
        maxNum = maxNum > arr[i] ? maxNum : arr[i];
    }
    int res = 0;
    while (maxNum != 0){
        res++;
        maxNum /= 10;
    }
    return res;
}
int getDigit(int a, int d){
    int res = 0;
    for(int i = 1; i < d; i++){
        a /= 10;
    }
    return a % 10;
}


int main()
{
    vector<int> a;
    a.push_back(3);
    a.push_back(2);
    a.push_back(1);
    a.push_back(5);
    a.push_back(6);
    a.push_back(2);

    for(int i = 0; i < a.size(); i++){
        cout << a[i] << endl;
    }

    cout << getDigit(168, 1) << endl;;

    return 0;
}