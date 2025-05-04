```
# 78. Subsets Solution
# 90. Subsets II Solution
```

# 78. Subsets Solution

## Problem Description
Given an integer array `nums` of unique elements, return all possible subsets (the power set). The solution set must not contain duplicate subsets and can be returned in any order.

### Example
```
Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
Explanation: All possible subsets of [1,2,3] are listed.

Example 2:
Input: nums = [0]
Output: [[],[0]]
```

## Solution
Below is the C++ solution to generate all subsets using a backtracking approach.

```cpp
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;
        backtrack(nums, 0, current, result);
        return result;
    }
    
private:
    void backtrack(vector<int>& nums, int start, vector<int>& current, vector<vector<int>>& result) {
        // Add the current subset to the result
        result.push_back(current);
        
        // Explore each element starting from 'start'
        for (int i = start; i < nums.size(); ++i) {
            // Include nums[i] in the current subset
            current.push_back(nums[i]);
            // Recurse with the next starting index
            backtrack(nums, i + 1, current, result);
            // Backtrack by removing nums[i]
            current.pop_back();
        }
    }
};
```

## Explanation
1. **Backtracking Approach**:
   - Use a recursive `backtrack` function to generate all subsets.
   - Parameters:
     - `nums`: The input array.
     - `start`: The index to start considering elements (ensures we don't reuse elements and maintains order).
     - `current`: The current subset being built.
     - `result`: The list of all subsets.
2. **Backtracking Process**:
   - At each step, add the `current` subset to `result` (including the empty subset initially).
   - Iterate through elements from `start` to the end of `nums`:
     - Include the current element `nums[i]` in `current`.
     - Recursively call `backtrack` with the next index (`i + 1`) to explore further elements.
     - Backtrack by removing the last element to try the next combination.
3. **Result**:
   - The `result` vector contains all possible subsets, including the empty subset and the full array.

## Time and Space Complexity
- **Time Complexity**: O(2^n), where `n` is the length of `nums`. There are 2^n possible subsets, and we generate each one.
- **Space Complexity**: O(n) for the recursion stack and the `current` subset, excluding the space for the output `result`. The output space is O(2^n) but is not counted as extra space per convention.

## Edge Cases
- Empty array: Return `[[]]` (only the empty subset).
- Single element: `nums = [1]` returns `[[],[1]]`.
- Multiple elements: `nums = [1,2,3]` generates all 2^3 = 8 subsets.
- Large array: Handles up to `n = 10` efficiently (2^10 = 1024 subsets).
- No duplicates: The problem guarantees unique elements, so no duplicate subsets are generated.


# 90. Subsets II Solution

## Problem Description
Given an integer array `nums` that may contain duplicates, return all possible unique subsets (the power set). The solution set must not contain duplicate subsets and can be returned in any order.

### Example
```
Input: nums = [1,2,2]
Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
Explanation: All possible unique subsets are listed, excluding duplicates.

Example 2:
Input: nums = [0]
Output: [[],[0]]
```

## Solution
Below is the C++ solution to generate all unique subsets using a backtracking approach with duplicate handling.

```cpp
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;
        // Sort the array to handle duplicates
        sort(nums.begin(), nums.end());
        backtrack(nums, 0, current, result);
        return result;
    }
    
private:
    void backtrack(vector<int>& nums, int start, vector<int>& current, vector<vector<int>>& result) {
        // Add the current subset to the result
        result.push_back(current);
        
        // Explore each element starting from 'start'
        for (int i = start; i < nums.size(); ++i) {
            // Skip duplicates to avoid duplicate subsets
            if (i > start && nums[i] == nums[i - 1]) {
                continue;
            }
            // Include nums[i] in the current subset
            current.push_back(nums[i]);
            // Recurse with the next starting index
            backtrack(nums, i + 1, current, result);
            // Backtrack by removing nums[i]
            current.pop_back();
        }
    }
};
```

## Explanation
1. **Sorting for Duplicate Handling**:
   - Sort the input array `nums` to ensure duplicate elements are adjacent, making it easier to skip them during backtracking.
2. **Backtracking Approach**:
   - Use a recursive `backtrack` function with parameters:
     - `nums`: The sorted input array.
     - `start`: The index to start considering elements (ensures order and prevents reusing elements).
     - `current`: The current subset being built.
     - `result`: The list of all unique subsets.
   - At each step:
     - Add the `current` subset to `result` (including the empty subset initially).
     - Iterate through elements from `start` to the end:
       - Skip the current element if it is a duplicate (i.e., `i > start` and `nums[i] == nums[i - 1]`) to avoid generating duplicate subsets.
       - Include `nums[i]` in `current`.
       - Recursively call `backtrack` with `i + 1` to explore further elements.
       - Backtrack by removing the last element to try the next combination.
3. **Result**:
   - The `result` vector contains all unique subsets, including the empty subset.

## Time and Space Complexity
- **Time Complexity**: O(2^n), where `n` is the length of `nums`. In the worst case, we generate all possible subsets (up to 2^n), but duplicates reduce the actual number. Sorting takes O(n log n), which is dominated by O(2^n).
- **Space Complexity**: O(n) for the recursion stack and the `current` subset, excluding the output `result`. The output space is O(2^n) in the worst case but is not counted as extra space.

## Edge Cases
- Empty array: Return `[[]]` (only the empty subset).
- Single element: `nums = [1]` returns `[[],[1]]`.
- All duplicates: `nums = [2,2,2]` returns `[[],[2],[2,2],[2,2,2]]`.
- No duplicates: Behaves like the Subsets problem (e.g., `nums = [1,2,3]`).
- Large array: Handles up to `n = 10` efficiently (2^10 = 1024 subsets).
- Mixed duplicates and unique elements: Correctly skips duplicates (e.g., `nums = [1,2,2,3]`).


