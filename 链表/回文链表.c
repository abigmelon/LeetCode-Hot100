#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode *current = head;
    struct ListNode *pre = NULL;
    while (current != NULL) {
        struct ListNode *next = current->next;
        current->next = pre;
        pre = current;
        current = next;
    }
    return pre;
}

_Bool isPalindrome(struct ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return 1;
    }
    // 1. 计算链表长度
    int count = 0;
    struct ListNode* tmp = head;
    while (tmp != NULL) {
        count++;
        tmp = tmp->next;
    }
    // 2. 找到后半段的起点（整数除法自动处理奇偶）
    int mid = count / 2;
    tmp = head;
    for (int i = 0; i < mid; i++) {
        tmp = tmp->next;
    }
    // 3. 反转后半段
    struct ListNode* head2 = reverseList(tmp);
    // 4. 逐一比较
    while (head2 != NULL) {
        if (head->val != head2->val) {
            return 0;
        }
        head = head->next;
        head2 = head2->next;
    }
    return 1;
}