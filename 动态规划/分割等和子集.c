#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

_Bool canPartition(int* nums, int numsSize) {
    int sum = 0;
    if(numsSize == 0) return 0;
    for(int i = 0; i < numsSize; i++){
        sum += nums[i];
    }
    if(sum % 2 == 1) return 0;
    int target = sum / 2;
    _Bool* dp = malloc((target + 1) * sizeof(_Bool));
    dp[0] = 1;
    for(int i = 1; i <= target; i++){
        dp[i] = 0;
    }
    for(int i = 0; i < numsSize; i++){
        int num = nums[i];
        for(int j = target; j >= num; j--){
            dp[j] = dp[j] || dp[j - num];
        }
    }
    return dp[target];
}