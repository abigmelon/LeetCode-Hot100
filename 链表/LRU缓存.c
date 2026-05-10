#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct DLinkedNode {
    int key;
    int value;
    struct DLinkedNode *prev;
    struct DLinkedNode *next;
} DLinkedNode;

typedef struct HashEntry {
    int key;
    DLinkedNode *node;
    struct HashEntry *next;
} HashEntry;

typedef struct {
    DLinkedNode *head;
    DLinkedNode *tail;
    HashEntry   **hash;
    int hashSize;
    int capacity;
    int size;
} LRUCache;

static int hashFunc(LRUCache *obj, int key) {
    int k = key < 0 ? -key : key;
    return k % obj->hashSize;
}

static DLinkedNode* hashGet(LRUCache *obj, int key) {
    int idx = hashFunc(obj, key);
    HashEntry *entry = obj->hash[idx];
    while (entry) {
        if (entry->key == key)
            return entry->node;
        entry = entry->next;
    }
    return NULL;
}

static void hashPut(LRUCache *obj, int key, DLinkedNode *node) {
    int idx = hashFunc(obj, key);
    HashEntry *entry = (HashEntry*)malloc(sizeof(HashEntry));
    entry->key  = key;
    entry->node = node;
    entry->next = obj->hash[idx];
    obj->hash[idx] = entry;
}

static void hashRemove(LRUCache *obj, int key) {
    int idx = hashFunc(obj, key);
    HashEntry *prev = NULL;
    HashEntry *cur  = obj->hash[idx];
    while (cur) {
        if (cur->key == key) {
            if (prev)
                prev->next = cur->next;
            else
                obj->hash[idx] = cur->next;
            free(cur);
            return;
        }
        prev = cur;
        cur  = cur->next;
    }
}

static void removeNode(LRUCache *obj, DLinkedNode *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

static void addToHead(LRUCache *obj, DLinkedNode *node) {
    node->prev = obj->head;
    node->next = obj->head->next;
    obj->head->next->prev = node;
    obj->head->next = node;
}

static void moveToHead(LRUCache *obj, DLinkedNode *node) {
    removeNode(obj, node);
    addToHead(obj, node);
}

static DLinkedNode* removeTail(LRUCache *obj) {
    DLinkedNode *node = obj->tail->prev;
    removeNode(obj, node);
    return node;
}

LRUCache* lRUCacheCreate(int capacity) {
    LRUCache *cache = (LRUCache*)malloc(sizeof(LRUCache));

    cache->head = (DLinkedNode*)malloc(sizeof(DLinkedNode));
    cache->tail = (DLinkedNode*)malloc(sizeof(DLinkedNode));
    cache->head->prev = NULL;
    cache->head->next = cache->tail;
    cache->tail->prev = cache->head;
    cache->tail->next = NULL;

    cache->hashSize = capacity * 2 + 1;
    cache->hash = (HashEntry**)calloc(cache->hashSize, sizeof(HashEntry*));

    cache->capacity = capacity;
    cache->size     = 0;

    return cache;
}

int lRUCacheGet(LRUCache* obj, int key) {
    DLinkedNode *node = hashGet(obj, key);
    if (node == NULL)
        return -1;

    moveToHead(obj, node);
    return node->value;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    DLinkedNode *node = hashGet(obj, key);

    if (node != NULL) {
        node->value = value;
        moveToHead(obj, node);
    } else {
        DLinkedNode *newNode = (DLinkedNode*)malloc(sizeof(DLinkedNode));
        newNode->key   = key;
        newNode->value = value;

        addToHead(obj, newNode);
        hashPut(obj, key, newNode);
        obj->size++;

        if (obj->size > obj->capacity) {
            DLinkedNode *evicted = removeTail(obj);
            hashRemove(obj, evicted->key);
            free(evicted);
            obj->size--;
        }
    }
}

void lRUCacheFree(LRUCache* obj) {
    DLinkedNode *cur = obj->head->next;
    while (cur != obj->tail) {
        DLinkedNode *tmp = cur;
        cur = cur->next;
        free(tmp);
    }

    for (int i = 0; i < obj->hashSize; i++) {
        HashEntry *entry = obj->hash[i];
        while (entry) {
            HashEntry *tmp = entry;
            entry = entry->next;
            free(tmp);
        }
    }

    free(obj->hash);
    free(obj->head);
    free(obj->tail);
    free(obj);
}

