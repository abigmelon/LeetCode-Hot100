#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int searchInsert(int* nums, int numsSize, int target) {
    int left = 0, right = numsSize - 1;
    while(left <= right){
        int mid = (left + right) / 2;
        if(nums[mid] < target) left = mid + 1;
        else if(nums[mid] >= target) right = mid - 1;
    }
    return left;
}