#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target)
    {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans_vec;
        // size如果小于4的话直接返回
        if (nums.size() < 4)
        {
            return {};
        }
        for (int i = 0; i < nums.size() - 3; ++i)
        {
            for (int j = i + 1; j < nums.size() - 2; ++j)
            {
                int left = j + 1;
                int right = nums.size() - 1;
                while (left < right)
                {
                    long long sum =
                            (long long)nums[i] + nums[j] + nums[left] + nums[right];
                    if (sum > target)
                    {
                        --right;
                    }
                    else if (sum < target)
                    {
                        ++left;
                    }
                    else
                    {
                        // 插入之后才需要判断是否需要去重
                        ans_vec.push_back(
                                {nums[i], nums[j], nums[left], nums[right]});
                        while (left < right && nums[left] == nums[left + 1])
                        {
                            ++left;
                        }

                        while (left < right && nums[right] == nums[right - 1])
                        {
                            --right;
                        }
                        if (left < right)
                        {
                            ++left;
                            --right;
                        }
                    }
                }

                while (j < nums.size() - 2 && nums[j] == nums[j + 1])
                {
                    ++j;
                }
            }
            while (i < nums.size() - 3 && nums[i] == nums[i + 1])
            {
                ++i;
            }
        }
        return ans_vec;
    }
};
