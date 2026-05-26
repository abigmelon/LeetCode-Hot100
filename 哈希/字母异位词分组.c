#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

typedef struct{
    char* original;
    char* sorted;
} Pair;

int cmpChar(const void* a, const void* b){
    return *(char*)a - *(char*)b;
}

void sortString(char* s){
    int len = strlen(s);
    qsort(s, len, sizeof(char), cmpChar);
}

int cmpPair(const void* a, const void* b){
    Pair* A = (Pair*)a;
    Pair* B = (Pair*)b;
    return strcmp(A->sorted, B->sorted);
}

char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    Pair* pairs = malloc(strsSize * sizeof(Pair));
    for (int i = 0; i < strsSize; i++) {
        int len = strlen(strs[i]);
        pairs[i].sorted = malloc((len + 1) * sizeof(char));
        strcpy(pairs[i].sorted, strs[i]);
        sortString(pairs[i].sorted);
        pairs[i].original = strs[i];
    }
    qsort(pairs, strsSize, sizeof(Pair), cmpPair);
    int groupCnt = 0;
    for (int i = 0; i < strsSize; i++) {
        if (i == 0 || strcmp(pairs[i].sorted, pairs[i - 1].sorted) != 0) {
            groupCnt++;
        }
    }
    *returnSize = groupCnt;
    *returnColumnSizes = calloc(groupCnt, sizeof(int));
    char*** result = malloc(groupCnt * sizeof(char**));
    int groupIdx = 0;
    for (int i = 0; i < strsSize; i++) {
        if (i > 0 && strcmp(pairs[i].sorted, pairs[i - 1].sorted) != 0) {
            groupIdx++;
        }
        (*returnColumnSizes)[groupIdx]++;
    }
    for (int i = 0; i < groupCnt; i++) {
        result[i] = malloc((*returnColumnSizes)[i] * sizeof(char*));
    }
    int* pos = calloc(groupCnt, sizeof(int));
    groupIdx = 0;
    for (int i = 0; i < strsSize; i++) {
        if (i > 0 && strcmp(pairs[i].sorted, pairs[i - 1].sorted) != 0) {
            groupIdx++;
        }
        result[groupIdx][pos[groupIdx]++] = pairs[i].original;
    }
    free(pos);
    for (int i = 0; i < strsSize; i++) {
        free(pairs[i].sorted);
    }
    free(pairs);
    return result;
}