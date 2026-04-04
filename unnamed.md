# 🚀 字符串相加（LeetCode 415）

---

## 🧠 题目
给定两个非负整数 `num1` 和 `num2`（字符串形式），返回它们的和（字符串形式）

👉 **不能用大整数库**

---

## 🎯 核心思路（模拟竖式加法）

👉 从低位到高位逐位相加  
👉 用 `carry` 记录进位

---

## 🔥 核心技巧

### ⭐ 方法本质
👉 **反转字符串 + 按位相加 + 处理进位**

---

## 📌 步骤拆解

### 1️⃣ 反转字符串（方便从低位开始）
```cpp
reverse(num1.begin(), num1.end());
reverse(num2.begin(), num2.end());
```

---

### 2️⃣ 逐位相加（先不处理进位）
```cpp
tmp[i] = left + right - '0' - '0';
```

👉 注意：
- 字符转数字：`char - '0'`

---

### 3️⃣ 统一处理进位
```cpp
carry = x + carry;
val = carry % 10;
carry /= 10;
```

---

### 4️⃣ 处理最后进位
```cpp
if (carry) ret += '1';
```

---

### 5️⃣ 结果反转
```cpp
reverse(ret.begin(), ret.end());
```

---

## 💻 完整代码

```cpp
class Solution 
{
public:
    string addStrings(string num1, string num2) 
    {
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());

        vector<int> tmp(max(num1.size(), num2.size()), 0);

        for (int i = 0; i < max(num1.size(), num2.size()); ++i)
        {
            char left = i >= num1.size() ? '0' : num1[i];
            char right = i >= num2.size() ? '0' : num2[i];

            tmp[i] = left + right - '0' - '0';
        }

        int carry = 0;
        string ret;

        for (auto x : tmp)
        {
            carry = x + carry;
            int val = carry % 10;
            carry /= 10;

            ret += (char)(val + '0');
        }

        if (carry)
        {
            ret += '1';
        }

        reverse(ret.begin(), ret.end());
        return ret;
    }
};
```

---

## 🧩 图解（示例）

```
  123
+ 789
------
```

反转后：
```
321
987
```

逐位相加（未进位）：
```
[10, 10, 10]
```

处理进位：
```
0 → carry=1
1 → carry=1
1 → carry=1
最后补 1
```

结果：
```
912
```

---

## ⚠️ 易错点（面试高频）

### ❌ 1. 忘记补 '0'
```cpp
i >= size ? '0' : num[i]
```

---

### ❌ 2. char 转 int 写错
```cpp
left + right - '0' - '0'   // ✅
```

---

### ❌ 3. 忘记最后 carry
```cpp
if (carry) ret += '1';
```

---

### ❌ 4. 顺序错误
👉 一定要：
```
先存 tmp → 再统一处理进位
```

---

## ⏱️ 复杂度

- 时间：`O(n)`
- 空间：`O(n)`

---

## 🚀 进阶写法（更优，面试加分🔥）

👉 **不需要 tmp，一次循环直接做**

```cpp
string addStrings(string num1, string num2) 
{
    int i = num1.size() - 1;
    int j = num2.size() - 1;
    int carry = 0;

    string ret;

    while (i >= 0 || j >= 0 || carry)
    {
        int x = i >= 0 ? num1[i--] - '0' : 0;
        int y = j >= 0 ? num2[j--] - '0' : 0;

        int sum = x + y + carry;

        ret += (sum % 10) + '0';
        carry = sum / 10;
    }

    reverse(ret.begin(), ret.end());
    return ret;
}
```

👉 优点：
- 空间更优（O(1)）
- 更接近面试标准答案

---

## 🧠 面试总结一句话

👉 **模拟竖式加法，从低位到高位，carry 控制进位**

---

## 💡 一句话记忆

👉 **“倒着加，带进位，最后翻转”**

---

要不要我帮你把👇这几题整理成一套“字符串处理模板”：
- 字符串相加
- 字符串乘法
- 大数运算合集  

👉 这一块腾讯面试很爱问