#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

_Bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target) {
    int m = matrixSize, n = matrixColSize[0];
    int i = 0, j = n - 1;
    while (i < m && j >= 0) {
        if (matrix[i][j] == target) {
            return 1;
        }
        if (matrix[i][j] < target) {
            i++;
        } else {
            j--;
        }
    }
    return 0;
}

// 最右上那一条始终是单调增的，非常适合用来作为比较的对象。
