#include <iostream>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <list>
#include <limits.h>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };


// 先序
vector<int> preorderTraversal(TreeNode* root) {
    vector<int> res;
    if(!root){
        return res;
    }
    stack<TreeNode*> s;
    s.push(root);
    while(!s.empty()){
        TreeNode* cur = s.top();
        s.pop();
        res.push_back(cur->val);
        if(cur->right){
            s.push(cur->right);
        }
        if(cur->left){
            s.push(cur->left);
        }
    }
    return res;
}

// 后序
vector<int> postorderTraversal(TreeNode* root) {
    vector<int> res;
    if(!root){
        return res;
    }
    stack<TreeNode*> s;
    s.push(root);
    stack<TreeNode*> sRes;
    while(!s.empty()){
        TreeNode* cur = s.top();
        s.pop();
        sRes.push(cur);
        if(cur->left){
            s.push(cur->left);
        }
        if(cur->right){
            s.push(cur->right);
        }
    }
    while(!sRes.empty()){
        res.push_back(sRes.top()->val);
        sRes.pop();
    }
    return res;
}

// 中序
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> res;
    stack<TreeNode*> s;
    while(!s.empty() || root){
        while(root){
            s.push(root);
            root = root->left;      
        }
        root = s.top();
        s.pop();
        res.push_back(root->val);
        root = root->right;
    }
    return res;
}

// 宽度优先遍历
vector<int> levelOrder(TreeNode* root) {
    vector<int> res;
    if(!root){
        return res;
    }
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        TreeNode* cur = q.front();
        res.push_back(cur->val);
        q.pop();
        if(cur->left){
            q.push(cur->left);
        }
        if(cur->right){
            q.push(cur->right);
        }
    }
    return res;
}


// 二叉树的宽度
// 使用哈希表
int getMaxWidth(TreeNode* head){
    if(head == nullptr){
        return 0;
    }
    int maxWidth = 0;   // 哪一层的节点数目是最多的
    int curWidth = 0;
    int curLevel = 0;   // 当前在哪一层
    unordered_map<TreeNode*, int> levelMap;     //节点在第几层
    levelMap.insert(pair<TreeNode*, int>(head, 1));
    queue<TreeNode*> q;
    q.push(head);
    TreeNode* node = nullptr;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    while (!q.empty()){
        node = q.front();
        left = node->left;
        right = node->right;
        q.pop();
        int curLevelNodes = levelMap.at(node);  // 节点所在的层数
        if(curLevelNodes == curLevel){
            curWidth++;
        }
        else{
            maxWidth = max(maxWidth, curWidth);
            curLevel++;
            curLevelNodes = 1;
        }
        if(left != nullptr){
            levelMap.insert(pair<TreeNode*, int>(left, levelMap.at(node) + 1));
            q.push(left);
        }
        if(right != nullptr){
            levelMap.insert(pair<TreeNode*, int>(right, levelMap.at(node) + 1));
            q.push(right);
        }
    }
    return maxWidth;
}
// 不使用哈希表
int getMaxWidth2(TreeNode* root) {
    if(!root){
        return 0;
    }
    queue<TreeNode*> q;
    q.push(root);
    int maxWidth = -1;
    int curLevelNodes = 0;      // 当前层的节点数
    TreeNode* curEnd = root;    // 当前层的最后一个节点
    TreeNode* nextEnd = nullptr;// 下一层的最后一个节点
    while(!q.empty()){
        TreeNode* cur = q.front();
        q.pop();
        curLevelNodes++;
        if(cur->left){
            q.push(cur->left);
            nextEnd = cur->left;
        }
        if(cur->right){
            q.push(cur->right);
            nextEnd = cur->right;
        }
        if(cur == curEnd){
            maxWidth = max(maxWidth, curLevelNodes);
            curEnd = nextEnd;
            nextEnd = nullptr;
        }
    }
    return maxWidth;
}


// 搜索二叉树
// 递归
long long preValue = (long long)INT_MIN - 1;
bool isValidBST(TreeNode* root) {
    if(!root){
        return true;
    }
    bool isLeftBST = isValidBST(root->left);
    if(!isLeftBST){
        return false;
    }
    if(root->val <= preValue){
        return false;
    }
    preValue = root->val;
    return isValidBST(root->right);
}
// 非递归
bool isValidBST2(TreeNode* root) {
    if(!root){
        return true;
    }
    long long preValue = (long long)INT_MIN - 1;
    stack<TreeNode*> s;
    TreeNode* cur = root;
    while(!s.empty() || cur){
        while(cur){
            s.push(cur);
            cur = cur->left;
        }
        cur = s.top();
        s.pop();
        if(cur->val <= preValue){
            return false;
        }
        preValue = cur->val;
        cur = cur->right;
    }
    return true;
}
// 二叉树套路解法
// class ReturnData{
// public:
//     ReturnData(bool isB, int mi, int ma) : isBST(isB), min(mi), max(ma) { }
//     bool isBST;
//     int min;
//     int max;
// };
// ReturnData process(Node* head){
//     if(head == nullptr){
//         return ReturnData(false, 0, 0);
//     }
//     ReturnData leftData = process(head->left);
//     ReturnData rightData = process(head->right);
//     int minValue = head->value;
//     int maxValue = head->value;
//     if(leftData.isBST != false){
//         minValue = min(minValue, leftData.min);
//         maxValue = max(maxValue, leftData.max);
//     }
//     if(rightData.isBST != false){
//         minValue = min(minValue, rightData.min);
//         maxValue = max(maxValue, rightData.max);
//     }
//     bool isBST = true;
//     if(leftData.isBST != false && (!leftData.isBST || leftData.max >= head->value)){
//         isBST = false;
//     }
//     if(rightData.isBST != false && (!rightData.isBST || head->value >= rightData.max)){
//         isBST = false;
//     }
//     return ReturnData(isBST, minValue, maxValue);
// }


// 完全二叉树
bool isCompleteTree(TreeNode* root) {
    if(!root){
        return true;
    }
    bool isLeaf = false;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        TreeNode* cur = q.front();
        q.pop();
        if((cur->right && !cur->left) || (isLeaf && (cur->left || cur->right))){
            return false;
        }
        if(cur->left){
            q.push(cur->left);
        }
        if(cur->right){
            q.push(cur->right);
        }
        if(!cur->left || !cur->right){
            isLeaf = true;
        }
    }
    return true;
}


// 满二叉树
struct Info{
    Info(int h, int n) : height(h),nodes(n){ }
    int height;
    int nodes;
};
Info f(TreeNode* head){
    if(!head){
        return Info(0, 0);
    }
    Info leftData = f(head->left);
    Info rightData = f(head->right);
    int height = max(leftData.height, rightData.height) + 1;
    int nodes = leftData.nodes + rightData.nodes + 1;
    return Info(height, nodes);
}
bool isFBT(TreeNode* head){
    if(head == nullptr){
        return true;
    }  
    Info data = f(head);
    return data.nodes == ((data.height << 1) - 1);
}


// 平衡二叉树
struct ReturnType{
    bool m_isBal;
    int m_height;
    ReturnType(bool isBal, int height) : m_isBal(isBal), m_height(height) { }
};
ReturnType process(TreeNode* root){
    if(!root){
        return ReturnType(true, 0);
    }
    ReturnType leftInfo = process(root->left);
    ReturnType rightInfo = process(root->right);
    bool isBal = leftInfo.m_isBal && rightInfo.m_isBal && abs(leftInfo.m_height - rightInfo.m_height) < 2;
    int height = max(leftInfo.m_height, rightInfo.m_height) + 1;
    return ReturnType(isBal, height);
}
bool isBalanced(TreeNode* root) {
    if(!root){
        return true;
    }
    return process(root).m_isBal;
}


// 最低公共祖先节点
// 方法一
void process(TreeNode* root, unordered_map<TreeNode*, TreeNode*>& fatherMap){
    if(!root){
        return;
    }
    fatherMap.insert(pair<TreeNode*, TreeNode*>(root->left, root));
    fatherMap.insert(pair<TreeNode*, TreeNode*>(root->right, root));
    process(root->left, fatherMap);
    process(root->right, fatherMap);
}
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(!root){
        return NULL;
    }
    unordered_map<TreeNode*, TreeNode*> fatherMap;
    fatherMap.insert(pair<TreeNode*, TreeNode*>(root, root));
    process(root, fatherMap);

    unordered_set<TreeNode*> s;

    TreeNode* cur = p;
    while(cur != fatherMap[cur]){
        s.insert(cur);
        cur = fatherMap[cur];
    }
    s.insert(root);
    
    cur = q;
    while(cur != fatherMap[cur]){
        if(s.find(cur) != s.end()){
            return cur;
        }
        cur = fatherMap[cur];
    }
    return root;
}  
// 方法二
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(!root || root == p || root == q){
        return root;
    }
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    if(left && right){
        return root;
    }
    return left != NULL? left : right;
}


class Node{
public:
    Node(int val) : value(val) { }
    int value;
    Node* left;
    Node* right;
    Node* parent;
};
// 后继节点
Node* getLeftMost(Node* node){
    if(node == nullptr){
        return node;
    }
    while (node->left != nullptr){
        node = node->left;
    }
    return node;
}
Node* getSuccessorNode(Node* node){
    if(node == nullptr){
        return node;
    }
    if(node->right != nullptr){
        return getLeftMost(node->right);
    }
    else{
        Node* parent = node->parent;
        while(parent != nullptr && parent->left != node){
            node = parent;
            parent = node->parent;
        }
        return parent;
    }
}


// 二叉树的序列化和反序列化
// Encodes a tree to a single string.
string serialize(TreeNode* root) {
    if(!root){
        return "#_";
    }
    string data = to_string(root->val) + "_";
    data += serialize(root->left);
    data += serialize(root->right);
    return data;
}
// Decodes your encoded data to tree.
TreeNode* deserialize(string data) {
    list<string> dataArray;
    string str;
    for(auto& ch : data){
        if(ch == '_'){
            dataArray.push_back(str);
            str.clear();
        }
        else{
            str.push_back(ch);
        }
    }
    if(!str.empty()){
        dataArray.push_back(str);
        str.clear();
    }
    return deserializeSub(dataArray);
}
TreeNode* deserializeSub(list<string>& dataArray){
    if(dataArray.front() == "#"){
        dataArray.erase(dataArray.begin());
        return NULL;
    }
    TreeNode* head = new TreeNode(stoi(dataArray.front()));
    dataArray.erase(dataArray.begin());
    head->left = deserializeSub(dataArray);
    head->right = deserializeSub(dataArray);
    return head;
}


// 折纸问题
// 递归过程，来到了某一个节点
// i是节点的层数，N一共的层数，donw == true 凹，down == false 凸
void printProcess(int i, int N, bool down){
    if(i > N){
        return;
    }
    printProcess(i+1, N, true);
    cout << (down ? "凹" : "凸") << " ";
    printProcess(i+1 , N, false);
}
void printAllfolds(int N){
    printProcess(1, N, true);
}

int main()
{

}