#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int maxSubArray(int* nums, int numsSize) {
    int curMax = nums[0];
    int ans = nums[0]; 
    for (int i = 1; i < numsSize; i++) {
        curMax = curMax > 0 ? curMax + nums[i] : nums[i];
        if (curMax > ans) ans = curMax;
    }
    return ans;
}

// 解析：
// 本题是动态规划的入门经典题——Kadane 算法，核心在于定义状态和状态转移。
//
// 一、定义状态
// curMax：以当前位置 i 结尾的连续子数组的最大和。
// ans：全局最大值，即所有 curMax 中的最大值。
//
// 二、状态转移
// 对于每个 nums[i]，只有两种选择：
//   1. 接上前面的子数组：curMax + nums[i]（前提是 curMax > 0，加入正收益）
//   2. 另起炉灶：nums[i] 自己成为一个新的子数组开头
// 所以：curMax = max(nums[i], curMax + nums[i])
// 代码中简化为三元运算符：curMax > 0 ? curMax + nums[i] : nums[i]
//
// 三、手动模拟
// nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
// i=1: curMax = -2>0? → 否 → 1             ans=1
// i=2: curMax =  1>0? → 是 → 1+(-3)=-2   ans=1
// i=3: curMax = -2>0? → 否 → 4             ans=4
// i=4: curMax =  4>0? → 是 → 4+(-1)= 3    ans=4
// i=5: curMax =  3>0? → 是 → 3+2    = 5    ans=5
// i=6: curMax =  5>0? → 是 → 5+1    = 6    ans=6
// i=7: curMax =  6>0? → 是 → 6+(-5)= 1    ans=6
// i=8: curMax =  1>0? → 是 → 1+4    = 5    ans=6
// 最终答案 6，对应子数组 [4, -1, 2, 1]
//
// 四、为什么不能用前缀和的"最大值减最小值"？
// 因为前缀和的 min 必须出现在 max 之前才有意义。
// 比如 [-2, 1]：preSum = [0, -2, -1]，max=0 在 min=-2 之前，
// 0-(-2)=2 对应的"子数组"是空的不存在，正确答案是 1。
// 如果要修复，需要边遍历边维护"当前位置之前的最小前缀和"，
// 这就等价于 Kadane 的另一种形式，不如直接用 Kadane 简洁。
//
// 五、复杂度
// 时间：O(n)，一趟遍历
// 空间：O(1)，只用两个变量