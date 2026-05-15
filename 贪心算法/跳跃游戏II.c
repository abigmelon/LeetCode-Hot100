#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define MAX(a, b) (a > b ? a : b)

int jump(int* nums, int numsSize) {
    int ans = 0;
    int cur = 0;
    int next = 0;
    for(int i = 0; i < numsSize - 1; i++){
        next = MAX(next, i + nums[i]);
        if(i == cur){
            cur = next;
            ans++;
        }
    }
    return ans;
}