#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

int longestCommonSubsequence(char* text1, char* text2) {
    int m = strlen(text1), n = strlen(text2);
    int arr[m][n];
    if(text1[0] == text2[0]) arr[0][0] = 1;
    else arr[0][0] = 0;
    for(int i = 1; i < n; i++){
        int same = 0;
        if(text1[0] == text2[i]) same = 1;
        arr[0][i] = (arr[0][i - 1] || same);
    }
    for(int i = 1; i < m; i++){
        int same = 0;
        if(text2[0] == text1[i]) same = 1;
        arr[i][0] = (arr[i - 1][0] || same);
    }
    for(int i = 1; i < m; i++){
        for(int j = 1; j < n; j++){
            if(text1[i] == text2[j])
                arr[i][j] = arr[i - 1][j - 1] + 1;
            else
                arr[i][j] = arr[i - 1][j] > arr[i][j - 1] ? arr[i - 1][j] : arr[i][j - 1];
        }
    }
    return arr[m - 1][n - 1];
}

// if(text1[i] == text2[j])
//                 arr[i][j] = arr[i - 1][j - 1] + 1;
//             else
//                 arr[i][j] = arr[i - 1][j] > arr[i][j - 1] ? arr[i - 1][j] : arr[i][j - 1];
// 重点就在这里，如果相同直接继承左上角的值再加1，
// 如果不相同选左边和上边最大的值就好