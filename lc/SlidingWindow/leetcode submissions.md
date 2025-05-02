
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

https://leetcode.com/submissions/#/3
