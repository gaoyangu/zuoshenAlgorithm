#include <iostream>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

class Node{
public:
    Node(int val) : value(val) { }
    int value;
    Node* left;
    Node* right;
};

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
int preValue = INTMAX_MIN;
bool checkBST(Node* head){
    if(head == nullptr){
        return true;
    }
    bool isLeftBST = checkBST(head->left);
    if(!isLeftBST){
        return false;
    }
    if(head->value <= preValue){
        return false;
    }
    else{
        preValue = head->value;
    }
    return checkBST(head->right);
}
// 
void process2(Node* head, vector<Node*> inOrderList){
    if(head == nullptr){
        return;
    }
    process2(head->left, inOrderList);
    inOrderList.push_back(head);
    process2(head->right, inOrderList);
}
bool checkBST2(Node* head){
    vector<Node*> inOrderList;
    process2(head, inOrderList);
    for(int i = 0; i < inOrderList.size() - 1; i++){
        if (inOrderList[i] >= inOrderList[i+1]){
            return false;
        }
    }
    return true;
}
// 非递归
bool checkBST3(Node* head){
    if(head != nullptr){
        int preValue = INTMAX_MIN;
        stack<Node*> s;
        while (!s.empty() || head != nullptr){
            if(head != nullptr){
                s.push(head);
                head = head->left;
            }
            else{
                head = s.top();
                s.pop();
                if(head->value <= preValue){
                    return false;
                }
                else{
                    preValue = head->value;
                }
                head = head->right;
            }
        }
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
bool isCBT(Node* head){
    if(head == nullptr){
        return true;
    }
    queue<Node*> q;
    // 是否遇到过左右两个孩子不全的节点
    bool leaf = false;
    Node* l = nullptr;
    Node* r = nullptr;
    q.push(head);
    while (!q.empty()){
        head = q.front();
        q.pop();
        l = head->left;
        r = head->right;
        if((leaf && (l != nullptr || r != nullptr)) 
            || (l == nullptr && r != nullptr)){
            return false;
        }
    }
    return true;
}

// 满二叉树
class Info{
public:
    Info(int h, int n) : height(h),nodes(n){ }
    int height;
    int nodes;
};
Info f(Node* head){
    if(head == nullptr){
        return Info(0, 0);
    }
    Info leftData = f(head->left);
    Info rightData = f(head->right);
    int height = max(leftData.height, rightData.height) + 1;
    int nodes = leftData.nodes + rightData.nodes + 1;
    return Info(height, nodes);
}
bool isFBT(Node* head){
    if(head == nullptr){
        return true;
    }  
    Info data = f(head);
    return data.nodes == (1 << data.height - 1);
}

// 平衡二叉树
class ReturnType{
public:
    ReturnType(bool isB, int hei) : isBalanced(isB), height(hei) { }
    bool isBalanced;
    int height;
};
ReturnType process(Node* head){
    if(head == nullptr){
        return ReturnType(true, 0);
    }
    ReturnType leftData = process(head->left);
    ReturnType rightData = process(head->right);
    int height = max(leftData.height, rightData.height) + 1;
    bool isBalanced = leftData.isBalanced && rightData.isBalanced 
                        && abs(leftData.height - rightData.height) < 2;
    return ReturnType(isBalanced, height);
}
bool isBalanced(Node* head){
    return process(head).isBalanced;
}

// 最低公共祖先节点
// 方法一
void process(Node* head, unordered_map<Node*, Node*> fatherMap){
    if(head == nullptr){
        return;
    }
    fatherMap.insert(pair<Node*, Node*>(head->left, head));
    fatherMap.insert(pair<Node*, Node*>(head->right, head));
    process(head->left, fatherMap);
    process(head->right);
}
Node* lca(Node* head, Node* o1, Node* o2){
    unordered_map<Node*, Node*> fatherMap;
    fatherMap.insert(pair<Node*, Node*>(head, head));
    process(head, fatherMap);
    unordered_set<Node*> s;
    Node* cur = o1;
    while (cur != fatherMap.at(cur)){
        s.insert(cur);
        cur = fatherMap.at(cur);
    }
    s.insert(head);

    cur = o2;
    while (cur != fatherMap.at(cur)){
        if(s.find(cur) != s.end()){
            return cur;
        }
        cur = fatherMap.at(cur);
    }
    return head;
}
// 方法二
Node* lowestAmcestor(Node* head, Node* o1, Node* o2){
    // base case
    if(head == nullptr || head == o1 || head == o2){
        return head;
    }
    Node* left = lowestAmcestor(head->left, o1, o2);
    Node* right = lowestAmcestor(head->right, o1, o2);
    if(left != nullptr && right != nullptr){
        return head;
    }
    return left != nullptr ? left : right;
}

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
            parent = node.parent;
        }
        return parent;
    }
}

// 二叉树的序列化和反序列化
string serialByPre(Node* head){
    if(head == nullptr){
        return "#_";
    }
    string res = head->value + "_";
    res += serialByPre(head->left);
    res += serialByPre(head->right);
    return res;
}
Node* reconPreOrder(queue<string> q){
    string value = q.front();
    q.pop();
    if(value == "#"){
        return nullptr;
    }
    Node* head = new Node(stoi(value));
    head->left = reconPreOrder(q);
    head->right = reconPreOrder(q);
    return head;
}
Node* reconByPreString(string preStr){
    queue<string> q;
    int pos = preStr.find("_");
    while (pos != preStr.npos) {
        string temp = preStr.substr(0, pos);
        q.push(temp);
        preStr = preStr.substr(pos + 1, preStr.size());
        pos = preStr.find("_");
    }
    return reconPreOrder(q);
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