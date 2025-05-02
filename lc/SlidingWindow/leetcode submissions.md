
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
