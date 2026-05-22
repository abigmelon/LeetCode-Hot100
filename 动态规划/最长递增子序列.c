#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int lengthOfLIS(int* nums, int numsSize) {
    if(numsSize == 0) return 0;
    int* dp = malloc(numsSize * sizeof(int));
    int len = 1;
    for(int i = 0; i < numsSize; i++){
        dp[i] = 1;
        for(int j = 0; j < i; j++){
            if(nums[j] < nums[i] && dp[j] + 1 > dp[i]){
                dp[i] = dp[j] + 1;
            }
        }
        if(dp[i] > len) len = dp[i];
    }
    free(dp);
    return len;
}

/*
 * ============================================================
 * 力扣 300. 最长递增子序列（Longest Increasing Subsequence）
 * ============================================================
 *
 * 【题目理解】
 * 给定一个整数数组 nums，找出其中最长的严格递增子序列的长度。
 * 子序列：从原数组中删除若干元素（可以不删除），剩余元素保持原有顺序。
 * 关键词："递增" + "子序列"（不要求连续）。
 *
 * 例如：nums = [10, 9, 2, 5, 3, 7, 101, 18]
 * 最长递增子序列是 [2, 3, 7, 101]，长度为 4。
 *
 *
 * 【为什么是动态规划】
 * 这个问题具有两个关键特征：
 *
 * 1. 最优子结构：
 *    以 nums[i] 结尾的最长递增子序列，可以由"以某个更小的 nums[j] 结尾
 *    的最长递增子序列"再拼上 nums[i] 得到。大问题的最优解包含了小问题
 *    的最优解。
 *
 * 2. 重叠子问题：
 *    计算 dp[i] 时，需要反复用到 dp[0] ~ dp[i-1] 的结果。
 *
 *
 * 【状态定义】
 * dp[i]：以 nums[i] 结尾的最长递增子序列的长度。
 *
 * 注意：子序列必须以 nums[i] 作为最后一个元素！
 *      最终答案是 max(dp[0], dp[1], ..., dp[n-1])，而非 dp[n-1]。
 *
 *
 * 【状态转移方程】
 * 对于位置 i，我们回头看所有在它前面的位置 j (0 <= j < i)：
 *   如果 nums[j] < nums[i]，说明可以把 nums[i] 接在以 nums[j] 结尾的
 *   递增子序列后面，形成一个更长的子序列，长度为 dp[j] + 1。
 *
 *   在所有可行的 j 中，取最大值：
 *       dp[i] = max( dp[j] + 1 )   对于所有 j < i 且 nums[j] < nums[i]
 *
 *   如果前面没有任何比它小的数，dp[i] = 1（只包含它自己）。
 *
 *
 * 【手动模拟】以 nums = [10, 9, 2, 5, 3, 7, 101, 18] 为例：
 *
 *   i=0, nums[0]=10:  前面没有元素       → dp[0]=1
 *   i=1, nums[1]=9:   前面没有更小的     → dp[1]=1
 *   i=2, nums[2]=2:   前面没有更小的     → dp[2]=1
 *   i=3, nums[3]=5:   2<5  → dp[3]=max(1, 1+1)=2
 *   i=4, nums[4]=3:   2<3  → dp[4]=max(1, 1+1)=2
 *   i=5, nums[5]=7:   2,5,3都<7 → dp[5]=max(1, 1+1, 2+1, 2+1)=3
 *   i=6, nums[6]=101: 前面都<101 → dp[6]=max(各dp[j]+1)=4
 *   i=7, nums[7]=18:  除了101外都<18 → dp[7]=max(各dp[j]+1)=4
 *
 *   dp = [1, 1, 1, 2, 2, 3, 4, 4]，答案为 max = 4。
 *
 *
 * 【复杂度分析】
 * 时间复杂度：O(n²)，两重循环，n 为数组长度。
 * 空间复杂度：O(n)，dp 数组的大小。
 *
 *
 * 【进阶：O(n log n) 解法 — 耐心排序】
 *
 * 上面的 DP 解法在 n 很大时（如 10^5）会超时。更高效的思路是"耐心排序"：
 *
 * 维护一个数组 tails，tails[k] 表示长度为 k+1 的递增子序列的"最小可能
 * 结尾值"。遍历 nums 中每个数 x：
 *   - 如果 x 比 tails 中所有数都大 → 追加到 tails 末尾（子序列变长）
 *   - 否则 → 用二分查找找到第一个 >= x 的位置，替换它（降低门槛，
 *     让后续的数更容易接上去）
 *
 * 最终 tails 的长度就是答案。注意 tails 数组本身不一定是真实的 LIS，
 * 只是长度正确。
 *
 * 代码骨架：
 *     int* tails = malloc(numsSize * sizeof(int));
 *     int size = 0;
 *     for (int i = 0; i < numsSize; i++) {
 *         int left = 0, right = size;
 *         while (left < right) {
 *             int mid = left + (right - left) / 2;
 *             if (tails[mid] < nums[i]) left = mid + 1;
 *             else right = mid;
 *         }
 *         tails[left] = nums[i];
 *         if (left == size) size++;
 *     }
 *     free(tails);
 *     return size;
 *
 *
 * 【常见误区】
 * 1. 把"子序列"当成"子数组/连续子串"来做 → 算法彻底错误。
 * 2. dp 定义成"前 i 个元素的最长 LIS" → 这样没法递推，因为不知道
 *    最后一个元素的值。
 * 3. 最后返回 dp[n-1] → LIS 不一定以最后一个元素结尾！
 * 4. 内层循环变量写错（如 j++ 写成了 i++）→ 死循环或错误结果。
 */