#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

char* decodeString(char* s) {
    int len = strlen(s);
    int* countStack = malloc(len * sizeof(int));
    int countTop = -1;
    char** strStack = malloc(len * sizeof(char*));
    int strTop = -1;
    int num = 0;
    char* res = malloc(1);
    res[0] = '\0';
    int resCap = 1;
    for(int i = 0; i < len; i++){
        char c = s[i];
        if(isdigit(c)) num = num * 10 + (c - '0');
        else if(isalpha(c)){
            if(strlen(res) + 2 > resCap){
                resCap *= 2;
                res = realloc(res, resCap);
            }
            int end = strlen(res);
            res[end] = c;
            res[end + 1] = '\0';
        }
        else if(c == '['){
            countStack[++countTop] = num;
            strStack[++strTop] = res;
            num = 0;
            res = malloc(1);
            res[0] = '\0';
            resCap = 1;
        }
        else if(c == ']'){
            int k = countStack[countTop--];
            char* prev = strStack[strTop--];
            prev = realloc(prev, strlen(prev) + k * strlen(res) + 1);
            for(int i = 0; i < k; i++){
                strcat(prev, res);
            }
            free(res);
            res = prev;
            resCap = strlen(prev) + 1;
        }
    }
    free(countStack);
    free(strStack);
    return res;
}

// ==================== 解析 ====================
// 题目：394. 字符串解码
// 编码规则：k[字符串] → 字符串重复 k 次。括号可以嵌套。
// 例："3[a2[c]]" → "accaccacc"
//
// 【核心思路：双栈 + 状态机】
// 这道题难在两个地方：1. 括号嵌套  2. 数字可能多位
// 解决嵌套的标准套路就是用栈来"存档/读档"。
//
// ── 两个栈的分工 ──
// countStack（数字栈）：遇到 '[' 时，把当前重复次数 k 存进去
// strStack（字符串栈）： 遇到 '[' 时，把外层已构建的字符串存进去
//
// 举个类比：就像玩 RPG 进副本——
//   遇到 '[' = 进入副本，先把外面的装备和状态存仓库（压栈）
//   遇到 ']' = 出副本，从仓库取回装备（弹栈），把副本里打到的战利品重复 k 次拼回去
//
// ── 四个分支的处理 ──
// 数字：累加到 num（num = num*10 + 数字），处理多位数如 "12"
// 字母：追加到 res 末尾，容量不够就 realloc 扩容
//  '['：存档 → 压 num 入数字栈，压 res 入字符串栈，然后 num 归零、res 清空
//  ']'：读档 → 弹数字栈得 k，弹字符串栈得外层串 prev，
//       把 res 重复 k 次拼到 prev 后，释放旧 res，res 指向 prev
//
// ── 内存管理要点 ──
// 1. res 是一个动态扩容的字符串，用 resCap 跟踪容量
// 2. 每次追加字母前检查 strlen(res)+2 > resCap，不够就翻倍扩容
// 3. '[' 时 res 重新 malloc(1) 并置空，resCap 重置为 1
// 4. ']' 时 prev 用 realloc 精确扩容到需要的大小，然后 strcat 拼接
// 5. ']' 拼接完成后 free 掉括号内的 res，因为它已经被合并到 prev 里了
// 6. 最后 free 两个栈数组（strStack 里的指针已随 realloc/free 处理，无需逐个释放）
//
// ── 复杂度 ──
// 时间：O(n * maxK)，n 为字符串长度，输出长度可能很大
// 空间：O(n)，两个栈的深度不超过嵌套层数
