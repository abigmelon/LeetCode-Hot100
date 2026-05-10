#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>


// 第一种方法：暴力遍历，对每一根柱子向左或者向右扩展，并且记录当前值
// 最后找到最大，但是肯定会TLE
// int largestRectangleArea(int* heights, int heightsSize) {
//     int* big = malloc(heightsSize * sizeof(int));
//     for(int i = 0; i < heightsSize; i++){
//         int width = 1;
//         int j = i, k = i;
//         while(--j >= 0){
//             if(heights[j] >= heights[i]) width++;
//             else break;
//         }
//         while(++k <= heightsSize - 1){
//             if(heights[k] >= heights[i]) width++;
//             else break; 
//         }
//         big[i] = heights[i] * width;
//     }
//     int max = 0;
//     for(int i = 0; i < heightsSize; i++){
//         if(big[i] >= max) max = big[i];
//     }
//     return max;
// }

int largestRectangleArea(int* heights, int heightsSize) {
    int newSize = heightsSize + 1;
    int* newHeights = malloc(newSize * sizeof(int));
    memcpy(newHeights, heights, heightsSize * sizeof(int));
    newHeights[newSize - 1] = 0;
    int* stack = malloc(newSize * sizeof(int));
    int top = -1;
    int max = 0;
    for(int i = 0; i < newSize; i++){
        while(top != -1 && newHeights[stack[top]] > newHeights[i]){
            int h = newHeights[stack[top--]];
            int left = (top == -1) ? -1 : stack[top];
            int right = i;
            int width = right - left - 1;
            int ans = h * width;
            if(max <= ans) max = ans;
        }
        stack[++top] = i;
    }
    free(stack);
    free(newHeights);
    return max;
}

// 设置一个栈，存放那些还不知道右边界可以到哪里的柱子
// 这个单调栈的用法是，在遍历的过程中，帮助每根柱子找到他的长度可以拉到多远