#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int** generate(int numRows, int* returnSize, int** returnColumnSizes) {
    int** ans = malloc(numRows * sizeof(int*));
    *returnSize = numRows;
    *returnColumnSizes = malloc(numRows * sizeof(int));
    for(int i = 0; i < numRows; i++){
        (*returnColumnSizes)[i] = i + 1;
        ans[i] = malloc((i + 1) * sizeof(int));
        ans[i][0] = ans[i][i] = 1;
        for(int j = 1; j < i; j++){
            ans[i][j] = ans[i - 1][j - 1] + ans[i - 1][j];
        } 
    }
    return ans;
}