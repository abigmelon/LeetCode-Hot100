#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int* partitionLabels(char* s, int* returnSize) {
    int last[26] = {0};
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        last[s[i] - 'a'] = i;
    }
    int* result = (int*)malloc(sizeof(int) * len);
    *returnSize = 0;
    int start = 0, end = 0;
    for (int i = 0; i < len; i++) {
        if (last[s[i] - 'a'] > end) {
            end = last[s[i] - 'a'];
        }
        if (i == end) {
            result[(*returnSize)++] = end - start + 1;
            start = end + 1;
        }
    }
    return result;
}