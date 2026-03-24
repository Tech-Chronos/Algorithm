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