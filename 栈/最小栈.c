#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int* stack;
    int* minStack;
    int top;
    int capacity;
} MinStack;


MinStack* minStackCreate() {
    MinStack* obj = malloc(sizeof(MinStack));
    obj->capacity = 10;
    obj->stack = malloc(obj->capacity * sizeof(int));
    obj->minStack = malloc(obj->capacity * sizeof(int));
    obj->top = -1;
    return obj;
}

void minStackPush(MinStack* obj, int val) {
    if(obj->top + 1 == obj->capacity){
        int newCap = obj->capacity << 1;
        obj->stack = realloc(obj->stack, newCap * sizeof(int));
        obj->minStack = realloc(obj->minStack, newCap * sizeof(int));
        obj->capacity = newCap;
    }
    obj->top++;
    obj->stack[obj->top] = val;
    if(obj->top == 0) obj->minStack[0] = val;
    else{
        obj->minStack[obj->top] = (val < obj->minStack[obj->top - 1] ? val : obj->minStack[obj->top - 1]);
    }
}

void minStackPop(MinStack* obj) {
    obj->top--;
}

int minStackTop(MinStack* obj) {
    return obj->stack[obj->top];
}

int minStackGetMin(MinStack* obj) {
    return obj->minStack[obj->top];
}

void minStackFree(MinStack* obj) {
    free(obj->stack);
    free(obj->minStack);
    free(obj);
}