#include <iostream>
#include <string>

using namespace std;

class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        if (s.empty())
        {
            return 0;
        }
        int left = 0, right = 0, n = s.size();
        int hash[128] = { 0 };
        int ret = 1;
        while (right < n)
        {
            ++hash[s[right]];
            if (hash[s[right]] < 2)
            {
                ++right;
                ret = max(ret, right - left);

            }
            else
            {
                while (s[left] != s[right])
                {
                    --hash[s[left]];
                    ++left;
                }
                ++left;
                --hash[s[right]];
                ++right;
                ret = max(ret, right - left);

            }
        }
        return ret;
    }
};