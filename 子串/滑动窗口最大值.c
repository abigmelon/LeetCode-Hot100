#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    *returnSize = numsSize - k + 1;
    int* ans = malloc(*returnSize * sizeof(int));
    int* queue = malloc(numsSize * sizeof(int));
    int head = 0, tail = -1;
    for(int i = 0; i < numsSize; i++){
        while(head <= tail && nums[queue[tail]] <= nums[i]){
            tail--;
        }
        queue[++tail] = i;
        int left = i - k + 1;
        if(queue[head] < left) head++;
        if(left >= 0){
            ans[left] = nums[queue[head]];
        }
    }
    free(queue);
    return ans;
}

// 解析：
// 本题是单调队列的经典应用题。核心思想：维护一个双端队列，始终保持队列内元素严格单调递减，
// 这样队首就永远是当前窗口的最大值。
//
// 一、数据结构
// queue：用数组模拟双端队列，存的是元素下标（不是值，因为需要用下标判断是否过期）
// head：队首指针（最大值候选人中下标最小的）
// tail：队尾指针（最新加入的候选人）
//
// 二、算法流程（每个元素 nums[i] 入队时的四步操作）
//   1. 踢队尾弱者：从队尾往前看，所有值 ≤ nums[i] 的元素全部弹出
//      ——因为它们比 nums[i] 小（或相等），且下标更早，永远不可能成为窗口最大值了
//   2. 新人入队尾：当前下标 i 加入队尾，此时队列仍保持单调递减
//   3. 踢队首过期：检查队首下标是否已滑出窗口左边界 (i-k+1)，是则弹出
//      ——每次窗口只移动一步，所以最多过期一个，用 if 而不是 while
//   4. 记录答案：当窗口形成后（i >= k-1），队首就是当前窗口最大值
//
// 三、手动模拟（nums=[1,3,-1,-3,5,3,6,7], k=3）
//   i=0, nums[0]=1:
//     踢弱者：队列空，跳过      入队：[0]                    窗口未满
//   i=1, nums[1]=3:
//     踢弱者：3>1 弹出0        入队：[1]                    窗口未满
//   i=2, nums[2]=-1:
//     踢弱者：-1<3 保留         入队：[1,2]    踢过期：1>=0 否   ans[0]=nums[1]=3 ✓
//   i=3, nums[3]=-3:
//     踢弱者：-3<-1 保留        入队：[1,2,3]  踢过期：1>=1 否   ans[1]=nums[1]=3 ✓
//   i=4, nums[4]=5:
//     踢弱者：5>-3弹3, 5>-1弹2, 5>3弹1
//                              入队：[4]      踢过期：4>=2 否   ans[2]=nums[4]=5 ✓
//   i=5, nums[5]=3:
//     踢弱者：3<5 保留          入队：[4,5]    踢过期：4>=3 否   ans[3]=nums[4]=5 ✓
//   i=6, nums[6]=6:
//     踢弱者：6>3弹5, 6>5弹4   入队：[6]      踢过期：6>=4 否   ans[4]=nums[6]=6 ✓
//   i=7, nums[7]=7:
//     踢弱者：7>6弹6           入队：[7]      踢过期：7>=5 否   ans[5]=nums[7]=7 ✓
//   输出：[3,3,5,5,6,7]
//
// 四、关键细节
//   1. 为什么存下标？因为需要判断 "deque[head] < i-k+1" 是否过期，存值做不到
//   2. 踢弱者用 <= 而不是 <：相等也踢掉旧的留新的，队列更紧凑，旧下标更容易过期
//   3. tail 初始化为 -1：表示空队列，head=0, tail=-1 时 head>tail，队列为空
//   4. 踢过期用 if 不用 while：每次窗口只滑一步，最多一个元素过期
//
// 五、复杂度
//   时间：O(n)，每个元素最多入队一次、出队一次
//   空间：O(n)，队列最多存 numsSize 个下标 + 答案数组 O(n-k+1)