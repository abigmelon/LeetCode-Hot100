#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

int cmp(const void* a, const void* b){
    int* A = *(int**)a;
    int* B = *(int**)b;
    return A[0] - B[0];
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes) {
    qsort(intervals, intervalsSize, sizeof(int*), cmp);
    int** ans = malloc(intervalsSize * sizeof(int*));
    *returnColumnSizes = malloc(intervalsSize * sizeof(int));
    int idx = 0;
    for(int i = 0; i < intervalsSize; i++){
        if(idx == 0 || intervals[i][0] > ans[idx - 1][1]){
            ans[idx] = malloc(2 * sizeof(int));
            ans[idx][0] = intervals[i][0];
            ans[idx][1] = intervals[i][1];
            (*returnColumnSizes)[idx] = 2;
            idx++;
        }else{
            if(intervals[i][1] > ans[idx - 1][1]){
                ans[idx - 1][1] = intervals[i][1];
            }
        }
    }
    *returnSize = idx;
    return ans;
}