#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

int expand(char* s, int left, int right){
    while(left >= 0 && right < strlen(s) && s[left] == s[right]){
        left--;
        right++;
    }
    return right - left - 1;
}

char* longestPalindrome(char* s) {
    int n = strlen(s);
    if(n == 0) return NULL;
    int start = 0, maxLen = 0;
    for(int i = 0; i < n; i++){
        int len1 = expand(s, i, i);
        int len2 = expand(s, i, i + 1);
        int len = len1 > len2 ? len1 : len2;
        if(len > maxLen){
            maxLen = len;
            start = i - (len - 1) / 2;
        }
    }
    char *res = malloc(sizeof(char) * (maxLen + 1));
    strncpy(res, s + start, maxLen);
    res[maxLen] = '\0';
    return res;
}

// 奇偶分开讨论，这个最好想