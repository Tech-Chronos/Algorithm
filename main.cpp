#include <iostream>
#include <string>

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

int main()
{
    string num1 = "456", num2 = "77";

    Solution::addStrings(num1, num2);

    return 0;
}