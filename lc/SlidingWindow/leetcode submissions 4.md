


# 560. Subarray Sum Equals K - Hash table

This document describes the solution to the "Subarray Sum Equals K" problem (LeetCode #560).

## Problem Description
Given an array of integers `nums` and an integer `k`, return the total number of continuous subarrays whose sum equals `k`.

### Example
```
Input: nums = [1,1,1], k = 2
Output: 2
Explanation: Subarrays [1,1] at indices [0,1] and [1,1] at indices [1,2] have sum 2.

Input: nums = [1,2,3], k = 3
Output: 2
Explanation: Subarrays [1,2] and [3] have sum 3.

Input: nums = [1,-1,0], k = 0
Output: 3
Explanation: Subarrays [1,-1], [1,-1,0], and [0] have sum 0.
```

### Constraints
- `1 <= nums.length <= 2 * 10^4`
- `-1000 <= nums[i] <= 1000`
- `-10^7 <= k <= 10^7`

## Solution Approach
The problem can be solved efficiently using a prefix sum technique combined with a hash map to track cumulative sums and count subarrays with sum `k`.

### Prefix Sum with Hash Map Approach
1. Initialize a hash map to store the frequency of prefix sums, with an initial entry of `{0: 1}` to handle subarrays starting from index 0.
2. Maintain a running sum (`prefixSum`) as you iterate through the array.
3. For each index:
   - Add the current element to `prefixSum`.
   - Check if `prefixSum - k` exists in the hash map. If it does, add its frequency to the result (each occurrence represents a subarray with sum `k`).
   - Increment the frequency of the current `prefixSum` in the hash map.
4. Return the total count of valid subarrays.

### Example Implementation (C++)
```cpp
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int result = 0;
        int sum = 0; 
        unordered_map<int, int> values; 
        values[0]++; //so sum - k == 0 is found in map
        
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i]; 
            if (values.find(sum - k) != values.end()){
                result += values[sum - k];
            } 
            values[sum]++;
        }

        return result;
    }
};
```

```cpp
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<long long, int> prefixSums;
        prefixSums[0] = 1; // For subarrays starting from index 0
        long long prefixSum = 0;
        int count = 0;
        
        for (int num : nums) {
            prefixSum += num;
            // Check if there’s a prefix sum that makes prefixSum - k
            if (prefixSums.find(prefixSum - k) != prefixSums.end()) {
                count += prefixSums[prefixSum - k];
            }
            // Update frequency of current prefix sum
            prefixSums[prefixSum]++;
        }
        
        return count;
    }
};
```

### How It Works
- **Prefix Sum**:
  - Compute the cumulative sum up to each index (`prefixSum`).
  - A subarray from index `i` to `j` has sum `k` if `prefixSum[j] - prefixSum[i-1] == k`.
- **Hash Map**:
  - Store the frequency of each `prefixSum` encountered.
  - For each `prefixSum`, check if `prefixSum - k` exists in the map. Its frequency indicates the number of subarrays ending at the current index with sum `k`.
- **Initialization**:
  - `prefixSums[0] = 1` accounts for cases where the entire subarray from index 0 sums to `k`.
- **Edge Cases**:
  - Single element: If `nums[0] == k`, counted via `prefixSums[0]`.
  - Negative numbers: Handled by `prefixSum` and hash map.
  - `k = 0`: Counts subarrays with sum 0 (e.g., [1,-1]).
  - Empty subarray: Not counted, as constraints ensure at least one element.
- **Result**: Returns the total number of subarrays with sum `k`.

### Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of `nums`. Each element is processed once, and hash map operations are O(1) on average.
- **Space Complexity**: O(n) for the hash map to store prefix sums.

### Alternative Approach
1. **Brute Force**:
   - Check every possible subarray by computing its sum using nested loops.
   - Time Complexity: O(n^2)
   - Space Complexity: O(1)
The prefix sum with hash map approach is preferred for its linear time complexity, making it efficient for large inputs up to `2 * 10^4`.


# 105. Construct Binary Tree from Preorder and Inorder Traversal - Hash Table, Divide and Conquer, Tree, Binary Tree

This document describes the solution to the "Construct Binary Tree from Preorder and Inorder Traversal" problem (LeetCode #105).

## Problem Description
Given two integer arrays `preorder` and `inorder` where `preorder` is the preorder traversal of a binary tree and `inorder` is the inorder traversal of the same tree, construct and return the binary tree. The values in the arrays are unique.

### Example
<img src="../assets/tree.jpg" width="20%">

```
Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]
Explanation:
- Preorder: [3,9,20,15,7] (root, left, right)
- Inorder: [9,3,15,20,7] (left, root, right)
The tree is constructed with 3 as root, 9 as left child, and 20 as right child (with 15 and 7 as its children).

Input: preorder = [-1], inorder = [-1]
Output: [-1]
Explanation: Single node tree with value -1.
```

### Constraints
- `1 <= preorder.length <= 3000`
- `inorder.length == preorder.length`
- `-3000 <= preorder[i], inorder[i] <= 3000`
- `preorder` and `inorder` consist of unique values.
- Each value of `inorder` also appears in `preorder`.
- `preorder` is guaranteed to be the preorder traversal of the tree.
- `inorder` is guaranteed to be the inorder traversal of the tree.

## Solution Approach
The problem can be solved using a recursive approach by leveraging the properties of preorder (root, left, right) and inorder (left, root, right) traversals to construct the binary tree.

### Recursive Construction Approach
1. Use the first element of `preorder` as the root of the current subtree.
2. Find the root’s position in the `inorder` array to split the inorder array into left and right subtrees.
3. Recursively:
   - Construct the left subtree using the elements before the root in `inorder` and the corresponding segment of `preorder`.
   - Construct the right subtree using the elements after the root in `inorder` and the remaining segment of `preorder`.
4. Use a hash map to store the indices of `inorder` values for O(1) lookup.
5. Return the root of the constructed tree.

### TreeNode Structure
```cpp
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
```

### Example Implementation (C++)
```cpp
class Solution {
    unordered_map<int, int> mapIn;

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
         for (int i = 0; i < inorder.size(); i++)
            mapIn[inorder[i]] = i;
        
        int rootIndex = 0; //the first element in preorder is root
        return splitTree(preorder, rootIndex, 0, inorder.size()-1);   
        
        //preorder =>root,left,(right=root,left,right)
        //inorder => left,root,(right=left,root,right)
    }
    
private:
    TreeNode* splitTree(vector<int>& P, int pivotix, int ileft, int iright) {
        int rval = P[pivotix];
        int inPivot = mapIn[rval]; //where is root located in inorder?
        
        TreeNode* root = new TreeNode(rval);  
        
        if (inPivot > ileft)
            root->left = splitTree(P, pivotix+1, ileft, inPivot-1);
        
        if (inPivot < iright)
            root->right = splitTree(P, pivotix+inPivot-ileft+1, inPivot+1, iright);
        
        return root;
    }
};
```

```cpp
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        // Map to store inorder value-to-index mappings
        unordered_map<int, int> inorderMap;
        for (int i = 0; i < inorder.size(); i++) {
            inorderMap[inorder[i]] = i;
        }
        
        int preorderIndex = 0;
        return build(preorder, inorder, 0, inorder.size() - 1, preorderIndex, inorderMap);
    }
    
private:
    TreeNode* build(vector<int>& preorder, vector<int>& inorder, int inStart, int inEnd, 
                    int& preorderIndex, unordered_map<int, int>& inorderMap) {
        if (inStart > inEnd) {
            return nullptr;
        }
        
        // Create root node from current preorder element
        TreeNode* root = new TreeNode(preorder[preorderIndex++]);
        
        // Find root's position in inorder
        int inorderRootIndex = inorderMap[root->val];
        
        // Recursively build left and right subtrees
        root->left = build(preorder, inorder, inStart, inorderRootIndex - 1, preorderIndex, inorderMap);
        root->right = build(preorder, inorder, inorderRootIndex + 1, inEnd, preorderIndex, inorderMap);
        
        return root;
    }
};
```

### How It Works
- **Preorder and Inorder Properties**:
  - `preorder`: First element is the root, followed by left subtree, then right subtree.
  - `inorder`: Left subtree, root, right subtree.
- **Hash Map**:
  - Maps each `inorder` value to its index for O(1) lookup of the root’s position.
- **Recursion**:
  - Use `preorderIndex` to track the current root in `preorder`.
  - Find the root’s index in `inorder` to split into left (`inStart` to `inorderRootIndex - 1`) and right (`inorderRootIndex + 1` to `inEnd`) subtrees.
  - Recursively construct left and right subtrees, advancing `preorderIndex`.
- **Edge Cases**:
  - Single node: `preorder = [x]`, `inorder = [x]` returns a single node.
  - Empty tree: Not applicable due to constraints.
  - Unbalanced tree: Correctly handled by recursive splits.
- **Result**: Returns the root of the constructed binary tree.

### Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the input arrays. Building the hash map takes O(n), and each node is processed once during recursion.
- **Space Complexity**: O(n) for the hash map and O(h) for the recursion stack, where `h` is the tree height (up to O(n) for a skewed tree, O(log n) for a balanced tree). Total is O(n).

### Alternative Approach
1. **Iterative with Stack**:
   - Use a stack to mimic the recursive process, building the tree by processing `preorder` and `inorder` iteratively.
   - Time Complexity: O(n)
   - Space Complexity: O(h)
The recursive approach with a hash map is preferred for its clarity and straightforward mapping of preorder and inorder properties, with efficient lookup for splitting subtrees.



# 692. Top K Frequent Words - Hash Table, Trie, Sorting, Heap (Priority Queue), Bucket Sort

This document describes the solution to the "Top K Frequent Words" problem (LeetCode #692).

## Problem Description
Given an array of strings `words` and an integer `k`, return the `k` most frequent words sorted in lexicographical order if they have the same frequency.

### Example
```
Input: words = ["i","love","leetcode","i","love","coding"], k = 2
Output: ["i","love"]
Explanation: "i" and "love" appear twice each, and are returned in lexicographical order.

Input: words = ["the","day","is","sunny","the","the","sunny","is","is"], k = 4
Output: ["is","sunny","the","day"]
Explanation: Frequencies: "the":3, "is":3, "sunny":2, "day":1. The top 4 words are sorted lexicographically.
```

### Constraints
- `1 <= words.length <= 500`
- `1 <= words[i].length <= 10`
- `words[i]` consists of lowercase English letters.
- `k` is in the range `[1, number of unique words in the input]`.

## Solution Approach
The problem can be solved by counting word frequencies with a hash map and using a priority queue to extract the top `k` words, ensuring lexicographical sorting for equal frequencies.

### Hash Map and Priority Queue Approach
1. Use a hash map to count the frequency of each word.
2. Create a min-heap (priority queue) that prioritizes higher frequencies and, for equal frequencies, lexicographically larger words (to pop smaller words first).
3. Push each word and its frequency into the heap, maintaining size `k` by popping when necessary.
4. Extract the top `k` words from the heap, reversing the result to get descending frequency and lexicographical order.

### Example Implementation (C++)
```cpp
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        map<string, int> cnt;
        for (auto& w : words)
            ++cnt[w];
        
        vector<vector<string>> bucket(words.size());
        for (auto it : cnt) //each index represent count and hold an aray of words that match the count
            bucket[it.second].push_back(it.first);
        
        vector<string> res;
        for (int i = (int)bucket.size() - 1; k > 0 && i >= 0; i--) {
            if (bucket[i].empty())
                continue;
            int n = min(k, (int)bucket[i].size());
            res.insert(res.end(), bucket[i].begin(), bucket[i].begin() + n);
            k -= n;
        }
        
        return res;
    }
};
```

```cpp
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        // Count frequency of each word
        unordered_map<string, int> freq;
        for (const string& word : words) {
            freq[word]++;
        }
        
        // Min-heap with custom comparator
        auto cmp = [](const pair<string, int>& a, const pair<string, int>& b) {
            if (a.second != b.second) {
                return a.second > b.second; // Higher frequency has lower priority
            }
            return a.first < b.first; // For same frequency, lexicographically larger has lower priority
        };
        priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> pq(cmp);
        
        // Add words to heap, maintain size k
        for (const auto& entry : freq) {
            pq.push({entry.first, entry.second});
            if (pq.size() > k) {
                pq.pop();
            }
        }
        
        // Extract top k words
        vector<string> result;
        while (!pq.empty()) {
            result.push_back(pq.top().first);
            pq.pop();
        }
        
        // Reverse to get descending frequency and lexicographical order
        reverse(result.begin(), result.end());
        return result;
    }
};
```

### How It Works
- **Frequency Counting**:
  - Use a hash map to count how many times each word appears.
- **Priority Queue**:
  - Use a min-heap to store up to `k` words.
  - The comparator prioritizes:
    - Lower frequency (so higher frequencies stay in the heap).
    - For equal frequencies, lexicographically smaller words (so larger ones are popped).
  - Push each word-frequency pair; if heap size exceeds `k`, pop the smallest.
- **Result Extraction**:
  - Pop all words from the heap into a vector.
  - Reverse the vector to get words in order of decreasing frequency and lexicographical order for equal frequencies.
- **Edge Cases**:
  - Single word: Returns that word if `k=1`.
  - `k` equals unique words: Returns all words sorted by frequency and lexicographically.
  - Ties in frequency: Lexicographical order ensures correct sorting.
- **Result**: Returns the `k` most frequent words in the required order.

### Time and Space Complexity
- **Time Complexity**: O(n log n + k log k), where `n` is the length of `words`. Building the frequency map is O(n), heap operations are O(n log k) for inserting up to `n` words with heap size `k`, and extracting/reversing is O(k log k).
- **Space Complexity**: O(n) for the hash map and O(k) for the priority queue, totaling O(n).

### Alternative Approach
1. **Bucket Sort**:
   - Use a hash map to count frequencies.
   - Create buckets for each frequency (up to `n`), and sort words lexicographically within each bucket.
   - Collect the top `k` words from the highest frequency buckets.
   - Time Complexity: O(n log n) due to sorting within buckets.
   - Space Complexity: O(n).
The priority queue approach is preferred for its clarity and efficiency, as it avoids sorting large buckets and directly maintains the top `k` elements.








