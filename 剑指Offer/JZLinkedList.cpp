#include <iostream>
#include <unordered_map>
using namespace std;

struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};

// JZ36 两个链表的第一个公共结点
// todo: 简短写法
class Solution36 {
public:
    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        int i = 0;
        ListNode* cur = pHead1;
        while(cur){
            i++;
            cur = cur->next;
        }
        cur = pHead2;
        while(cur){
            i--;
            cur = cur->next;
        }
        // 较长的链表
        cur = i >= 0 ? pHead1 : pHead2; 
        // 较短的链表
        pHead1 = cur == pHead1 ? pHead2 : pHead1;
        i = abs(i);
        while (i > 0){
            cur = cur->next;
            i--;
        }
        while(cur && pHead1){
            if(cur->val == pHead1->val){
                return cur;
            }
            else{
                cur = cur->next;
                pHead1 = pHead1->next;               
            }
        }
        return cur;
    }
};

// JZ56 删除链表中重复的结点
// todo: 递归写法
class Solution56 {
public:
    ListNode* deleteDuplication(ListNode* pHead) {
        ListNode* vhead = new ListNode(-1);
        vhead->next = pHead;
        ListNode* pre = vhead;
        ListNode* cur = pHead;
        while(cur){
            if(cur->next && cur->val == cur->next->val){
                cur = cur->next;
                while(cur->next && cur->val == cur->next->val){
                    cur = cur->next;
                }
                cur = cur->next;
                pre->next = cur;
            }
            else{
                pre = cur;
                cur = cur->next;
            }
        }
        return vhead->next;
    }
};

// JZ25 复杂链表的复制
struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};
// 额外空间复杂度：O(N)
class Solution25a {
public:
    RandomListNode* Clone(RandomListNode* pHead) {
        unordered_map<RandomListNode*, RandomListNode*> m;
        RandomListNode* cur = pHead;
        while(cur){
            m.insert(make_pair(cur, new RandomListNode(cur->label)));
            cur = cur->next;
        }
        RandomListNode* vhead = new RandomListNode(-1);
        cur = m[pHead];
        vhead->next = cur;
        while(cur){
            cur->next = m[pHead->next];
            cur->random = m[pHead->random];
            cur = cur->next;
            pHead = pHead->next;
        }
        return vhead->next;
    }
};
// 额外空间复杂度：O(1)
class Solution25b {
public:
    RandomListNode* Clone(RandomListNode* pHead) {
        if(!pHead){
            return pHead;
        }
        RandomListNode* cur = pHead;
        while(cur){
            RandomListNode* next = cur->next;
            cur->next = new RandomListNode(cur->label);
            cur->next->next = next;
            cur = cur->next->next;
        }
        cur = pHead;
        while(cur){
            cur->next->random = cur->random != nullptr ? cur->random->next : nullptr;
            cur = cur->next->next;
        }
        RandomListNode* vhead = pHead->next;
        cur = pHead;
        RandomListNode* curCopy = nullptr;
        RandomListNode* next = nullptr;
        while(cur){
            next = cur->next->next;
            curCopy = cur->next;
            cur->next = next;
            curCopy->next = next != nullptr ? next->next : nullptr;
            cur = next;
        }
        return vhead;
    }
};