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

// 解析：
// 递归法，由于两个链表是不增的，所以两个头节点中一定有一个是最小的
// 把这个最小的节点作为头节点，然后递归把剩下的链表和另一个链表进行合并，最后返回头节点就行