#include <iostream>

using namespace std;

// 双向链表

class ListNode {
public:
    ListNode(int v) : value(v), prev(NULL), next(NULL) {}

    int value;
    ListNode* prev;
    ListNode* next;
};

class MylinkedList {
public:
    /** Initialize your data structure here. */
    MylinkedList() : size(0), head(NULL), tail(NULL) {}

    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index) {
        if (index < 0 || index > size) {
            return -1;
        }
        ListNode* p = head;
        for (int i = 0; i < index; i++) {
            p = p->next;
        }
        return p->value;
    }

    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val) {
        if (head != NULL) {
            ListNode* node = new ListNode(val);
            node->next = head;
            head->prev = node;
            head = node;
        }
        else {
            head = new ListNode(val);
            tail = head;
        }
        size++;
    }

    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
        if (tail != NULL) {
            ListNode* node = new ListNode(val);
            node->prev = tail;
            tail->next = node;
            tail = node;
        }
        else {
            tail = new ListNode(val);
            head = tail;
        }
        size++;
    }

    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val) {
        if (index <= 0) {
            addAtHead(val);
            return;
        }
        if (index == size) {
            addAtTail(val);
            return;
        }
        if (index > size) {
            return;
        }

        ListNode* p = NULL, * cur = head;
        for (int i = 0; i < index; i++) {
            p = cur;
            cur = cur->next;
            i++;
        }

        ListNode* node = new ListNode(val);
        p->next = node;
        node->prev = p;
        node->next = cur;
        cur->prev = node;
        size++;
    }

    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {
        if (!head) {
            return;
        }
        if (index == 0) {
            ListNode* del = head;
            head = head->next;
            if (head) {
                head->prev = NULL;
            }
            else {
                tail = NULL;
            }
            delete del;
            size--;
            return;
        }
        if (index == size - 1) {
            ListNode* del = tail;
            tail = tail->prev;
            if (tail) {
                tail->next = NULL;
            }
            delete del;
            size--;
            return;
        }

        ListNode* p = NULL, * cur = head;
        for (int i = 0; i < index; i++) {
            p = cur;
            cur = cur->next;
            i++;
        }
        ListNode* del = cur;
        p->next = cur->next;
        if (cur->next) {
            cur->next->prev = p;
        }
        delete del;
        size--;
        return;
    }

    int size;
    ListNode* head;
    ListNode* tail;
};


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

int main()
{
    MylinkedList m1;
    m1.addAtTail(1);
    m1.addAtTail(2);
    m1.addAtTail(3);
    m1.addAtTail(4);

    MylinkedList m2;
    m2.addAtTail(1);
    m2.addAtTail(2);
    m2.addAtTail(3);
    m2.addAtTail(4);

    printPublicList(m1.head, m2.head);

}