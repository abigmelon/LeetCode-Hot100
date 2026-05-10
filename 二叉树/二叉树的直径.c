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

int max = 0;

int maxDepth(struct TreeNode* root) {
    if(root == NULL) return 0;
    int left = maxDepth(root->left);
    int right = maxDepth(root->right);
    int d = left + right;
    if(d > max) max = d;
    return 1 + (left > right ? left : right);
}

int diameterOfBinaryTree(struct TreeNode* root) {
    max = 0;
    maxDepth(root);
    return max;
}

// 整棵树的直径 = 所有节点中 左深度 + 右深度 的最大值
// 机子会给多组数据，所以记得在主函数里把最大值归零