#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define MIN(a, b) (a > b ? b : a)

int maxArea(int* height, int heightSize) {
    int left = 0, right = heightSize - 1;
    int max = 0;
    while(left < right){
        int cur = MIN(height[left], height[right]) * (right - left);
        if(cur > max) max = cur;
        if(height[left] < height[right]) left++;
        else right--;
    }
    return max;
}