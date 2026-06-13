#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

int minPathSum(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];
    int shortWay[m][n];
    shortWay[0][0] = grid[0][0];
    for(int i = 1; i < n; i++){
        shortWay[0][i] = shortWay[0][i - 1] + grid[0][i];
    }
    for(int i = 1; i < m; i++){
        shortWay[i][0] = shortWay[i - 1][0] + grid[i][0];
    }
    for(int i = 1; i < m; i++){
        for(int j = 1; j < n; j++){
            shortWay[i][j] = min(shortWay[i - 1][j], shortWay[i][j - 1]) + grid[i][j];
        }
    }
    return shortWay[m - 1][n - 1];
}

// 写宏的时候注意括号保护，别省这一步