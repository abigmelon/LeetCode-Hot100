#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>


int findLeft(int* nums, int numsSize, int target) {
    int left = 0, right = numsSize - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] >= target)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return left;
}

int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int* ans = (int*)malloc(2 * sizeof(int));
    ans[0] = -1;
    ans[1] = -1;

    if (numsSize == 0) return ans;

    int first = findLeft(nums, numsSize, target);
    if (first == numsSize || nums[first] != target) return ans;

    int last = findLeft(nums, numsSize, target + 1) - 1;

    ans[0] = first;
    ans[1] = last;
    return ans;
}