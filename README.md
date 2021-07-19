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

### 2.认识O(NlogN)的排序
#### 2.1 使用递归求数组的最大值
```cpp
int process(const vector<int> & arr, int L, int R)
{
    if(L == R)  //base case
        return arr[L];
    int mid = L + ((R - L) >> 1);
    int leftMax = process(arr, L, mid);
    int rightMax = process(arr, mid+1, R);
    return max(leftMax, rightMax);
}
```
#### 2.2 归并排序
小和问题：在一个数组中，每一个数左边比当前数小的数累加起来，叫做这个数组的小和。

例：
```cpp
[1, 3, 4, 2, 5]
1: 0
3: 1
4: 1 + 3
2: 1
5: 1 + 3 + 4 + 2
all = 0 + 1 + 4 + 1 + 10 = 16
```
```cpp
int merge(vector<int> & arr, int L, int M, int R){
    vector<int> help;
    int p1 = L;
    int p2 = M + 1;
    int res = 0;
    while (p1 <= M && p2 <= R){
        res += arr[p1] < arr[p2] ? (R - p2 + 1) * arr[p1] : 0;
        help.push_back(arr[p1] < arr[p2] ? arr[p1++] : arr[p2++]);
    }
    while(p1 <= M){
        help.push_back(p1++);
    }
    while (p2 <= R){
        help.push_back(p2++);
    }
    for(int i = 0; i < help.size(); i++){
        arr[L + i] = help[i];
    }
    return res;
} 

int process(vector<int> & arr, int L, int R){
    if(L == R)
        return 0;
    int mid = L + ((R - L) >> 1);
    return process(arr, L, mid) + process(arr, mid + 1, R) + merge(arr, L, mid, R);
}

int smallSum(vector<int> & arr){
    if(arr.size() < 2){
        return 0;
    }
    return process(arr, 0, arr.size() - 1);
}
```

#### 2.3 快速排序

给定一个数组arr和一个数num，请把小于等于num的数放在数组的左边，大于num的数放在数组的右边。要求时间复杂度为O(N)，空间复杂度为O(1)。

分两种情况：

(1) arr[i] <= num，arr[i]和 <=区的下一个数交换，<=区右扩，i++

(2) arr[i] > num，i++

**荷兰国旗问题**：

给定一个数组arr和一个数num，请把小于num的数放在数组的左边，等于num的数放在数组的中间，大于num的数放在数组的右边。要求时间复杂度为O(N)，空间复杂度为O(1)。

分三种情况：

(1) arr[i] < num，arr[i]和 <区下一个交换，<区右扩，i++

(2) arr[i] == num，i++

(3) arr[i] > num，arr[i]和 >区前一个交换，>区左扩，i不变

#### 2.4 堆排序
小根堆

已知一个几乎有序的数组，几乎有序是指，如果把数组排好顺序的话，每个元素移动的距离可以不超过k，并且k相对于数组来说比较小。请选择一个合适的排序算法针对这个数据进行排序。

思路：假设k=6，准备一个小根堆，首先遍历前7个数，小根堆的最小值一定在0位置。

复杂度：O(N*logk)
```cpp
void sortedArrDistanceLessK(vector<int> & arr, int k){
    vector<int> v;
    make_heap(v.begin(), v.end(), greater<int>());
    int index = 0;
    for(; index <= min((int)arr.size(), k); index++){
        v.push_back(arr[index]);
        push_heap(v.begin(), v.end());
    }
    int i = 0;
    for(; index < arr.size(); i++, index++){
        v.push_back(arr[index]);
        push_heap(v.begin(), v.end());

        arr[i] = v[0];
        pop_heap(v.begin(), v.end());
        v.pop_back();  
    }
    while (!v.empty()){
        arr[i++] = v[0];
        pop_heap(v.begin(), v.end());
        v.pop_back();  
    }
}
```
### 4. 链表
单链表的节点结构
```cpp
template <typename T>
class Node{
    T value;
    Node *next;
};
```
双链表的节点结构
```cpp
template <typename T>
class Node{
    T value;
    Node *next;
    Node *last;
};
```
单链表和双链表结构只需要给定一个头部节点head，就可以找到剩下的所有节点。

**1. 反转单向和双向链表**

[题目]：分别实现反转单向链表和反转双向链表的函数

[要求]：如果链表的长度为N，时间复杂度要求为O(N)，额外空间复杂度要求为O(1)

反转单向链表
```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
ListNode* reverseList(ListNode* head) {
    ListNode* prev = NULL;
    ListNode* curr = head;
    while(curr){
        ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
```
反转双向链表
```cpp
ListNode* reverseList(ListNode* head) {
    ListNode* prev = NULL;
    ListNode* curr = head;
    while(curr){
        ListNode* next = curr->next;
        curr->next = prev;
        curr->last = next;
        prev = curr;
        curr = next;
    }
    return prev;
}
```

**2. 打印两个有序链表的公共部分**

[题目]：给定两个有序链表的头指针head1和head2，打印两个链表的公共部分

[要求]：如果链表的长度为N，时间复杂度要求为O(N)，额外空间复杂度要求为O(1)

```cpp
void printPublicList(ListNode* head1, ListNode* head2) {
    ListNode* p1 = head1;
    ListNode* p2 = head2;
    while (p1 != NULL && p2 != NULL) {
        if (p1->value == p2->value) {
            cout << p1->value << endl;
            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p1->value < p2->value) {
            p1 = p1->next;
        }
        else {
            p2 = p2->next;
        }
    }
}
```



