#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include "../uthash.h"

typedef struct {
    int key;
    int freq;
    UT_hash_handle hh;
} HashEntry;

typedef struct {
    int val;
    int freq;
} HeapNode;

void minHeapPush(HeapNode* heap, int* size, HeapNode node) {
    int i = (*size)++;
    while(i > 0 && node.freq < heap[(i - 1) / 2].freq){
        heap[i] = heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap[i] = node;
}

HeapNode minHeapPop(HeapNode* heap, int* size) {
    HeapNode top = heap[0];
    HeapNode val = heap[--(*size)];
    int i = 0;
    while(i * 2 + 1 < *size){
        int child = i * 2 + 1;
        if(child + 1 < *size && heap[child + 1].freq < heap[child].freq) child++;
        if(val.freq <= heap[child].freq) break;
        heap[i] = heap[child];
        i = child;
    }
    heap[i] = val;
    return top;
}

int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    HashEntry* hash = NULL;
    HashEntry* e;
    for(int i = 0; i < numsSize; i++){
        HASH_FIND_INT(hash, &nums[i], e);
        if(e == NULL){
            e = malloc(sizeof(HashEntry));
            e->key = nums[i];
            e->freq = 1;
            HASH_ADD_INT(hash, key, e);
        } else {
            e->freq++;
        }
    }
    HeapNode* heap = malloc(k * sizeof(HeapNode));
    int size = 0;
    HashEntry *cur, *tmp;
    HASH_ITER(hh, hash, cur, tmp){
        HeapNode node = {cur->key, cur->freq};
        if(size < k){
            minHeapPush(heap, &size, node);
        } else if(node.freq > heap[0].freq){
            minHeapPop(heap, &size);
            minHeapPush(heap, &size, node);
        }
    }
    *returnSize = k;
    int* ans = malloc(k * sizeof(int));
    for(int i = k - 1; i >= 0; i--){
        HeapNode top = minHeapPop(heap, &size);
        ans[i] = top.val;
    }
    HASH_ITER(hh, hash, cur, tmp){
        HASH_DEL(hash, cur);
        free(cur);
    }
    free(heap);
    return ans;
}
