#include <iostream>
#include <stack>
#include <queue>
#include <unordered_map>

using namespace std;

class Node{
public:
    int value;
    Node* left;
    Node* right;
};

// 先序
void preOrderUnRecur(Node* head){
    if(head != nullptr){
        stack<Node*> s;
        s.push(head);
        while (!s.empty()){
            head = s.top();
            s.pop();
            cout << head->value << " ";
            if(head->right != nullptr){
                s.push(head->right);
            }
            if(head->left != nullptr){
                s.push(head->left);
            }
        }
    }
}

// 后序
void posOrderUnRecur(Node* head){
    if(head != nullptr){
        stack<Node*> s1;
        stack<Node*> s2;
        s1.push(head); 
        while (!s1.empty()){
            head = s1.top();
            s1.pop();
            s2.push(head);
            if(head->right != nullptr){
                s1.push(head->left);
            }
            if(head->left != nullptr){
                s1.push(head->right);
            }
        }
        while(!s2.empty()){
            cout << s2.top()->value << " ";
            s2.pop();
        }
    }
}

// 中序
void inOrderUnRecur(Node* head){
    if(head != nullptr){
        stack<Node*> s;
        while (!s.empty() || head != nullptr){
            if(head != nullptr){
                s.push(head->left);
                head = head->left;
            }
            else{
                head = s.top();
                s.pop();
                cout << head->value << " ";
                head = head->right;
            }
        }
    }
}

// 宽度优先遍历
void w(Node* head){
    if(head == nullptr){
        return;
    }
    queue<Node*> q;
    q.push(head);
    while (!q.empty()){
        Node* cur = q.front();
        q.pop();
        cout << cur->value;
        if(cur->left != nullptr){
            q.push(cur->left);
        }
        if(cur->right != nullptr){
            q.push(cur->right);
        }
    }
}

// 二叉树的宽度
int getMaxWidth(Node* head){
    if(head == nullptr){
        return 0;
    }
    int maxWidth = 0;
    int curWidth = 0;
    int curLevel = 0;
    unordered_map<Node*, int> levelMap;
    levelMap.insert(pair<Node*, int>(head, 1));
    queue<Node*> q;
    q.push(head);
    Node* node = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
    while (!q.empty()){
        node = q.front();
        left = node->left;
        right = node->right;
        q.pop();
        int curLevelNodes = levelMap.at(node);
        if(curLevelNodes == curLevel){
            curWidth++;
        }
        else{
            maxWidth = max(maxWidth, curWidth);
            curLevel++;
            curLevelNodes = 1;
        }
        if(left != nullptr){
            levelMap.insert(pair<Node*, int>(left, levelMap.at(node) + 1));
            q.push(left);
        }
        if(right != nullptr){
            levelMap.insert(pair<Node*, int>(right, levelMap.at(node) + 1));
            q.push(right);
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

int main()
{

}