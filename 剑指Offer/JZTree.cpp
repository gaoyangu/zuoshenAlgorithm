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