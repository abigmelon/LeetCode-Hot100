#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int subarraySum1(int* nums, int numsSize, int k) {
    if(numsSize == 0) return 0;
    int* preSum = malloc((numsSize + 1) * sizeof(int));
    preSum[0] = 0;
    for(int i = 0; i < numsSize; i++){
        preSum[i + 1] = preSum[i] + nums[i];
    }
    int ans = 0;
    for(int i = 1; i <= numsSize; i++){
        for(int j = 0; j < i; j++){
            if(preSum[i] - preSum[j] == k) ans++;
        }
    }
    return ans;
}

// ========== 手动哈希表 (链地址法) ==========
#define HASH_SIZE 20011  // 取一个素数，略大于最大元素数

typedef struct HashNode {
    int key;              // 前缀和
    int count;            // 出现次数
    struct HashNode* next;
} HashNode;

static inline int hash(int key) {
    // 处理负数：先取模再加 TABLE_SIZE 再取模
    return (key % HASH_SIZE + HASH_SIZE) % HASH_SIZE;
}

int subarraySum(int* nums, int numsSize, int k) {
    HashNode* table[HASH_SIZE];
    memset(table, 0, sizeof(table));

    // 初始化：前缀和 0 出现 1 次（处理从头开始的子数组）
    HashNode* zero = (HashNode*)malloc(sizeof(HashNode));
    zero->key = 0;
    zero->count = 1;
    int h = hash(0);
    zero->next = table[h];
    table[h] = zero;

    int preSum = 0, ans = 0;

    for (int i = 0; i < numsSize; i++) {
        preSum += nums[i];
        int target = preSum - k;

        // 1. 查表：之前有几个 preSum == target
        h = hash(target);
        HashNode* cur = table[h];
        while (cur) {
            if (cur->key == target) {
                ans += cur->count;
                break;
            }
            cur = cur->next;
        }

        // 2. 将当前前缀和插入/更新
        h = hash(preSum);
        cur = table[h];
        HashNode* found = NULL;
        while (cur) {
            if (cur->key == preSum) {
                found = cur;
                break;
            }
            cur = cur->next;
        }
        if (found) {
            found->count++;          // 已存在，次数+1
        } else {
            HashNode* node = (HashNode*)malloc(sizeof(HashNode));
            node->key = preSum;
            node->count = 1;
            node->next = table[h];   // 头插法
            table[h] = node;
        }
    }

    // 3. 释放哈希表内存
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* cur = table[i];
        while (cur) {
            HashNode* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }

    return ans;
}
