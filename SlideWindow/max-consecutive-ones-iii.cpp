//
// Created by 有趣的中国人 on 2025/12/24.
//
#include <iostream>
#include <vector>

using namespace std;
class Solution
{
public:
    int longestOnes(vector<int>& nums, int k)
    {
        int left = 0, right = 0;
        int zero = 0;
        int ans = 0;

        for (right = 0; right < nums.size(); ++right)
        {
            if (nums[right] == 0) ++zero;

            while (zero > k)
            {
                while (nums[left] != 0)
                {
                    ++left;
                }
                ++left;
                --zero;
            }
            ans = max(right - left + 1, ans);
        }
        return ans;
    }
};
