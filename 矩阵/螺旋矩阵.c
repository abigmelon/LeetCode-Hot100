#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};  // 右、下、左、上
    int m = matrixSize, n = matrixColSize[0];
    int* ans = malloc(m * n * sizeof(int));
    *returnSize = m * n;
    int i = 0, j = 0, d = 0, x = 0, y = 0;
    for(int k = 0; k < m * n; k++){
        ans[k] = matrix[i][j];
        matrix[i][j] = INT_MAX;
        x = i + directions[d][0];
        y = j + directions[d][1];
        if(x < 0 || x >= m || y < 0 || y >= n || matrix[x][y] == INT_MAX){
            d = (d + 1) % 4;
        }
        i += directions[d][0];
        j += directions[d][1];
    }
    return ans;
}