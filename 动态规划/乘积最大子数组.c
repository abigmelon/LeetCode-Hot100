#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)

int maxProduct(int* nums, int numsSize) {
    if(numsSize == 0) return 0;
    if(numsSize == 1) return nums[0];
    int cur = nums[0];
    int max = nums[0];
    int min = nums[0];
    for(int i = 1; i < numsSize; i++){
        int p = max;
        max = MAX(MAX(max * nums[i], nums[i]), min * nums[i]);
        min = MIN(MIN(p * nums[i], nums[i]), min * nums[i]);
        cur = MAX(max, cur);
    }
    return cur;
}

// maxDP[i + 1] = max(maxDP[i] * A[i + 1], A[i + 1],minDP[i] * A[i + 1])
// minDP[i + 1] = min(minDP[i] * A[i + 1], A[i + 1],maxDP[i] * A[i + 1])
// dp[i + 1] = max(dp[i], maxDP[i + 1])
// 用空间换时间，因为每一个数组里的数都是int类型的，所以不用担心乘起来绝对值会比原来小
// 一直保存当前的最大值和最小值，比较一下当前的最大值就出来了
