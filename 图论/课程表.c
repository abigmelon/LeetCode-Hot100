#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

bool dfs(int u, int** adj, int* adjSize, int* colors) {
    colors[u] = 1;      //标记自己
    for (int i = 0; i < adjSize[u]; i++) {
        int v = adj[u][i];
        if (colors[v] == 1) {
            return true;        //找到自己了
        }
        if (colors[v] == 0) {
            if (dfs(v, adj, adjSize, colors)) {
                return true;        //递归交给后面，如果成环了就把结果传上来
            }
        }
    }
    colors[u] = 2;      //标记这个地方没有环
    return false;
}

bool canFinish(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize) {
    bool cycle = false;
    int* outSize = malloc(sizeof(int) * numCourses);
    int* length = malloc(sizeof(int) * numCourses);
    memset(outSize, 0, sizeof(int) * numCourses);
    memset(length, 0, sizeof(int) * numCourses);
    for(int i = 0; i < prerequisitesSize; i++){
        int in = prerequisites[i][1];
        int out = prerequisites[i][0];
        outSize[in]++;
    }
    int** graph = malloc(sizeof(int*) * numCourses);
    for(int i = 0; i < numCourses; i++){
        if(outSize[i] > 0) graph[i] = malloc(sizeof(int) * outSize[i]);
        else graph[i] = malloc(sizeof(int) * 1);
    }
    for(int i = 0; i < prerequisitesSize; i++){
        int in = prerequisites[i][1];
        int out = prerequisites[i][0];
        graph[in][length[in]] = out;
        length[in]++;
    }
    int* colors = malloc(sizeof(int) * numCourses);
    memset(colors, 0, sizeof(int) * numCourses);
    for(int i = 0; i < numCourses; i++){
        if(colors[i] == 0){
            if(dfs(i, graph, outSize, colors)){
                cycle = true;
                break;
            }
        }
    }
    for(int i = 0; i < numCourses; i++) free(graph[i]);
    free(graph);
    free(outSize);
    free(length);
    free(colors);
    return !cycle;
}
