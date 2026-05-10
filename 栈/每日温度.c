#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// 暴力解法
// int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize) {
//     int* ans;
//     for(int i = 0; i < n; i++){
//         for(int j = i + 1; j < n; j++){
//             if(temperatures[j] > temperatures[i]){  
//                 ans[i] = j - i;
//                 break;
//             }
//         }
//     }
//     return ans;
// }
// 这个解法太坏了，复杂度是O(n^2)

// 正常的做法：单调栈

int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize) {
    *returnSize = temperaturesSize;
    int* ans = malloc(temperaturesSize * sizeof(int));
    memset(ans, 0, temperaturesSize * sizeof(int));
    int* stack = malloc(temperaturesSize * sizeof(int));    //存下标
    int top = -1;
    for(int i = 0; i < temperaturesSize; i++){
        while(top != -1 && temperatures[i] > temperatures[stack[top]]){
            int prev = stack[top];
            top--;
            ans[prev] = i - prev;
        }
        stack[++top] = i;
    }
    free(stack);
    return ans;
}

// 题解：
// 还是用空间换时间的思路，没找到的下标存在一个栈里，找到了比他大的就一个一个吐出去，这样只用遍历一遍，复杂度是O(n)
// 做这种题需要多想想，不要一上来就开始写代码，写出来的一般都对不了