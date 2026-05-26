#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

void reverse(int* nums, int left, int right){
    while(left < right){
        int tmp = nums[left];
        nums[left] = nums[right];
        nums[right] = tmp;
        left++;
        right--;
    }
}

void rotate(int* nums, int numsSize, int k) {
    int n = k % numsSize;
    if(n == 0) return;
    reverse(nums, 0, numsSize - 1);
    reverse(nums, 0, n - 1);
    reverse(nums, n, numsSize - 1);
    return;
}

// 第一次：反转整个数组
// [1, 2, 3, 4, 5, 6, 7]  →  [7, 6, 5, 4, 3, 2, 1]

// 第二次：反转前 k 个元素（索引 0 ~ k-1）
// [7, 6, 5,|4, 3, 2, 1]  →  [5, 6, 7, 4, 3, 2, 1]

// 第三次：反转剩余元素（索引 k ~ n-1）
// [5, 6, 7,|4, 3, 2, 1]  →  [5, 6, 7, 1, 2, 3, 4]

// 这种轮转类型的题目好像都可以用反转的思路做，不管是数组也好还是矩阵也好，多往这方面思考一下