#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

void sortColors(int* nums, int numsSize) {
    int p0 = 0, p1 = 0;
    for (int i = 0; i < numsSize; i++) {
        int x = nums[i];
        nums[i] = 2;
        if (x <= 1) {
            nums[p1++] = 1;
        }
        if (x == 0) {
            nums[p0++] = 0;
        }
    }
}