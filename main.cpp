#include <iostream>
#include <string>

using namespace std;

class Solution
{
public:
    static int lengthOfLongestSubstring(string s)
    {
        int hash[512] = { 0 };
        int ret = 0;
        for (int left = 0, right = 0; right < s.size(); ++right)
        {
            hash[right]++;

            while (hash[right] == 2)
            {
                hash[left]--;
                ++left;
            }

            ret = max(ret, right - left  + 1);
        }
        return ret;
    }
};

int main()
{
    string str = "abcabcbb" ;
    int ret = Solution::lengthOfLongestSubstring(str);

    return 0;
}