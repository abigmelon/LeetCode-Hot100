#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

const char* table[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

void dfs(int i, int n, char** ans, int* returnSize, char* path, char* digits){
    if(i == n){
        ans[*returnSize] = malloc((n + 1) * sizeof(char));
        strcpy(ans[*returnSize], path);
        (*returnSize)++;
        return;     //回到上一步
    }
    const char* s = table[digits[i] - '0'];
    for(int j = 0; s[j]; j++){      //用s[j]可以避免那个分类讨论，反正字符存在就行
        path[i] = s[j];
        dfs(i + 1, n, ans, returnSize, path, digits);       //下一位
    }

}

char** letterCombinations(char* digits, int* returnSize) {
    int n = strlen(digits);

    if(n == 0){
        *returnSize = 0;
        return NULL;
    }

    int ansSize = 1;
    for(int i = 0; i < n; i++){
        if(digits[i] == '7' || digits[i] == '9') ansSize *= 4;
        else ansSize *= 3;
    }
    char** ans = malloc(sizeof(char*) * ansSize);
    char* path = malloc(sizeof(char) * (n + 1));        //这里的path长度已经卡死是n + 1了，不用动态调整
    path[n] = '\0';
    *returnSize = 0;

    dfs(0, n, ans, returnSize, path, digits);

    free(path);
    return ans;
}