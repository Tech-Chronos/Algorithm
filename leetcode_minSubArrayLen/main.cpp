#include <iostream>
#include <vector>
using namespace std;

// 长度最小的子数组
class Solution
{
public:
    int minSubArrayLen(int target, vector<int>& nums)
    {
        int ans = nums.size() + 1;
        int left = 0, right = 0;
        int sum = 0;
        int n = nums.size();
        // 判断窗口
        while(right < n)
        {
            sum += nums[right];
            while (sum >= target)
            {
                int len = right - left + 1;
                if (len < ans)  ans = len;
                // 出窗口，判断返回值
                sum -= nums[left];
                ++left;
            }
            // 进窗口
            ++right;
        }
        if (ans == n + 1)   return 0;
        return ans;
    }
};