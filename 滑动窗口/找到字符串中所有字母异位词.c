#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int* findAnagrams1(char* s, char* p, int* returnSize) {
    int sLen = strlen(s), pLen = strlen(p);
    *returnSize = 0;
    if (pLen > sLen) return NULL;
    int* ans = (int*)malloc(sLen * sizeof(int));
    int cntP[26] = {0}, cntS[26];
    for (int i = 0; i < pLen; i++) cntP[p[i] - 'a']++;
    for (int idx = 0; idx + pLen <= sLen; idx++) {
        memset(cntS, 0, sizeof(cntS));
        for (int j = 0; j < pLen; j++) cntS[s[idx + j] - 'a']++;
        int match = 1;
        for (int k = 0; k < 26; k++) {
            if (cntS[k] != cntP[k]) {
            match = 0; break;
            }
        }
        if (match) ans[(*returnSize)++] = idx;
    }
    return ans;
}

// 滑动窗口会更快一些：

int* findAnagrams(char* s, char* p, int* returnSize) {
    int sLen = strlen(s), pLen = strlen(p);
    *returnSize = 0;
    if (pLen > sLen) return NULL;
    int* ans = (int*)malloc(sLen * sizeof(int));
    int cnt[26] = {0};
    for (int i = 0; i < pLen; i++) cnt[p[i] - 'a']++;
    int diff = 0;
    for (int i = 0; i < 26; i++) if (cnt[i] != 0) diff++;
    for (int i = 0; i < sLen; i++) {
        int in = s[i] - 'a';
        cnt[in]--;
        if (cnt[in] == 0) diff--;
        else if (cnt[in] == -1) diff++;
        if (i >= pLen) {
            int out = s[i - pLen] - 'a';
            cnt[out]++;
            if (cnt[out] == 0) diff--;
            else if (cnt[out] == 1) diff++;
        }
        if (diff == 0) ans[(*returnSize)++] = i - pLen + 1;
    }
    return ans;
}