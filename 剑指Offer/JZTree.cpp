#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


// Definition for binary tree
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// JZ4 重建二叉树
class SolutionJZ4 {
public:
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        if(pre.size() == 0 || pre.size() != vin.size()){
            return nullptr;
        }
        int root = pre[0];
        TreeNode* node = new TreeNode(root);
        if(pre.size() == 1){
            return node;
        }
        auto pos = find(vin.begin(), vin.end(), root);
        if(pos == vin.end()){
            return nullptr;
        }
        int leftSize = pos - vin.begin();
        int rightSize = vin.end() - pos - 1;
        node->left = reConstructBinaryTree(vector<int>(pre.begin() + 1, pre.begin() + 1 + leftSize), 
                                          vector<int>(vin.begin(), vin.begin() + leftSize));
        node->right = reConstructBinaryTree(vector<int>(pre.begin() + 1 + leftSize, pre.end()), 
                                          vector<int>(vin.begin() + leftSize + 1, vin.end()));
        return node;
    }
};

// JZ26 二叉搜索树与双向链表
class SolutionJZ26 {
public:
    TreeNode* head = nullptr;
    TreeNode* pre = nullptr;
    TreeNode* Convert(TreeNode* pRootOfTree) {
        if(!pRootOfTree){
            return nullptr;
        }        
        Convert(pRootOfTree->left);
        if(!pre){
            head = pRootOfTree;
        }else{
            pre->right = pRootOfTree;
            pRootOfTree->left = pre;
        }
        pre = pRootOfTree;
        Convert(pRootOfTree->right);
        return head;
    }
};

// JZ17 树的子结构
class SolutionJZ17 {
public:
    //递归判断是否是子结构
    bool isSub(TreeNode* pRoot1, TreeNode* pRoot2){
        if(!pRoot2){
            return true;
        }
        else if(!pRoot1){
            return false;
        }
        return pRoot1->val == pRoot2->val && isSub(pRoot1->left, pRoot2->left) && isSub(pRoot1->right, pRoot2->right);
    }
    //递归判断子树里有无所求子结构
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2) {
        if(!pRoot1 || !pRoot2){
            return false;
        }
        return isSub(pRoot1, pRoot2) || HasSubtree(pRoot1->left, pRoot2) || HasSubtree(pRoot1->right, pRoot2);
    }
};

// JZ23 二叉搜索树的后序遍历序列
class SolutionJZ23 {
public:
    bool VerifySquenceOfBST(vector<int> sequence) {
        int n = sequence.size();
        if(n == 0){
            return false;
        }
        return check(sequence, 0, n - 1);
    }
    bool check(vector<int>& sequence, int l, int r){
        if(l >= r){    // 若当前子树只有一个节点
            return true;
        }
        int root = sequence[r];    // 当前子树的根节点
        
        // 划分出右子树
        int j = r - 1;
        while(j >= 0 && sequence[j] > root){
            j--;
        }
        // 检查左子树是不是存在大于根节点的数
        for(int i = l; i <= j; i++){
            if(sequence[i] > root){
                return false;
            }
        }
        // 分治法检查左子树和右子树
        return check(sequence, l, j) && check(sequence, j + 1, r - 1);
    }
};