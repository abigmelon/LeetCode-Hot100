#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MIN(a, b) (a > b ? b : a)

_Bool inDict(char* s, int start, int end, char** wordDict, int wordDictSize){
    int len = end - start;
    for(int k = 0; k < wordDictSize; k++){
        if(strlen(wordDict[k]) == len && strncmp(s + start, wordDict[k], len) == 0){
            return 1;
        }
    }
    return 0;
}

_Bool wordBreak(char* s, char** wordDict, int wordDictSize) {
    int len = strlen(s);
    _Bool dp[len + 1];
    dp[0] = 1;
    for(int i = 1; i <= len; i++){
        dp[i] = 0;
    }
    for(int i = 1; i <= len; i++){
        for(int j = 0; j < i; j++){
            if(dp[j] == 1 && inDict(s, j, i, wordDict, wordDictSize) == 1){
                dp[i] = 1;
                break;
            }
        }
    }
    return dp[len];
}

/*
================================================================================
  LeetCode 139. 单词拆分 (Word Break) 题解
================================================================================

【题目】
  给定字符串 s 和单词字典 wordDict，判断 s 能否被拆分为字典中的单词。
  字典中的单词可以重复使用。

【DP 类型】可行性判断（dp 为 bool 型）

【动态规划思路】

  1. 状态定义
     dp[i] = s 的前 i 个字符（s[0..i-1]）能否被字典中的单词拼出

     索引含义：
       s:   l  e  e  t  c  o  d  e
       dp: 0  1  2  3  4  5  6  7  8
       dp[0] = 空前缀
       dp[4] = s 的前 4 个字符 "leet"
       dp[8] = 整个字符串 "leetcode"

  2. 初始化
     dp[0] = true   —— 空前缀默认可以拼出
     dp[1..n] = false

  3. 状态转移
     对于位置 i，枚举分割点 j (0 <= j < i)：
       如果 dp[j] == true 且 s[j..i-1] 在字典中
         → dp[i] = true，break

     含义：前 j 个字符能拼出，且中间 s[j..i-1] 是一个单词，
           则前 i 个字符也能拼出。

     用 break 是因为只需要找到一种分法即可，无需继续枚举。

  4. 遍历顺序
     外层 i：1 → len(s)    —— 从小到大枚举前缀长度
     内层 j：0 → i-1        —— 枚举分割点

  5. 返回值
     return dp[len(s)]

【辅助函数 inDict】
  判断子串 s[start..end-1] 是否在字典中：
  - 先比较长度（快速排除），再用 strncmp 比较内容
  - s + start 指针直接定位子串起点，无需额外拷贝

【复杂度分析】
  时间复杂度：O(n² × m)，n = len(s)，m = wordDictSize
    外层 O(n)，内层 O(n)，每次 inDict 遍历字典 O(m)
  空间复杂度：O(n)，dp 数组

【举例】s = "leetcode", wordDict = ["leet", "code"]

        l e e t c o d e
    0   1   2   3   4   5   6   7   8
    T   F   F   F   T   F   F   F   T
        ├─────────┤   ├─────────────┤
         j=0,i=4        j=4,i=8
      s[0..3]="leet"  s[4..7]="code"
      在字典中 ✓       在字典中 ✓

  dp[4] = true（dp[0] T + "leet" 在字典）
  dp[8] = true（dp[4] T + "code" 在字典）

【与 322.零钱兑换 对比】

              零钱兑换            单词拆分
  ──────────┼─────────────────┼────────────────
  dp 类型    │ int（求最值）     │ bool（求可行性）
  dp 含义    │ 凑出金额 i 的最少硬币 │ 前 i 个字符能否拼出
  初始化     │ dp[0]=0, 其余 ∞   │ dp[0]=true, 其余 false
  转移方程   │ min(dp[i], dp[i-c]+1) │ dp[j] && wordInDict(s[j..i])
  初始化方向 │ 小 → 大（正序）    │ 小 → 大（正序）
  物品使用   │ 无限次（完全背包）  │ 无限次

【易错点提醒】
  ✗ dp[i] == 1   → 这是比较，不会修改 dp[i] 的值
  ✓ dp[i] = 1    → 这才是赋值

  ✗ for i < len   → 漏掉了最后一个位置 dp[len]
  ✓ for i <= len  → dp[len] 才代表整个字符串的结果
*/