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

int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    if(root == NULL){
        *returnSize = 0;
        return NULL;
    }
    
    int capacity = 2000;  // 题目最大节点数
    int** result = malloc(capacity * sizeof(int*));
    int* colSizes = malloc(capacity * sizeof(int));
    int level = 0;

    struct TreeNode** queue = malloc(2000 * sizeof(struct TreeNode*));
    int head = 0, tail = 0;
    queue[tail++] = root;

    while (head < tail) {
        int levelSize = tail - head;
        result[level] = malloc(levelSize * sizeof(int));

        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* node = queue[head++];
            result[level][i] = node->val;
            if (node->left)  queue[tail++] = node->left;
            if (node->right) queue[tail++] = node->right;
        }

        colSizes[level] = levelSize;
        level++;
    }

    free(queue);
    *returnSize = level;
    *returnColumnSizes = colSizes;
    return result;
}

// 解析：
// 层序遍历 = BFS，用队列实现。核心流程：
//   1. 根节点入队
//   2. 每轮先看队列中有几个节点（levelSize），这就是当前层的节点数
//   3. 依次弹出这 levelSize 个节点，收集值，并把左右孩子入队
//   4. 把当前层结果存入二维数组
//   5. 队列为空则结束
// 关键技巧：在开始处理一层之前，先记下队列长度。
// 因为出队的同时会入队下一层的节点，不提前记下来就无法区分"当前层"和"下一层"。
// 返回值的特殊之处：需要 returnColumnSizes 数组来告诉调用者每一层有多少个节点。