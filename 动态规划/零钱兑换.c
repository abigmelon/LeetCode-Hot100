#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MIN(a, b) (a > b ? b : a)

int coinChange(int* coins, int coinsSize, int amount) {
    int dp[amount + 1];
    dp[0] = 0;
    for(int i = 1; i <= amount; i++){
        dp[i] = amount + 1;     //无限大的标志
    }
    for(int i = 1; i <= amount; i++){
        for(int j = 0; j < coinsSize; j++){
            if(coins[j] <= i){
                dp[i] = MIN(dp[i], dp[i - coins[j]] + 1);
            }
        }
    }
    if(dp[amount] == amount + 1) return -1;
    else return dp[amount];
}

/*
================================================================================
  LeetCode 322. 零钱兑换 (Coin Change) 题解
================================================================================

【题目】
  给定不同面额的硬币 coins 和一个总金额 amount。计算凑出该金额所需的最少硬币数。
  每种硬币数量无限。如果凑不出来，返回 -1。

【动态规划思路】

  1. 状态定义
     dp[i] = 凑出金额 i 所需的最少硬币数

  2. 初始化
     dp[0] = 0                    —— 凑 0 元不需要硬币
     dp[i] = amount + 1 (i > 0)   —— 相当于"无穷大"，表示暂时凑不出

     为什么用 amount+1？最坏情况全用 1 元硬币也就是 amount 枚，
     所以 amount+1 永远不会是有效答案。

  3. 状态转移
     对于每个金额 i，枚举每种硬币 c：
       如果 c <= i，说明当前硬币可用：
         dp[i] = min(dp[i], dp[i - c] + 1)

     含义：如果最后一枚硬币用 c，则之前只需凑 i-c，加上这枚就是 dp[i-c]+1。
     和当前 dp[i] 取最小。

  4. 遍历顺序
     外层 i：1 → amount      —— 从小到大，保证子问题先求解
     内层 j：每种硬币         —— 完全背包，正序遍历

  5. 返回值
     如果 dp[amount] 仍为 amount+1，说明无法凑出，返回 -1
     否则返回 dp[amount]

【复杂度分析】
  时间复杂度：O(amount × n)，n 为硬币种类数
  空间复杂度：O(amount)

【举例】coins = [1, 2, 5], amount = 11

   i    0  1  2  3  4  5  6  7  8  9  10  11
  dp    0  1  1  2  2  1  2  2  3  3   2   3

  dp[11] = 3，方案：5 + 5 + 1

【核心要点】
  本题是"完全背包求最小值"的标准模板，关键在于：
  - 求最小值时，dp 初始化为"无穷大"
  - 转移方程用 min
  - 正序遍历实现物品无限使用
*/