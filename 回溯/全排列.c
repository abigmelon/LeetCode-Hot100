#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

long long size(int n){
    int ans = 1;
    for(int i = 2; i <= n; i++) ans *= i;
    return ans;
}

void dfs(int* nums, int depth, int numsSize, bool* used, int* path, int** ans, int* idx){
    if(depth == numsSize){
        memcpy(ans[*idx], path, sizeof(int) * numsSize);        //传参的时候用*idx，不然没办法把值传到函数外面，或者用全局变量
        //上面这一行就是先保存一组的意思
        (*idx)++;
        return;     //这里return的含义是回到上一层
    }
    for(int i = 0; i < numsSize; i++){
        if(used[i]) continue;
        used[i] = true;     //正在使用
        path[depth] = nums[i];
        dfs(nums, depth + 1, numsSize, used, path, ans, idx);
        used[i] = false;        //用完了放回去
    }
}

int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int total = size(numsSize);
    int** ans = malloc(sizeof(int*) * total);
    for(int i = 0; i < size(numsSize); i++){
        ans[i] = malloc(sizeof(int) * numsSize);
    }
    bool* used = calloc(numsSize, sizeof(bool));        //calloc的作用是全部置0
    int* path = malloc(sizeof(int) * numsSize);
    int idx = 0;
    
    dfs(nums, 0, numsSize, used, path, ans, &idx);

    *returnSize = total;
    *returnColumnSizes = malloc(sizeof(int) * total);
    for(int i = 0; i < total; i++){
        (*returnColumnSizes)[i] = numsSize;
    }
    
    free(used);
    free(path);
    return ans;
}