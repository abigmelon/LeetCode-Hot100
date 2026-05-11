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

int arr[10005] = {0};
int idx = 0;

void inOrder(struct TreeNode* root){
    if(root == NULL) return;
    inOrder(root->left);
    arr[idx++] = root->val;
    inOrder(root->right);
}

int kthSmallest(struct TreeNode* root, int k) {
    idx = 0;
    inOrder(root);
    return arr[k - 1];
}