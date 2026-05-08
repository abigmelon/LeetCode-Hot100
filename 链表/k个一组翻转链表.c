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
    int size = 0;
    while (head != NULL) {
        size++;
        head = head->next;
    }
    return size;
}

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

struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    if (head == NULL || sizeList(head) < k) return head;
    struct ListNode *groupTail = head;
    for (int i = 1; i < k; i++) {
        groupTail = groupTail->next;
    }
    struct ListNode *nextGroup = groupTail->next;
    groupTail->next = NULL;
    struct ListNode *newHead = reverseList(head);
    head->next = reverseKGroup(nextGroup, k);
    return newHead;
}

// 解析：
// 跟两两交换一个思路，只是组大小从2变成了k：
// 1.不够k个就不用反转，直接吐出来
// 2.用groupTail找到第k个节点，它就是反转后的新head
// 3.剪断链表（groupTail->next = NULL），让reverseList只反转前k个
// 4.原来的head变成尾巴，接上递归处理好的后面部分
// 5.返回新的head（即原来的第k个节点）