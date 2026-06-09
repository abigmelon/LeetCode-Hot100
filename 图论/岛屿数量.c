#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

void dfs(char** grid, int m, int n, int i, int j) {
    if(i < 0 || i >= m || j < 0 || j >= n || grid[i][j] != '1'){
        return;
    }       //终止条件
    grid[i][j] = '2';
    dfs(grid, m, n, i, j - 1);
    dfs(grid, m, n, i, j + 1);
    dfs(grid, m, n, i - 1, j);
    dfs(grid, m, n, i + 1, j);
}       //向一个岛屿的四周扩散

int numIslands(char** grid, int gridSize, int* gridColSize) {
    int m = gridSize, n = gridColSize[0];       //行数和列数
    int ans = 0;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(grid[i][j] == '1'){
                dfs(grid, m, n, i, j);
                ans++;
            }
        }
    }
    return ans;
}