#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* swapPairs(struct ListNode* head) {
    if (head == NULL || head->next == NULL) return head;
    struct ListNode* newHead = head->next;
    head->next = swapPairs(newHead->next);
    newHead->next = head;
    return newHead;
}

// 解析：
// 此题能看出来是通过递归写，但是步骤值得思考：
// 1.空或者只剩一个就不用交换，直接吐出来
// 2.把节点2的地址变成新的head地址（这么说能准确一点）
// 3.相信递归能处理好后面的东西（节点1指向新的头）
// 4.节点2指向节点1
// 5.返回新的head（在第一层中即是节点2）