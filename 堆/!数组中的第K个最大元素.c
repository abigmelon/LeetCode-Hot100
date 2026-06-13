#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

void minHeapPush(int* heap, int* size, int val) {
    int i = (*size)++;
    while(i > 0 && val < heap[(i - 1) / 2]){
        heap[i] = heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap[i] = val;
}

int minHeapPop(int* heap, int* size) {
    int top = heap[0];
    int val = heap[--(*size)];
    int i = 0;
    while(i * 2 + 1 < *size){
        int child = i * 2 + 1;
        if(child + 1 < *size && heap[child + 1] < heap[child]) child++;
        if(val <= heap[child]) break;
        heap[i] = heap[child];
        i = child;
    }
    heap[i] = val;
    return top;
}

int findKthLargest(int* nums, int numsSize, int k) {
    int* heap = malloc(k * sizeof(int));
    int size = 0;
    for(int i = 0; i < k; i++){
        minHeapPush(heap, &size, nums[i]);
    }
    for(int i = k; i < numsSize; i++){
        if(nums[i] > heap[0]){
            minHeapPop(heap, &size);
            minHeapPush(heap, &size, nums[i]);
        }
    }
    int result = heap[0];
    free(heap);
    return result;
}
