#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include "../uthash.h"

#define MAX(a, b) ((b) > (a) ? (b) : (a))

typedef struct {
    int key;
    UT_hash_handle hh;
} HashEntry;

int longestConsecutive(int* nums, int numsSize) {
    HashEntry* hashSet = NULL;
    HashEntry* e;

    for (int i = 0; i < numsSize; i++) {
        HASH_FIND_INT(hashSet, &nums[i], e);
        if (e == NULL) {
            e = malloc(sizeof(HashEntry));
            e->key = nums[i];
            HASH_ADD_INT(hashSet, key, e);
        }
    }

    int ans = 0;
    HashEntry* tmp;
    HASH_ITER(hh, hashSet, e, tmp) {
        int x = e->key;
        int y = x - 1;
        HASH_FIND_INT(hashSet, &y, e);
        if (e) {
            continue;
        }

        y = x;
        do {
            y++;
            HASH_FIND_INT(hashSet, &y, e);
        } while (e);

        ans = MAX(ans, y - x);
    }

    HASH_ITER(hh, hashSet, e, tmp) {
        HASH_DEL(hashSet, e);
        free(e);
    }

    return ans;
}