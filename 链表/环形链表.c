#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

_Bool hasCycle(struct ListNode *head) {
    if (head == NULL || head->next == NULL) {
        return 0;
    }
    struct ListNode *slow = head;
    struct ListNode *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return 1;
        }
    }
    return 0;
}

// 解析：
// 快慢指针，之前在抖音上刷到过了，所以不难
// 主要是要知道这种方法