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

struct TreeNode* trans(int* num, int left, int right){
    if(left > right) return NULL;
    int mid = (left + right) / 2;
    struct TreeNode* root = malloc(sizeof(struct TreeNode));
    root->val = num[mid];
    root->left = trans(num, left, mid - 1);
    root->right = trans(num, mid + 1, right);
    return root;
}

struct TreeNode* sortedArrayToBST(int* nums, int numsSize) {
    struct TreeNode* root = trans(nums, 0, numsSize - 1);
    return root;
}