## 567. Permutation in String - Hash Table, Two Pointers, String, Sliding Window
#### https://leetcode.com/problems/permutation-in-string/description/
Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.

In other words, return true if one of s1's permutations is the substring of s2.
```py
**Example 1:**
Input: s1 = "ab", s2 = "eidbaooo"<br>
Output: true<br>
Explanation: s2 contains one permutation of s1 ("ba").<br>

**Example 2:**
Input: s1 = "ab", s2 = "eidboaoo"<br>
Output: false
```
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

## 3. Longest Substring Without Repeating Characters - Hash Table, String, Sliding Window
#### https://leetcode.com/problems/longest-substring-without-repeating-characters/description/
Given a string s, find the length of the longest substring without duplicate characters.
```py
Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.
Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.

Constraints:
0 <= s.length <= 5 * 104
s consists of English letters, digits, symbols and spaces.

Hint: Generate all possible substrings & check for each substring if it's valid and keep updating maxLen accordingly.
```
```c++
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        set<char> cs;
        
        int maxL = 0;
        int start = 0;
        
        for(int i =0; i < s.length(); i++)
        {
            char ch = s[i];
            if(cs.count(ch) == 1)
            {
                //already exists
                while(cs.count(ch) != 0)
                {
                    //erase the characters from map one by one
                    cs.erase(s[start]);
                    start++;
                }
            }
            
            cs.insert(ch);
            
            maxL = max(maxL, i - start + 1);
        }
        
        return maxL;
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

## 142. Linked List Cycle II - Hash Table, Linked List, Two Pointers
Given the head of a linked list, return the node where the cycle begins. If there is no cycle, return null.

There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. Internally, pos is used to denote the index of the node that tail's next pointer is connected to (0-indexed). It is -1 if there is no cycle. Note that pos is not passed as a parameter.

Do not modify the linked list.
```py
Example 1:

Input: head = [3,2,0,-4], pos = 1
Output: tail connects to node index 1
Explanation: There is a cycle in the linked list, where tail connects to the second node.
```
<img src="../assets/circularlinkedlist.png" width="30%">

```py
Example 2:

Input: head = [1,2], pos = 0
Output: tail connects to node index 0
Explanation: There is a cycle in the linked list, where tail connects to the first node.
```
<img src="../assets/circularlinkedlist_test2.png" width="20%">

```py
Example 3:

Input: head = [1], pos = -1
Output: no cycle
Explanation: There is no cycle in the linked list.
 
Constraints:

The number of the nodes in the list is in the range [0, 104].
-105 <= Node.val <= 105
pos is -1 or a valid index in the linked-list.
 

Follow up: Can you solve it using O(1) (i.e. constant) memory?
```

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) { 
        if(!head || !head->next)
            return nullptr;
            
        ListNode * slow = head;
        ListNode * fast = head;
        ListNode * match = head;
        
        while(slow->next && fast->next && fast->next->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            
            if(slow == fast)
            {
                while(match != slow)
                {
                    match = match->next;
                    slow = slow->next;
                }

                return match;
            }
        }
        
        return nullptr;
    }
};
```

## 205. Isomorphic Strings - Hash Table, String

## Problem Description
Given two strings `s` and `t`, determine if they are isomorphic. Two strings are isomorphic if the characters in `s` can be replaced to get `t`. All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character, but a character may map to itself.

### Example
```
Input: s = "egg", t = "add"
Output: true
Explanation: The mapping is 'e' -> 'a' and 'g' -> 'd'. Each character in s maps to a unique character in t.

Input: s = "foo", t = "bar"
Output: false
Explanation: 'f' maps to 'b', but 'o' cannot map to both 'a' and 'r'.

Input: s = "paper", t = "title"
Output: true
Explanation: The mapping is 'p' -> 't', 'a' -> 'i', 'e' -> 'l', 'r' -> 'e'.
```

### Constraints
- `1 <= s.length <= 5 * 10^4`
- `t.length == s.length`
- `s` and `t` consist of any valid ASCII characters.

```c++
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        
        if(s.length() != t.length())
            return false;
        
        map<char, char> mapEnc;
        set<char> setUsed;
        
        for(int i =0; i < t.length(); i++)
        {
            if(mapEnc.find(s[i]) != mapEnc.end())
            {
                if(mapEnc[s[i]] != t[i])
                    return false;
                
                continue;           
            }
         
            if(setUsed.count(t[i]))
            {
                return false;
            }
            
            mapEnc[s[i]] = t[i];
            setUsed.insert(t[i]);
        }
        
        return true;       
    }
};
```

## Solution Approach
To determine if two strings are isomorphic, we can use a mapping approach:
1. Ensure both strings have the same length.
2. Use two hash maps (or arrays for ASCII characters) to track mappings from `s` to `t` and `t` to `s`.
3. Iterate through both strings simultaneously:
   - For each character pair `(s[i], t[i])`, check if the current mapping is consistent.
   - If a character in `s` is already mapped to a different character in `t`, or vice versa, return `false`.
4. If all characters are processed without conflicts, return `true`.

### Example Implementation (C++)
```cpp
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s.length() != t.length()) return false;
        
        unordered_map<char, char> s_to_t;
        unordered_map<char, char> t_to_s;
        
        for (int i = 0; i < s.length(); ++i) {
            char char_s = s[i];
            char char_t = t[i];
            
            // Check mapping from s to t
            if (s_to_t.find(char_s) == s_to_t.end()) {
                s_to_t[char_s] = char_t;
            } else if (s_to_t[char_s] != char_t) {
                return false;
            }
            
            // Check mapping from t to s
            if (t_to_s.find(char_t) == t_to_s.end()) {
                t_to_s[char_t] = char_s;
            } else if (t_to_s[char_t] != char_s) {
                return false;
            }
        }
        
        return true;
    }
};
```

### How It Works
- **Length Check**: If lengths differ, the strings cannot be isomorphic.
- **Bidirectional Mapping**:
  - `s_to_t` tracks mappings from characters in `s` to `t`.
  - `t_to_s` ensures no character in `t` is mapped to multiple characters in `s`.
- **Iteration**: For each character pair, ensure the mapping is consistent in both directions.
- **Return**: If no conflicts are found, the strings are isomorphic.

### Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the strings.
- **Space Complexity**: O(k), where `k` is the number of unique characters (bounded by the ASCII character set, max 128 for standard ASCII).

### Alternative Approach
Instead of two hash maps, you can use one hash map and a set to track used characters in `t`. This reduces space complexity slightly but maintains the same time complexity.



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



## 2. Add Two Numbers - Linked List, Recursion

This document describes the solution to the "Add Two Numbers" problem (LeetCode #2).

## Problem Description
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list. You may assume the two numbers do not contain any leading zero, except the number 0 itself.

### Example
```
2 -> 4 -> 3
5 -> 6 -> 4
-----------
7 -> 0 -> 8
-----------
Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [7,0,8]
Explanation: 342 + 465 = 807.

Input: l1 = [0], l2 = [0]
Output: [0]
Explanation: 0 + 0 = 0.

Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
Output: [8,9,9,9,0,0,0,1]
Explanation: 9999999 + 9999 = 10009998.
```

### Constraints
- The number of nodes in each linked list is in the range `[1, 100]`.
- `0 <= Node.val <= 9`
- It is guaranteed that the list represents a number that does not have leading zeros.

## Solution Approach
The problem can be solved by simulating the addition process, handling carry-over digits, and constructing a new linked list for the result.

### Approach
1. Initialize a dummy head node for the result list and a pointer to build the list.
2. Use a `carry` variable to track carry-over from addition.
3. Iterate through both lists while there are digits or a carry:
   - Sum the current digits (if available) and the carry.
   - Create a new node with the units digit (`sum % 10`).
   - Update the carry (`sum / 10`).
   - Move to the next nodes in the input lists (if available).
4. Return the result list starting from the node after the dummy head.

### ListNode Structure
```cpp
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
```

### Example Implementation (C++)
```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummyHead = new ListNode(0);
        ListNode* curr = dummyHead;
        int carry = 0;
        while (l1 != NULL || l2 != NULL || carry != 0) {
            int x = l1 ? l1->val : 0;
            int y = l2 ? l2->val : 0;
            int sum = carry + x + y;
            carry = sum / 10;
            curr->next = new ListNode(sum % 10);
            curr = curr->next;
            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;
        }
        return dummyHead->next;       
    }
};
```

```cpp
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0);
        ListNode* current = dummy;
        int carry = 0;
        
        while (l1 || l2 || carry) {
            int sum = carry;
            if (l1) {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2) {
                sum += l2->val;
                l2 = l2->next;
            }
            
            current->next = new ListNode(sum % 10);
            current = current->next;
            carry = sum / 10;
        }
        
        return dummy->next;
    }
};
```

### How It Works
- **Dummy Node**: Simplifies list construction by avoiding special handling for the head.
- **Addition Loop**: Processes digits from both lists and the carry:
  - Adds values from `l1`, `l2` (if available), and `carry`.
  - Creates a new node with the units digit.
  - Updates `carry` for the next iteration.
- **Edge Cases**: Handles cases where one list is longer or a carry persists after processing all digits.
- **Result**: The list after `dummy` contains the sum in reverse order.

### Time and Space Complexity
- **Time Complexity**: O(max(N, M)), where `N` and `M` are the lengths of the input lists, as we traverse each list once.
- **Space Complexity**: O(max(N, M)), for the output list containing the result.


## 5. Longest Palindromic Substring - Two Pointers, String, Dynamic Programming

This document describes the solution to the "Longest Palindromic Substring" problem (LeetCode #5).

## Problem Description
Given a string `s`, return the longest palindromic substring in `s`. A substring is palindromic if it reads the same forward and backward.

### Example
```
Input: s = "babad"
Output: "bab"
Explanation: "aba" is also valid, but "bab" is equally long and correct.

Input: s = "cbbd"
Output: "bb"
Explanation: "bb" is the longest palindromic substring.

Input: s = "a"
Output: "a"
Explanation: A single character is a palindrome.

Hints:
-How can we reuse a previously computed palindrome to compute a larger palindrome?
-If “aba” is a palindrome, is “xabax” a palindrome? Similarly is “xabay” a palindrome?
-Complexity based hint:
If we use brute-force and check whether for every start and end position a substring is a palindrome we have O(n^2) start - end pairs and O(n) palindromic checks. Can we reduce the time for palindromic checks to O(1) by reusing some previous computation.
```

### Constraints
- `1 <= s.length <= 1000`
- `s` consists of only digits and English letters.

## Solution Approach
The problem can be solved efficiently using the "Expand Around Center" approach, which checks for palindromes by expanding around each possible center.

### Expand Around Center Approach
1. Iterate through each index `i` in the string, treating it as a potential center of a palindrome.
2. For each index, expand around:
   - The index itself (for odd-length palindromes, e.g., "aba").
   - Between the index and the next index (for even-length palindromes, e.g., "bb").
3. While expanding, check if characters on both sides are equal and stay within bounds.
4. Track the longest palindrome found by storing its start index and length.

### Example Implementation (C++)
```cpp
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    void expandFromCenter(int left, int right, string& s, vector<string>& ps) 
    {
        bool found = false;
        for(; left >= 0 && right < s.length() && s[left] == s[right]; left--, right++)
            found = true;
        
        if ( found )
        {
            int len = right - (left+1);
            ps.push_back(s.substr(left+1, len));
        }
    }
    
    string longestPalindrome(string s) {
        if(s.length() == 1)
            return s;
        
        vector<string> pstrings; //collection of all pali strings
        
        //we are going to move from left to right
        //abccbxyz -- bccb - center is in between 
        //abcdcxy -- cdc - center is on a character
        for(int i = 1; i < s.length(); i++) {
            //check if there is a pali string around s[i], s[i] at center
            int left = i-1;
            int right = i+1;
                  
            expandFromCenter(left, right, s, pstrings);
            
            //check if there is a pali string where pali string has even characters
            //s[i-1] == s[i]
            right = i;
            expandFromCenter(left, right, s, pstrings);    
        }
            
        string answer = "";
        for(auto&x : pstrings) {
            if(x.length() > answer.length())
                answer = x;
        }
        
        if(answer.length() == 0)
            answer = s[0];
        
        return answer;     
    }
};
```

```cpp
class Solution {
public:
    string longestPalindrome(string s) {
        int start = 0, maxLength = 0;
        
        for (int i = 0; i < s.length(); i++) {
            // Odd-length palindrome (center at i)
            int len1 = expandAroundCenter(s, i, i);
            // Even-length palindrome (center between i and i+1)
            int len2 = expandAroundCenter(s, i, i + 1);
            // Get the maximum length of the two
            int len = max(len1, len2);
            
            // Update if we found a longer palindrome
            if (len > maxLength) {
                maxLength = len;
                start = i - (len - 1) / 2;
            }
        }
        
        return s.substr(start, maxLength);
    }
    
private:
    int expandAroundCenter(const string& s, int left, int right) {
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            left--;
            right++;
        }
        // Return length of palindrome
        return right - left - 1;
    }
};
```

### How It Works
- **Center Expansion**:
  - For each index `i`, check for odd-length palindromes by expanding around `i`.
  - Check for even-length palindromes by expanding around the gap between `i` and `i+1`.
- **Expansion Function**: Expands while characters match and indices are valid, returning the length of the palindrome.
- **Tracking**: Update `start` and `maxLength` when a longer palindrome is found.
- **Result**: Extract the substring using the recorded `start` and `maxLength`.
- **Edge Cases**: Handles single-character strings and cases where the entire string is a palindrome.

### Time and Space Complexity
- **Time Complexity**: O(n²), where `n` is the length of the string. Each of the `n` centers may expand up to `n` characters.
- **Space Complexity**: O(1), excluding the output string, as only a constant amount of extra space is used.

### Alternative Approaches
1. **Dynamic Programming**:
   - Use a table to store whether `s[i:j]` is a palindrome.
   - Time Complexity: O(n²)
   - Space Complexity: O(n²)
2. **Manacher's Algorithm**:
   - Optimized for finding the longest palindromic substring.
   - Time Complexity: O(n)
   - Space Complexity: O(n)
The Expand Around Center approach is simpler to implement and sufficient for the given constraints.







