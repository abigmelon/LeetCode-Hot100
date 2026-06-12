#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

int findDuplicate(int* nums, int numsSize) {
    int slow = 0, fast = 0;
    while(1){
        slow = nums[slow];
        fast = nums[nums[fast]];
        if(slow == fast) break;
    }

    int head = 0;
    while(slow != head){
        slow = nums[slow];
        head = nums[head];
    }
    return slow;
}

// 参考环形链表II那个数学推导