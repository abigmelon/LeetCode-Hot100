#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

/* ================================================================
 *  组合总和 (39) — "选或不选" 思路
 *
 *  决策树（candidates = [2,3,5], target = 5）：
 *
 *                        dfs(0, 5)          ← 面对 candidates[0]=2
 *                  ┌─────────┴─────────┐
 *             不选 2                  选 2
 *                ↓                      ↓
 *           dfs(1, 5)              dfs(0, 3)    ← 选 2 后还能再选 2（无限次）
 *         ┌──────┴──────┐        ┌──────┴──────┐
 *      不选 3         选 3    不选 3         选 3
 *        ↓             ↓        ↓             ↓
 *     dfs(2,5)    dfs(2,2)   dfs(1,3)     dfs(1,0) → left=0! 保存 [2,3]
 *      ...          ...
 *
 *  和 for 循环模板的区别：
 *     - for 循环版：在循环里选一个，然后递归下一层
 *     - 选或不选版：每个元素只问一次 "要 or 不要"，递归两条分支
 * 有点类似于背包问题的分类思路
 * ================================================================ */

void dfs(int start, int left, int* candidates, int candidatesSize, int* returnSize, int** ans, int** returnColumnSizes, int* path, int depth){
    if(left == 0){
        (*returnColumnSizes)[*returnSize] = depth;
        ans[*returnSize] = (int*)malloc(sizeof(int) * depth);
        memcpy(ans[*returnSize], path, sizeof(int) * depth);
        (*returnSize)++;
        return;
    }

    if(start >= candidatesSize || left < 0) return;

    dfs(start + 1, left, candidates, candidatesSize, returnSize, ans, returnColumnSizes, path, depth);

    path[depth] = candidates[start];        //拿

    dfs(start, left - candidates[start], candidates, candidatesSize, returnSize, ans, returnColumnSizes, path, depth + 1);
}
int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {
    if(candidatesSize == 0){
        (*returnSize) = 0;
        return NULL;
    }

    int** ans = malloc(sizeof(int*) * 150);
    *returnColumnSizes = (int*)malloc(sizeof(int) * 150);
    int* path = (int*)malloc(sizeof(int) * 150);
    (*returnSize) = 0;

    dfs(0, target, candidates, candidatesSize, returnSize, ans, returnColumnSizes, path, 0);
    
    free(path);
    return ans;
}
