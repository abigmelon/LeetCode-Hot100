#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

void dfs_permute(int* nums, int numsSize, int depth,
                 bool* used, int* path, int** ans, int* idx) {
    // ----- 终止条件：走到叶子（路径长度 == numsSize）-----
    if (depth == numsSize) {
        ans[*idx] = (int*)malloc(sizeof(int) * numsSize);
        memcpy(ans[*idx], path, sizeof(int) * numsSize);
        (*idx)++;
        return;
    }

    // ----- 遍历所有数字，跳过已使用的 -----
    for (int i = 0; i < numsSize; i++) {
        if (used[i]) continue;       // 剪枝：数字已在当前路径中

        used[i] = true;              // 做选择
        path[depth] = nums[i];

        dfs_permute(nums, numsSize, depth + 1, used, path, ans, idx);

        used[i] = false;             // 撤销选择（回溯！）
    }
}


void dfs_subsets(int* nums, int numsSize, int start, int depth,
                 int* path, int** ans, int* idx, int* colSizes) {
    // ----- 每个节点都是答案，先保存 -----
    colSizes[*idx] = depth;
    ans[*idx] = (int*)malloc(sizeof(int) * depth);
    memcpy(ans[*idx], path, sizeof(int) * depth);
    (*idx)++;

    // ----- 从 start 开始往后选，天然去重 -----
    for (int i = start; i < numsSize; i++) {
        path[depth] = nums[i];       // 做选择

        dfs_subsets(nums, numsSize, i + 1, depth + 1, path, ans, idx, colSizes);

        // path[depth] 会被下一轮循环覆盖，无需显式撤销
    }
}

// 1. 终止条件判断 → 到达叶子节点，收集结果，return
// 2. for 循环遍历当前层的候选选择
//    ├── 剪枝：跳过不合法的选择
//    ├── 做选择（写入 path、标记 used）
//    ├── dfs(进入下一层)
//    └── 撤销选择（回溯）