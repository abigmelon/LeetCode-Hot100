#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    if (list1 == NULL) {
        return list2;
    }
    if (list2 == NULL) {
        return list1;
    }
    struct ListNode *head = NULL;
    if (list1->val < list2->val) {
        head = list1;
        head->next = mergeTwoLists(list1->next, list2);
    } else {
        head = list2;
        head->next = mergeTwoLists(list1, list2->next);
    }
    return head;
}

struct ListNode* sortList(struct ListNode* head) {
    if (head == NULL || head->next == NULL) return head;
    struct ListNode *slow = head;
    struct ListNode *fast = head;
    struct ListNode *prev = NULL;
    while (fast != NULL && fast->next != NULL) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    prev->next = NULL;
    struct ListNode *left = sortList(head);
    struct ListNode *right = sortList(slow);
    return mergeTwoLists(left, right);
}

// 解析：
// 归并排序（自顶向下），把链表不断切成两半再合并：
// 1.终止条件：空或单节点，已经有序，直接返回
// 2.快慢指针找中点，prev用来剪断链表（prev->next = NULL）
// 3.递归排序左半(head)和右半(slow)
// 4.mergeTwoLists合并两个有序链表