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













