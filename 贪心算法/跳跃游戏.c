#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

_Bool canJump(int* nums, int numsSize) {
    int maxLen = 0;
    for(int i = 0; i < numsSize; i++){
        if(maxLen < i) return 0;
        else{
            maxLen = maxLen > i + nums[i] ? maxLen : i + nums[i];
        }
        if(maxLen >= numsSize - 1) return 1;
    }
    return 1;
}