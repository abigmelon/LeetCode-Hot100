#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int dfs(struct TreeNode* node, int* globalMax) {
    if(node == NULL) return 0;
    int left = dfs(node->left, globalMax);
    int right = dfs(node->right, globalMax);
    int leftGain = MAX(left, 0);
    int rightGain = MAX(right, 0);
    int pathSum = node->val + leftGain + rightGain;
    *globalMax = MAX(*globalMax, pathSum);
    return node->val + MAX(leftGain, rightGain);
}

int maxPathSum(struct TreeNode* root) {
    int globalMax = INT_MIN;
    dfs(root, &globalMax);
    return globalMax;
}
