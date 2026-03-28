#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

//class Solution
//{
//public:
//    static int lengthOfLongestSubstring(string s)
//    {
//        int hash[512] = { 0 };
//        int ret = 0;
//        for (int left = 0, right = 0; right < s.size(); ++right)
//        {
//            hash[right]++;
//
//            while (hash[right] == 2)
//            {
//                hash[left]--;
//                ++left;
//            }
//
//            ret = max(ret, right - left  + 1);
//        }
//        return ret;
//    }
//};

class Solution
{
public:
    static string addStrings(string& num1, string& num2)
    {
        int size1 = num1.size() - 1;
        int size2 = num2.size() - 1;
        string ret;
        char add = 0;
        char other = 0;

        int size = max(size1, size2);

        for (int i = size1, j = size2; size > 0; --size)
        {
            char left, right;
            if (i <= 0) left = 0;
            if (j <= 0) right = 0;
            if (i > 0)  left = num1[i];
            if (j > 0)  right = num2[j];

            add = (int)left + (int)right + (int)other;
            if (add >= 10)
            {
                add -= 10;
                other = 1;
            }
            ret += to_string((int)add);

            --i;
            --j;
        }
        if (other != 0) ret += other;

        return ret;
    }
};


vector<vector<int>> SumEqualK(const vector<int>& nums, int k)
{
    int sum = 0;
    unordered_map<int, vector<int>> hash; // 存放的是 前缀和 和 下标的映射
    vector<vector<int>> ret;
    hash[0].push_back(-1);

    for (int i = 0; i < nums.size(); ++i)
    {
        sum += nums[i];
        int target = sum - k;
        if (hash.count(target) > 0)
        {
            // 如果有这个target，那么这个位置之后，一直到当前这个位置，满足和为K
            for (auto start : hash[target])
            {
                // 迭代器区间构造
                ret.emplace_back(nums.begin() + start + 1, nums.begin() + i + 1);
            }
        }
        hash[sum].push_back(i);
    }

    return std::move(ret);
}

int findNumberOfLIS(vector<int>& nums)
{
    // len[i] 表示以 i 为结尾的最长递增子序列的长度
    vector<int> len(nums.size(), 1);
    // count[i] 表示以 i 为结尾的最长递增子序列的个数
    vector<int> count(nums.size(), 1);

    for (int i = 1; i < nums.size(); ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            // 必须比 nums[j] 大 在更新
            if (nums[i] > nums[j])
            {
                // 表示 以 j 为结尾的最长递增子序列的长度 + 1，就是len[i]
                // 说名 最长递增子序列的长度没有变化，个数只要加上 count[j] 就可以了
                if (len[j] + 1 == len[i])
                {
                    count[i] += count[j];
                }
                else if (len[j] + 1 > len[i]) // 说明最长递增子序列的个数变化了
                {
                    count[i] = count[j];
                    len[i] = len[j] + 1;
                }
            }
        }
    }
    int ret = count[0];
    int max_len = len[0];
    for (int i = 1; i < len.size(); ++i)
    {
        if (max_len < len[i])
        {
            max_len = len[i];
            ret = count[i];
        }
        else if (max_len == len[i])
        {
            ret += count[i];
        }
    }
    return ret;
}

int main()
{
    vector<int> nums({1,1,1});

    auto ret = SumEqualK(nums, 1);

    for (auto& e : ret)
    {
        for (int i = 0; i < e.size(); ++i)
        {
            std::cout << e[i] << " ";
        }
        std::cout << endl;
    }


    return 0;
}