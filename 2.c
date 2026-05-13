#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b){
    return *(int*)a - *(int*)b;
}

int findMax(int *a, int *b, int n){
    int amin = 0, amax = n - 1;
    int bmin = 0, bmax = n - 1;
    int ans = 0;
    for(int i = 0; i < n; i++){
        if(a[amin] > b[bmin]){
            ans += 3;
            amin++; bmin++;
        } else if(a[amax] > b[bmax]){
            ans += 3;
            amax--; bmax--;
        } else {
            if(a[amin] == b[bmax])
                ans += 2;
            else
                ans += 1;
            amin++; bmax--;
        }
    }
    return ans;
}

int main(){
    int n, c[1000], s[1000];
    while(scanf("%d", &n) == 1){
        if(n == 0) break;
        for(int i = 0; i < n; i++) scanf("%d", &c[i]);
        for(int i = 0; i < n; i++) scanf("%d", &s[i]);
        qsort(c, n, sizeof(int), cmp);
        qsort(s, n, sizeof(int), cmp);
        int max = findMax(s, c, n);
        int min = 4 * n - findMax(c, s, n);
        printf("%d %d\n", max, min);
    }
    return 0;
}
