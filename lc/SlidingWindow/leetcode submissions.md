
# 1431. Kids With the Greatest Number of Candies

This document describes the solution to the "Kids With the Greatest Number of Candies" problem (LeetCode #1431).

## Problem Description
Given an array `candies` where `candies[i]` represents the number of candies the `i`-th kid has, and an integer `extraCandies`, determine whether each kid can have the greatest number of candies among all kids by giving them all the `extraCandies`. Return a boolean array `result` of length `n`, where `result[i]` is `true` if, after giving the `i`-th kid all the extra candies, they will have the greatest number of candies, and `false` otherwise. Multiple kids can have the greatest number of candies.

### Example
```
Input: candies = [2,3,5,1,3], extraCandies = 3
Output: [true,true,true,false,true]
Explanation: 
- Kid 0: 2 + 3 = 5 (equal to max, true)
- Kid 1: 3 + 3 = 6 (greater than max, true)
- Kid 2: 5 + 3 = 8 (greater than max, true)
- Kid 3: 1 + 3 = 4 (less than max, false)
- Kid 4: 3 + 3 = 6 (greater than max, true)

Input: candies = [4,2,1,1,2], extraCandies = 1
Output: [true,false,false,false,false]
Explanation: Max candies is 4. Only kid 0 (4 + 1 = 5) can reach or exceed it.

Input: candies = [12,1,12], extraCandies = 10
Output: [true,false,true]
Explanation: Kids 0 and 2 can reach 22 candies, but kid 1 can only reach 11.
```

### Constraints
- `n == candies.length`
- `2 <= n <= 100`
- `1 <= candies[i] <= 100`
- `1 <= extraCandies <= 50`

## Solution Approach
The problem can be solved by finding the maximum number of candies any kid has and checking if each kid can reach or exceed this maximum by adding `extraCandies`.

### Linear Scan Approach
1. Find the maximum number of candies in the `candies` array.
2. Iterate through the `candies` array:
   - For each kid, check if `candies[i] + extraCandies` is greater than or equal to the maximum.
   - Store `true` in the result array if the condition is met, `false` otherwise.
3. Return the result array.

### Example Implementation (C++)
```cpp
class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        if(candies.size() == 0)
            return vector<bool>();
            
        auto mx = INT_MIN;
        for(auto x: candies)
            mx = max(mx, x);

        vector<bool> result;
        result.reserve(candies.size());

        for(auto x: candies)
            if(x + extraCandies >= mx)
                result.push_back(true);
            else 
                result.push_back(false);

        return result;
    }
};
```

```cpp
class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        int maxCandies = *max_element(candies.begin(), candies.end());
        vector<bool> result(candies.size());
        
        for (int i = 0; i < candies.size(); i++) {
            result[i] = (candies[i] + extraCandies >= maxCandies);
        }
        
        return result;
    }
};
```

### How It Works
- **Find Maximum**: Use `max_element` to find the highest number of candies any kid has.
- **Check Each Kid**: For each kid, compute `candies[i] + extraCandies` and compare it to `maxCandies`.
  - If greater than or equal, set `result[i]` to `true` (they can have the greatest number of candies).
  - Otherwise, set `result[i]` to `false`.
- **Edge Cases**:
  - All kids have the same candies: All may become `true` if `extraCandies` is sufficient.
  - Small arrays (e.g., length 2): Handled naturally by the loop.
- **Result**: The boolean array indicates which kids can have the greatest number of candies.

### Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the `candies` array, as we scan the array twice (once for max, once for comparison).
- **Space Complexity**: O(n), for the output `result` array. (Excluding the output, it’s O(1).)

### Alternative Approach
1. **Manual Max Calculation**:
   - Iterate through the array once to find the maximum instead of using `max_element`.
   - Time Complexity: O(n)
   - Space Complexity: O(n) for output
The `max_element` approach is concise and equally efficient, making it preferable for clarity.



# 9. Palindrome Number

This document describes the solution to the "Palindrome Number" problem (LeetCode #9).

## Problem Description
Given an integer `x`, return `true` if `x` is a palindrome, and `false` otherwise. An integer is a palindrome if it reads the same forward and backward.

### Example
```
Input: x = 121
Output: true
Explanation: 121 reads the same forward and backward.

Input: x = -121
Output: false
Explanation: -121 is not a palindrome as it reads 121- backward.

Input: x = 10
Output: false
Explanation: 10 reads as 01 backward, which is not the same.

Hint: Beware of overflow when you reverse the integer.
```

### Constraints
- `-2^31 <= x <= 2^31 - 1`

## Solution Approach
The problem can be solved by reversing the integer and comparing it with the original number, while handling edge cases like negative numbers and potential overflow.

### Reverse Integer Approach
1. If the number is negative, return `false` (negative numbers cannot be palindromes due to the sign).
2. Initialize a variable to store the reversed number.
3. While the input number is not zero:
   - Extract the last digit using modulo (`x % 10`).
   - Append the digit to the reversed number by multiplying the current reversed number by 10 and adding the digit.
   - Remove the last digit from the input number by integer division (`x / 10`).
4. Compare the reversed number with the original number to determine if it’s a palindrome.

### Example Implementation (C++)
```cpp
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0 || (x % 10 == 0 && x != 0)) return false;
        int rev = 0;
        while (rev < x) {
            rev = rev * 10 + x % 10;
            x /= 10;
            cout << rev<<endl;
        }
        
        return x == rev || x == rev / 10;
    }
};
``

```cpp
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        }
        
        long long reversed = 0; // Use long long to handle potential overflow
        int original = x;
        
        while (x > 0) {
            int digit = x % 10;
            reversed = reversed * 10 + digit;
            x /= 10;
        }
        
        return reversed == original;
    }
};
```

### How It Works
- **Negative Check**: Negative numbers are not palindromes due to the leading minus sign.
- **Reversal**:
  - Extract digits from the end using modulo.
  - Build the reversed number by shifting digits left (multiplying by 10) and adding the new digit.
- **Comparison**: Check if the reversed number equals the original.
- **Edge Cases**:
  - Zero: Is a palindrome (handled correctly).
  - Large numbers: Use `long long` for `reversed` to prevent overflow.
  - Single digit: Always a palindrome (e.g., 5).
- **Result**: Returns `true` if the number is a palindrome, `false` otherwise.

### Time and Space Complexity
- **Time Complexity**: O(log x), where `x` is the input number, as we process each digit (number of digits is proportional to log x base 10).
- **Space Complexity**: O(1), as we only use a constant amount of extra space (excluding the input).

### Alternative Approach
1. **Convert to String**:
   - Convert the integer to a string and check if it reads the same forward and backward.
   - Time Complexity: O(log x) for conversion, O(log x) for comparison
   - Space Complexity: O(log x) for the string
The reverse integer approach is preferred as it avoids string conversion and uses constant space.

# 268. Missing Number Solution

## Problem Description
Given an array `nums` containing `n` distinct numbers in the range `[0, n]`, return the only number in the range that is missing from the array.

### Example
```
Input: nums = [3,0,1]
Output: 2
Explanation: n = 3 since there are 3 numbers, so all numbers in range [0,3] are expected: [0,1,2,3]. The missing number is 2.
```

## Solution
Below is the C++ solution to find the missing number using the XOR operation.

```cpp
class Solution {
public:
    
    int missingNumber(vector<int>& nums) {
        int res = nums.size();
        
        //[0,1,3] => 0^1^3^0^1^2^3 => (0^0)^(1^1)^(2^2)^3 => 0^0^0^3 => 0^3 => 3
        for(int i=0; i<nums.size(); i++){
            res ^= i;
            res ^= nums[i];
        }
        return res;
    }
};

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int result = nums.size(); // Initialize with n
        
        // XOR all indices and values
        for (int i = 0; i < nums.size(); ++i) {
            result ^= i;        // XOR with index
            result ^= nums[i];  // XOR with value
        }
        
        return result;
    }
};
```

## Explanation
1. **XOR Approach**:
   - The array contains `n` numbers from the range `[0, n]`, so one number is missing.
   - Initialize `result` with `n` (the upper bound of the range).
   - Iterate through the array:
     - XOR `result` with each index `i` (representing expected numbers `0` to `n-1`).
     - XOR `result` with each value `nums[i]` (the numbers present in the array).
   - The final `result` is the missing number because:
     - XORing a number with itself cancels it out (e.g., `x ^ x = 0`).
     - The missing number will remain as it is only present in the indices (or `n`) and not in the array.
2. **Why XOR?**:
   - XOR is efficient and avoids issues with sum-based approaches (e.g., potential integer overflow for large `n`).
3. **Result**:
   - Return `result`, which is the missing number.

## Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the array, as we iterate through the array once.
- **Space Complexity**: O(1), as we only use a single variable for the result.

## Edge Cases
- Single element: `nums = [0]` (n=1, missing 1) or `nums = [1]` (missing 0).
- Missing 0: `nums = [1,2,3]` returns 0.
- Missing `n`: `nums = [0,1,2]` returns 3.
- Large array: Handles up to `n = 10^4` efficiently.
- All numbers present except one: Correctly identifies the missing number in `[0,n]`.
- 

# 41. First Missing Positive Solution

## Problem Description
Given an unsorted integer array `nums`, return the smallest missing positive integer. You must implement an algorithm that runs in O(n) time and uses O(1) auxiliary space (i.e., modify the array in-place).

### Example
```
Input: nums = [1,2,0]
Output: 3
Explanation: The numbers in the range [1,3] are [1,2], so the smallest missing positive integer is 3.

Example 2:
Input: nums = [3,4,-1,1]
Output: 2
Explanation: 1 is in the array but 2 is missing.

Example 3:
Input: nums = [7,8,9,11,12]
Output: 1
Explanation: The smallest positive integer 1 is missing.
```

## Solution
Below is the C++ solution to find the first missing positive integer by using the array indices as a hash table.

```cpp
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        vector<int> v(n+1, 0);
        for(auto& x: nums)
            if(x > 0 && x <= n)
                v[x] = x;
        
        for(int i=1 ; i <= n ; i++) 
            if(v[i] != i) 
                return i;
        
        return n+1;
    }
};

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        
        // Step 1: Ignore non-positive and numbers > n, mark them as 1
        bool containsOne = false;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == 1) {
                containsOne = true;
            } else if (nums[i] <= 0 || nums[i] > n) {
                nums[i] = 1;
            }
        }
        
        // If 1 is not present, it is the answer
        if (!containsOne) {
            return 1;
        }
        
        // Step 2: Use array indices as hash table
        // Mark presence of each number x by making nums[x-1] negative
        for (int i = 0; i < n; ++i) {
            int index = abs(nums[i]) - 1;
            nums[index] = -abs(nums[index]);
        }
        
        // Step 3: Find the first index with a positive number
        for (int i = 0; i < n; ++i) {
            if (nums[i] > 0) {
                return i + 1;
            }
        }
        
        // If all numbers from 1 to n are present, return n + 1
        return n + 1;
    }
};
```

## Explanation
1. **Problem Insight**:
   - The smallest missing positive integer must be in the range `[1, n+1]`, where `n` is the array length, because if all numbers `1` to `n` are present, the answer is `n+1`.
   - We can use the array itself as a hash table by marking the presence of numbers via their indices.
2. **Step 1: Clean the Array**:
   - Iterate through the array:
     - Check if `1` is present (`containsOne`).
     - Replace non-positive numbers (`<= 0`) or numbers greater than `n` with `1`, as they cannot be the answer or affect the range `[1, n]`.
   - If `1` is not found, return `1` as the answer.
3. **Step 2: Mark Presence**:
   - Treat the array as a hash table where index `i` corresponds to the number `i+1`.
   - For each number `x` in the array, mark the presence of `x` by making `nums[x-1]` negative (use `abs` to handle already negative values).
   - This ensures we don't lose information when numbers are repeated or modified.
4. **Step 3: Find Missing Number**:
   - Iterate through the array again.
   - The first index `i` where `nums[i]` is positive indicates that `i+1` was never marked (i.e., `i+1` is missing).
   - If no such index is found, all numbers `1` to `n` are present, so return `n+1`.
5. **In-Place Modification**:
   - The solution modifies the array to mark presence without using extra space.

## Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the array. We perform three linear passes: one to clean the array, one to mark presence, and one to find the missing number.
- **Space Complexity**: O(1), as we only use a constant amount of extra space (a boolean variable) and modify the array in-place.

## Edge Cases
- Empty array: Return 1 (not applicable due to constraints, but handled implicitly).
- Single element: `nums = [1]` returns 2; `nums = [2]` returns 1.
- No positive numbers: `nums = [0,-1,-2]` returns 1.
- All numbers from 1 to n: `nums = [1,2,3]` returns 4.
- Missing 1: `nums = [2,3,4]` returns 1.
- Large array: Handles up to `n = 5 * 10^5` efficiently.
- Duplicates: Correctly handles cases like `[1,1,1]` (returns 2).



# 287. Find the Duplicate Number
Given an array of integers nums containing n + 1 integers where each integer is in the range [1, n] inclusive.

There is only one repeated number in nums, return this repeated number.

You must solve the problem without modifying the array nums and using only constant extra space.
```
Example 1:

Input: nums = [1,3,4,2,2]
Output: 2

Example 2:
Input: nums = [3,1,3,4,2]
Output: 3

Example 3:
Input: nums = [3,3,3,3,3]
Output: 3
```


```cpp
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for(int i = 1; i < nums.size(); i++)
        {
            if((nums[i-1]^nums[i])==0)
                return nums[i];
        }
             
        return 0;
    }
};
```

# 20. Valid Parentheses Solution

## Problem Description
Given a string `s` containing only the characters `'('`, `')'`, `'{'`, `'}'`, `'['`, and `']'`, determine if the input string is valid. A string is valid if:
- Open brackets are closed by the same type of brackets.
- Open brackets are closed in the correct order.
- Every close bracket has a corresponding open bracket of the same type.

### Example
```
Input: s = "()[]{}"
Output: true
Explanation: The string is valid as all brackets are properly matched and closed in the correct order.
```

## Solution
Below is the C++ solution to check if a string of parentheses is valid using a stack.

```cpp
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        
        map<char, char> smap;
        smap[')'] = '(';
        smap[']'] = '[';
        smap['}'] = '{';    
        
        for(auto& x: s){
            switch(x)
            {
                case '(':
                case '{':
                case '[':
                    st.push(x);
                    break;
                case ')':
                case '}':
                case ']':
                    if(!st.empty() && st.top() == smap[x]){
                        st.pop();
                    }
                    else
                        return false;
            }            
        }
        
        return st.empty();
    }
};
```

## Explanation
1. **Stack-Based Approach**:
   - Use a stack to keep track of opening brackets.
   - Iterate through each character in the string:
     - If the character is an opening bracket (`'('`, `'{'`, `'['`), push it onto the stack.
     - If the character is a closing bracket (`')'`, `'}'`, `']'`):
       - Check if the stack is empty (no matching opening bracket). If so, return `false`.
       - Pop the top bracket from the stack and verify it matches the current closing bracket:
         - `')'` must match `'('`.
         - `'}'` must match `'{'`.
         - `']'` must match `'['`.
       - If they don't match, return `false`.
2. **Final Check**:
   - After processing all characters, check if the stack is empty. If not, there are unclosed opening brackets, so return `false`.
   - If the stack is empty, all brackets were properly matched, so return `true`.
3. **Result**:
   - Return whether the string is valid based on the stack operations.

## Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the string. We process each character exactly once.
- **Space Complexity**: O(n), in the worst case, where the stack stores up to `n/2` opening brackets (e.g., `"((("`).

## Edge Cases
- Empty string: Return `true` (valid).
- Single character: `s = "("` or `s = ")"` returns `false`.
- Unmatched brackets: `s = "([)"` returns `false` (incorrect order).
- All matching brackets: `s = "()[]{}"` returns `true`.
- Only closing brackets: `s = "))"` returns `false`.
- Large string: Handles up to `n = 10^4` efficiently.
- Nested brackets: `s = "{[()]}"` returns `true`.

# 242. Valid Anagram
Given two strings s and t, return true if t is an anagram of s, and false otherwise.

```
Example 1:
Input: s = "anagram", t = "nagaram"
Output: true

Example 2:
Input: s = "rat", t = "car"
Output: false
```

```cpp
class Solution {
public:
    bool isAnagram(string s, string t) {
        
        if(s.length() != t.length())
            return false;
        
        map<char, int> mS;
        map<char, int> mT;
        
        for(auto& x: s)
            mS[x]++;

        for(auto& x: t)
            mT[x]++;

        return (mS == mT);
    }
};
```

# 70. Climbing Stairs - DP
You are climbing a staircase. It takes n steps to reach the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

```
Example 1:
Input: n = 2
Output: 2
Explanation: There are two ways to climb to the top.
1. 1 step + 1 step
2. 2 steps

Example 2:
Input: n = 3
Output: 3
Explanation: There are three ways to climb to the top.
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step
```

```cpp
class Solution {
public:
    int climbStairs(int n) {
        if(n <= 2)
            return n;
        
        auto pp = 1; //prevpre
        auto p = 2; //prev
        int current = 0;
        
        for(auto s=3; s<=n; s++)
        {
            current = p + pp;
            pp = p;
            p = current;
        }
        
        return current;
    }
};
```

# 1004. Max Consecutive Ones III

Given a binary array nums and an integer k, return the maximum number of consecutive 1's in the array if you can flip at most k 0's.

```
Example 1:

Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
Output: 6
Explanation: [1,1,1,0,0,1,1,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.
Example 2:

Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
Output: 10
Explanation: [0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.
```
```cpp
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        
        int start =0, end =0, zc =0;
        
        int ans = 0;
        
        while(end < nums.size())
        {
            if(nums[end] == 0)
                zc++;
            
            if(zc <= k)
                ans = max(ans, end - start + 1);
                
            while(zc > k)
            {
                //shift window ro right
                if(nums[start] == 0)
                    zc--;
                start++;
            }
            
            end++;
        }
            
        
        return ans;
    }
};
```

# 424. Longest Repeating Character Replacement

You are given a string s and an integer k. You can choose any character of the string and change it to any other uppercase English character. You can perform this operation at most k times.

Return the length of the longest substring containing the same letter you can get after performing the above operations.
```
Example 1:
Input: s = "ABAB", k = 2
Output: 4
Explanation: Replace the two 'A's with two 'B's or vice versa.

Example 2:
Input: s = "AABABBA", k = 1
Output: 4
Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.
There may exists other ways to achieve this answer too.
```

```cpp
class Solution {
public:
    int characterReplacement(string s, int k) {
        map<char,int> mChars;
        
        int start = 0;
        int end = 0;
        int n = s.length();
        
        if( n <= k + 1)
            return n;
        
        int max_window = 1; //max number of times 'x' char appears in a string
        int ans = 0;
        
        while(end < n)
        {
            //add the characters to map and keep count
            mChars[s[end]]++;
            max_window = max(max_window, mChars[s[end]]);
            
            //if our window exceeds max occurence of same char + k
            if((end - start + 1) > max_window + k)
            {
                //move to right and minus a char from left
                mChars[s[start]]--;
                start++;    
            }
            
            ans = max(end-start+1, ans);  
            end++;
        }
            
         return ans;     
    }
};
```

# 904. Fruit Into Baskets Solution

## Problem Description
You are visiting a farm with a single row of fruit trees arranged in an array `fruits`, where `fruits[i]` represents the type of fruit on the `i`th tree. You have two baskets, and each basket can hold only one type of fruit with no limit on the amount. Starting at any tree, you can pick one fruit from each tree as you move right, but you must stop if you encounter a fruit type that cannot fit in either basket. Return the maximum number of fruits you can pick.

### Example
```
Input: fruits = [1,2,1]
Output: 3
Explanation: Start at index 0, pick all fruits [1,2,1] with two baskets (one for type 1, one for type 2). Total = 3.

Example 2:
Input: fruits = [0,1,2,2]
Output: 3
Explanation: We can pick from trees [1,2,2].
If we had started at the first tree, we would only pick from trees [0,1].

Example 3:
Input: fruits = [1,2,3,2,2]
Output: 4
Explanation: We can pick from trees [2,3,2,2].
If we had started at the first tree, we would only pick from trees [1,2].
```

## Solution
Below is the C++ solution to find the maximum number of fruits that can be picked using a sliding window approach.

```cpp
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        if(fruits.size() <= 1)
            return fruits.size();
        
        map<int,int> maxTrees;
        
        int i = 0;
        int maxNumTrees = 2;
        
        for(int j=0; j < fruits.size(); j++)
        {
            maxTrees[fruits[j]]++;
            

            while(maxTrees.size() > 2) {
                maxTrees[fruits[i]]--;
                if(maxTrees[fruits[i]] == 0)
                    maxTrees.erase(fruits[i]);
                i++;
            }
            
            maxNumTrees = max(maxNumTrees, j-i+1);
        }
        
        return maxNumTrees;
    }
};


class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        unordered_map<int, int> basket; // Tracks fruit type and count
        int maxFruits = 0;
        int left = 0;
        
        // Slide window to find max fruits with at most two types
        for (int right = 0; right < fruits.size(); ++right) {
            basket[fruits[right]]++;
            
            // If more than two fruit types, shrink window
            while (basket.size() > 2) {
                basket[fruits[left]]--;
                if (basket[fruits[left]] == 0) {
                    basket.erase(fruits[left]);
                }
                left++;
            }
            
            // Update maxFruits with current window size
            maxFruits = max(maxFruits, right - left + 1);
        }
        
        return maxFruits;
    }
};
```

## Explanation
1. **Sliding Window Approach**:
   - Use a sliding window to track a contiguous subarray of fruits with at most two distinct types.
   - Maintain a hash map (`basket`) to store the count of each fruit type in the current window.
   - Use two pointers:
     - `right`: Expands the window by adding new fruits.
     - `left`: Shrinks the window when there are more than two fruit types.
2. **Process**:
   - Iterate `right` through the array, adding each fruit `fruits[right]` to `basket`.
   - If `basket` contains more than two fruit types, shrink the window from the left:
     - Decrease the count of `fruits[left]` in `basket`.
     - If the count becomes 0, remove the fruit type from `basket`.
     - Increment `left`.
   - After each step, update `maxFruits` with the current window size (`right - left + 1`).
3. **Result**:
   - Return `maxFruits`, the maximum number of fruits that can be picked with at most two types.

## Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the `fruits` array. Each element is added to the window once (`right` moves `n` times) and removed at most once (`left` moves at most `n` times).
- **Space Complexity**: O(1), as the hash map `basket` stores at most three fruit types at any time (when shrinking occurs at size 3), which is constant.

## Edge Cases
- Empty array: Return 0 (not applicable due to constraints, but handled implicitly).
- Single fruit type: `fruits = [1,1,1]` returns the array length (e.g., 3).
- Two fruit types: `fruits = [1,2,1,2]` returns the array length (e.g., 4).
- More than two types: `fruits = [1,2,3,2,2]` returns 4 (subarray `[2,3,2,2]`).
- Large array: Handles up to `n = 10^5` efficiently.
- All different types: `fruits = [1,2,3,4]` returns 2 (e.g., `[1,2]`).
- 

# 724. Find Pivot Index
Given an array of integers nums, calculate the pivot index of this array.

The pivot index is the index where the sum of all the numbers strictly to the left of the index is equal to the sum of all the numbers strictly to the index's right.

If the index is on the left edge of the array, then the left sum is 0 because there are no elements to the left. This also applies to the right edge of the array.

Return the leftmost pivot index. If no such index exists, return -1.

```
Example 1:

Input: nums = [1,7,3,6,5,6]
Output: 3
Explanation:
The pivot index is 3.
Left sum = nums[0] + nums[1] + nums[2] = 1 + 7 + 3 = 11
Right sum = nums[4] + nums[5] = 5 + 6 = 11
Example 2:

Input: nums = [1,2,3]
Output: -1
Explanation:
There is no index that satisfies the conditions in the problem statement.
Example 3:

Input: nums = [2,1,-1]
Output: 0
Explanation:
The pivot index is 0.
Left sum = 0 (no elements to the left of index 0)
Right sum = nums[1] + nums[2] = 1 + -1 = 0
```

```cpp
class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        
        int sumL = 0, sumR = 0;
        int totalSum = 0;
        for(auto& x : nums)
            totalSum += x;
        
        int len = nums.size();
        if(len == 1)
            return 0;
        
        for(int pivot = 0; pivot < len; pivot++)
        {
            if(pivot == 0)
                sumL = 0;
            else
                sumL += nums[pivot-1];
            
            if(pivot == len -1)
                sumR = 0;
            else
                sumR = totalSum - sumL - nums[pivot];
            
            if(sumL == sumR)
                return pivot;
        }
           
        return -1;
    }
};
```

# 1480. Running Sum of 1d Array
Given an array nums. We define a running sum of an array as runningSum[i] = sum(nums[0]…nums[i]).

Return the running sum of nums.
```
Example 1:

Input: nums = [1,2,3,4]
Output: [1,3,6,10]
Explanation: Running sum is obtained as follows: [1, 1+2, 1+2+3, 1+2+3+4].
Example 2:

Input: nums = [1,1,1,1,1]
Output: [1,2,3,4,5]
Explanation: Running sum is obtained as follows: [1, 1+1, 1+1+1, 1+1+1+1, 1+1+1+1+1].
Example 3:

Input: nums = [3,1,2,10,1]
Output: [3,4,6,16,17]
```

```cpp
class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        vector<int> result;
        int runningSum = 0;
        for(auto& x: nums)
            runningSum += x,
            result.push_back(runningSum);
            
        return result;
    }
};
```

# 238. Product of Array Except Self
Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].

The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

You must write an algorithm that runs in O(n) time and without using the division operation.

```
Input: nums = [1,2,3,4]
Output: [24,12,8,6]

Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]
```

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> prefixes(nums.size());
        vector<int> suffixes(nums.size());
        
        int pproduct = 1;        
        int sproduct = 1;
        
        int lastindex = nums.size()-1;

        int j = nums.size();

        for(int i =0; i < nums.size(); i++)
        {
            j--;
            pproduct *= nums[i];
            prefixes[i] = (pproduct);   
            
            sproduct *= nums[j];
            suffixes[j] = sproduct;
        }
        
        vector<int> result;
        for(int i =0; i < nums.size(); i++) {
            int p = (i == 0) ? 1 : prefixes[i-1];
            int s = (i == lastindex) ? 1 : suffixes[i+1];
            
            result.push_back(p * s);
        }
        
        return result;
    }
};

/*
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int product = 1;
        
        int zeroCnt = count(nums.begin(), nums.end(), 0);
        if(zeroCnt > 1)
        {
            //product will be 0
            vector<int> result(nums.size(), 0);
            return result;
        }
                
        int zeroIndex = -1;
        for(int i = 0; i< nums.size(); i++) { 
            if(nums[i])
                product *= nums[i];
            else
                zeroIndex = i;
        }
        
        if(zeroCnt)
        {
            vector<int> result(nums.size(), 0);
            result[zeroIndex] = product;
            return result;
        }
        
        vector<int> result;

        for(auto& x: nums) {   
            result.push_back(product / x);
        }
        
        return result;
    }
};
*/

/*
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        //loop inside a loop
        vector<int> result;
        for(int i =0; i < nums.size(); i++) {
            int product = 1;
            for(int j = 0; j < nums.size(); j++)
            {
                if(i == j)
                    continue;
                
                product *= nums[j];
            }
            
            result.push_back(product);
        }
        
        return result;
    }
};
*/
```
