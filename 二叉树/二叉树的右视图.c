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

// ============================================================================
// 方法一：BFS 层序遍历 —— 每层取最后一个节点
// ============================================================================
int* rightSideView(struct TreeNode* root, int* returnSize) {
    *returnSize = 0;
    if(root == NULL) return NULL;
    struct TreeNode* queue[105];
    int head = 0, tail = 0;
    queue[tail++] = root;
    int* ans = malloc(100 * sizeof(int));
    int idx = 0;
    while(head < tail){
        int levelsize = tail - head;
        for(int i = 0; i < levelsize; i++){
            struct TreeNode* node = queue[head++];
            if(i == levelsize - 1) ans[idx++] = node->val;
            if(node->left)  queue[tail++] = node->left;
            if(node->right) queue[tail++] = node->right;
        }
    }
    *returnSize = idx;
    return ans;
}

/*
============================================================================
方法二：DFS（根→右→左）—— 每个深度取第一个遇到的节点
============================================================================
*/
/*
void dfs(struct TreeNode* root, int depth, int* ans, int* idx) {
    if (root == NULL) return;

    // 当前深度第一次遇到节点 → 说明它就是从右边看到的节点
    if (depth == *idx) {
        ans[(*idx)++] = root->val;
    }

    dfs(root->right, depth + 1, ans, idx);  // 先右
    dfs(root->left,  depth + 1, ans, idx);  // 再左
}

int* rightSideView(struct TreeNode* root, int* returnSize) {
    int* ans = (int*)malloc(100 * sizeof(int));
    int idx = 0;
    dfs(root, 0, ans, &idx);
    *returnSize = idx;
    return ans;
}
*/

// ============================================================================
// 方法三：DFS 覆盖法（最直白！）
// 思路：标准前序遍历（根→左→右），每个深度直接覆盖写入。
//       先左后右 → 右节点后访问 → 自然覆盖左节点 → 留下右视图
// ============================================================================
void dfs_overwrite(struct TreeNode* root, int depth, int* ans, int* maxDepth) {
    if (root == NULL) return;

    ans[depth] = root->val;                         // 直接写入，后面的会覆盖前面的
    if (depth > *maxDepth) *maxDepth = depth;        // 记录当前最大深度

    dfs_overwrite(root->left,  depth + 1, ans, maxDepth);  // 先左
    dfs_overwrite(root->right, depth + 1, ans, maxDepth);  // 后右 → 右覆盖左！
}

int* rightSideView_overwrite(struct TreeNode* root, int* returnSize) {
    int* ans = (int*)malloc(100 * sizeof(int));
    int maxDepth = -1;                                // 初始-1，空树时 returnSize = 0
    dfs_overwrite(root, 0, ans, &maxDepth);
    *returnSize = maxDepth + 1;                       // 深度从0开始，+1 = 节点数
    return ans;
}