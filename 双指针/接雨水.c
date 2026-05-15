#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define MIN(a, b) (a < b ? a : b)

int trap(int* height, int heightSize) {
    int* preMax = malloc(heightSize * sizeof(int));
    int* sufMax = malloc(heightSize * sizeof(int));
    int lmax = 0, rmax = 0;
    for(int i = 0; i < heightSize; i++){
        if(height[i] > lmax) lmax = height[i];
        preMax[i] = lmax;
    }
    for(int i = heightSize - 1; i >= 0; i--){
        if(height[i] > rmax) rmax = height[i];
        sufMax[i] = rmax;
    }
    int sum = 0;
    for(int i = 0; i < heightSize; i++){
        int h = MIN(preMax[i], sufMax[i]) - height[i];
        if(h > 0) sum += h;
    }
    return sum;
}