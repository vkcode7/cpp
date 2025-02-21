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
