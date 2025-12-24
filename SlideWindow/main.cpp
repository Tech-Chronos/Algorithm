#include <iostream>
using  namespace  std;

class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        int hash[128] = {0};
        int left = 0, right = 0;
        int ans = 0;
        for (right = 0; right < s.size(); ++right)
        {
            if (hash[s[right]] == 0) ++hash[s[right]];
            else
            {
                ++hash[s[right]];
                while (s[left] != s[right])
                {
                    --hash[s[left]];
                    ++left;
                }
                --hash[s[left]];
                ++left;
            }

            ans = max(right - left + 1, ans);
        }

        return ans;
    }
};