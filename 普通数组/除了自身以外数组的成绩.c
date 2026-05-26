#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int* pre = malloc(numsSize * sizeof(int));
    int* suf = malloc(numsSize * sizeof(int));
    pre[0] = 1;
    suf[numsSize - 1] = 1;
    for(int i = 1; i < numsSize; i++){
        pre[i] = pre[i - 1] * nums[i - 1];
    }
    for(int i = numsSize - 2; i >= 0; i--){
        suf[i] = suf[i + 1] * nums[i + 1];
    }
    int* ans = malloc(numsSize * sizeof(int));
    for(int i = 0; i < numsSize; i++){
        ans[i] = pre[i] * suf[i];
    }
    free(pre);
    free(suf);
    return ans;
}

// 前缀和后缀和的思想