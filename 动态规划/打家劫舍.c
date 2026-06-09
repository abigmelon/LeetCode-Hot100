#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define MAX(a, b) (a > b ? a : b)

int rob(int* nums, int numsSize) {
    if(numsSize == 0) return 0;
    if(numsSize == 1) return nums[0];
    int prev2 = nums[0];
    int prev1 = nums[1] > nums[0] ? nums[1] : nums[0];
    for(int i = 2; i < numsSize; i++){
        int cur = prev1 > (nums[i] + prev2) ? prev1 : (nums[i] + prev2);
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}