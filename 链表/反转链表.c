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

//解析：
//反转其实不是把节点反过来，是把指针反过来
//比如把->变成<-，这样子应该好理解很多