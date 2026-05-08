#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *detectCycle(struct ListNode *head) {
    struct ListNode *slow = head;
    struct ListNode *fast = head;
    while(fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            struct ListNode *p1 = head;
            struct ListNode *p2 = slow;
            while (p1 != p2) {
                p1 = p1->next;
                p2 = p2->next;
            }
            return p1;
        }
    }
    return NULL;
}

// 解析：
// 设头节点到入口需要a，头到相遇需要b，环长为c
// 2b-b=kc，b=kc
// 环中kc-a，再走a到环口
// 从起始点也是走a到环口，所以相遇点就是入口点
// 解题的关键在于利用这个二倍的关系
