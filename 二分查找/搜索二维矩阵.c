#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

_Bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target) {
    int m = matrixSize, n = matrixColSize[0];
    int left = -1, right = m * n;
    while(left + 1 < right){
        int mid = (left + right) / 2;
        int x = matrix[mid / n][mid % n];
        if(x == target) return 1;
        if(x < target) left = mid;
        else right = mid;
    }
    return 0;
}

// 本质是把二维数组转换为一维数组再去套二分模板