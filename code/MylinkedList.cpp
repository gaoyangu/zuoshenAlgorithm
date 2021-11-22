#include <iostream>
#include <stack>
#include <unordered_map>

using namespace std;

 struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };


// 反转单向链表
ListNode* reverseList(ListNode* head) {
    ListNode* pre = nullptr;
    ListNode* cur = head;
    while(cur){
        ListNode* next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    return pre;
}


// 打印两个有序链表的公共部分
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


// 判断一个链表是否为回文结构
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

bool isPalindrome2(ListNode* head) {
    if(head == nullptr || head->next == nullptr){
        return true;
    }
    ListNode* fast = head->next;
    ListNode* slow = head;
    while(fast->next && fast->next->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    stack<ListNode*> s;
    while(slow != nullptr){
        s.push(slow);
        slow = slow->next;
    }
    while(!s.empty()){
        if(head->val != s.top()->val){
            return false;
        }
        s.pop();
        head = head->next;
    }
    return true;
}

bool isPalindrome3(ListNode* head) {
    if(head == nullptr || head->next == nullptr){
        return true;
    }

    // 找到前半部分链表的尾节点并反转后半部分链表
    ListNode* firstHalfEnd = endOfFirstHalf(head);
    ListNode* secondHalfStart = reverseList(firstHalfEnd->next);

    // 判断是否回文
    ListNode* p1 = head;
    ListNode* p2 = secondHalfStart;
    bool result = true;
    while(p2 != nullptr){
        if(p1->val != p2->val){
            result = false;
            break;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    
    // 还原链表并返回结果
    firstHalfEnd->next = reverseList(secondHalfStart);
    return result;
}
ListNode* endOfFirstHalf(ListNode* head){
    ListNode* fast = head;
    ListNode* slow = head;
    while(fast->next && fast->next->next){
        slow = slow->next;      // slow -> mid
        fast = fast->next->next;// fast -> end
    }
    return slow;
}


// 将单向链表按某值划分成左边小、中间相等、右边大的形式
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


// 复制含有随机指针节点的链表
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
Node* copyRandomList(Node* head) {
    if(head == NULL){
        return NULL;
    }
    Node* cur = head;
    unordered_map<Node*, Node*> map;
    while(cur != NULL){
        //map.insert(pair<Node*, Node*>(cur, new Node(cur->val)));
        map[cur] = new Node(cur->val);
        cur = cur->next;
    }
    cur = head;
    while(cur != NULL){
        map[cur]->next = map[cur->next];
        map[cur]->random = map[cur->random];
        cur = cur->next;
    }
    return map[head];
}

Node* copyRandomList(Node* head) {
    if(head == NULL){
        return NULL;
    }
    Node* cur = head;
    Node* next = NULL;
    // 1. 复制各节点，并构建拼接链表
    while(cur != NULL){
        next = cur->next;
        cur->next = new Node(cur->val);
        cur->next->next = next;
        cur = next;
    }
    cur = head;
    Node* copyNode = NULL;
    // 2. 构建各新节点的 random 指向
    while(cur != NULL){
        next = cur->next->next;
        copyNode = cur->next;
        copyNode->random = cur->random != NULL ? cur->random->next : NULL;
        cur = next;
    }
    Node* res = head->next;
    cur = head;
    // 3. 拆分两个链表
    while(cur != NULL){
        next = cur->next->next;
        copyNode = cur->next;
        copyNode->next = (next != NULL ? next->next : NULL);
        cur->next = next;
        cur = next;
    }
    return res;
}


// 找到链表第一个入环节点，如果无环，返回null
ListNode* getLoopNode(ListNode* head) {
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
        return nullptr;
    }
    ListNode* n1 = head->next;          // n1 -> slow
    ListNode* n2 = head->next->next;    // n2 -> fast
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

int main()
{
    MylinkedList m1;
    m1.addAtIndex(0,1);
    m1.addAtIndex(1,2);
    m1.addAtIndex(2,3);
    m1.addAtIndex(3,2);
    m1.addAtIndex(4,1);

    cout << isPalindrome3(m1.head);
}