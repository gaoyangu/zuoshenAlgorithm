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

ListNode* copyListWithRand1(ListNode* head) {
    unordered_map<ListNode*, ListNode*> map;    //key: old node, value: new node
    ListNode* cur = head;
    while (cur != nullptr){
        map.insert(pair<ListNode*, ListNode*>(cur, new ListNode(cur->value)));
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