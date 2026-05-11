#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* build(int preStart, int preEnd, int inStart, int inEnd){
    if(preStart > preEnd) return NULL;
    struct TreeNode* node = 
}

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    
}

// 前序的第一个节点是根节点，中序根左边是左子树，右边是右子树
// 步骤拆解
// 第 1 步：从前序数组取第一个元素，这就是当前树的根节点。
// 第 2 步：在中序数组中找到这个根节点的位置。位置左边的元素个数 = 左子树的大小，右边的 = 右子树的大小。
// 第 3 步：知道了左子树大小，你就能在前序数组中切出左子树的前序、右子树的前序。
// 第 4 步：递归构造左子树和右子树。