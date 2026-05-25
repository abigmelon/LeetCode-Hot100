#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define SWAP(a, b) do { int tmp = (a); (a) = (b); (b) = tmp; } while (0)

void rotate(int** matrix, int matrixSize, int* matrixColSize) {
    int n = matrixSize;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            SWAP(matrix[i][j], matrix[j][i]);
        }
    }

    for (int i = 0; i < n; i++) {
        int* row = matrix[i];
        for (int j = 0; j < n / 2; j++) {
            SWAP(row[j], row[n - 1 - j]);
        }
    }
}

// 转置 + 行反转