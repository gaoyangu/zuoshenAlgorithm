#include <iostream>
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