#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

//每一层只从当前位置之后的数字中选，就可以直接避免重复问题

long long size(int n){
    long long ans = 1 << n;
    return ans;
}

void dfs(int* nums, int numsSize, int start, int depth, int* path, int** ans, int* idx, int* colSizes){
    colSizes[*idx] = depth;
    ans[*idx] = (int*)malloc(sizeof(int) * depth);
    memcpy(ans[*idx], path, sizeof(int) * depth);
    (*idx)++;

    for(int i = start; i < numsSize; i++){      //从start往后选，start自增，这样就可以保证不重复
        path[depth] = nums[i];
        dfs(nums, numsSize, i + 1, depth + 1, path, ans, idx, colSizes);
    }
}

int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    long long total = size(numsSize);
    int** ans = malloc(sizeof(int*) * total);
    int* colSizes = (int*)malloc(sizeof(int) * total);
    int* path = (int*)malloc(sizeof(int) * numsSize);
    int idx = 0;

    dfs(nums, numsSize, 0, 0, path, ans, &idx, colSizes);

    *returnSize = total;
    *returnColumnSizes = colSizes;
    free(path);
    return ans;
}