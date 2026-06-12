#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

int majorityElement(int* nums, int numsSize) {
    int num = 0;
    int score = 0;
    for(int i = 0; i < numsSize; i++){
        if(nums[i] != num) score--;
        if(nums[i] == num) score++;
        if(score < 1){
            num = nums[i];
            score = 1;
        }
    }
    return num;
}

// 绝对众数的数量一定是比其他数要更多的（由题意，不存在相等的情况）
// 所以只需要在出现相同的数时加1分，出现不相同的数时减1分，只要掉到0分就换掉这个数
// 最后留下的一定就是绝对众数