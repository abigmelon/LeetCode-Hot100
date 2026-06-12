#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

char result[1024][9][10];
int ansCount = 0;
char board[9][10];
bool col[9];    // 列占用，col[j] = 第j列是否有皇后
bool dg[18];    // 主对角线 "\"，下标 = row - col + n，同一条对角线上 row-col 是常数
bool ug[18];    // 副对角线 "/"，下标 = row + col，同一条对角线上 row+col 是常数

void dfs(int row, int n){
    if(row == n){
        for(int i = 0; i < n; i++){
            strcpy(result[ansCount][i], board[i]);
        }
        ansCount++;
        return;
    }
    for(int c = 0; c < n; c++){
        if(col[c] || dg[row - c + n] || ug[row + c]) continue;

        board[row][c] = 'Q';
        col[c] = dg[row - c + n] = ug[row + c] = true;

        dfs(row + 1, n);

        board[row][c] = '.';
        col[c] = dg[row - c + n] = ug[row + c] = false;
    }
}

char*** solveNQueens(int n, int* returnSize, int** returnColumnSizes) {
    ansCount = 0;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            board[i][j] = '.';
        }
        board[i][n] = '\0';
    }
    memset(col, 0, sizeof(col));
    memset(dg, 0, sizeof(dg));
    memset(ug, 0, sizeof(ug));

    dfs(0, n);

    *returnSize = ansCount;
    *returnColumnSizes = malloc(sizeof(int) * ansCount);
    char*** ans = malloc(sizeof(char**) * ansCount);
    for(int i = 0; i < ansCount; i++){
        (*returnColumnSizes)[i] = n;
        ans[i] = malloc(sizeof(char*) * n);
        for(int j = 0; j < n; j++){
            ans[i][j] = strdup(result[i][j]);
        }
    }

    return ans;
}

// 终止条件
// 剪枝
// 递归
// 还原