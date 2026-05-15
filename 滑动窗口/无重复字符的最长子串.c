#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int lengthOfLongestSubstring1(char* s) {
    int len = strlen(s);
    if (len == 0) return 0;

    int* exist = (int*)malloc(128 * sizeof(int));
    int max = 0;

    for (int start = 0; start < len; start++) {
        memset(exist, 0, 128 * sizeof(int));
        int cur = 0;
        for (int end = start; end < len; end++) {
            if (exist[(unsigned char)s[end]] == 0) {
                exist[(unsigned char)s[end]] = 1;
                cur++;
            } else {
                break;
            }
        }
        if (cur > max) max = cur;
    }

    free(exist);
    return max;
}

// 这个方法比较暴力，接下来这个用队列做，复杂度会低一些

int lengthOfLongestSubstring(char* s) {
    int len = strlen(s);
    if (len == 0) return 0;
    int lastPos[128];
    for (int i = 0; i < 128; i++) lastPos[i] = -1;
    int left = 0, max = 0;
    for (int right = 0; right < len; right++) {
        char ch = (char)s[right];
        if (lastPos[ch] >= left) {
            left = lastPos[ch] + 1;
        }
        lastPos[ch] = right;
        int curLen = right - left + 1;
        if (curLen > max) max = curLen;
    }
    return max;
}