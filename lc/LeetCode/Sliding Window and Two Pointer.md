```bash
# 523. Continuous Subarray Sum
# 125. Valid Palindrome [Super Easy, use isalnum(), tolower()]
# 76. Minimum Window Substring Solution [Easy]
# 392. Is Subsequence [Easy]
# 844. Backspace String Compare Solution [Super Easy with Stack]
# 26. Remove Duplicates from Sorted Array Solution [Super Easy]
# 567. Permutation in String - Hash Table, Two Pointers, String, Sliding Window [Easy]
# 3. Longest Substring Without Repeating Characters - Hash Table, String, Sliding Window [Easy using 2 maps]
# 205. Isomorphic Strings - Hash Table, String
# 5. Longest Palindromic Substring - Two Pointers, String, Dynamic Programming
# 451. Sort Characters By Frequency - Hash Table, Sorting, Heap (Priority Queue), Bucket Sort, Counting [Easy using a map and vector]
# 2262. Substring with Largest Variance - Dynamic Programming [Revisit]
# 394. Decode String - Stack, Recursion [Easy]
# 443. String Compression - Two Pointers [Easy]
# 387. First Unique Character in a String - Hash Table, Queue [Very Easy]
# 273. Integer to English Words [Easy]
# 283. Move Zeroes Solution - Two Pointers [Very Easy]
# 88. Merge Sorted Array Solution - Two Pointers [Easy]
# 239. Sliding Window Maximum - Queue, Sliding Window, Heap (Priority Queue), Monotonic Queue - [Medium Revisit]
# 299. Bulls and Cows Solution [Easy]
# 11. Container With Most Water Solution [Medium]
```

# How to use Sliding Window Technique?
There are basically two types of sliding window:

## 1. Fixed Size Sliding Window:
The general steps to solve these questions by following below steps:

- Find the size of the window required, say K.
- Compute the result for 1st window, i.e. include the first K elements of the data structure.
- Then use a loop to slide the window by 1 and keep computing the result window by window.

## 2. Variable Size Sliding Window:
The general steps to solve these questions by following below steps:

- In this type of sliding window problem, we increase our right pointer one by one till our condition is true.
- At any step if our condition does not match, we shrink the size of our window by increasing left pointer.
- Again, when our condition satisfies, we start increasing the right pointer and follow step 1.
- We follow these steps until we reach to the end of the array.

## Monotonic Stack
A monotonic stack is a stack where elements are maintained in either a strictly increasing or decreasing order. This order allows for efficient solutions to problems involving comparisons between elements, such as finding the next greater or smaller element in a sequence. 

## Monotonic deque
Here we introduce an interesting data structure. It's a deque with an interesting property - the elements in the deque from head to tail are in decreasing order (hence the name monotonic).

To achieve this property, we modify the push operation so that when we push an element into the deque, we first pop everything smaller than it out of the deque.

# 523. Continuous Subarray Sum
Given an integer array nums and an integer k, return true if nums has a good subarray or false otherwise.

A good subarray is a subarray where:

its length is at least two, and
the sum of the elements of the subarray is a multiple of k.

```bash
Example 1:
Input: nums = [23,2,4,6,7], k = 6
Output: true
Explanation: [2, 4] is a continuous subarray of size 2 whose elements sum up to 6.
```

```cpp
class Solution {
public:
/*
For each cumulative sum, calculate the remainder when it is divided by k. The remainder can help us determine if the sum of any subarray (up to the current index) is a multiple of k.

If at two different points in the array, the cumulative sums give the same remainder when divided by k, it means the sum of the elements between ↔️ these two points is a multiple of k.
*/
    unordered_map<int, int> remaindersFound;

    bool checkSubarraySum(vector<int>& nums, int k) {
        int currSum = 0;
        remaindersFound[0] = -1; // To handle the case when subarray starts from index 0

        for (int i = 0; i < nums.size(); i++) {
            currSum += nums[i];
            int remainder = currSum % k;

            if (remaindersFound.find(remainder) != remaindersFound.end()) {
                // Check if the length of the subarray is at least 2
                if (i - remaindersFound[remainder] >= 2) {
                    return true;
                }
            } else {
                remaindersFound[remainder] = i;
            }
        }

        return false;    
    }
};
```

# 125. Valid Palindrome [Super Easy]
https://leetcode.com/problems/valid-palindrome/

A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric characters include letters and numbers.

Given a string s, return true if it is a palindrome, or false otherwise.
```
Example 1:
Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.
```cpp
class Solution {
public:
    bool isPalindrome(string s) {
        int left = 0, right = s.size() - 1;
        
        while (left < right) {
            // Skip non-alphanumeric characters from left
            while (left < right && !isalnum(s[left])) {
                left++;
            }
            // Skip non-alphanumeric characters from right
            while (left < right && !isalnum(s[right])) {
                right--;
            }
            // Compare characters (case-insensitive)
            if (tolower(s[left]) != tolower(s[right])) {
                return false;
            }
            left++;
            right--;
        }
        
        return true;
    }
};
```
- **Time Complexity**: O(n), where `n` is the length of the string. We traverse the string once with two pointers, and each character is checked at most once.
- **Space Complexity**: O(1), as we only use a constant amount of extra space for the pointers and temporary variables.


# 76. Minimum Window Substring Solution [Easy]
https://leetcode.com/problems/minimum-window-substring/description/

Given two strings `s` and `t`, return the minimum window substring of `s` such that every character in `t` (including duplicates) is included in the window. If there is no such substring, return the empty string `""`. The test cases guarantee that the answer is unique.

### Example
```
Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" contains 'A', 'B', and 'C' from string t.
```

## Solution
Below is the C++ solution to find the minimum window substring using a sliding window approach.

```cpp
// TC=O(n), SC=O(k), k is chars in t
class Solution {
public:
    string minWindow(string s, string t) {
        // If t is empty or s is shorter than t, return empty string
        if (t.empty() || s.length() < t.length()) {
            return "";
        }
        
        // Frequency map for characters in t
        unordered_map<char, int> tFreq;
        for (char c : t) {
            tFreq[c]++;
        }
        
        // Required number of characters to match
        int required = tFreq.size();
        int formed = 0;
        
        // Frequency map for current window
        unordered_map<char, int> windowFreq;
        
        // Initialize result: {length, left, right}
        int minLen = INT_MAX, minLeft = 0;
        
        // Sliding window pointers
        int left = 0, right = 0;
        
        while (right < s.length()) {
            // Add character at right to window
            char c = s[right];
            
            // If current character is in t and frequency matches
            if (tFreq.count(c)){
                windowFreq[c]++;
                if(windowFreq[c] == tFreq[c])
                    formed++;
            }
            
            // Try to shrink window from left
            while (left <= right && formed == required) {
                // Update minimum window if current is smaller
                if (right - left + 1 < minLen) {
                    minLen = right - left + 1;
                    minLeft = left;
                }
                
                // Remove character at left from window
                char leftChar = s[left];
                if (windowFreq.count(leftChar)){
                    windowFreq[leftChar]--;
                    // If leftChar is in t and frequency drops below required
                    if (windowFreq[leftChar] < tFreq[leftChar])
                        formed--;
                }
                   
                left++;
            }
            
            right++;
        }
        
        // Return minimum window or empty string if none found
        return minLen == INT_MAX ? "" : s.substr(minLeft, minLen);
    }
};
```

## Explanation
1. **Sliding Window**:
   - Use two pointers: `left` and `right` to define the window.
   - Use a hash map `windowFreq` to track character frequencies in the current window.
   - Use `formed` to count how many characters in the window match the required frequency from `t`.
   - Expand the window by moving `right`:
     - Add the character at `s[right]` to `windowFreq`.
     - If the character is in `t` and its frequency in the window matches `tFreq`, increment `formed`.
   - Shrink the window when `formed == required` (all characters in `t` are covered):
     - Update the minimum window (length and starting position) if the current window is smaller.
     - Remove the character at `s[left]` from `windowFreq`.
     - If the character is in `t` and its frequency drops below the required count, decrement `formed`.
     - Move `left` forward.
2. **Result**:
   - If no valid window is found (`minLen == INT_MAX`), return `""`.
   - Otherwise, return the substring of `s` from `minLeft` with length `minLen`.



# 392. Is Subsequence [Easy]
https://leetcode.com/problems/is-subsequence/description/
Given two strings s and t, return true if s is a subsequence of t, or false otherwise.

A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).

```
Example 1:
Input: s = "abc", t = "ahbgdc"
Output: true
```
```cpp
class Solution {
public:
    bool isSubsequence(string s, string t) {        
        int j = 0;
        for(int i = 0; i < t.length(); i++)
        {
            if(t[i] == s[j])
            {
                j++; //look for next char next
                if(j == s.length())
                    return true;
            }
        }
        
        return false;
    }
};
```


# 844. Backspace String Compare Solution [Super Easy with Stack]
https://leetcode.com/problems/backspace-string-compare/description/

Given two strings `s` and `t`, return `true` if they are equal when both are typed into empty text editors, where `'#'` represents a backspace character. A backspace deletes the character before it (if any).

### Example
```
Input: s = "ab#c", t = "ad#c"
Output: true
Explanation: Both s and t become "ac" after processing backspaces.
```

## Solution
Below is the C++ solution to compare two strings after processing backspace characters.
```cpp
class Solution {
public:
    string clean(string s)
    {
        string cleaned = "";
        stack<char> st;
        for(auto x: s)
        {
            if(x == '#') {
                if(!st.empty())
                    st.pop();
            }
            else
                st.push(x);
        }  
        
        while(!st.empty()) {
            cleaned += st.top(), st.pop();
        }

        return cleaned;
    }
    
    bool backspaceCompare(string s, string t) {
        s = clean(s);
        t = clean(t);
        
        return s==t;
    }
};
```

```cpp
class Solution {
public:
    bool backspaceCompare(string s, string t) {
        return processString(s) == processString(t);
    }
    
private:
    string processString(const string& str) {
        string result;
        for (char c : str) {
            if (c != '#') {
                result.push_back(c);
            } else if (!result.empty()) {
                result.pop_back();
            }
        }
        return result;
    }
};
```

## Time and Space Complexity
- **Time Complexity**: O(n + m), where `n` and `m` are the lengths of strings `s` and `t`, respectively. Each string is processed once.
- **Space Complexity**: O(n + m) in the worst case, for storing the processed strings. (Note: A more space-efficient solution using two pointers exists, but this approach is clearer and still meets constraints.)


# 26. Remove Duplicates from Sorted Array Solution [Super Easy]
https://leetcode.com/problems/remove-duplicates-from-sorted-array/

Given a sorted array `nums`, remove the duplicates in-place such that each element appears only once and return the new length. Do not allocate extra space for another array; you must do this by modifying the input array in-place with O(1) extra memory.

### Example
```
Input: nums = [1,1,2]
Output: 2, nums = [1,2,_]
Explanation: The function returns length = 2, with the first two elements of nums being [1,2]. The remaining elements are not important.
```

## Solution
Below is the C++ solution to remove duplicates from a sorted array in-place.

```cpp
//T&S C: O(n), O(1)

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int k = 0;
        int n = nums.size();
        for(int i =1; i < nums.size(); i++)
        {
            if(nums[i] == nums[i-1]) {
                nums.erase(nums.begin()+i); //element at i-th index will be removed
                k++;
                i--;
            }
        }
        
        return n - k;
    }
};

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        
        int writePos = 1; // Position to write the next unique element
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] != nums[i - 1]) {
                nums[writePos++] = nums[i];
            }
        }
        
        return writePos;
    }
};
```

## Edge Cases
- Empty array: Return 0.
- Single element: Return 1, no duplicates.
- All elements identical (e.g., `[1,1,1]`): Return 1, `nums` becomes `[1,_,_]`.
- No duplicates (e.g., `[1,2,3]`): Return original length, array unchanged.
- Large sorted array with duplicates: Efficiently handles all cases.


# 567. Permutation in String - Hash Table, Two Pointers, String, Sliding Window [Easy]
https://leetcode.com/problems/permutation-in-string/description/

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

# 3. Longest Substring Without Repeating Characters - Hash Table, String, Sliding Window [Easy]
https://leetcode.com/problems/longest-substring-without-repeating-characters/description/

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

# 205. Isomorphic Strings - Hash Table, String [Easy using 2 maps]
https://leetcode.com/problems/isomorphic-strings/description/

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
//badc not same as baba\

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


# 5. Longest Palindromic Substring - Two Pointers, String, Dynamic Programming [Easy]
https://leetcode.com/problems/longest-palindromic-substring/description/

## Problem Description
Given a string `s`, return the longest palindromic substring in `s`.

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


# 451. Sort Characters By Frequency - Hash Table, Sorting, Heap (Priority Queue), Bucket Sort, Counting - [Easy using a map and vector]
https://leetcode.com/problems/sort-characters-by-frequency/description/

Given a string `s`, sort it in decreasing order based on the frequency of the characters. The frequency of a character is the number of times it appears in the string. If two characters have the same frequency, their relative order in the output is not specified.

### Example
```
Input: s = "tree"
Output: "eert"
Explanation: 'e' appears twice, while 'r' and 't' appear once. Thus, "eert" is valid (as is "eetr").

Input: s = "cccaaa"
Output: "aaaccc"
Explanation: Both 'c' and 'a' appear three times, so "aaaccc" is valid (as is "cccaaa").

Input: s = "Aabb"
Output: "bbAa"
Explanation: 'b' appears twice, 'A' and 'a' appear once. Case is preserved.
```

### Constraints
- `1 <= s.length <= 5 * 10^5`
- `s` consists of uppercase and lowercase English letters and digits.

## Solution Approach
The problem can be solved using a frequency map and sorting, or a bucket sort approach for efficiency.

### Frequency Map and Sorting Approach
1. Count the frequency of each character using a hash map.
2. Create a list of character-frequency pairs and sort it by frequency in descending order.
3. Build the result string by repeating each character by its frequency.

### Example Implementation (C++)
```cpp
class Solution {
public:
    string frequencySort(string s) {
        map<char, int> sF;
        int max_ = 0;
        for(auto x: s) {
            sF[x]++;
            max_ = max(max_, sF[x]);
        }

        vector<vector<char>> vB(max_+1);
        for(auto [k, v]: sF)
        {
            vB[v].push_back(k);
        }

        string ans = "";

        for(int i = max_; i > 0; i--)
        {
            auto vC = vB[i];
            if(vC.size() > 0)
            {
                for(auto x: vC)
                {
                    for(int k=0; k < i; k++)
                        ans += x;
                }
            }
        }

        return ans;
    }
};
```

```cpp
class Solution {
public:
    string frequencySort(string s) {
        // Step 1: Count frequency of each character
        unordered_map<char, int> freq;
        for (char c : s) {
            freq[c]++;
        }
        
        // Step 2: Create vector of pairs and sort by frequency
        vector<pair<char, int>> freqVec(freq.begin(), freq.end());
        sort(freqVec.begin(), freqVec.end(), 
             [](const pair<char, int>& a, const pair<char, int>& b) {
                 return a.second > b.second;
             });
        
        // Step 3: Build result string
        string result = "";
        for (auto& p : freqVec) {
            result += string(p.second, p.first);
        }
        
        return result;
    }
};
```

### How It Works
- **Frequency Counting**: Use an `unordered_map` to count how many times each character appears.
- **Sorting**:
  - Convert the map to a vector of pairs `(character, frequency)`.
  - Sort the vector by frequency in descending order using a lambda function.
- **String Construction**: Iterate through the sorted vector, appending each character repeated by its frequency.
- **Edge Cases**:
  - Single character: Returns the character itself.
  - Characters with equal frequency: Order doesn’t matter, handled by sorting.
- **Result**: The string is sorted by character frequency, preserving character case.

### Time and Space Complexity
- **Time Complexity**: O(n + k log k), where `n` is the length of the string and `k` is the number of unique characters (up to 128 for ASCII). The sorting step dominates for small `n`.
- **Space Complexity**: O(k), for the hash map and vector of pairs, plus O(n) for the output string.

### Alternative Approach (Bucket Sort)
1. Count character frequencies using a hash map.
2. Group characters by frequency into buckets (max frequency is `n`).
3. Iterate through buckets in descending order, appending characters.
- **Time Complexity**: O(n), as bucket sort avoids comparison-based sorting.
- **Space Complexity**: O(n) for buckets and output.
The bucket sort approach is more efficient for large strings but slightly more complex to implement.


# 2262. Substring with Largest Variance - Dynamic Programming [Revisit]
https://leetcode.com/problems/substring-with-largest-variance/description/

The variance of a string is defined as the largest difference between the number of occurrences of any two distinct characters in the string. Given a string `s`, return the largest variance possible among all substrings of `s`. A substring is a contiguous sequence of characters within `s`.

### Example
```
Input: s = "aababbb"
Output: 3
Explanation: The substring "babbb" has 3 'b's and 1 'a', so the variance is 3 - 1 = 2. Another substring "abbb" has 3 'b's and 0 'a', variance is 3 - 0 = 3 (after considering 'a' and 'b').

Input: s = "abcde"
Output: 0
Explanation: No two characters appear more than once in any substring, so the variance is 0.
```

### Constraints
- `1 <= s.length <= 10^5`
- `s` consists of lowercase English letters.

```py
Hint 1
Think about how to solve the problem if the string had only two distinct characters.
Hint 2
If we replace all occurrences of the first character by +1 and those of the second character by -1, can we efficiently calculate the largest possible variance of a string with only two distinct characters?
Hint 3
Now, try finding the optimal answer by taking all possible pairs of characters into consideration.
```

## Solution Approach
The problem can be solved by considering all pairs of distinct characters and using a Kadane-like algorithm to find the maximum variance for each pair in substrings.

### Modified Kadane’s Algorithm Approach
1. Iterate over all pairs of characters `(c1, c2)` (e.g., 'a' and 'b') in the string.
2. For each pair, convert the string into a sequence where:
   - `c1` is counted as `+1`.
   - `c2` is counted as `-1`.
   - Other characters are ignored.
3. Use a Kadane-like algorithm to find the maximum subarray sum (representing `count(c1) - count(c2)`), but with a constraint:
   - The substring must contain at least one `c2` (to ensure a valid variance).
4. Track the global maximum variance across all pairs.

### Example Implementation (C++)
```cpp
class Solution {
public:
    int largestVariance(string s) {
        int maxVariance = 0;
        unordered_set<char> unique(s.begin(), s.end());
        
        // Try all pairs of distinct characters
        for (char c1 : unique) {
            for (char c2 : unique) {
                if (c1 == c2) continue;
                
                // Kadane-like algorithm for c1 (+1) and c2 (-1)
                int currVariance = 0; // Current sum of +1/-1
                bool hasC2 = false;   // Tracks if c2 is in current substring
                bool hadC2 = false;   // Tracks if c2 was in a previous substring
                
                for (char c : s) {
                    if (c == c1) {
                        currVariance++;
                    } else if (c == c2) {
                        hasC2 = true;
                        hadC2 = true;
                        currVariance--;
                    }
                    
                    if (hasC2) {
                        // Valid substring with at least one c2
                        maxVariance = max(maxVariance, currVariance);
                    }
                    
                    if (currVariance < 0 && hadC2) {
                        // Reset to consider new substring with at least one c2
                        currVariance = 0;
                        hasC2 = false;
                    }
                }
            }
        }
        
        return maxVariance;
    }
};
```

### How It Works
- **Character Pairs**: Iterate over all pairs of distinct characters (up to 26 * 25 pairs for lowercase letters).
- **Sequence Conversion**: For each pair `(c1, c2)`, treat `c1` as `+1`, `c2` as `-1`, and ignore others.
- **Kadane-like Algorithm**:
  - Track `currVariance` (sum of `+1`/`-1` for the current substring).
  - Ensure the substring contains at least one `c2` (`hasC2`).
  - Use `hadC2` and `firstC2` to handle cases where a negative sum can be reset to include a prior `c2`.
- **Edge Cases**:
  - Single character type: Variance is 0 (no valid pair).
  - No `c2` in substring: Invalid for variance calculation.
- **Result**: The maximum variance is the largest `count(c1) - count(c2)` across all pairs and substrings.

### Time and Space Complexity
- **Time Complexity**: O(n * k^2), where `n` is the length of the string and `k` is the number of unique characters (up to 26 for lowercase letters). We process the string for each pair of characters.
- **Space Complexity**: O(k), for the set of unique characters.

### Alternative Approach
A brute-force approach checking all substrings and calculating variance for each is infeasible (O(n^2 * k)). The modified Kadane’s algorithm is optimal for the given constraints, balancing efficiency and correctness.


# 394. Decode String - Stack, Recursion [Easy]
https://leetcode.com/problems/decode-string/description/

Given an encoded string, return its decoded string. The encoding rule is: `k[encoded_string]`, where the `encoded_string` inside the square brackets is repeated exactly `k` times. `k` is a positive integer. The input string is guaranteed to be valid, with no extra white spaces, well-formed square brackets, and no digits in the original decoded string.

### Example
```
Input: s = "3[a]2[bc]"
Output: "aaabcbc"
Explanation: Decode "3[a]" to "aaa" and "2[bc]" to "bcbc", resulting in "aaabcbc".

Input: s = "3[a2[c]]"
Output: "accaccacc"
Explanation: First decode "2[c]" to "cc", then "3[a2[c]]" becomes "3[acc]" which decodes to "accaccacc".

Input: s = "2[abc]3[cd]ef"
Output: "abcabccdcdcdef"
Explanation: Decode "2[abc]" to "abcabc", "3[cd]" to "cdcdcd", then append "ef".
```

### Constraints
- `1 <= s.length <= 30`
- `s` consists of lowercase English letters, digits, and square brackets `[]`.
- `s` is guaranteed to be a valid input.
- All integers in `s` are in the range `[1, 300]`.

## Solution Approach
The problem can be solved using a stack-based approach to handle nested brackets and repetitions.

### Stack-Based Approach
1. Use two stacks:
   - One for counts (to store the number of repetitions).
   - One for strings (to store intermediate decoded strings).
2. Iterate through the input string:
   - If a digit is encountered, build the number (may be multi-digit).
   - If an opening bracket `[` is encountered, push the current number and current string onto their respective stacks, then reset them.
   - If a letter is encountered, append it to the current string.
   - If a closing bracket `]` is encountered:
     - Pop the string and count from the stacks.
     - Repeat the current string `count` times and append it to the popped string.
     - Update the current string with the result.
3. Return the final decoded string.

### Example Implementation (C++)
```cpp
class Solution {
public:
    string reverse(string s)
    {
        string r = "";

        for(int i = s.size()-1; i >= 0; i--)
        {
            r = r + s.at(i);
        }

        return r;
    }

    string repeat(string s, int k)
    {
        if (k < 2)
            return s;

        string r = "";
        for(int i = 0; i < k; i++)
        {
            r += s;
        }

        return r;
    }

    string decodeString(string s) {
        stack<char> st;
        
        for(auto& c: s)
        {
            if (c == ']')
            {
                string sub = "";
                while(!st.empty() && st.top() != '[')
                {
                    auto tc = st.top();
                    st.pop();
                    sub += tc;
                }

                //'['
                st.pop(); //remove [
                //3[a]2[bc]
                //no more alphas
                int num = 0;
                int tens = 1;
                while(!st.empty() && isdigit(st.top()))
                {
                    char cdigit = st.top();
                    int digit = cdigit - '0';

                    num = num + (digit * tens);
                    tens = tens * 10;
                    st.pop();
                }
                string rev = reverse(sub);
                string enc = repeat(rev, num);

                for(auto cs: enc)
                    st.push(cs);
            }
            else
            {
                st.push(c);
            }
        }
        
        string enc = "";
        while(!st.empty())
        {
            enc += st.top();
            st.pop();  
        }  

        return reverse(enc);
    }
};
```

### Time and Space Complexity
- **Time Complexity**: O(n * maxK), where `n` is the length of the input string and `maxK` is the maximum repetition count (up to 300). Each character is processed once, but string repetition may amplify the output size.
- **Space Complexity**: O(m), where `m` is the maximum nesting level of brackets, for the stacks. The output string is not counted in space complexity.

### Alternative Approach
1. **Recursive DFS**:
   - Parse the string recursively, treating each bracketed section as a subproblem.
   - Time Complexity: O(n * maxK)
   - Space Complexity: O(m) for the recursion stack
The stack-based approach is preferred for its iterative nature and clarity in handling nested structures.

# 443. String Compression - Two Pointers [Easy]
https://leetcode.com/problems/string-compression/description/

## Problem Description
Given an array of characters `chars`, compress it using the following algorithm:
- For each group of consecutive repeating characters:
  - If the group's length is 1, append the character to the result.
  - Otherwise, append the character followed by the group's length.
- The compressed string is stored in the input `chars` array, and the new length of the array is returned.
- The solution must be in-place, and only the first `new length` elements of `chars` are considered after compression.

### Example
```
Input: chars = ["a","a","b","b","c","c","c"]
Output: 6, chars = ["a","2","b","2","c","3"]
Explanation: "aa" is compressed to "a2", "bb" to "b2", and "ccc" to "c3". The new length is 6.

Input: chars = ["a"]
Output: 1, chars = ["a"]
Explanation: Single character remains unchanged.

Input: chars = ["a","b","b","b","b","b","b","b","b","b","b","b","b"]
Output: 4, chars = ["a","b","1","2"]
Explanation: "a" remains "a", "bbbbbbbbbbbb" is compressed to "b12". The new length is 4.
```

### Constraints
- `1 <= chars.length <= 2000`
- `chars[i]` is a lowercase English letter, uppercase English letter, digit, or symbol.

## Solution Approach
The problem can be solved by iterating through the array, counting consecutive repeating characters, and writing the compressed result in-place.

### Two-Pointer Approach
1. Use a pointer `write` to track the position where the next character or count should be written.
2. Iterate through the array with a pointer `read`:
   - Count consecutive occurrences of the same character.
   - Write the character at the `write` position.
   - If the count is greater than 1, convert the count to a string and write its digits.
3. Return the final `write` position as the new length.

### Example Implementation (C++)
```cpp
class Solution {
public:
    int compress(vector<char>& chars) {
        int write = 0; // Position to write the compressed result
        int read = 0;  // Position to read the input
        
        while (read < chars.size()) {
            char currentChar = chars[read];
            int count = 0;
            
            // Count consecutive occurrences
            while (read < chars.size() && chars[read] == currentChar) {
                count++;
                read++;
            }
            
            // Write the character
            chars[write++] = currentChar;
            
            // Write the count if greater than 1
            if (count > 1) {
                string countStr = to_string(count);
                for (char c : countStr) {
                    chars[write++] = c;
                }
            }
        }
        
        return write;
    }
};
```

### How It Works
- **Pointers**:
  - `write`: Tracks where to place the next character or digit in the compressed array.
  - `read`: Scans the array to count consecutive characters.
- **Compression**:
  - For each group of identical characters, count their occurrences.
  - Write the character once.
  - If the count is greater than 1, convert the count to a string and write each digit.
- **In-Place**:
  - Overwrite the original array starting at `write`, ensuring the compressed result fits within the first `write` positions.
- **Edge Cases**:
  - Single character: Written as is, length 1.
  - All same characters: Compressed to one character plus count digits (e.g., "aaaaa" to "a5").
  - No consecutive repeats: Each character written once, length unchanged.
- **Result**: The array is modified in-place, and the new length (`write`) is returned.

### Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of `chars`, as we traverse the array once and handle counts in linear time.
- **Space Complexity**: O(1), excluding the output array modification, as we only use a constant amount of extra space (temporary string for counts is small and bounded).

### Alternative Approach
1. **Two-Pass with Extra Space**:
   - First pass: Compute the compressed string in a temporary array.
   - Second pass: Copy back to the input array.
   - Time Complexity: O(n)
   - Space Complexity: O(n)
  The in-place approach is preferred as it meets the problem’s requirement for in-place modification and minimizes space usage.


# 387. First Unique Character in a String - Hash Table, Queue [Very Easy]
https://leetcode.com/problems/first-unique-character-in-a-string/

Given a string `s`, find the first non-repeating character in it and return its index. If no such character exists, return `-1`.

### Example
```
Input: s = "leetcode"
Output: 0
Explanation: The first unique character is 'l' at index 0.

Input: s = "loveleetcode"
Output: 2
Explanation: The first unique character is 'v' at index 2.

Input: s = "aabb"
Output: -1
Explanation: No character appears exactly once.
```

### Constraints
- `1 <= s.length <= 10^5`
- `s` consists of only lowercase English letters.

## Solution Approach
The problem can be solved using a frequency map to count character occurrences, followed by a second pass to find the first character with a count of 1.

### Two-Pass Frequency Map Approach
1. Create a frequency map to count the occurrences of each character in the string.
2. Iterate through the string again to find the first character whose frequency is 1.
3. Return the index of that character, or `-1` if no such character exists.

### Example Implementation (C++)
```cpp
class Solution {
public:
    int firstUniqChar(string s) {
        // Frequency map for lowercase letters
        vector<int> freq(26, 0);
        
        // Count occurrences of each character
        for (char c : s) {
            freq[c - 'a']++;
        }
        
        // Find first character with frequency 1
        for (int i = 0; i < s.length(); i++) {
            if (freq[s[i] - 'a'] == 1) {
                return i;
            }
        }
        
        return -1;
    }
};
```

### How It Works
- **Edge Cases**:
  - Single character: Returns 0 (frequency is 1).
  - No unique character: Returns -1 (e.g., "aabb").
  - Long string: Vector handles up to 10^5 characters efficiently.
- **Result**: Returns the index of the first unique character or -1 if none exists.

### Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the string, as we perform two passes through the string.
- **Space Complexity**: O(1), as the frequency vector has a fixed size of 26 (constant for lowercase letters).

### Alternative Approach
1. **Hash Map with Indices**:
   - Use a hash map to store character frequencies and their first indices.
   - Iterate through the string once to populate the map.
   - Find the smallest index of a character with frequency 1.
   - Time Complexity: O(n)
   - Space Complexity: O(k), where `k` is the number of unique characters (up to 26).
The vector-based approach is preferred for its simplicity and guaranteed O(1) space due to the fixed alphabet size.


# 273. Integer to English Words [Easy]
https://leetcode.com/problems/integer-to-english-words/description/

Convert a non-negative integer `num` to its English words representation.

### Example
```
Input: num = 123
Output: "One Hundred Twenty Three"
Explanation: 123 is written as "One Hundred" for 100, "Twenty" for 20, and "Three" for 3.

Input: num = 12345
Output: "Twelve Thousand Three Hundred Forty Five"
Explanation: 12345 is broken into groups: 12 (Twelve Thousand), 345 (Three Hundred Forty Five).

Input: num = 1234567
Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
Explanation: 1234567 is broken into groups: 1 (One Million), 234 (Two Hundred Thirty Four Thousand), 567 (Five Hundred Sixty Seven).

Input: num = 0
Output: "Zero"
Explanation: 0 is simply "Zero".
```

### Constraints
- `0 <= num <= 2^31 - 1`

## Solution Approach
The problem can be solved by processing the number in groups of three digits (thousands, millions, billions) and converting each group to words using predefined mappings for numbers 1-19, tens, and larger units.

### Group-by-Three Approach
1. Define arrays for:
   - Numbers 1-19 (e.g., "One", "Two", ..., "Nineteen").
   - Tens (e.g., "Twenty", "Thirty", ..., "Ninety").
   - Large units (e.g., "Thousand", "Million", "Billion").
2. Handle the special case of `num = 0` by returning "Zero".
3. Process the number in groups of three digits from right to left:
   - Extract the last three digits using modulo (`num % 1000`).
   - Convert the three-digit number to words (hundreds, tens, ones).
   - Append the appropriate unit (Thousand, Million, Billion) based on the group position.
   - Divide `num` by 1000 to process the next group.
4. Combine the words for each group, ensuring proper spacing and trimming.

### Example Implementation (C++)

```cpp
class Solution {
public:
    vector<string> below20 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    
    vector<string> tens = {"", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety", "Hundred"};
    
    string convert(int n)
    {
        if(n >= 1000000000)
            return convert(n / 1000000000) + " Billion" + convert(n % 1000000000);
        
        if(n >= 1000000)
            return convert(n / 1000000) + " Million" + convert(n % 1000000);

        if(n >= 1000)
            return convert(n / 1000) + " Thousand" + convert(n % 1000);

        if(n >= 100)
            return convert(n / 100) + " Hundred" + convert(n % 100);

        if(n >= 20)
            return " " + tens[n/10] + convert(n % 10);
        
        if(n >= 1)
            return " " + below20[n];
            
        return "";
    }
    
    string numberToWords(int num) {
        if(num == 0)
            return "Zero";
        return convert(num).substr(1);
    }
};
```

```cpp
class Solution {
public:
    string numberToWords(int num) {
        if (num == 0) return "Zero";
        
        // Define word mappings
        vector<string> below20 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", 
                                 "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", 
                                 "Seventeen", "Eighteen", "Nineteen"};
        vector<string> tens = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
        vector<string> thousands = {"", "Thousand", "Million", "Billion"};
        
        string result = "";
        int groupIndex = 0;
        
        while (num > 0) {
            int threeDigits = num % 1000;
            if (threeDigits > 0) {
                string group = convertThreeDigits(threeDigits, below20, tens);
                if (!group.empty()) {
                    if (!result.empty()) result = " " + result;
                    result = group + (thousands[groupIndex].empty() ? "" : " " + thousands[groupIndex]) + result;
                }
            }
            num /= 1000;
            groupIndex++;
        }
        
        return result;
    }
    
private:
    string convertThreeDigits(int num, const vector<string>& below20, const vector<string>& tens) {
        string result = "";
        
        // Handle hundreds
        if (num >= 100) {
            result += below20[num / 100] + " Hundred";
            num %= 100;
            if (num > 0) result += " ";
        }
        
        // Handle tens and ones
        if (num >= 20) {
            result += tens[num / 10];
            num %= 10;
            if (num > 0) result += " " + below20[num];
        } else if (num > 0) {
            result += below20[num];
        }
        
        return result;
    }
};
```

### How It Works
- **Zero Case**: If `num = 0`, return "Zero" directly.
- **Group Processing**:
  - Extract three digits at a time (`num % 1000`).
  - Convert the three-digit number to words using `convertThreeDigits`:
    - Hundreds: Add the word for `num / 100` followed by "Hundred".
    - Tens and Ones: If `num >= 20`, add the tens word and optionally the ones word; otherwise, use the `below20` word.
  - Append the appropriate unit (Thousand, Million, Billion) based on the group index.
- **Combining**:
  - Prepend each group’s words to the result, adding spaces as needed.
  - Skip empty groups (e.g., 1000 has no words for the last three digits).
- **Edge Cases**:
  - Single digit: Handled by `below20` in `convertThreeDigits`.
  - Numbers like 100: Only "One Hundred" is added.
  - Large numbers: Processed group by group up to billions.
- **Result**: Returns the English words representation of the number.

### Time and Space Complexity
- **Time Complexity**: O(log n), where `n` is the input number, as we process up to 4 groups of three digits (since `n <= 2^31 - 1` has at most 10 digits).
- **Space Complexity**: O(1), as the storage for word mappings and the result string is bounded by a constant (output string excluded).

### Alternative Approach
1. **Recursive**:
   - Recursively break the number into groups and convert each group.
   - Time Complexity: O(log n)
   - Space Complexity: O(log n) due to recursion stack.
The iterative approach is preferred for its simplicity and constant space usage, avoiding recursion while clearly handling each group.


# 283. Move Zeroes Solution - Two Pointers [Very Easy]

## Problem Description
Given an integer array `nums`, move all `0`'s to the end of it while maintaining the relative order of the non-zero elements. The operation must be done in-place without making a copy of the array.

### Example
```
Input: nums = [0,1,0,3,12]
Output: [1,3,12,0,0]
```

## Solution
Below is the C++ solution to move all zeroes to the end of the array.

```cpp
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        // Step 1: Move all non-zero elements to the front
        int write = 0;
        for(int i=0; i < nums.size(); i++)
        {
            if(nums[i] != 0 )
                nums[write++] = nums[i];
        }

        // Step 2: Fill the rest with zeroes
        while(write < nums.size())
            nums[write++] = 0;
    }
};


```
## Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the array. We traverse the array once to move non-zero elements and once to fill zeroes.
- **Space Complexity**: O(1), as we only use a constant amount of extra space.

## Edge Cases
- Empty array: No operation needed.
- Array with all zeroes: All elements remain zero, no change in order.
- Array with no zeroes: Array remains unchanged.
- Single element: No change needed.


# 88. Merge Sorted Array Solution - Two Pointers [Easy]
https://leetcode.com/problems/merge-sorted-array/description/

Given two sorted integer arrays `nums1` and `nums2`, merge `nums2` into `nums1` as one sorted array. The number of elements initialized in `nums1` and `nums2` are `m` and `n` respectively. You may assume that `nums1` has a size equal to `m + n` such that it has enough space to hold additional elements from `nums2`. The merge must be done in-place.

### Example
```
Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
Output: [1,2,2,3,5,6]
```

## Solution
Below is the C++ solution to merge two sorted arrays in  `nums1` and `nums2` in-place.

```cpp
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1; // Pointer for nums1
        int j = n - 1; // Pointer for nums2
        int k = m + n - 1; // Pointer for merged array
        
        // Merge from the end to avoid overwriting
        while (j >= 0) {
            if (i >= 0 && nums1[i] > nums2[j]) {  //<=   NOTE i>=0 
                nums1[k--] = nums1[i--];
            } else {
                nums1[k--] = nums2[j--];
            }
        }
    }
};
```

## Explanation
1. **Three-Pointer Approach**:
   - Use `i` to track the last element of `nums1` (initially `m - 1`).
   - Use `j` to track the last element of `nums2` (initially `n - 1`).
   - Use `k` to track the position in `nums1` where the next element will be placed (initially `m + n - 1`).
2. **Merge from End**:
   - Compare elements from `nums1` and `nums2`.
   - Place the larger element at position `k` in `nums1` and decrement the corresponding pointer (`i` or `j`) and `k`.
   - Continue until all elements from `nums2` are placed (`j >= 0`).
   - If `nums1` has remaining elements, they are already in place.
3. **In-Place**: The solution modifies `nums1` directly without using extra space.

## Time and Space Complexity
- **Time Complexity**: O(m + n), as we process each element from both arrays once.
- **Space Complexity**: O(1), as we only use a constant amount of extra space for pointers.

## Edge Cases
- `m = 0`: `nums1` is empty, copy all elements from `nums2`.
- `n = 0`: `nums2` is empty, `nums1` remains unchanged.
- `m + n = 0`: Both arrays are empty, no operation needed.
- One array is much larger than the other: The solution handles uneven sizes correctly.

# 239. Sliding Window Maximum - Queue, Sliding Window, Heap (Priority Queue), Monotonic Queue

This document describes the solution to the "Sliding Window Maximum" problem (LeetCode #239).

## Problem Description
Given an array `nums` and an integer `k`, return the maximum value in each sliding window of size `k` as the window moves from left to right. The sliding window moves one position to the right at each step, and there are `n - k + 1` windows, where `n` is the length of the array.

### Example
```
Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation:
Window position                Max
[1 3 -1] -3 5 3 6 7           3
 1 [3 -1 -3] 5 3 6 7          3
 1 3 [-1 -3 5] 3 6 7          5
 1 3 -1 [-3 5 3] 6 7          5
 1 3 -1 -3 [5 3 6] 7          6
 1 3 -1 -3 5 [3 6 7]          7

Input: nums = [1], k = 1
Output: [1]
Explanation: Single element window has max 1.

Hint 1
How about using a data structure such as deque (double-ended queue)?
Hint 2
The queue size need not be the same as the window’s size.
Hint 3
Remove redundant elements and the queue should store only elements that need to be considered.
```

### Constraints
- `1 <= nums.length <= 10^5`
- `-10^4 <= nums[i] <= 10^4`
- `1 <= k <= nums.length`

## Solution Approach
The problem can be solved efficiently using a deque to maintain indices of potential maximum values in the sliding window, ensuring the front of the deque always holds the index of the maximum.

### Deque-Based Approach
1. Use a deque to store indices of elements in the current window, maintaining a decreasing order of values (front has the largest value).
2. For each index `i` in the array:
   - Remove indices from the front of the deque if they are outside the current window (`i - k`).
   - Remove indices from the back of the deque if their values are less than `nums[i]`, as they cannot be the maximum in future windows.
   - Add the current index `i` to the back of the deque.
3. After processing the first `k` elements, the front of the deque gives the maximum for each window. Store it in the result array for each subsequent step.

### Example Implementation (C++)
```cpp
class Solution {
public:   
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> result;
        if (k == 0) return result;
        deque<int> w;
        for (int i = 0, n = (int)nums.size(); i < n; i++) {
            while (!w.empty() && w.front() <= i-k) {
                w.pop_front();
            }
            
            while (!w.empty() && nums[w.back()] <= nums[i])
                w.pop_back();
            w.push_back(i);
            
            if (i >= k-1)
                result.push_back(nums[w.front()]);
        }
        return result;
    }
};
```

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq; // Stores indices of potential max values
        vector<int> result;
        
        for (int i = 0; i < nums.size(); i++) {
            // Remove indices outside the current window
            while (!dq.empty() && dq.front() <= i - k) {
                dq.pop_front();
            }
            
            // Remove indices of smaller values as they can't be max
            while (!dq.empty() && nums[dq.back()] < nums[i]) {
                dq.pop_back();
            }
            
            // Add current index
            dq.push_back(i);
            
            // After first k elements, front of deque is the max
            if (i >= k - 1) {
                result.push_back(nums[dq.front()]);
            }
        }
        
        return result;
    }
};
```

### How It Works
- **Deque**:
  - Stores indices of elements in decreasing order of their values.
  - Front always holds the index of the maximum element in the current window.
- **Processing**:
  - Remove out-of-window indices from the front (`i - k` or earlier).
  - Remove indices of smaller elements from the back, as they’re irrelevant for future maxima.
  - Add the current index to the back.
- **Result**:
  - After processing `k` elements, the front of the deque gives the maximum for each window.
  - Store `nums[dq.front()]` in the result starting from index `k-1`.
- **Edge Cases**:
  - `k = 1`: Each element is its own window maximum.
  - `k = nums.length`: Single window, return the maximum of the array.
  - Single element: Deque handles it correctly.
- **Result**: Returns an array of maximum values for each sliding window.

### Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the array. Each element is pushed and popped at most once from the deque.
- **Space Complexity**: O(k), for the deque, which stores at most `k` indices, plus O(n-k+1) for the output array.

### Alternative Approaches
1. **Brute Force**:
   - Compute the maximum for each window by scanning all `k` elements.
   - Time Complexity: O(n * k)
   - Space Complexity: O(1) (excluding output)


# 299. Bulls and Cows Solution

## Problem Description
You are playing the Bulls and Cows game. You have a secret number and a friend's guess, both represented as strings of equal length. Each digit in the guess is compared with the secret:
- A "bull" is a digit that is in the correct position.
- A "cow" is a digit that is in the secret but in the wrong position.
Return a hint in the format `"xAyB"`, where `x` is the number of bulls and `y` is the number of cows. Assume the secret and guess contain only digits and are of equal length.

### Example
```
Input: secret = "1807", guess = "7810"
Output: "1A3B"
Explanation: Bulls: '8' (position 3). Cows: '1', '0', '7' (present but in wrong positions).
```

## Solution
Below is the C++ solution to compute the bulls and cows hint.

```cpp
class Solution {
public:
    string getHint(string secret, string guess) {
        int bulls = 0;
        int cows = 0;
        string cowss = "";
        string cowsg;
        
        for(int i = 0; i < secret.length(); i++) {
            if(secret[i] == guess[i])
                bulls++;
            else {
                cowss += secret[i];
                cowsg += guess[i];
            }
        }
        
        for(auto x: cowss) {
            for(auto&y : cowsg)
                if(x == y)
                {
                    cows++;
                    y = 'x';
                    break;
                }
        }

        stringstream hint;
        hint << bulls << "A"<<cows<<"B";
        return hint.str();
    }
};

class Solution {
public:
    string getHint(string secret, string guess) {
        int bulls = 0, cows = 0;
        unordered_map<char, int> secretCount;
        
        // Step 1: Count bulls and store non-bull digits in secret
        for (int i = 0; i < secret.size(); ++i) {
            if (secret[i] == guess[i]) {
                bulls++;
            } else {
                secretCount[secret[i]]++;
            }
        }
        
        // Step 2: Count cows by checking non-bull positions in guess
        for (int i = 0; i < guess.size(); ++i) {
            if (secret[i] != guess[i] && secretCount[guess[i]] > 0) {
                cows++;
                secretCount[guess[i]]--;
            }
        }
        
        // Format the result
        return to_string(bulls) + "A" + to_string(cows) + "B";
    }
};
```

## Explanation
1. **Bulls Calculation**:
   - Iterate through both strings simultaneously.
   - If the digits at position `i` in `secret` and `guess` match (`secret[i] == guess[i]`), increment the `bulls` counter.
   - For non-matching positions, increment the count of the `secret[i]` digit in a hash map (`secretCount`).
2. **Cows Calculation**:
   - Iterate through both strings again.
   - For positions where digits do not match (`secret[i] != guess[i]`), check if `guess[i]` exists in `secretCount` (i.e., it appears in a non-bull position in `secret`).
   - If so, increment `cows` and decrement the count in `secretCount` to avoid double-counting.
3. **Result Formatting**:
   - Return the hint as a string in the format `"xAyB"`, where `x` is the number of bulls and `y` is the number of cows.

## Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the strings. We perform two passes through the strings and use hash map operations (O(1) on average).
- **Space Complexity**: O(1), since the hash map stores at most 10 distinct digits (0-9), which is constant.

## Edge Cases
- Empty strings: Not applicable due to constraints (strings are non-empty and equal length).
- No bulls or cows: `secret = "1234"`, `guess = "5678"` returns `"0A0B"`.
- All bulls: `secret = "1234"`, `guess = "1234"` returns `"4A0B"`.
- All cows: `secret = "1234"`, `guess = "4321"` returns `"0A4B"`.
- Repeated digits: `secret = "1122"`, `guess = "2211"` returns `"0A4B"`.


# 11. Container With Most Water Solution

## Problem Description
Given an integer array `height` of length `n`, where each element represents the height of a vertical line at index `i`, find two lines that together with the x-axis form a container that holds the most water. The container's width is the distance between the indices, and its height is the minimum of the two line heights. Return the maximum area of water the container can store.

### Example
```
Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The maximum area is formed by lines at indices 1 and 8 (heights 8 and 7), with area = min(8,7) * (8-1) = 49.
```
<img src="../assets/question_11.jpg" width="40%">

## Solution
Below is the C++ solution to find the maximum area of water using a two-pointer approach.

```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {  
        int area = 0;
        for(int i = 0, j = height.size()-1; i<j;)
        {
            auto w = j-i;
            auto h = min(height[i], height[j]);
            
            if(height[i] < height[j])
                i++;
            else
                j--;
            
            area = max(area, w * h );
        }
        
        return area;
    }
};

class Solution {
public:
    int maxArea(vector<int>& height) {
        int maxWater = 0;
        int left = 0, right = height.size() - 1;
        
        while (left < right) {
            // Calculate area: width * min(height[left], height[right])
            int width = right - left;
            int h = min(height[left], height[right]);
            maxWater = max(maxWater, width * h);
            
            // Move the pointer with the smaller height
            if (height[left] <= height[right]) {
                left++;
            } else {
                right--;
            }
        }
        
        return maxWater;
    }
};
```

## Explanation
1. **Two-Pointer Approach**:
   - Use two pointers: `left` starting at the beginning (index 0) and `right` starting at the end (index `n-1`).
   - The area of water is calculated as `width * height`, where:
     - Width is `right - left`.
     - Height is the minimum of `height[left]` and `height[right]`.
   - Update `maxWater` with the maximum area seen so far.
2. **Pointer Movement**:
   - To maximize the area, move the pointer pointing to the shorter line inward:
     - If `height[left] <= height[right]`, increment `left`.
     - Otherwise, decrement `right`.
   - This ensures we explore combinations that could potentially yield a larger area (moving the shorter line might find a taller one, while moving the taller line would only reduce the area due to a smaller width).
3. **Termination**:
   - Continue until `left` meets `right`.
4. **Result**:
   - Return `maxWater`, the maximum area found.

## Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the array. The two pointers traverse the array once, with `left` and `right` collectively moving at most `n` steps.
- **Space Complexity**: O(1), as we only use a constant amount of extra space for variables.

## Edge Cases
- Array with two elements: Return `min(height[0], height[1]) * 1`.
- All heights equal: Maximum area is `height[0] * (n-1)` (using the first and last lines).
- Smallest height at ends: Correctly handles cases like `[1,1000,1]` by moving pointers inward.
- Large array: Efficiently processes up to `n = 10^5` within constraints.
- Monotonic array: Handles increasing or decreasing arrays by checking all valid pairs.

# Candy Crush 1D
https://leetcode.com/discuss/post/380650/bloomberg-phone-candy-crush-1d-by-suprit-r11f/

Write a function to crush candy in one dimensional board. In candy crushing games, groups of like items are removed from the board. In this problem, any sequence of 3 or more like items should be removed and any items adjacent to that sequence should now be considered adjacent to each other. This process should be repeated as many time as possible. You should greedily remove characters from left to right.

```cpp
#include <string>
#include <stack>
#include <vector>

class Solution {
public:
    string removeDuplicates(string s) {
        // Stack to store pairs of character and their count
        stack<pair<char, int>> st;
        
        for (char c : s) {
            // If stack is not empty and current char matches top char
            if (!st.empty() && st.top().first == c) {
                st.top().second++; // Increment count
            } else {
                st.push({c, 1}); // Push new char with count 1
            }
            
            // If count reaches 3, remove the sequence
            if (!st.empty() && st.top().second >= 3) {
                st.pop();
            }
        }
        
        // Build result string from stack
        string result = "";
        while (!st.empty()) {
            auto [c, count] = st.top();
            st.pop();
            result = string(count, c) + result; // Prepend count occurrences of char
        }
        
        // Repeat process if result still has sequences of 3 or more
        string prev = s;
        while (result != prev) {
            prev = result;
            result = removeDuplicates(result); // Recursively apply the same logic
        }
        
        return result;
    }
};
```
