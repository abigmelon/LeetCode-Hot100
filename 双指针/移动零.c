#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

void moveZeroes(int* nums, int numsSize) {
    int left0idx = -1;
    for(int i = 0; i < numsSize; i++){
        if(nums[i] == 0){
            left0idx = i;
            break;
        }
    }
    if(left0idx == -1) return;
    int cur = left0idx + 1;
    while(cur < numsSize){
        if(nums[cur] == 0){
            cur++;
            continue;
        }else{
            nums[left0idx] = nums[cur];
            nums[cur] = 0;
            left0idx++;
            cur++;
        }
    }
    return;
}