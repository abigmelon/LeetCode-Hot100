#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

char result[32768][17][17];
int resultSize = 0;
char path[17][17];
int pathLen = 0;
int colLens[32768];

bool sym(char* s, int left, int right){
    int len = strlen(s);
    while(left < right){
        if(s[left] != s[right]) return false;
        left++;
        right--;
    }
    return true;
}

void dfs(char* s, int start, int len){
    if(start == len){
        for(int i = 0; i < pathLen; i++){
            strcpy(result[resultSize][i], path[i]);
        }
        colLens[resultSize] = pathLen;
        resultSize++;
        return;
    }
    for(int i = start; i < len; i++){
        if(!sym(s, start, i)) continue;
        int l = i - start + 1;
        strncpy(path[pathLen], s + start, l);
        path[pathLen][l] = '\0';
        pathLen++;
        dfs(s, i + 1, len);
        pathLen--;
    }
}

char*** partition(char* s, int* returnSize, int** returnColumnSizes) {
    resultSize = 0;
    pathLen = 0;
    int len = strlen(s);
    dfs(s, 0, len);
    *returnSize = resultSize;
    *returnColumnSizes = (int*)malloc(sizeof(int) * resultSize);
    char*** ans = (char***)malloc(sizeof(char**) * resultSize);
    for(int i = 0; i < resultSize; i++){
        (*returnColumnSizes)[i] = colLens[i];
        ans[i] = (char**)malloc(sizeof(char*) * colLens[i]);
        for(int j = 0; j < colLens[i]; j++){
            ans[i][j] = strdup(result[i][j]);
        }
    }
    return ans;
}