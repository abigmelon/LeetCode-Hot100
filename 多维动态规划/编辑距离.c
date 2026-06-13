#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

int minDistance(char* word1, char* word2) {
    int m = strlen(word1), n = strlen(word2);
    int** dp = (int**)malloc((m + 1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        dp[i] = (int*)malloc((n + 1) * sizeof(int));
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j;
    }
    for (int i = 0; i <= m; i++) {
        dp[i][0] = i;
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;      //三种操作
            if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);     //从左上角移过来
            }
        }
    }
    int result = dp[m][n];
    return result;
}
