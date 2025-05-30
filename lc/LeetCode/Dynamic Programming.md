```bash
# 509. Fibonacci Number [Super Easy]
# 70. Climbing Stairs [Easy]
# 152. Maximum Product Subarray [Easy]
# 121. Best Time to Buy and Sell Stock - Array, Dynamic Programming [Easy]
# 322. Coin Change - Dynamic Programming [Easy, Revisit]
# 53. Maximum Subarray - Array, Divide and Conquer, Dynamic Programming [Easy]
# 42. Trapping Rain Water - Two Pointers, Dynamic Programming, Stack, Monotonic Stack [Medium]
# 198. House Robber [Medium]
# 139. Word Break [Medium]
# 300. Longest Increasing Subsequence [Medium]
# 2272. Substring with Largest Variance [Medium, Revisit]
```

**Kadane's algorithm** is a dynamic programming algorithm that finds the maximum subarray sum in an array of integers. It maintains two values: global_max, which represents the maximum sum encountered so far, and local_max, which represents the maximum sum ending at the current index. As the algorithm traverses the array from left to right, it updates these values. The algorithm is efficient because it only requires O(n) time and O(1) space to store two values and does not need any additional data structures.

# 509. Fibonacci Number [Super Easy]
https://leetcode.com/problems/fibonacci-number/

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

class SolutionUsingDp {
public:
    map<int,int> mf;
    int fib(int n) {
        if(mf.find(n) != mf.end())
            return mf[n];

        int fn = n < 2 ? n : fib(n-2) + fib(n-1);
        mf[n] = fn;
        return fn;
    }
};
```

# 70. Climbing Stairs [Super Easy]
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

# 152. Maximum Product Subarray  [Easy]
https://leetcode.com/problems/maximum-product-subarray/description/

Given an integer array `nums`, find a contiguous non-empty subarray within the array that has the largest product, and return the maximum product. The array may contain positive, negative, and zero values.

### Example
```
Input: nums = [2,3,-2,4]
Output: 6
Explanation: The subarray [2,3] has the largest product 6.

Input: nums = [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
```

## Solution
Below is the C++ solution to find the maximum product subarray using a dynamic programming approach.

```cpp
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        auto curr_prod_l = 1;
        auto curr_prod_r = 1;
               
        auto n = nums.size();
        auto best = INT_MIN;
        for(int i = 0, j = n-1; i < n; i++, j--) {
            
            auto ix = nums[i];
            auto jx = nums[j];
            
            curr_prod_l = ix * curr_prod_l;
            curr_prod_r = jx * curr_prod_r;

            best = max(best, max(curr_prod_l, curr_prod_r));

            if(!ix)
                curr_prod_l = 1;

            if(!jx)
                curr_prod_r = 1;
        }
        
        return best;
    }
};


class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        
        int maxProd = nums[0]; // Tracks the overall maximum product
        int currMax = nums[0]; // Maximum product ending at current index
        int currMin = nums[0]; // Minimum product ending at current index
        
        for (int i = 1; i < nums.size(); ++i) {
            // Store currMax for use in currMin calculation
            int tempMax = currMax;
            
            // Update currMax: max of current element, product with max, product with min
            currMax = max({nums[i], currMax * nums[i], currMin * nums[i]});
            
            // Update currMin: min of current element, product with previous max, product with previous min
            currMin = min({nums[i], tempMax * nums[i], currMin * nums[i]});
            
            // Update overall maximum product
            maxProd = max(maxProd, currMax);
        }
        
        return maxProd;
    }
};
```


# 121. Best Time to Buy and Sell Stock - Array, Dynamic Programming [Easy]
https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/

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
        int maxProfit = 0;
        int buyPrice = prices[0];

        for(int i=1; i < prices.size(); i++)
        {
            int x = prices[i];
            buyPrice = min(x, buyPrice);
            maxProfit = max(maxProfit, x - buyPrice);
        }

        return maxProfit;
    }
};
```


# 322. Coin Change - Dynamic Programming [Easy, Revisit]
https://leetcode.com/problems/coin-change/description/

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


# 53. Maximum Subarray - [Easy]
https://leetcode.com/problems/maximum-subarray/

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
https://leetcode.com/problems/trapping-rain-water/

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
    int trap(vector<int>& height) {
        int n = height.size();
        vector<int> lh(n, 0);
        vector<int> rh(n, 0);

        int maxL = 0;
        int maxR = 0;

        for(int i=0, j = n-1; i < n; i++, j--)
        {
            maxL = max(maxL, height[i]);
            lh[i] = maxL - height[i];

            maxR = max(maxR, height[j]);
            rh[j] = maxR - height[j];
        }

        int sum = 0;
        for(int i=0; i< n; i++)
            sum += min(lh[i], rh[i]);

        return sum;
    }
};
```

```
Input: height
[0,1,0,2,1,0,1,3,2,1,2,1]

height on left: maxL - input
[0 0 1 0 1 2 1 0 1 2 1 2]

height on right: maxR - input
[3 2 3 1 2 3 2 0 0 1 0 0]

final height: min(left, right)
[0,1,0,2,1,0,1,3,2,1,2,1]
```

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

# 198. House Robber [Medium, Revisit]
https://leetcode.com/problems/house-robber/

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


# 139. Word Break [medium, Revisit]

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


# 300. Longest Increasing Subsequence [Medium, Revisit]

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
[10,9,2,5,3,7,101,18]
[ 1,1,1,2,2,3,  4, 4]

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


# 2272. Substring with Largest Variance

## Problem Description
Given a string `s` consisting of lowercase letters, return the largest variance of any substring. The variance of a substring is defined as the largest difference between the frequencies of any two distinct characters in that substring. If no substring contains at least two distinct characters, return 0.

### Example
```
Example 1:
Input: s = "aababbb"
Output: 3
Explanation: The substring "babbb" has 3 'b's and 2 'a's, so the variance is 3 - 2 = 1. Another substring "abbb" has 3 'b's and 1 'a', giving variance 3 - 1 = 2. The largest variance among all substrings is 3 from "aabbb" (4 'b's - 1 'a' = 3).

Example 2:
Input: s = "abcde"
Output: 0
Explanation:
No letter occurs more than once in s, so the variance of every substring is 0.
```

## Solution
Below is the C++ solution to find the largest variance in a substring using a modified Kadane's algorithm approach.

```cpp
class Solution {   //<-- THIS IS BEST AND EASIEST
public:
    int largestVariance(string s) {
        map<char, int> mFreq;

        for (char ch : s) {
            mFreq[ch]++;
        }
        int globalMax = 0;
        
        for (auto [major, major_count]: mFreq) {
            for (auto [minor, minor_count]: mFreq) {
                // major and minor cannot be the same, and both must appear in s.
                if (major == minor)
                    continue;
                
                // Find the maximum variance of major - minor.        
                int majorCountTracker = 0;
                int minorCountTracker = 0;
                
                for (char ch : s) {    
                    if (ch == major) {
                        majorCountTracker++;
                    }
                    if (ch == minor) {
                        minorCountTracker++;
                        minor_count--; // The remaining minor in the rest of s.
                    }
                    
                    // Only update the variance (local_max) if there is at least one minor.
                    if (minorCountTracker > 0) //basically both major and minor found
                        globalMax = max(globalMax, majorCountTracker - minorCountTracker);
                    
                    // We can discard the previous string if there is at least one remaining minor
                    // restart from current position in s 
                    if (majorCountTracker < minorCountTracker && minor_count > 0) {
                        majorCountTracker = minorCountTracker = 0;
                    }
                }
            }
        }
        
        return globalMax;
    }
};
```
### Complexity Analysis for above solution [Medium, Revisit]

Let n be the length of the input string s and k be the number of distinct characters in s.

Time complexity: O(n⋅k^2)

Kadane's algorithm requires O(n) time to traverse s. For each pair of alphabets (major, minor), we need to traverse s once. In the worst-case scenario, s contains k=26 different letters, so there are k⋅(k−1) possible pairs of letters.
Space complexity: O(1)

In the Kadane's algorithm, we only need to update a few variables, major_count, minor_count, rest_minor and global_max, which require O(1) space.

```cpp
class Solution {
public:

    int largestVariance(string s) {
        int result = 0;
        for (char highFreqChar = 'a'; highFreqChar <= 'z'; ++highFreqChar) {
            for (char lowFreqChar = 'a'; lowFreqChar <= 'z'; ++lowFreqChar) {
                if (highFreqChar == lowFreqChar) continue;
                
                int highFreq = 0;
                int lowFreq = 0;
                bool lowFreqAbandoned = false;
                
                for (const char& ch : s) {
                    if (ch == highFreqChar) ++highFreq;
                    if (ch == lowFreqChar) ++lowFreq;
                    
                    if (lowFreq > 0) {
                        result = max(result, highFreq - lowFreq);
                    } else {
                        // Edge case: there are no `lowFreqChar` in current interval.
                        // In case if we re-started Kadane algo calculation - 
                        // we can "extend" current interval with 1 previously abandoned 'lowFreqChar'
                        if (lowFreqAbandoned) {
                            result = max(result, highFreq - 1);
                        }
                    } 
                    
                    if (lowFreq > highFreq) {
                        // Kadane's algo calculation re-start: abandon previous chars and their freqs.
                        // Important: the last abandoned char is the `lowFreqChar` - this can be used on further iterations.
                        lowFreq = 0;
                        highFreq = 0;
                        lowFreqAbandoned = true;
                    }
                }
            }
        }
        return result;
    }

    int largestVariance2(string s) {
        int ans = 0;
        set<char> alphabet(s.begin(), s.end());
        for (char c1: alphabet) {
            for (char c2: alphabet) {
                if (c1 == c2) {
                    continue;
                }
                                
                int v1 = 0; //c1 is high freq
                int v2 = 0; //c2 is low freq
                int now = 0;
                bool flag = false;
                for (char &c : s) {
                    if (c == c2) flag = true;
                    v1 += c == c1;
                    v2 += c == c2;
                    if (v2 > v1) { //low freq > high freq so reset
                        v1 = v2 = 0;
                    }
                    
                    if (v2 > 0) 
                        now = max(now, v1-v2);
                }
                
                if (v1 > 0 && v2 == 0) {
                    if (v1 == s.length()) return 0;
                    if (flag) {
                        v2 = 1;
                        //edge case such as "abbb"
                        // where c1='b', and c2='a', v2 will be reset to 0 in that case
                        //after 1st character is processed as v1 will be 0 
                        //triggering(v2 > v1)
                        now = max(now, v1-v2);
                    }
                }
                
                ans = max(ans, now);            
            }
        }
        return ans;
    }
};
```

## Explanation
1. **Problem Insight**:
   - The variance is the maximum difference between the counts of any two characters in a substring.
   - We need to consider all possible pairs of characters (c1, c2) and find the substring where `count(c1) - count(c2)` is maximized, provided both characters appear.
2. **Frequency Precomputation**:
   - Compute the frequency of each character in `s` to skip pairs where either character is absent.
3. **Pairwise Character Comparison**:
   - Iterate over all pairs of characters `(c1, c2)` where `c1` is the major character (higher count) and `c2` is the minor character (lower count).
   - Skip pairs where `c1 == c2` or either character has zero frequency.
4. **Modified Kadane’s Algorithm**:
   - For each pair `(c1, c2)`, process the string twice (forward and reverse) to handle cases where the optimal substring depends on the order of characters.
   - Maintain two counters:
     - `count1`: Number of `c1` in the current substring.
     - `count2`: Number of `c2` in the current substring.
   - For each character in the string:
     - Increment `count1` if the character is `c1`.
     - Increment `count2` if the character is `c2`.
     - If `count2 > 0`, compute the variance as `count1 - count2` and update `maxVariance`.
     - If `count1 > 0` but `count2 == 0`, reset both counts to 0 (like Kadane’s algorithm) to start a new substring, as we need at least one `c2` for a valid variance.
5. **Result**:
   - Return `maxVariance`, the largest variance found across all substrings and character pairs.

## Time and Space Complexity
- **Time Complexity**: O(n * 26 * 26 * 2), where `n` is the length of the string. We iterate over all pairs of characters (26 * 26), process the string twice (forward and reverse) for each pair, and each string traversal takes O(n). Simplifies to O(n) since 26 * 26 * 2 is constant.
- **Space Complexity**: O(1), as we use a fixed-size frequency array (size 26) and a constant amount of extra space for variables. The reversed string in the second pass uses O(n) temporarily, but this can be considered part of the processing.

## Edge Cases
- Single character: `s = "a"` returns 0 (no substring with two distinct characters).
- No valid substring: `s = "aaaa"` returns 0 (all characters identical).
- All distinct characters: `s = "abc"` returns 1 (e.g., substring "ab" has 1 'a' - 0 'b' = 1).
- Repeated characters: `s = "aababbb"` handles correctly (returns 3 for "aabbb").
- Large string: Efficiently processes up to `n = 10^4` with constant factors.
- All possible character pairs: Tests all relevant pairs to find the maximum variance.
