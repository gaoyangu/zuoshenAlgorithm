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
    while (p1 != nullptr && p2 != nullptr) {
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

**3. 判断一个链表是否为回文结构**

[题目] 给定一个单链表的头节点head，请判断该链表是否为回文结构。

[例子] 1->2->1，返回true；1->2->2->1，返回true；15->6->15，返回true；1->2->3，返回false。

[要求] 如果链表长度为N，时间复杂度达到O(N)，额外空间复杂度达到O(1)。

方法一：全部压到栈中。额外空间复杂度O(N)
```cpp
bool isPalindrome1(ListNode* head) {
    stack<ListNode*> s;
    ListNode* cur = head;
    while (cur != nullptr) {
        s.push(cur);
        cur = cur->next;
    }
    while (head != nullptr) {
        if (head->value != s.top()->value) {
            return false;
        }
        s.pop();
        head = head->next;
    }
    return true;
}
```
方法二：只把右侧压到栈中。额外空间复杂度O(N/2)
```cpp
bool isPalindrome2(ListNode* head) {
    if(head == nullptr || head->next == nullptr) {
        return true;
    }
    ListNode* right = head->next;
    ListNode* cur = head;
    while (cur->next != nullptr && cur->next->next != nullptr){
        right = right->next;
        cur = cur->next->next;
    }
    stack<ListNode*> s;
    while (right != nullptr){
        s.push(right);
        right = right->next;
    }
    while (!s.empty()){
        if (head->value != s.top()->value) {
            return false;
        }
        s.pop();
        head = head->next;
    }
    return true;
}
```
方法三：额外空间复杂度O(1)
```cpp
bool isPalindrome3(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return true;
    }

    ListNode* n1 = head;
    ListNode* n2 = head;
    while (n2->next != nullptr && n2->next->next != nullptr) {
        n1 = n1->next;          // n1 -> mid
        n2 = n2->next->next;    // n2 -> end
    }
    n2 = n1->next;      // n2 -> right part first node
    n1->next = nullptr; // mid.next -> null
    ListNode* n3 = nullptr;
    while (n2 != nullptr){  // right part convert
        n3 = n2->next;
        n2->next = n1;
        n1 = n2;
        n2 = n3;
    }
    n3 = n1;
    n2 = head;

    bool res = true;
    while (n1 != nullptr && n2 != nullptr){ // check palindrome
        if (n1->value != n2->value) {
            res = false;
            break;
        }
        n1 = n1->next;
        n2 = n2->next;
    }

    n1 = n3->next;
    n3->next = nullptr;
    while (n1 != nullptr){  // recover list
        n2 = n1->next;
        n1->next = n3;
        n3 = n1;
        n1 = n2;
    }
    return res;
}
```

**4. 将单向链表按某值划分成左边小、中间相等、右边大的形式**

[题目]：给定一个单链表的头节点head，节点的值类型是整型，再给定一个整数pivot。实现一个调整链表的函数，将链表调整为左部分都是值小于pivot的节点，中间部分都是值等于pivot的节点，右部分都是值大于pivot的节点。

[进阶]：在实现原问题功能的基础上增加如下的要求

[要求]：调整后所有小于pivot的节点之间的相对顺序和调整前一样

[要求]：调整后所有等于pivot的节点之间的相对顺序和调整前一样

[要求]：调整后所有大于pivot的节点之间的相对顺序和调整前一样

[要求]：时间复杂度请达到O(N)，额外空间复杂度请达到O(1)

笔试：
```cpp
申请一个Node类型的数组，在数组上进行partitation
```
面试：
```cpp
ListNode* listPartition2(ListNode* head, int pivot){
    ListNode* sH = nullptr;
    ListNode* sT = nullptr;
    ListNode* eH = nullptr;
    ListNode* eT = nullptr;
    ListNode* bH = nullptr;
    ListNode* bT = nullptr;

    ListNode* next = nullptr;
    while (head != nullptr){
        next = head->next;
        head->next = nullptr;
        if (head->value < pivot) {
            if (sH == nullptr) {
                sH = head;
                sT = head;
            }
            else {
                sT->next = head;    //将旧的尾巴的next连向当前节点
                sT = head;          //将当前节点变成新的尾巴
            }
        }
        else if (head->value == pivot) {
            if (eH == nullptr) {
                eH = head;
                eT = head;
            }
            else {
                eT->next = head;
                eT = head;
            }
        }
        else {
            if (bH == nullptr) {
                bH = head;
                bT = head;
            }
            else {
                bT->next = head;
                bT = head;
            }
        }
        head = next;
    }
    // small and equal reconnect
    if (sT != nullptr) {    //如果有小于区域
        sT->next = eH;
        eT = (eT == nullptr ? sT : eT);
    }
    // all reconnect
    if (eT != nullptr) {
        eT->next = bH;
    }
    return sH != nullptr ? sH : (eH != nullptr ? eH : bH);
}  
```

**5. 复制含有随机指针节点的链表**

[题目]：一种特殊的单链表节点类描述如下
```cpp
class Node{
    Node(int val){
        value = val;
    }

    int value;
    Node *next;
    Node *rand;
}
```
rand指针是单链表节点结构中新增的指针， rand可能指向链表中的任意一个节点，也可能指向null。给定一个由Node节点类型组成的无环单链表的头节点head，请实现一个函数完成这个链表的复制，并返回复制的新链表的头节点。

[要求]：时间复杂度O(N)，额外空间复杂度O(1)

使用哈希表，额外空间复杂度：O(N)
```cpp
ListNode* copyListWithRand1(ListNode* head) {
    unordered_map<ListNode*, ListNode*> map;    //key: old node, value: new node
    ListNode* cur = head;
    while (cur != nullptr){
        map.insert(cur, new ListNode(cur->value));
        cur = cur->next;
    }
    cur = head;
    while (cur != nullptr){
        map.at(cur)->next = map.at(cur->next);
        map.at(cur)->rand = map.at(cur->rand);
        cur = cur->next;
    }
    return map.at(head);
}
```

额外空间复杂度：O(1)
```cpp
ListNode* copyListWithRand2(ListNode* head) {
    if (head == nullptr) {
        return nullptr;
    }
    ListNode* cur = head;
    ListNode* next = nullptr;
    while (cur != nullptr) {
        next = cur->next;
        cur->next = new ListNode(cur->value);
        cur->next->next = next;
        cur = next;
    }
    cur = head;
    ListNode* curCopy = nullptr;
    while (cur != nullptr){
        next = cur->next->next;
        curCopy = cur->next;
        curCopy->rand = cur->rand != nullptr ? cur->rand->next : nullptr;
        cur = next;
    }
    ListNode* res = head->next;
    cur = head;
    while (cur != nullptr){
        next = cur->next->next;
        curCopy = cur->next;
        cur->next = next;
        curCopy->next = (next != nullptr ? next->next : nullptr);
        cur = next;
    }
    return res;
}
```

**6. 两个单链表相交的一系列问题**

[题目]：给定两个可能有环也可能无环的单链表，头节点head1和head2。请实现一个函数，如果两个链表相交，请返回相交的第一个节点。如果不相交，返回null

[要求]：如果两个链表长度之和为N，时间复杂度请达到O(N)，额外空间复杂度请达到O(1)

```cpp
// 找到链表第一个入环节点，如果无环，返回null
ListNode* getLoopNode(ListNode* head) {
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
        return nullptr;
    }
    ListNode* n1 = head->next;          // n1 -> slow
    ListNode* n2 = head->next->next;    // n2 -> slow
    while (n1 != n2){
        if (n2->next == nullptr || n2->next->next == nullptr) {
            return nullptr;
        }
        n2 = n2->next->next;
        n1 = n1->next;
    }
    n2 = head;
    while (n1 != n2){
        n1 = n1->next;
        n2 = n2->next;
    }
    return n1;
}
// 如果两个链表都无环，返回第一个相交节点，如果不相交，返回null
ListNode* noLoop(ListNode* head1, ListNode* head2) {
    if (head1 == nullptr || head2 == nullptr) {
        return nullptr;
    }
    ListNode* cur1 = head1;
    ListNode* cur2 = head2;
    int n = 0;
    while (cur1->next != nullptr){
        n++;
        cur1 = cur1->next;
    }
    while (cur2->next != nullptr) {
        n--;
        cur2 = cur2->next;
    }
    if (cur1 != cur2) {
        return nullptr;
    }
    cur1 = n > 0 ? head1 : head2;
    cur2 = (cur1 == head1 ? head2 : head1);
    n = abs(n);
    while (n != 0){
        n--;
        cur1 = cur1->next;
    }
    while (cur1 != cur2){
        cur1 = cur1->next;
        cur2 = cur2->next;
    }
    return cur1;
}
// 两个有环链表，返回第一个相交节点，不相交返回null
ListNode* bothLoop(ListNode* head1, ListNode* loop1, ListNode* head2, ListNode* loop2) {
    ListNode* cur1 = nullptr;
    ListNode* cur2 = nullptr;
    if (loop1 == loop2) {
        cur1 = head1;
        cur2 = head2;
        int n = 0;
        while (cur1 != loop1){
            n++;
            cur1 = cur1->next;
        }
        while (cur2 != loop2) {
            n--;
            cur2 = cur2->next;
        }
        cur1 = n > 0 ? head1 : head2;
        cur2 = (cur1 == head1 ? head2 : head1);
        n = abs(n);
        while (n != 0) {
            n--;
            cur1 = cur1->next;
        }
        while (cur1 != cur2){
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        return cur1;
    }
    else {
        cur1 = loop1->next;
        while (cur1 != loop1) {
            if (cur1 == loop2) {
                return loop1;
            }
            cur1 = cur1->next;
        }
    }
    return nullptr;
}
ListNode* getIntersectNode(ListNode* head1, ListNode* head2) {
    if (head1 == nullptr || head2 == nullptr) {
        return nullptr;
    }
    ListNode* loop1 = getLoopNode(head1);
    ListNode* loop2 = getLoopNode(head2);
    if (loop1 == nullptr && loop2 == nullptr) {
        return noLoop(head1, head2);
    }
    if (loop1 != nullptr && loop2 == nullptr) {
        return bothLoop(head1, loop1, head2, loop2);
    }
    return nullptr;
}
```







