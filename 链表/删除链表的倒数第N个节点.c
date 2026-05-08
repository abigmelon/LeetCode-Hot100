#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

int sizeList(struct ListNode* head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    int size = sizeList(head);
    struct ListNode ans;
    ans.next = head;
    struct ListNode *p = &ans;
    for (int i = 0; i < size - n; i++) {
        p = p->next;
    }
    struct ListNode *del = p->next;
    p->next = del->next;
    free(del);
    return ans.next;
}