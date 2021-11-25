#include <iostream>
#include <list>
using namespace std;

// 二叉树节点间的最大距离问题
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), righ(right）{}
 };

class Info {
public:
    Info(int dis, int h) : maxDistance(dis), height(h) {}
    int maxDistance;
    int height;
};
Info process(TreeNode* root){
    if(root == nullptr){
        return Info(0,0);
    }
    Info leftInfo = process(root->left);
    Info rightInfo = process(root->right);
    // Info
    int p1 = leftInfo.maxDistance;
    int p2 = rightInfo.maxDistance;
    int p3 = leftInfo.height + rightInfo.height + 1;
    int maxDistance = max(p3, max(p1, p2));
    int height = max(leftInfo.height, rightInfo.height) + 1;
    return Info(maxDistance, height);
}
int diameterOfBinaryTree(TreeNode* root) {
    if(root == nullptr){
        return 0;
    }
    return process(root).maxDistance - 1;
}


// 派对的最大快乐值
class Employee {
public:
    int happy; //这名员工可以带来的快乐值 
    list<Employee*> nexts; //这名员工有哪些直接下级 
};

class InfoHappy {
public:
    InfoHappy(int come, int nocome) : comeMaxhappy(come), nocomeMaxhappy(nocome){ }
    int comeMaxhappy;
    int nocomeMaxhappy;
};

InfoHappy* process(Employee* x) {
    if (x->nexts.empty()) {
        return new InfoHappy(x->happy, 0);
    }
    int com = x->happy; // x 来的情况下，整棵树最大收益
    int nocom = 0;      // x 不来的情况下，整棵树最大收益
    for (Employee* next : x->nexts) {
        InfoHappy* nextinfo = process(next);
        com += nextinfo->nocomeMaxhappy;
        nocom += max(nextinfo->comeMaxhappy, nextinfo->nocomeMaxhappy);
    }
    return new InfoHappy(com, nocom);
}


// Morris 遍历
void morris(Node* head) {
    if (head == nullptr) {
        return;
    }
    Node* cur = head;
    Node* mostRight = nullptr;
    while (cur) {
        mostRight = cur->left;
        if (mostRight != nullptr) {    // 如果有左子树
            while (mostRight->right && mostRight->right != cur) {
                mostRight = mostRight->right;
            }
            // mostRight 变成了cur左子树上的最右节点
            if (mostRight->right == nullptr) {
                mostRight->right = cur;
                cur = cur->left;
                continue;
            }
            else {  // mostRight == cur
                mostRight->right = nullptr;
            }
        }
        cur = cur->right;
    }
}

// 先序遍历
void morrisPre(Node* head) {
    if (!head) {
        return;
    }
    Node* cur = head;
    Node* mostRight = nullptr;
    while (cur) {
        mostRight = cur->left;
        if (mostRight != nullptr) {    // 如果有左子树
            while (mostRight->right && mostRight->right != cur) {
                mostRight = mostRight->right;
            }
            // mostRight 变成了cur左子树上的最右节点
            if (mostRight->right == nullptr) {
                cout << cur->value << endl;
                mostRight->right = cur;
                cur = cur->left;
                continue;
            }
            else {  // mostRight == cur
                mostRight->right = nullptr;
            }
        }
        else{
            cout << cur->value << endl;
        }
        cur = cur->right;
    }
}

// 中序遍历
void morrisIn(Node* head) {
    if (!head) {
        return;
    }
    Node* cur = head;
    Node* mostRight = nullptr;
    while (cur) {
        mostRight = cur->left;
        if (mostRight != nullptr) {    // 如果有左子树
            while (mostRight->right && mostRight->right != cur) {
                mostRight = mostRight->right;
            }
            // mostRight 变成了cur左子树上的最右节点
            if (mostRight->right == nullptr) {
                mostRight->right = cur;
                cur = cur->left;
                continue;
            }
            else {  // mostRight == cur
                mostRight->right = nullptr;
            }
        }
        cout << cur->value << endl;
        cur = cur->right;
    }
}

// 后序遍历
// 反转链表
Node* reverseEdge(Node* from){
    Node* pre = nullptr;
    Node* next = nullptr;
    while(from){
        next = from->right;
        from->right = pre;
        pre = from;
        from = next;
    }
    return pre;
}
// 以 x 为头的树，逆序打印这棵树的右边界
void printEdge(Node* x){
    Node* tail = reverseEdge(x);
    Node* cur = tail;
    while(cur){
        cout << cur->value << " " << endl;
        cur = cur->right;
    }
    reverseEdge(x);
}
void morrisPos(Node* head) {
    if (!head) {
        return;
    }
    Node* cur = head;
    Node* mostRight = nullptr;
    while (cur) {
        mostRight = cur->left;
        if (mostRight != nullptr) {    // 如果有左子树
            while (mostRight->right && mostRight->right != cur) {
                mostRight = mostRight->right;
            }
            // mostRight 变成了cur左子树上的最右节点
            if (mostRight->right == nullptr) {
                mostRight->right = cur;
                cur = cur->left;
                continue;
            }
            else {  // mostRight == cur
                mostRight->right = nullptr;
                printEdge(cur->left);
            }
        }
        cur = cur->right;
    }
    printEdge(head);
    cout << endl;
}


// 是否是搜索二叉树
bool isBST(Node* head) {
    if (!head) {
        return true;
    }
    Node* cur = head;
    Node* mostRight = nullptr;
    int preValue = INTMAX_MIN;
    while (cur) {
        mostRight = cur->left;
        if (mostRight != nullptr) {    // 如果有左子树
            while (mostRight->right && mostRight->right != cur) {
                mostRight = mostRight->right;
            }
            // mostRight 变成了cur左子树上的最右节点
            if (mostRight->right == nullptr) {
                mostRight->right = cur;
                cur = cur->left;
                continue;
            }
            else {  // mostRight == cur
                mostRight->right = nullptr;
            }
        }
        if(cur->value <= preValue){
            return false;
        }
        preValue = cur->value;
        cur = cur->right;
    }
    return true;
}