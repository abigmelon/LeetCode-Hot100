#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

int firstMissingPositive(int* nums, int numsSize) {
    for(int i = 0; i < numsSize; i++){
        while(nums[i] >= 1 && nums[i] <= numsSize && nums[i] != nums[nums[i] - 1]){
            int tmp = nums[i];
            nums[i] = nums[tmp - 1];
            nums[tmp - 1] = tmp;
        }
    }
    for(int i = 0; i < numsSize; i++){
        if(nums[i] != i + 1) return i + 1;
    }
    return numsSize + 1;
}