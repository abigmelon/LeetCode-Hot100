#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int maxProfit1(int* prices, int pricesSize) {
    int max = 0;
    for(int i = 0; i < pricesSize; i++){
        for(int j = i + 1; j < pricesSize; j++){
            if((prices[j] - prices[i]) > 0){
                int delta = prices[j] - prices[i];
                max = max > delta ? max : delta;
            }
        }
    }
    return max;
}

// 更聪明的做法：

int maxProfit(int* prices, int pricesSize) {
    int minPrice = prices[0];
    int ans = 0;
    for(int i = 0; i < pricesSize; i++){
        int p = prices[i];
        ans = ans > p - minPrice ? ans : p - minPrice;
        minPrice = minPrice > p ? p : minPrice;
    }
    return ans;
}

// 对于每一个当前元素而言，它总想找到它前面最小的那个
// 所以只需动态维护最小值就可以降低复杂度