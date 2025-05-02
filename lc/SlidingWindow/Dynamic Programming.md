## 509. Fibonacci Number
The Fibonacci numbers, commonly denoted F(n) form a sequence, called the Fibonacci sequence, such that each number is the sum of the two preceding ones, starting from 0 and 1. That is,

F(0) = 0, F(1) = 1
F(n) = F(n - 1) + F(n - 2), for n > 1.
Given n, calculate F(n).
```cpp
class Solution {
public:
    int fib(int n) {
        return n < 2 ? n : fib(n-1) + fib(n-2);
    }
};
```

## 70. Climbing Stairs
https://leetcode.com/problems/climbing-stairs/

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

## 121. Best Time to Buy and Sell Stock - Array, Dynamic Programming
#### https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/
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


## 322. Coin Change - Array, Dynamic Programming, Breadth-First Search
#### https://leetcode.com/problems/coin-change/description/
You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.

Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

You may assume that you have an infinite number of each kind of coin.
```py
Example 1:

Input: coins = [1,2,5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1
Example 2:

Input: coins = [2], amount = 3
Output: -1
Example 3:

Input: coins = [1], amount = 0
Output: 0
 
Constraints:

1 <= coins.length <= 12
1 <= coins[i] <= 231 - 1
0 <= amount <= 104
```
```c++
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        //let there are smaller amounts => 0 to amount
        //we will solve for coins needed for each of these amounts
        //and use the previous smaller amounts in next ones
        vector<int> dp(amount+1, amount+1); //0...amount so need amount+1 slots, initialize to amount+1 which is absurdly large
        //dp tells you how many coins are needed for each 0,1,2,3,4...,amount
        
        dp[0] = 0; //0 coins needed for 0 cents
        
        //for each amount
        for(int amt=1; amt < amount+1; amt++)
        {
            //finding min coins needed for amt value
            for(auto& coin: coins)
            {
                if(amt >= coin) //amt should be greater than coin
                {
                    dp[amt] = min(dp[amt], 1 /*coin*/ + dp[amt-coin]); // 1 coin + value reminaing which is (amt - coin)
                }
            }    
        }
        
        //if dp[amount] = amount+1 => we couldnt find a way to make it
        return dp[amount] > amount ? -1 : dp[amount];   
    }
};
```


## 53. Maximum Subarray - Array, Divide and Conquer, Dynamic Programming

## Problem Description
Given an integer array `nums`, find the subarray (containing at least one number) which has the largest sum and return its sum.

### Example
```
Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: The subarray [4,-1,2,1] has the largest sum 6.

Input: nums = [1]
Output: 1
Explanation: The subarray [1] has the largest sum 1.

Input: nums = [5,-3,5]
Output: 7
Explanation: The subarray [5,-3,5] has the largest sum 7.
```

### Constraints
- `1 <= nums.length <= 10^5`
- `-10^4 <= nums[i] <= 10^4`

```c++
class Solution {
public:
	int maxSubArray(vector<int>& nums) {
		int curMax = 0, maxTillNow = INT_MIN;
		for (auto& x : nums) {
			curMax = max(x, curMax + x);
			maxTillNow = max(maxTillNow, curMax);
		}

		return maxTillNow;
	}
};
```

## Solution Approach
The problem can be solved efficiently using Kadane's Algorithm, which iterates through the array while maintaining the maximum sum subarray ending at each position.

### Kadane's Algorithm
1. Initialize two variables:
   - `max_so_far`: Tracks the maximum sum found.
   - `current_max`: Tracks the maximum sum of the subarray ending at the current index.
2. Iterate through the array:
   - For each element, update `current_max` as the maximum of the current element alone or the current element plus `current_max`.
   - Update `max_so_far` if `current_max` is greater.
3. Return `max_so_far`.

### Example Implementation (C++)
```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int max_so_far = nums[0];
        int current_max = nums[0];
        
        for (int i = 1; i < nums.size(); i++) {
            current_max = max(nums[i], current_max + nums[i]);
            max_so_far = max(max_so_far, current_max);
        }
        
        return max_so_far;
    }
};
```

### How It Works
- **Initialization**: Start with the first element as both `max_so_far` and `current_max`.
- **Iteration**: For each element:
  - Decide whether to start a new subarray at the current element (`nums[i]`) or extend the existing subarray (`current_max + nums[i]`).
  - Update `max_so_far` if the new `current_max` is larger.
- **Edge Case**: Since the array has at least one element, the algorithm handles single-element arrays naturally.

### Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the array, as we traverse the array once.
- **Space Complexity**: O(1), as we only use two variables regardless of input size.

### Alternative Approach
A divide-and-conquer approach can also solve this problem by splitting the array into two halves, computing the maximum subarray sum for each half, and considering subarrays that cross the midpoint. However, this has a time complexity of O(n log n) and is less efficient than Kadane's Algorithm.



# 42. Trapping Rain Water - Two Pointers, Dynamic Programming, Stack, Monotonic Stack

This document describes the solution to the "Trapping Rain Water" problem (LeetCode #42).

## Problem Description
Given `n` non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining. The elevation map is represented by an array `height` where `height[i]` is the height of the bar at index `i`.

### Example
```
Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: Water is trapped at indices 2, 4, 5, 6, 9, and 10, totaling 6 units.

Input: height = [4,2,0,3,2,5]
Output: 9
Explanation: Water is trapped at indices 1, 2, 3, and 4, totaling 9 units.
```
<img src="../assets/rainwatertrap.png" width="30%">

### Constraints
- `n == height.length`
- `1 <= n <= 2 * 10^4`
- `0 <= height[i] <= 10^5`

## Solution Approach
The problem can be solved efficiently using a two-pointer technique to calculate the water trapped at each index by determining the minimum of the maximum heights on both sides.

### Two-Pointer Approach
1. Initialize two pointers: `left` at the start (0) and `right` at the end (`n-1`).
2. Maintain two variables: `leftMax` (maximum height on the left) and `rightMax` (maximum height on the right).
3. While `left < right`:
   - If `height[left] < height[right]`:
     - Update `leftMax` with `max(leftMax, height[left])`.
     - Add trapped water at `left` as `leftMax - height[left]`.
     - Move `left` right.
   - Else:
     - Update `rightMax` with `max(rightMax, height[right])`.
     - Add trapped water at `right` as `rightMax - height[right]`.
     - Move `right` left.
4. Return the total water trapped.

### Example Implementation (C++)
```cpp
class Solution {
public:
    int trap(vector<int>& height)
    {
        if(height.empty())
            return 0;
        int ans = 0;
        int size = height.size();
        vector<int> left_max(size), right_max(size);
        
        //[0,1,0,2,1,0,1,3,2,1,2,1]
        left_max[0] = height[0];
        right_max[size-1] = height[size-1];
        cout << right_max[size-1]<<endl;
        
        for (int i = 1; i < size; i++) {
            left_max[i] = max(height[i], left_max[i - 1]);
            right_max[size - (i+1)] = max(right_max[size-i], height[size - (i+1)]);
        }
        
        for (int i = 0; i < size; i++) {
            ans += min(left_max[i], right_max[i]) - height[i];
        }
        
        return ans;
    }
};
```


# 198. House Robber Solution

## Problem Description
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, represented by a non-negative integer array `nums`. The only constraint is that you cannot rob two adjacent houses. Return the maximum amount of money you can rob without alerting the police.

### Example
```
Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3). Total amount = 1 + 3 = 4.
```

## Solution
Below is the C++ solution to find the maximum amount of money that can be robbed using dynamic programming.

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 1)
            return nums[0];
        
        vector<int> dp(n, 0);
        dp[0] = nums[0];
        dp[1] = max(dp[0], nums[1]);
        for(int k = 2; k < n; k++) {
            dp[k] = max(dp[k-2] + nums[k], dp[k-1]);
        }
        
        return dp[n-1];
    }
};

class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        if (nums.size() == 1) {
            return nums[0];
        }
        
        // Use two variables to store the max money up to the previous houses
        int prev2 = 0; // Max money up to i-2
        int prev1 = nums[0]; // Max money up to i-1
        
        for (int i = 1; i < nums.size(); ++i) {
            // At house i, either rob it (add nums[i] to prev2) or skip it (keep prev1)
            int current = max(prev1, prev2 + nums[i]);
            prev2 = prev1;
            prev1 = current;
        }
        
        return prev1;
    }
};
```

## Explanation
1. **Edge Cases**:
   - If the array is empty, return 0.
   - If the array has one house, return its value (`nums[0]`).
2. **Dynamic Programming (Space-Optimized)**:
   - Instead of using an array to store the maximum money for each house, use two variables:
     - `prev1`: Maximum money up to the previous house (i-1).
     - `prev2`: Maximum money up to the house before that (i-2).
   - For each house `i`:
     - Decide whether to rob it (add `nums[i]` to `prev2`) or skip it (keep `prev1`).
     - Update `current` as the maximum of these two choices.
     - Shift variables: `prev2` becomes `prev1`, and `prev1` becomes `current`.
3. **Return**: The value of `prev1` after the loop, which represents the maximum money that can be robbed.

## Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the array, as we process each house once.
- **Space Complexity**: O(1), as we only use two variables regardless of input size.

## Edge Cases
- Empty array: Return 0.
- Single house: Return its value.
- Two houses: Return the maximum of the two values.
- All houses with zero value: Return 0.
- Large array with varying values: Efficiently computes the maximum using the iterative approach.


# 139. Word Break Solution

## Problem Description
Given a string `s` and a dictionary of strings `wordDict`, return `true` if `s` can be segmented into a space-separated sequence of one or more dictionary words. The same word in the dictionary may be reused multiple times in the segmentation.

### Example
```
Example 1:
Input: s = "leetcode", wordDict = ["leet","code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".

Example 2:
Input: s = "applepenapple", wordDict = ["apple","pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
Note that you are allowed to reuse a dictionary word.

Example 3:
Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: false
```

## Solution
Below is the C++ solution to determine if a string can be segmented into words from a dictionary using dynamic programming.

```cpp
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        //s = "catsandog";
        //wordDict = {"cats","dog","sand","and","cat"};
        //dp[i] indicates whehter substring of length i can be segmented.
        vector<bool> dp(s.size()+1, false);
        
         //assume empty string is always in the wordDict
        dp[0] = true;
        
        // we mark as true every index that we managed to segment so far
        for (int i = 1; i <= s.length(); i++) {
            for (int j = 0; j < i; j++) {
                if(!dp[j])
                    continue;
                
                cout << "j is "<<j << " substr is ";
                string word = s.substr(j, i-j);
                cout << word << endl;
                if (find(wordDict.begin(), wordDict.end(), word) != wordDict.end())                           {
                    cout << "setting dp["<<i<<"] as true"<<endl;
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp.back();
    }
};

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        // Create a set for O(1) lookup
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        
        // dp[i] represents whether s[0:i] can be segmented
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true; // Empty string is valid
        
        // Check each prefix of s
        for (int i = 1; i <= s.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                // If s[0:j] is valid and s[j:i] is in wordDict
                if (dp[j] && wordSet.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }
        
        return dp[s.size()];
    }
};
```

## Explanation
1. **Dynamic Programming Setup**:
   - Create a set (`wordSet`) from `wordDict` for O(1) lookup of dictionary words.
   - Use a boolean DP array `dp` where `dp[i]` indicates whether the substring `s[0:i]` can be segmented into words from `wordDict`.
   - Initialize `dp[0] = true` (empty string is valid).
2. **DP Transition**:
   - For each position `i` (1 to `s.size()`), consider all possible prefixes ending at `j` (0 to `i-1`):
     - If `dp[j] = true` (substring `s[0:j]` is valid) and the substring `s[j:i]` is in `wordSet`, set `dp[i] = true`.
     - Break the inner loop once `dp[i] = true` to optimize.
3. **Result**:
   - Return `dp[s.size()]`, which indicates whether the entire string can be segmented.

## Time and Space Complexity
- **Time Complexity**: O(n²), where `n` is the length of the string. We iterate over each position `i` and check all previous positions `j`. String substring creation and lookup in the set are O(n) and O(1) on average, respectively, but the dominant factor is the nested loops.
- **Space Complexity**: O(n) for the `dp` array, plus O(m) for the `wordSet`, where `m` is the total length of words in `wordDict`. Overall, O(n + m).

## Edge Cases
- Empty string: Return `true` (handled by `dp[0] = true`).
- Empty dictionary: Return `false` unless `s` is empty.
- String not segmentable: `s = "catsandog"`, `wordDict = ["cats","dog","sand","and","cat"]` returns `false`.
- Reusable words: `s = "aaaa"`, `wordDict = ["a"]` returns `true`.
- Long string with valid segmentation: Efficiently handles constraints (`s.length <= 300`).


# 300. Longest Increasing Subsequence Solution

## Problem Description
Given an integer array `nums`, return the length of the longest strictly increasing subsequence. A subsequence is a sequence that can be derived from an array by deleting some or no elements without changing the order of the remaining elements.

### Example
```
Example 1:
Input: nums = [10,9,2,5,3,7,101,18]
Output: 4
Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.

Example 2:
Input: nums = [0,1,0,3,2,3]
Output: 4

Example 3:
Input: nums = [7,7,7,7,7,7,7]
Output: 1
```

## Solution
Below is the C++ solution to find the length of the longest increasing subsequence using dynamic programming.

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> T(nums.size()+1, 1); //initialize to 1
        
        for(int i=1; i < nums.size(); i++)
        {
            int j = 0;
            while(j < i)
            {
                if(nums[j] < nums[i])
                {
                    T[i] = max(T[i], T[j]+1);
                }
                
                ++j;   
            }            
        }
        
        int maxT = 1;
        for(auto& t : T)
            maxT = max(maxT, t);
        
        return maxT;
    }
};

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        
        // dp[i] represents the length of the LIS ending at index i
        vector<int> dp(nums.size(), 1);
        int maxLength = 1;
        
        // Compute LIS for each index
        for (int i = 1; i < nums.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            maxLength = max(maxLength, dp[i]);
        }
        
        return maxLength;
    }
};
```

## Explanation
1. **Edge Case**:
   - If the array is empty, return 0.
2. **Dynamic Programming Setup**:
   - Create a DP array `dp` where `dp[i]` represents the length of the longest increasing subsequence (LIS) that ends at index `i`.
   - Initialize `dp[i] = 1` for all `i`, as each element by itself is an LIS of length 1.
   - Initialize `maxLength = 1` to track the overall longest LIS.
3. **DP Transition**:
   - For each index `i` (1 to `nums.size()-1`):
     - Check all previous indices `j` (0 to `i-1`).
     - If `nums[i] > nums[j]`, the element at `i` can extend the LIS ending at `j`.
     - Update `dp[i] = max(dp[i], dp[j] + 1)` to consider the longest subsequence ending at `j` plus the current element.
   - Update `maxLength` to track the maximum `dp[i]` seen so far.
4. **Result**:
   - Return `maxLength`, the length of the longest increasing subsequence.

## Time and Space Complexity
- **Time Complexity**: O(n²), where `n` is the length of the array. We have a nested loop where the outer loop runs `n` times and the inner loop runs up to `i` times for each `i`.
- **Space Complexity**: O(n), for the `dp` array.

## Edge Cases
- Empty array: Return 0.
- Single element: Return 1.
- All elements identical: Return 1 (e.g., `[1,1,1]`).
- Strictly decreasing array: Return 1 (e.g., `[5,4,3,2,1]`).
- Strictly increasing array: Return `n` (e.g., `[1,2,3,4]`).
- Large array: Handles up to `n = 2500` within constraints.

