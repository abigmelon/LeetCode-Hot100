#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

typedef struct {
    int* maxHeap;
    int* minHeap;
    int maxSize;
    int minSize;
    int maxCap;
    int minCap;
} MedianFinder;

void maxHeapPush(int* heap, int* size, int val) {
    int i = (*size)++;
    while(i > 0 && val > heap[(i - 1) / 2]){
        heap[i] = heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap[i] = val;
}

int maxHeapPop(int* heap, int* size) {
    int top = heap[0];
    int val = heap[--(*size)];
    int i = 0;
    while(i * 2 + 1 < *size){
        int child = i * 2 + 1;
        if(child + 1 < *size && heap[child + 1] > heap[child]) child++;
        if(val >= heap[child]) break;
        heap[i] = heap[child];
        i = child;
    }
    heap[i] = val;
    return top;
}

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

MedianFinder* medianFinderCreate() {
    MedianFinder* obj = malloc(sizeof(MedianFinder));
    obj->maxCap = 1024;
    obj->minCap = 1024;
    obj->maxHeap = malloc(obj->maxCap * sizeof(int));
    obj->minHeap = malloc(obj->minCap * sizeof(int));
    obj->maxSize = 0;
    obj->minSize = 0;
    return obj;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    if(obj->maxSize == 0 || num <= obj->maxHeap[0]){
        if(obj->maxSize == obj->maxCap){
            obj->maxCap *= 2;
            obj->maxHeap = realloc(obj->maxHeap, obj->maxCap * sizeof(int));
        }
        maxHeapPush(obj->maxHeap, &obj->maxSize, num);
    } else {
        if(obj->minSize == obj->minCap){
            obj->minCap *= 2;
            obj->minHeap = realloc(obj->minHeap, obj->minCap * sizeof(int));
        }
        minHeapPush(obj->minHeap, &obj->minSize, num);
    }
    if(obj->maxSize > obj->minSize + 1){
        int val = maxHeapPop(obj->maxHeap, &obj->maxSize);
        if(obj->minSize == obj->minCap){
            obj->minCap *= 2;
            obj->minHeap = realloc(obj->minHeap, obj->minCap * sizeof(int));
        }
        minHeapPush(obj->minHeap, &obj->minSize, val);
    } else if(obj->minSize > obj->maxSize){
        int val = minHeapPop(obj->minHeap, &obj->minSize);
        if(obj->maxSize == obj->maxCap){
            obj->maxCap *= 2;
            obj->maxHeap = realloc(obj->maxHeap, obj->maxCap * sizeof(int));
        }
        maxHeapPush(obj->maxHeap, &obj->maxSize, val);
    }
}

double medianFinderFindMedian(MedianFinder* obj) {
    if(obj->maxSize > obj->minSize){
        return obj->maxHeap[0];
    }
    return (obj->maxHeap[0] + obj->minHeap[0]) / 2.0;
}

void medianFinderFree(MedianFinder* obj) {
    free(obj->maxHeap);
    free(obj->minHeap);
    free(obj);
}
