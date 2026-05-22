#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MAX(a, b) (a > b ? a : b)

int longestValidParentheses(char* s) {
    int n = strlen(s);
    int* stack = (int*)malloc((n + 1) * sizeof(int));
    int top = 0;
    stack[top++] = -1;
    int maxLen = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            stack[top++] = i;
        } else {
            top--;
            if (top == 0) {
                stack[top++] = i;
            } else {
                maxLen = MAX(maxLen, i - stack[top - 1]);
            }
        }
    }
    free(stack);
    return maxLen;
}

