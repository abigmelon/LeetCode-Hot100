#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

_Bool isValid(char* s) {
    int len = strlen(s);
    char* stack = malloc(len * sizeof(char));
    int top = -1;
    for(int i = 0; i < len; i++){
        char c = s[i];
        if(c == '(' || c == '[' || c == '{'){
            stack[++top] = c;
        }
        else{
            if(top == -1){
                free(stack);
                return 0;
            }
            else{
                char left = stack[top];
                top--;
                if(left == '(' && s[i] == ')') continue;
                else if (left == '[' && s[i] == ']') continue;
                else if (left == '{' && s[i] == '}') continue;
                else return 0;
            }
        }
    }
    free(stack);
    if(top == -1) return 1;
    else return 0;
}

// 解析：
// 栈的经典应用题——括号匹配。核心就一句话：左括号入栈，右括号弹栈比类型。
// 遍历到左括号就压进去，遍历到右括号就弹出栈顶看是不是同一类型。
// 两种情况直接判无效：1. 右括号来时栈空了（没有左括号等着配对）；2. 弹出来的左括号类型对不上。
// 最后栈不为空也无效（有左括号没被匹配）。
// 注意 malloc 之后每个 return 之前都要 free，不然内存泄漏。

