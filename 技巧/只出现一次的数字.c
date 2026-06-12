#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

// 利用异或运算 a ⊕ a = 0 的性质，
// 我们可以用异或来「消除」所有出现了两次的元素，
// 最后剩下的一定是只出现一次的元素。
// 0 ⊕ a = a，这个东西还有结合和交换律 

int singleNumber(int* nums, int numsSize) {
    int ans = 0;
    for(int i = 0; i < numsSize; i++){
        ans ^= nums[i];
    }
    return ans;
}