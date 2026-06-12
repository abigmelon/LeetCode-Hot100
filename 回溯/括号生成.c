#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

void dfs(char** ans, int* returnSize, char* path, int left, int right, int n){
    if(left == n && right == n){
        ans[*returnSize] = malloc(sizeof(char) * (2 * n + 1));
        strcpy(ans[*returnSize], path);
        (*returnSize)++;
        return;
    }
    
    if(left < n){
        path[left + right] = '(';
        dfs(ans, returnSize, path, left + 1, right, n);
    }

    if(right < left){
        path[left + right] = ')';
        dfs(ans, returnSize, path, left, right + 1, n);
    }
}

// 递归的思路其实并不需要想得那么清楚，整体上来讲
// 1.终止条件+复制
// 2.条件1+递归
// 3.条件2+递归
// ……


char** generateParenthesis(int n, int* returnSize) {
    *returnSize = 0;
    int maxSize = 1;
    for(int i = 0; i < n; i++){
        maxSize = maxSize * (2 * n - i) / (i + 1);
    }   
    maxSize /= (n + 1);

    char** ans = malloc(sizeof(char*) * maxSize);
    char* path = malloc(sizeof(char) * (2 * n + 1));
    path[2 * n] = 0;

    dfs(ans, returnSize, path, 0, 0, n);

    free(path);
    return ans;
}