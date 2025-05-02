## 567. Permutation in String - Hash Table, Two Pointers, String, Sliding Window
#### https://leetcode.com/problems/permutation-in-string/description/
Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.

In other words, return true if one of s1's permutations is the substring of s2.
```py
**Example 1:**
Input: s1 = "ab", s2 = "eidbaooo"<br>
Output: true<br>
Explanation: s2 contains one permutation of s1 ("ba").<br>

**Example 2:**
Input: s1 = "ab", s2 = "eidboaoo"<br>
Output: false
```
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

## 3. Longest Substring Without Repeating Characters - Hash Table, String, Sliding Window
#### https://leetcode.com/problems/longest-substring-without-repeating-characters/description/
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

Constraints:
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

## 205. Isomorphic Strings - Hash Table, String

## Problem Description
Given two strings `s` and `t`, determine if they are isomorphic. Two strings are isomorphic if the characters in `s` can be replaced to get `t`. All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character, but a character may map to itself.

### Example
```
Input: s = "egg", t = "add"
Output: true
Explanation: The mapping is 'e' -> 'a' and 'g' -> 'd'. Each character in s maps to a unique character in t.

Input: s = "foo", t = "bar"
Output: false
Explanation: 'f' maps to 'b', but 'o' cannot map to both 'a' and 'r'.

Input: s = "paper", t = "title"
Output: true
Explanation: The mapping is 'p' -> 't', 'a' -> 'i', 'e' -> 'l', 'r' -> 'e'.
```

### Constraints
- `1 <= s.length <= 5 * 10^4`
- `t.length == s.length`
- `s` and `t` consist of any valid ASCII characters.

```c++
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        
        if(s.length() != t.length())
            return false;
        
        map<char, char> mapEnc;
        set<char> setUsed;
        
        for(int i =0; i < t.length(); i++)
        {
            if(mapEnc.find(s[i]) != mapEnc.end())
            {
                if(mapEnc[s[i]] != t[i])
                    return false;
                
                continue;           
            }
         
            if(setUsed.count(t[i]))
            {
                return false;
            }
            
            mapEnc[s[i]] = t[i];
            setUsed.insert(t[i]);
        }
        
        return true;       
    }
};
```

## Solution Approach
To determine if two strings are isomorphic, we can use a mapping approach:
1. Ensure both strings have the same length.
2. Use two hash maps (or arrays for ASCII characters) to track mappings from `s` to `t` and `t` to `s`.
3. Iterate through both strings simultaneously:
   - For each character pair `(s[i], t[i])`, check if the current mapping is consistent.
   - If a character in `s` is already mapped to a different character in `t`, or vice versa, return `false`.
4. If all characters are processed without conflicts, return `true`.

### Example Implementation (C++)
```cpp
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s.length() != t.length()) return false;
        
        unordered_map<char, char> s_to_t;
        unordered_map<char, char> t_to_s;
        
        for (int i = 0; i < s.length(); ++i) {
            char char_s = s[i];
            char char_t = t[i];
            
            // Check mapping from s to t
            if (s_to_t.find(char_s) == s_to_t.end()) {
                s_to_t[char_s] = char_t;
            } else if (s_to_t[char_s] != char_t) {
                return false;
            }
            
            // Check mapping from t to s
            if (t_to_s.find(char_t) == t_to_s.end()) {
                t_to_s[char_t] = char_s;
            } else if (t_to_s[char_t] != char_s) {
                return false;
            }
        }
        
        return true;
    }
};
```

### How It Works
- **Length Check**: If lengths differ, the strings cannot be isomorphic.
- **Bidirectional Mapping**:
  - `s_to_t` tracks mappings from characters in `s` to `t`.
  - `t_to_s` ensures no character in `t` is mapped to multiple characters in `s`.
- **Iteration**: For each character pair, ensure the mapping is consistent in both directions.
- **Return**: If no conflicts are found, the strings are isomorphic.

### Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the strings.
- **Space Complexity**: O(k), where `k` is the number of unique characters (bounded by the ASCII character set, max 128 for standard ASCII).

### Alternative Approach
Instead of two hash maps, you can use one hash map and a set to track used characters in `t`. This reduces space complexity slightly but maintains the same time complexity.


## 5. Longest Palindromic Substring - Two Pointers, String, Dynamic Programming

This document describes the solution to the "Longest Palindromic Substring" problem (LeetCode #5).

## Problem Description
Given a string `s`, return the longest palindromic substring in `s`. A substring is palindromic if it reads the same forward and backward.

### Example
```
Input: s = "babad"
Output: "bab"
Explanation: "aba" is also valid, but "bab" is equally long and correct.

Input: s = "cbbd"
Output: "bb"
Explanation: "bb" is the longest palindromic substring.

Input: s = "a"
Output: "a"
Explanation: A single character is a palindrome.

Hints:
-How can we reuse a previously computed palindrome to compute a larger palindrome?
-If “aba” is a palindrome, is “xabax” a palindrome? Similarly is “xabay” a palindrome?
-Complexity based hint:
If we use brute-force and check whether for every start and end position a substring is a palindrome we have O(n^2) start - end pairs and O(n) palindromic checks. Can we reduce the time for palindromic checks to O(1) by reusing some previous computation.
```

### Constraints
- `1 <= s.length <= 1000`
- `s` consists of only digits and English letters.

## Solution Approach
The problem can be solved efficiently using the "Expand Around Center" approach, which checks for palindromes by expanding around each possible center.

### Expand Around Center Approach
1. Iterate through each index `i` in the string, treating it as a potential center of a palindrome.
2. For each index, expand around:
   - The index itself (for odd-length palindromes, e.g., "aba").
   - Between the index and the next index (for even-length palindromes, e.g., "bb").
3. While expanding, check if characters on both sides are equal and stay within bounds.
4. Track the longest palindrome found by storing its start index and length.

### Example Implementation (C++)
```cpp
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    void expandFromCenter(int left, int right, string& s, vector<string>& ps) 
    {
        bool found = false;
        for(; left >= 0 && right < s.length() && s[left] == s[right]; left--, right++)
            found = true;
        
        if ( found )
        {
            int len = right - (left+1);
            ps.push_back(s.substr(left+1, len));
        }
    }
    
    string longestPalindrome(string s) {
        if(s.length() == 1)
            return s;
        
        vector<string> pstrings; //collection of all pali strings
        
        //we are going to move from left to right
        //abccbxyz -- bccb - center is in between 
        //abcdcxy -- cdc - center is on a character
        for(int i = 1; i < s.length(); i++) {
            //check if there is a pali string around s[i], s[i] at center
            int left = i-1;
            int right = i+1;
                  
            expandFromCenter(left, right, s, pstrings);
            
            //check if there is a pali string where pali string has even characters
            //s[i-1] == s[i]
            right = i;
            expandFromCenter(left, right, s, pstrings);    
        }
            
        string answer = "";
        for(auto&x : pstrings) {
            if(x.length() > answer.length())
                answer = x;
        }
        
        if(answer.length() == 0)
            answer = s[0];
        
        return answer;     
    }
};
```

```cpp
class Solution {
public:
    string longestPalindrome(string s) {
        int start = 0, maxLength = 0;
        
        for (int i = 0; i < s.length(); i++) {
            // Odd-length palindrome (center at i)
            int len1 = expandAroundCenter(s, i, i);
            // Even-length palindrome (center between i and i+1)
            int len2 = expandAroundCenter(s, i, i + 1);
            // Get the maximum length of the two
            int len = max(len1, len2);
            
            // Update if we found a longer palindrome
            if (len > maxLength) {
                maxLength = len;
                start = i - (len - 1) / 2;
            }
        }
        
        return s.substr(start, maxLength);
    }
    
private:
    int expandAroundCenter(const string& s, int left, int right) {
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            left--;
            right++;
        }
        // Return length of palindrome
        return right - left - 1;
    }
};
```

### How It Works
- **Center Expansion**:
  - For each index `i`, check for odd-length palindromes by expanding around `i`.
  - Check for even-length palindromes by expanding around the gap between `i` and `i+1`.
- **Expansion Function**: Expands while characters match and indices are valid, returning the length of the palindrome.
- **Tracking**: Update `start` and `maxLength` when a longer palindrome is found.
- **Result**: Extract the substring using the recorded `start` and `maxLength`.
- **Edge Cases**: Handles single-character strings and cases where the entire string is a palindrome.

### Time and Space Complexity
- **Time Complexity**: O(n²), where `n` is the length of the string. Each of the `n` centers may expand up to `n` characters.
- **Space Complexity**: O(1), excluding the output string, as only a constant amount of extra space is used.

### Alternative Approaches
1. **Dynamic Programming**:
   - Use a table to store whether `s[i:j]` is a palindrome.
   - Time Complexity: O(n²)
   - Space Complexity: O(n²)
2. **Manacher's Algorithm**:
   - Optimized for finding the longest palindromic substring.
   - Time Complexity: O(n)
   - Space Complexity: O(n)
The Expand Around Center approach is simpler to implement and sufficient for the given constraints.
