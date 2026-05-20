int findMin(int* nums, int numsSize) {
    int left = -1, right = numsSize - 1;
    while(left + 1 < right){
        int mid = (left + right) / 2;
        if(nums[mid] < nums[numsSize - 1]){
            right = mid;
        }else left = mid;
    }
    return nums[right];
}