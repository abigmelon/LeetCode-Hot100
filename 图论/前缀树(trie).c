#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

typedef struct Node{
    struct Node* son[26];
    bool end;
} Node;

typedef struct{
    Node* root;
} Trie;

Trie* trieCreate(){
    Trie* obj = malloc(sizeof(Trie));
    obj->root = calloc(1, sizeof(Node));
    return obj;
}

void trieInsert(Trie* obj, char* word){
    Node* cur = obj->root;
    for(int i = 0; word[i]; i++){
        int c = word[i] - 'a';
        if(cur->son[c] == NULL){
            cur->son[c] = calloc(1, sizeof(Node));
        }
        cur = cur->son[c];
    }
    cur->end = true;
}

int trieFind(Trie* obj, char* word){
    Node* cur = obj->root;
    for(int i = 0; word[i]; i++){
        int c = word[i] - 'a';
        if(cur->son[c] == NULL){
            return 0;
        }
        cur = cur->son[c];
    }
    return cur->end ? 2 : 1;
}

bool trieSearch(Trie* obj, char* word) {
    return trieFind(obj, word) == 2;
}

bool trieStartsWith(Trie* obj, char* prefix) {
    return trieFind(obj, prefix) != 0;
}

void trieFreeNode(Node* node) {
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < 26; i++) {
        trieFreeNode(node->son[i]);
    }
    free(node);
}

void trieFree(Trie* obj) {
    trieFreeNode(obj->root);
    free(obj);
}