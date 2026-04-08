#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

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


//int main()
//{
//    vector<int> nums({1,1,1});
//
//    auto ret = SumEqualK(nums, 1);
//
//    for (auto& e : ret)
//    {
//        for (int i = 0; i < e.size(); ++i)
//        {
//            std::cout << e[i] << " ";
//        }
//        std::cout << endl;
//    }
//
//
//    return 0;
//    //return 0;
//}


string decodeString(string s)
{
    stack<int> num_st;
    stack<string> str_st;
    str_st.push("");
    for (int i = 0; i < s.size();)
    {
        // 如果是数字
        if (s[i] >= '0' && s[i] <= '9')
        {
            int tmp = 0;
            while (s[i] >= '0' && s[i] <= '9')
            {
                tmp = tmp * 10 + (char)(s[i] - '0');
                ++i;
            }
            num_st.push(tmp);
        }

        // 如果是左括号
        if (s[i] == '[')
        {
            ++i;
            string str;
            while (s[i] >= 'a' && s[i] <= 'z')
            {
                str += s[i];
                ++i;
            }
            str_st.push(str);
        }

        // 如果是右括号
        if (s[i] == ']')
        {
            string str;

            int num = num_st.top();
            num_st.pop();

            string tmp = str_st.top();
            str_st.pop();

            while (num--)
            {
                str += tmp;
            }

            str_st.top() += str;
            ++i;
        }

        while (s[i] >= 'a' && s[i] <= 'z')
        {
            str_st.top() += s[i];
            ++i;
        }
    }
    return str_st.top();
}


// 建立小堆
void AdjustDown(vector<int>& nums, int parent)
{
    int child = parent * 2 + 1;
    while (child < nums.size())
    {
        if (child + 1 < nums.size() && nums[child] > nums[child + 1])
        {
            ++child;
        }
        if (nums[child] < nums[parent])
        {
            swap(nums[child], nums[parent]);
            parent = child;
            child = parent * 2 + 1;
        }
        else break;
    }
}

vector<int> sortArray(vector<int>& nums)
{
    // 先建堆
    for (int i = (nums.size() - 2) / 2; i >= 0; --i)
    {
        AdjustDown(nums, i);
    }

    int n = nums.size();
    // 排序
    vector<int> tmp(nums.size());
    for (int i = 0; i < n; ++i)
    {
        tmp[i] = nums[0];
        swap(nums[0], nums[n - 1]);
        nums.pop_back();
        AdjustDown(nums, 0);
    }
    return tmp;
}

bool validateStackSequences(vector<int>& pushed, vector<int>& popped)
{
    stack<int> st;
    int n = pushed.size();
    int j = 0;
    for (int i = 0; i < n; ++i)
    {
        st.push(pushed[i]);
        while (j < n && !st.empty() && st.top() == popped[j])
        {
            st.pop();
            ++j;
        }
    }

    return j == n && st.empty();
}



// Definition for a binary tree node.
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


int widthOfBinaryTree(TreeNode* root)
{
    deque<pair<TreeNode*, long long>> q;
    q.emplace_back(root, 0);

    long long width = 0;
    while (!q.empty())
    {
        long long size = q.size();
        long long left = LLONG_MAX, right = LLONG_MIN;
        while (size--)
        {
            auto front = q.front();
            left = min(left, front.second);
            right = max(right, front.second);
            q.pop_front();
            if (front.first->left)
                q.emplace_back(front.first->left, (unsigned int)front.second * 2 + 1);
            if (front.first->right)
                q.emplace_back(front.first->right, (unsigned int)front.second * 2 + 2);
        }
        width = max(width, right - left + 1);
    }
    return width;
}


int main()
{
    // [1,3,2,5,null,null,9,6,null,7]
    TreeNode* root = new TreeNode(1);
    TreeNode* root1 = new TreeNode(3);
    TreeNode* root2 = new TreeNode(2);
    TreeNode* root3 = new TreeNode(5);
    TreeNode* root4 = new TreeNode(9);
    TreeNode* root5 = new TreeNode(6);
    TreeNode* root6 = new TreeNode(7);


    root->left = root1;
    root->right = root2;
    root1->left = root3;
    root1->right = nullptr;
    root2->left = nullptr;
    root2->right = root4;
    root3->left = root5;
    root3->right = nullptr;

    root4->left = root6;
    root4->right = nullptr;

    root5->left = root5->right = root6->left = root6->right = nullptr;

    cout << widthOfBinaryTree(root);

    delete root;
    delete root1;
    delete root2;
    delete root3;
    delete root4;
    delete root5;
    delete root6;

    return 0;
}
