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

int getSize(struct TreeNode* root){
    if(root == NULL) return 0;
    return 1 + getSize(root->left) + getSize(root->right);
}

void inorder(struct TreeNode* root, int* arr, int* idx){
    if(root == NULL) return;
    inorder(root->left, arr, idx);
    arr[(*idx)++] = root->val;
    inorder(root->right, arr, idx);
}

// idx：当前写到哪了，用指针传，这样递归里改了外面也知道

int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    int size = getSize(root);
    int* ans = malloc(size * sizeof(int));
    int idx = 0;
    inorder(root, ans, &idx);
    *returnSize = size;
    return ans;
}

// 迭代解法：

int* inorderTraversal_2(struct TreeNode* root, int* returnSize) {
    int size = getSize(root);
    int* ans = malloc(size * sizeof(int));
    struct TreeNode** stack = malloc(size * sizeof(struct TreeNode*));
    int top = -1;
    int idx = 0;
    struct TreeNode* cur = root;
    while(top != -1 || cur != NULL){
        if(cur != NULL){
            stack[++top] = cur;
            cur = cur->left;
        } else{
            cur = stack[top--];
            ans[idx++] = cur->val;
            cur = cur->right;
        }
    }
    *returnSize = size;
    free(stack);
    return ans;
}