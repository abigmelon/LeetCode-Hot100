#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    if (headA == NULL || headB == NULL) {
        return NULL;
    }
    struct ListNode *pA = headA;
    struct ListNode *pB = headB;
    while(pA != pB) {
        pA = (pA == NULL) ? headB : pA->next;
        pB = (pB == NULL) ? headA : pB->next;
    }
    return pA;
}

//解析：双指针法
//假设这两个指针长这个样子
//A: 1 -> 2
//          -> 3 -> 4 -> 5
//B:      6
//设两个指针，一个从A开始，一个从B开始，分别为pA和pB
//A走完了就去B走，B走完了就去A走
//这两个相遇的时候走过的路程和一定是相等的
//直接返回地址就行