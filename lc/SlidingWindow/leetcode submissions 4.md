# 443. String Compression - Two Pointers

This document describes the solution to the "String Compression" problem (LeetCode #443).

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
        queue<char> q;
        
        if(chars.size() <= 1)
            return chars.size();
        
        for(int i = 0; i < chars.size(); i++)
        {
            int count = 1;
            
            q.push(chars[i]);
            while(i+1 < chars.size() && chars[i] == chars[i+1]) {
                count++;
                i++;
            }
            
            if(count > 1)
            {
                string scount = to_string(count);
                for(auto c: scount)
                    q.push(c);
            }  
        }
        
        chars.clear();
        while(!q.empty())
        {
            chars.push_back(q.front());
            q.pop();
        }
        
        return chars.size();
    }
};
```

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


# 387. First Unique Character in a String - Hash Table, Queue


This document describes the solution to the "First Unique Character in a String" problem (LeetCode #387).

## Problem Description
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
        if(s.empty())
            return -1;
        
        unordered_map<char, int> unique;
        int index = 0;
        for(auto x : s)
        {
            if(unique.find(x) != unique.end())
                unique[x] = -1;
            else
                unique[x] = index;
            
            index++;
        }
        
        index = s.size();
        for(auto it : unique)
        {
            if(it.second == -1)
                continue;
            
            index = min(index, it.second);
        }
        
        return index == s.size() ? -1 : index;
    }
};
```

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
- **Frequency Map**:
  - Use a vector of size 26 (for lowercase letters) to store the count of each character.
  - Iterate through the string and increment the count for each character (`c - 'a'` maps 'a' to  créditos: 0, 'b' to 1, etc.).
- **Second Pass**:
  - Iterate through the string and check the frequency of each character.
  - Return the index of the first character with a frequency of 1.
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


# 273. Integer to English Words

This document describes the solution to the "Integer to English Words" problem (LeetCode #273).

## Problem Description
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

https://leetcode.com/submissions/#/5
