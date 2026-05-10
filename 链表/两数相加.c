#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode ans;
    ans.next = NULL;
    struct ListNode *tail = &ans;
    int add = 0;
    while (l1 || l2) {
        int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + add;
        struct ListNode *node = (struct ListNode *)malloc(sizeof(struct ListNode));
        node->val = sum % 10;
        node->next = NULL;
        add = sum / 10;
        tail->next = node;
        tail = node;
        if (l1) l1 = l1->next;
        if (l2) l2 = l2->next;
    }
    if (add) {
        struct ListNode *node = (struct ListNode *)malloc(sizeof(struct ListNode));
        node->val = 1;
        node->next = NULL;
        tail->next = node;
    }   //记得检查最后一位
    return ans.next;
}

// 解析：
// 注意保留进位，头插和尾插的区别和遗落的最后一位1（如果存在）