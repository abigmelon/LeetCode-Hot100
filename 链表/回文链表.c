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
    int count = 0;
    struct ListNode* tmp = head;
    while (tmp != NULL) {
        count++;
        tmp = tmp->next;
    }
    int mid = count / 2;
    tmp = head;
    for (int i = 0; i < mid; i++) {
        tmp = tmp->next;
    }
    struct ListNode* head2 = reverseList(tmp);
    while (head2 != NULL) {
        if (head->val != head2->val) {
            return 0;
        }
        head = head->next;
        head2 = head2->next;
    }
    return 1;
}

//解析：
//首先找到链表的中点，然后把后半部分链表反转，最后比较前半部分和反转后的后半部分是否相等
//如果相等就是回文链表，否则就不是回文链表
//其实从这道题就可以看出来，有的题目是需要之前积累的思路（反转链表）来完成的，只要想到了就不难
//以下是更干净的写法：
// 876. 链表的中间结点
// struct ListNode* middleNode(struct ListNode* head) {
//     struct ListNode *slow = head, *fast = head;
//     while (fast && fast->next) {
//         slow = slow->next;
//         fast = fast->next->next;
//     }
//     return slow;
// }

// 206. 反转链表
// struct ListNode* reverseList(struct ListNode* head) {
//     struct ListNode *pre = NULL, *cur = head;
//     while (cur) {
//         struct ListNode* nxt = cur->next;
//         cur->next = pre;
//         pre = cur;
//         cur = nxt;
//     }
//     return pre;
// }

// bool isPalindrome(struct ListNode* head) {
//     struct ListNode* mid = middleNode(head);
//     struct ListNode* head2 = reverseList(mid);
//     while (head2) {
//         if (head->val != head2->val) { // 不是回文链表
//             return false;
//         }
//         head = head->next;
//         head2 = head2->next;
//     }
//     return true;
// }