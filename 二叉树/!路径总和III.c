#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include "../uthash.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef struct {
    long long key;
    int val;
    UT_hash_handle hh;
} HashMap;

int dfs(struct TreeNode* node, long long curSum, int targetSum, HashMap** map) {
    if(node == NULL) return 0;
    curSum += node->val;
    long long need = curSum - targetSum;
    int count = 0;
    HashMap* e;
    HASH_FIND(hh, *map, &need, sizeof(long long), e);
    if(e) count = e->val;
    HASH_FIND(hh, *map, &curSum, sizeof(long long), e);
    if(e == NULL){
        e = malloc(sizeof(HashMap));
        e->key = curSum;
        e->val = 1;
        HASH_ADD(hh, *map, key, sizeof(long long), e);
    } else {
        e->val++;
    }
    count += dfs(node->left, curSum, targetSum, map);
    count += dfs(node->right, curSum, targetSum, map);
    HASH_FIND(hh, *map, &curSum, sizeof(long long), e);
    e->val--;
    if(e->val == 0){
        HASH_DEL(*map, e);
        free(e);
    }
    return count;
}

int pathSum(struct TreeNode* root, int targetSum) {
    HashMap* map = NULL;
    HashMap* zero = malloc(sizeof(HashMap));
    zero->key = 0;
    zero->val = 1;
    HASH_ADD(hh, map, key, sizeof(long long), zero);
    int ans = dfs(root, 0, targetSum, &map);
    HASH_DEL(map, zero);
    free(zero);
    return ans;
}
