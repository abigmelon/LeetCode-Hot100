#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

struct Node {
    int val;
    struct Node *next;
    struct Node *random;
};

struct Node* copyRandomList(struct Node* head) {
	struct Node *oldNode[1000];
    struct Node *newNode[1000];
    int i = 0;
    while(head!= NULL){
        struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
        newnode->val = head->val;
        newnode->next = NULL;
        newnode->random = NULL;
        oldNode[i] = head;
        newNode[i] = newnode;
        i++;
        head = head->next;
    }
    for(int j = 0; j < i - 1; j++){
        newNode[j]->next = newNode[j + 1];
    }
    for(int j = 0; j < i; j++){
        if(oldNode[j]->random != NULL){
            int index = 0;
            while(oldNode[index] != oldNode[j]->random){
                index++;
            }
            newNode[j]->random = newNode[index];
        }
    }
    if(i == 0) return NULL;
    return newNode[0];
}

// 解析：
// 核心是用两个数组建立"原节点→新节点"的映射：
// 1.第一遍遍历：创建所有新节点，同时把原节点地址和新节点地址按顺序存入两个数组
// 2.第二遍遍历：把新节点的next串起来（newNode[j]->next = newNode[j+1]）
// 3.第三遍遍历：填random，先在oldNode里找到原random的下标，newNode同下标即对应新节点
// 4.返回newNode[0]（空链表返回NULL）