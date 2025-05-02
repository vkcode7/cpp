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

## 200. Number of Islands - Array, Depth-First Search, Breadth-First Search, Union Find, Matrix
#### https://leetcode.com/problems/number-of-islands/description/
Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.
```py
Example 1:

Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1
Example 2:

Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3
 
Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 300
grid[i][j] is '0' or '1'.
```
```c++
class Solution {
public:
    void markIsland(vector<vector<char>>& grid, int row, int col, int rows, int cols)
    {

        if(row < 0 || col < 0 || row == rows || col == cols) return;
        
        if(grid[row][col]=='1') {
            grid[row][col] = '2';
            markIsland(grid, row-1, col, rows, cols);
            markIsland(grid, row+1, col, rows, cols);
            markIsland(grid, row, col-1, rows, cols);
            markIsland(grid, row, col+1, rows, cols);
        }
        
        return;     
    }
    
    int numIslands(vector<vector<char>>& grid) {
        
        int islands = 0;
        for(int row = 0; row < grid.size(); row++)
        {
            int cols = grid[0].size();
            for(int col = 0; col < cols; col++)
            {
                if(grid[row][col] == '1') {
                    islands++;
                    markIsland(grid, row, col, grid.size(), cols);
                }
            }
            
        }
        
        return islands;
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

## 112. Path Sum - Tree, Depth-First Search, Breadth-First Search, Binary Tree
#### https://leetcode.com/problems/path-sum/description/
Given the root of a binary tree and an integer targetSum, return true if the tree has a root-to-leaf path such that adding up all the values along the path equals targetSum.

A leaf is a node with no children.
```py
Example 1:

Input: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
Output: true
Explanation: The root-to-leaf path with the target sum is shown.
```
<img src="../assets/pathsum1.jpg" width="40%">

```py
Example 2:

Input: root = [1,2,3], targetSum = 5
Output: false
Explanation: There are two root-to-leaf paths in the tree:
(1 --> 2): The sum is 3.
(1 --> 3): The sum is 4.
There is no root-to-leaf path with sum = 5.
```
<img src="../assets/pathsum2.jpg" width="20%">

```py
Example 3:

Input: root = [], targetSum = 0
Output: false
Explanation: Since the tree is empty, there are no root-to-leaf paths.
 
Constraints:

The number of nodes in the tree is in the range [0, 5000].
-1000 <= Node.val <= 1000
-1000 <= targetSum <= 1000
```
```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:    
    bool hasPathSum(TreeNode* root, int targetSum) {        
        if(!root)
            return false;
        
        targetSum -= root->val;
        
        if(!root->left && !root->right) 
            return (targetSum ==0);
        
        return hasPathSum(root->left, targetSum) || hasPathSum(root->right, targetSum);
    }
};
```

## 107. Binary Tree Level Order Traversal II - Tree, Breadth-First Search, Binary Tree
#### https://leetcode.com/problems/binary-tree-level-order-traversal-ii/description/
Given the root of a binary tree, return the bottom-up level order traversal of its nodes' values. (i.e., from left to right, level by level from leaf to root).

```py
Example 1:

Input: root = [3,9,20,null,null,15,7]
Output: [[15,7],[9,20],[3]]
```
<img src="../assets/tree1.jpg" width="20%">

```py
Example 2:

Input: root = [1]
Output: [[1]]
Example 3:

Input: root = []
Output: []
 
Constraints:

The number of nodes in the tree is in the range [0, 2000].
-1000 <= Node.val <= 1000
```
```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    
    int getTreeHeight(TreeNode *node) {
        if(!node)
            return 0;
        
        int leftH = getTreeHeight(node->left);
        int rightH = getTreeHeight(node->right);
 
        return max(leftH, rightH) + 1;       
    }
    
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> ans;
        
        if(!root)
            return ans;
        
        int levels = getTreeHeight(root);
        
        queue<TreeNode*> q;
        
        q.push(root);
               
        ans.resize(levels);
        int cur_index = levels - 1;
        
        while(q.size()>0)
        {
            int qSize = q.size(); //gives num of nodes at same level

            vector<int> val(qSize, 0);

            //iterate through all nodes and add their kids
            for(int i = 0; i < qSize; i++) 
            {
                TreeNode * node = q.front();
                val[i] = node->val;

                if(node->left)
                    q.push(node->left);

                if(node->right)
                    q.push(node->right);

                //pop the node just processed
                q.pop(); //removes the node from Q
            }

            ans[cur_index]= val; 
            cur_index--;
        }
        
        return ans;
    }
};
```

## 589. N-ary Tree Preorder Traversal - Stack, Tree, Depth-First Search
#### https://leetcode.com/problems/n-ary-tree-preorder-traversal/description/
Given the root of an n-ary tree, return the preorder traversal of its nodes' values.

Nary-Tree input serialization is represented in their level order traversal. Each group of children is separated by the null value (See examples)
```py
Example 1:

Input: root = [1,null,3,2,4,null,5,6]
Output: [1,3,5,6,2,4]
```
<img src="../assets/narytreeexample.png" width="40%">

```py
Example 2:

Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
Output: [1,2,3,6,7,11,14,4,8,12,5,9,13,10]
 
Constraints:

The number of nodes in the tree is in the range [0, 104].
0 <= Node.val <= 104
The height of the n-ary tree is less than or equal to 1000.
 
Follow up: Recursive solution is trivial, could you do it iteratively?
```
<img src="../assets/sample_4_964.png" width="40%">

```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    
    void Traverse(Node *node, vector<int>& vOut) {
        if(node == nullptr)
            return;
        
        for(auto& n : node->children) {
            if(n) {
                vOut.push_back(n->val);
                Traverse(n, vOut);  
            }
        }
    }
    
    vector<int> preorder(Node* root) {
        vector<int> vOut;
        if(root) {
            vOut.push_back(root->val);
            Traverse(root, vOut);
        }  
        
        return vOut;
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


## 217. Contains Duplicate - Array, Hash Table, Sorting

This document describes the solution to the "Contains Duplicate" problem from LeetCode.

## Problem Description
Given an integer array `nums`, return `true` if any value appears at least twice in the array, and return `false` if every element is distinct.

### Example
```
Input: nums = [1,2,3,1]
Output: true
Explanation: The element 1 appears twice.

Input: nums = [1,2,3,4]
Output: false
Explanation: All elements are distinct.

Input: nums = [1,1,1,3,3,4,3,2,4,2]
Output: true
Explanation: Multiple elements (1, 2, 3, 4) appear more than once.
```

### Constraints
- `1 <= nums.length <= 10^5`
- `-10^9 <= nums[i] <= 10^9`

```c++
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
    sort(nums.begin(),nums.end());
        int i=0;
        while(i<nums.size()-1){
            if((nums[i]^nums[i+1])==0){
                return true;
                break;
            }
            else{
                i++;
            }
        }
        return false;
    }
};
```

## Solution Approach
The most efficient way to check for duplicates is to use a hash set to track seen elements.

### Hash Set Approach
1. Create an empty hash set to store encountered numbers.
2. Iterate through the array:
   - If the current number is already in the set, return `true` (duplicate found).
   - Otherwise, add the number to the set.
3. If the loop completes without finding a duplicate, return `false`.

### Example Implementation (C++)
```cpp
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> seen;
        for (int num : nums) {
            if (seen.count(num) > 0) {
                return true;
            }
            seen.insert(num);
        }
        return false;
    }
};
```

### How It Works
- **Hash Set**: The `unordered_set` provides O(1) average-case time complexity for lookups and insertions.
- **Iteration**: For each element, check if it exists in the set. If it does, a duplicate is found. If not, add it to the set.
- **Edge Case**: The array is guaranteed to have at least one element, so no additional checks are needed for empty arrays.

### Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the array, as we traverse the array once.
- **Space Complexity**: O(n), as the hash set may store up to `n` elements in the worst case (no duplicates).

### Alternative Approaches
1. **Sorting**:
   - Sort the array and check adjacent elements for equality.
   - Time Complexity: O(n log n)
   - Space Complexity: O(1) (if sorting in-place)
2. **Brute Force**:
   - Compare each element with every other element.
   - Time Complexity: O(n²)
   - Space Complexity: O(1)
The hash set approach is preferred due to its optimal time complexity.












