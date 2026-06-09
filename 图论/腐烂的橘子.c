#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

int orangesRotting(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize, n = gridColSize[0];
    int** queue = malloc(sizeof(int*) * m * n);
    memset(queue, -1, sizeof(int*) * m * n);
    int head = 0, tail = -1;
    int freshCnt = 0;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(grid[i][j] == 1) freshCnt++;
            else if(grid[i][j] == 2){
                queue[++tail] = malloc(sizeof(int) * 2);
                queue[tail][0] = i;
                queue[tail][1] = j;
            }
        }
    }
    int ways[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int minute = 0;
    while(head <= tail){
        int size = tail - head + 1;
        int rotted = 0;
        for(int k  = 0; k < size; k++){
            int* cur = queue[head++];
            int i = cur[0], j = cur[1];
            free(cur);
            for(int d = 0; d < 4; d++){
                int ii = i + ways[d][0], jj = j + ways[d][1];
                if(ii >= 0 && ii < m && jj >= 0 && jj < n && grid[ii][jj] == 1){
                    grid[ii][jj] = 2;
                    freshCnt--;
                    rotted = 1;
                    queue[++tail] = malloc(sizeof(int) * 2);
                    queue[tail][0] = ii;
                    queue[tail][1] = jj;
                }
            }
        }
        if(rotted) minute++;
    }
    return freshCnt == 0 ? minute : -1;
}