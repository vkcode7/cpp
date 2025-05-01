## 567. Permutation in String

Given two strings s1 and s2, return true if s2 contains a 
permutation of s1, or false otherwise.

In other words, return true if one of s1's permutations is the substring of s2.

**Example 1:**
Input: s1 = "ab", s2 = "eidbaooo"<br>
Output: true<br>
Explanation: s2 contains one permutation of s1 ("ba").<br>

**Example 2:**
Input: s1 = "ab", s2 = "eidboaoo"<br>
Output: false

```c++
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if(s1.size() > s2.size())
            return false;

        vector<int> ms1(26, 0);

        for(auto x: s1) 
            ms1[x -'a']++;

        int len = s1.size();

        vector<int> ms2(26, 0);
        for(int k = 0; k < len; k++) 
            ms2[s2[k] -'a']++;

        if(s1.size() ==  s2.size())
            return (ms1 == ms2);
            
        //make a sliding window
        //keep adding next character and removing the previous on head
        for(int start = len; start < s2.size(); start++)
        {
            if(ms1 == ms2)
                return true;

            ms2[s2[start-len] -'a']--;
            ms2[s2[start] -'a']++;
        }
        
        if(ms1 == ms2)
            return true;

        return false;
    }
};
```

## 3. Longest Substring Without Repeating Characters
Given a string s, find the length of the longest substring without duplicate characters.
```py
Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.
Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
```

**Constraints:**
```py
0 <= s.length <= 5 * 104
s consists of English letters, digits, symbols and spaces.

Hint: Generate all possible substrings & check for each substring if it's valid and keep updating maxLen accordingly.
```
```c++
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        set<char> cs;
        
        int maxL = 0;
        int start = 0;
        
        for(int i =0; i < s.length(); i++)
        {
            char ch = s[i];
            if(cs.count(ch) == 1)
            {
                //already exists
                while(cs.count(ch) != 0)
                {
                    //erase the characters from map one by one
                    cs.erase(s[start]);
                    start++;
                }
            }
            
            cs.insert(ch);
            
            maxL = max(maxL, i - start + 1);
        }
        
        return maxL;
    }
};
```

## 121. Best Time to Buy and Sell Stock - Array, Dynamic Programming

You are given an array prices where prices[i] is the price of a given stock on the ith day.

You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.

Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.
```py
Example 1:

Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.
Example 2:

Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transactions are done and the max profit = 0.
 
Constraints:

1 <= prices.length <= 105
0 <= prices[i] <= 104
```
```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int max_profit = 0;
        int buy_price = INT_MAX;
        for(auto x: prices)
        {
            buy_price = min(buy_price, x);
            max_profit = max(x - buy_price, max_profit);             
        }
        
        return max_profit;
    }
};
```


