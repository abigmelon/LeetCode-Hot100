#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int ans[101][10001];
int ans_ready = 0;

void ensure_init() {
    if (!ans_ready) {
        memset(ans, -1, sizeof(ans));
        ans_ready = 1;
    }
}

int find(int i, int j) {
    if (i == 0) {
        return j == 0 ? 0 : INT_MAX;
    }

    int* cur = &ans[i][j];
    if (*cur != -1) {
        return *cur;
    }

    if (j < i * i) {
        *cur = find(i - 1, j);
    } else {
        *cur = MIN(find(i - 1, j),
                   find(i, j - i * i) + 1);
    }
    return *cur;
}

int numSquares(int n) {
    ensure_init();
    return find((int)sqrt(n), n);
}