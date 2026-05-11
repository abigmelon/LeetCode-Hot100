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

_Bool dfs(struct TreeNode* node, long long left, long long right){
    if(node == NULL) return 1;
    long long x = node->val;
    return left < x && x < right && dfs(node->left, left, x) && dfs(node->right, x, right);
}

_Bool isValidBST(struct TreeNode* root) {
    return dfs(root, LLONG_MIN, LLONG_MAX);
}

// 给每一个节点划定一个合法值的区间：
// 对于x = root->val，它的范围根据题目就是long long的范围
// 对于它左边的元素，合法值区间变为LLONG_MIN到x
// 对于它右边的元素，合法值区间变为x到LLONG_MAX
// 以此类推，递归处理