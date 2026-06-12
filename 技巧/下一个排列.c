#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

void nextPermutation(int* nums, int numsSize) {
    int down = 1;
    for(int i = 0; i < numsSize - 1; i++){
        if(nums[i] < nums[i + 1]){
            down = 0;
            break;
        }
    }
    if(down == 1){
        int left = 0, right = numsSize - 1;
        while(left < right){
            int tmp = nums[left];
            nums[left] = nums[right];
            nums[right] = tmp;
            left++;
            right--;
        }
        return;
    }
    int x_idx = numsSize - 2;
    while(x_idx >= 0){
        if(nums[x_idx] < nums[x_idx + 1]) break;
        else x_idx--;
    }
    int y_idx = numsSize - 1;
    while(y_idx > x_idx){
        if(nums[y_idx] > nums[x_idx]) break;
        else y_idx--;
    }
    int tmp = nums[x_idx];
    nums[x_idx] = nums[y_idx];
    nums[y_idx] = tmp;
    int left = x_idx + 1, right = numsSize - 1;
    while(left < right){
        int tmp = nums[left];
        nums[left] = nums[right];
        nums[right] = tmp;
        left++;
        right--;
    }
    return;
}

// 下一次举例子的时候数组还是写长一点，不然容易爆出想不到的bug

// 也许是更好的代码：
// #define SWAP(a, b) do { int tmp = (a); (a) = (b); (b) = tmp; } while (0)

// void nextPermutation(int* nums, int numsSize) {
//     int i = numsSize - 2;

//     // 第一步：从右到左找到第一个小于 nums[i+1] 的数 nums[i]
//     while (i >= 0 && nums[i] >= nums[i + 1]) {
//         i--;
//     }

//     // 如果找到了，进入第二步；否则跳过第二步，反转整个数组
//     if (i >= 0) {
//         int j = numsSize - 1;
//         while (nums[j] <= nums[i]) {
//             j--;
//         }
//         // 交换 nums[i] 和 nums[j]
//         SWAP(nums[i], nums[j]);
//     }

//     // 第三步：反转 [i+1, n-1]（如果上面跳过第二步，此时 i = -1）
//     int left = i + 1, right = numsSize - 1;
//     while (left < right) {
//         SWAP(nums[left], nums[right]);
//         left++;
//         right--;
//     }
// }

// 其实是在最后一步做了一个融合，其他思路都差不到哪里去
// 第一遍做感觉没有必要把代码精简到这么变态的程度