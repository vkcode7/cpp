```bash
# 1431. Kids With the Greatest Number of Candies [Super Easy] via Kadane
# 9. Palindrome Number [Super Easy] via reverse the number
# 268. Missing Number [Super Easy] via XORing [0^0 = 0; 0^1=1^0=1; 1^1=0]
# 41. First Missing Positive [Easy]
# 287. Find the Duplicate Number - sort and use xor between consecutive numbers in the vector [Easy]
# 20. Valid Parentheses [Easy]
# 242. Valid Anagram [Super Easy]
# 70. Climbing Stairs - DP [Easy] Step(N) = Step(N-1) + Step(N-2)
# 1004. Max Consecutive Ones III [Medium, Revisit]
# 424. Longest Repeating Character Replacement [Medium, Revisit]
# 904. Fruit Into Baskets [Medium, Revisit]
# 724. Find Pivot Index [Easy]
# 1480. Running Sum of 1d Array [Super Easy]
# 238. Product of Array Except Self [Easy]
```
```matlib
LeetCode Submissions = 14/14
BackTracking = 0/2
Binary Search = 3/3
Dynamic Programming = 11/11
Graphs = 9/10
LinkedList = 10/10
Median and Moving Avg = 5/6
Sliding Window = 20/20
Binary Trees = 15/18
Matrix = 6/6
Hash tables = 6/6

Total = 99/106
```

# 1431. Kids With the Greatest Number of Candies [Super Easy] via Kadane
https://leetcode.com/problems/kids-with-the-greatest-number-of-candies/description/

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
```

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

### Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the `candies` array, as we scan the array twice (once for max, once for comparison).
- **Space Complexity**: O(n), for the output `result` array. (Excluding the output, it’s O(1).)


# 9. Palindrome Number [Super Easy] via reverse the number
https://leetcode.com/problems/palindrome-number/description/

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

### Reverse Integer Approach / Alternative Approach is via string conversion
1. If the number is negative, return `false` (negative numbers cannot be palindromes due to the sign).
2. Reverse the number and compare

### Example Implementation (C++)

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

### Time and Space Complexity
- **Time Complexity**: O(n), where n is numnber of digits
- **Space Complexity**: O(1), as we only use a constant amount of extra space (excluding the input).


# 268. Missing Number [Super Easy] via XORing [0^0 = 0; 0^1=1^0=1; 1^1=0]
https://leetcode.com/problems/missing-number/description/

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
            res = res ^ i ^ nums[i]; //XOR with index and value
        }
        return res;
    }
};
```

## Explanation
1. **XOR Approach**:
     - XORing a number with itself cancels it out (e.g., `x ^ x = 0`).
     - The missing number will remain as it is only present in the indices (or `n`) and not in the array.
       
## Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the array, as we iterate through the array once.
- **Space Complexity**: O(1), as we only use a single variable for the result.
  

# 41. First Missing Positive [Easy]

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
```

## Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the array. We perform three linear passes: one to clean the array, one to mark presence, and one to find the missing number.
- **Space Complexity**: O(1), as we only use a constant amount of extra space (a boolean variable) and modify the array in-place.


# 287. Find the Duplicate Number - sort and use xor between consecutive numbers in the vector [Easy]
https://leetcode.com/problems/find-the-duplicate-number/description/

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

# 20. Valid Parentheses [Easy]
https://leetcode.com/problems/valid-parentheses/description/

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
        
        for(auto x: s)
        {
            if(x == '(' or x == '{' or x == '[')
                st.push(x);
            else if(x == '}' or x == ']' or x == ')')
                if(!st.empty())
                {
                    auto t = st.top();
                    auto xc = smap[x];
                    if(xc == t)
                    {
                        st.pop();
                    }
                    else
                        return false;
                }
                else
                    return false;
        }
        
        return st.empty(); //unclosed opening brackets still there
    }
};
```

## Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the string. We process each character exactly once.
- **Space Complexity**: O(n), in the worst case, where the stack stores up to `n/2` opening brackets (e.g., `"((("`).


# 242. Valid Anagram [Super Easy] - store both string chars in a map and compare it. T=O(n), S=O(1)
https://leetcode.com/problems/valid-anagram/description/

Given two strings s and t, return true if t is an anagram of s, and false otherwise.

An anagram is a word or phrase formed by rearranging the letters of another, using all the original letters exactly once.

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

# 70. Climbing Stairs - DP [Easy] TC=O(n), SC=O(1)
https://leetcode.com/problems/climbing-stairs/description/

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

# 1004. Max Consecutive Ones III [Medium, Revisit]
https://leetcode.com/problems/max-consecutive-ones-iii/

Given a binary array nums and an integer k, return the maximum number of consecutive 1's in the array if you can flip at most k 0's.

```
Example 1:
Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
Output: 6
Explanation: [1,1,1,0,0,1,1,1,1,1,1]
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

# 424. Longest Repeating Character Replacement [Medium, Revisit]

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

# 1480. Running Sum of 1d Array [Super Easy]
Given an array nums. We define a running sum of an array as running Sum[i] = sum(nums[0]…nums[i]).

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

# 238. Product of Array Except Self [Easy]
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
