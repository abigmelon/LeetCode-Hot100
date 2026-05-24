#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

char* minWindow(char* s, char* t) {
    int need[128];
    memset(need, 0, 128 * sizeof(int));
    int needCnt = 0;
    for(int i = 0; t[i] != '\0'; i++){
        if(need[t[i]] == 0) needCnt++;
        need[t[i]]++;
    }
    int window[128];
    memset(window, 0, 128 * sizeof(int));
    int cnt = 0;
    int left = 0, right = 0;
    int start = 0, len = INT_MAX - 1;
    while(s[right] != '\0'){
        char c = s[right++];
        if(need[c] > 0){
            window[c]++;
            if(window[c] == need[c]) cnt++;
        }
        while(cnt == needCnt){
            if(len > right - left){
                start = left;
                len = right - left;
            }
            char head = s[left++];
            if(need[head] > 0){
                if(window[head] == need[head]) cnt--;
                window[head]--;
            }
        }   
    }
    if(len == INT_MAX - 1){
        char* empty = (char*)malloc(1);
        empty[0] = '\0';
        return empty;
    }
    char* res = malloc((len + 1) * sizeof(char));
    strncpy(res, s + start, len);
    res[len] = '\0';
    return res;
}