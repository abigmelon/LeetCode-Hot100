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

_Bool isMirror(struct TreeNode* p, struct TreeNode* q){
    if(p == NULL && q == NULL) return 1;
    if(p == NULL || q == NULL) return 0;
    if(p->val != q->val) return 0;
    return isMirror(p->left, q->right) && isMirror(p->right, q->left);
}

_Bool isSymmetric(struct TreeNode* root) {
    return isMirror(root->left, root->right);
}

// 解析：
// 判断一棵树是否轴对称——以根节点为中轴线，左右互为镜像。
// 核心是写一个辅助函数 isMirror(p, q)，判断两棵树是否互为镜像。
// 镜像的三要素：
//   1. 两棵树的根节点值相同
//   2. p 的左子树 与 q 的右子树 镜像
//   3. p 的右子树 与 q 的左子树 镜像
// 注意区分"左右子树各自对称"和"左右子树互为镜像"——这是两个不同的概念。
// 比如 [1,2,2,null,3,null,3]：左右子树单独看都是对称的（只有一个节点），
// 但互为镜像需要 2的左=2的右、2的右=2的左，这里一边是null一边是3，不相等。
// 与翻转二叉树（226题）的关系：对称二叉树等价于"左子树翻转后等于右子树"。