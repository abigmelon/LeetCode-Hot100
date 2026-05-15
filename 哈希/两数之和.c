#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    for (int i = 0; ; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] + nums[j] == target) {
                int* ans = malloc(2 * sizeof(int));
                *returnSize = 2;
                ans[0] = i;
                ans[1] = j;
                return ans;
            }
        }
    }
}