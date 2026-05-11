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

void dfs(struct TreeNode* node, struct TreeNode** head){
    if(node == NULL) return;
    dfs(node->right, head);
    dfs(node->left, head);
    node->left = NULL;
    node->right = *head;
    *head = node;
}

void flatten(struct TreeNode* root) {
    struct TreeNode* head = NULL;
    dfs(root, &head);
}

// 解析：采用头插法构建链表
// 按照右 左 根的顺序来遍历
// 通过头插法来一直更新head