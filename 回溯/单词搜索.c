#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

bool dfs(char** board, int boardSize, int* boardColSize, char* word, int i, int j, int index){
    if(word[index] == '\0') return true;
    if(i < 0 || i >= boardSize || j < 0 || j >= boardColSize[0] || board[i][j] != word[index]) return false;
    
    char temp = board[i][j];
    board[i][j] = '*';
    
    bool i1 = dfs(board, boardSize, boardColSize, word, i + 1, j, index + 1);
    bool i2 = dfs(board, boardSize, boardColSize, word, i - 1, j, index + 1);
    bool i3 = dfs(board, boardSize, boardColSize, word, i, j + 1, index + 1);
    bool i4 = dfs(board, boardSize, boardColSize, word, i, j - 1, index + 1);
    if(i1 || i2 || i3 || i4) return true;
    board[i][j] = temp;
    return false;
}

// 终止条件
// 剪枝
// 递归（四种情况）

bool exist(char** board, int boardSize, int* boardColSize, char* word) {
    for(int i = 0; i < boardSize; i++){
        for(int j = 0; j < boardColSize[0]; j++){
            if(board[i][j] == word[0]){
                bool flag = dfs(board, boardSize, boardColSize, word, i, j, 0);
                if(flag) return flag;
            }
        }
    }
    return false;
}