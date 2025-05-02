# 33. Search in Rotated Sorted Array

This document describes the solution to the "Search in Rotated Sorted Array" problem (LeetCode #33).

## Problem Description
Given an integer array `nums` sorted in ascending order and rotated at some pivot unknown to you (e.g., `[0,1,2,4,5,6,7]` might become `[4,5,6,7,0,1,2]`), and an integer `target`, return the index of `target` in `nums`, or `-1` if it is not present. The algorithm must run in O(log n) time complexity.

### Example
```
Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4
Explanation: The array is rotated, and 0 is at index 4.

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
Explanation: 3 is not in the array.

Input: nums = [1], target = 0
Output: -1
Explanation: Single element array does not contain 0.
```

### Constraints
- `1 <= nums.length <= 5000`
- `-10^4 <= nums[i] <= 10^4`
- All values of `nums` are unique.
- `nums` is an ascending sorted array that is possibly rotated.
- `-10^4 <= target <= 10^4`

## Solution Approach
The problem can be solved using a modified binary search that accounts for the rotation by determining which half of the array is sorted and whether the target lies in that half.

### Modified Binary Search Approach
1. Initialize two pointers, `left` and `right`, to the start and end of the array.
2. While `left <= right`:
   - Compute the middle index `mid`.
   - If `nums[mid] == target`, return `mid`.
   - Check if the left half (`left` to `mid`) is sorted by comparing `nums[left]` and `nums[mid]`:
     - If sorted and `target` is within `[nums[left], nums[mid])`, search the left half (`right = mid - 1`).
     - Otherwise, search the right half (`left = mid + 1`).
   - If the left half is not sorted, the right half (`mid` to `right`) must be sorted:
     - If `target` is within `(nums[mid], nums[right]]`, search the right half (`left = mid + 1`).
     - Otherwise, search the left half (`right = mid - 1`).
3. If the target is not found, return `-1`.

### Example Implementation (C++)
```cpp
class Solution {
public:
    
    int getPivot(vector<int>& nums, int n){
        int left = 0;
        int right = n-1;
        
        if (nums[left] < nums[right])
          return 0;

        while (left <= right) {
          int pivot = (left + right) / 2;
          if (nums[pivot] > nums[pivot + 1])
            return pivot + 1;
          else {
            if (nums[pivot] < nums[left])
              right = pivot - 1;
            else
              left = pivot + 1;
          }
        }
        return 0;
    }
    
    int binarySearch(vector<int>& nums, int s, int e, int target){
        int m = s + (e-s)/2;
        while(s <= e){
            if(nums[m]== target){
                return m;
            }
            else if(nums[m]< target){
                s = m+1;
            }
            else{
                e = m-1;
            }
            m = s + (e-s)/2;
        }
        return -1;
    }
    
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        if(n == 1)
            return( nums[0] ==  target ? 0 : -1);
        
        int pivot = getPivot(nums, n);
        if(target >= nums[pivot] && target <= nums[n-1]){
            return binarySearch(nums, pivot, n-1, target);
        }
        else{
            return binarySearch(nums, 0, pivot-1, target);
        }
    }
    
};
```

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] == target) {
                return mid;
            }
            
            // Check if left half is sorted
            if (nums[left] <= nums[mid]) {
                // Check if target is in left half
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            // Right half must be sorted
            else {
                // Check if target is in right half
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        
        return -1;
    }
};
```

### How It Works
- **Binary Search**:
  - At each step, compute the middle index and compare `nums[mid]` with `target`.
- **Sorted Half Check**:
  - If `nums[left] <= nums[mid]`, the left half is sorted.
    - If `target` is in `[nums[left], nums[mid])`, search left.
    - Else, search right.
  - If `nums[left] > nums[mid]`, the right half is sorted.
    - If `target` is in `(nums[mid], nums[right]]`, search right.
    - Else, search left.
- **Edge Cases**:
  - Single element: Returns index if `nums[0] == target`, else `-1`.
  - No rotation: Works like standard binary search.
  - Target not present: Returns `-1` after exhausting search.
  - Full rotation: Handles cases where pivot is at the start.
- **Result**: Returns the index of `target` or `-1` if not found.

### Time and Space Complexity
- **Time Complexity**: O(log n), where `n` is the length of `nums`, as the search space is halved in each step.
- **Space Complexity**: O(1), as only a constant amount of extra space is used.

### Alternative Approach
1. **Find Pivot and Binary Search**:
   - First, find the pivot (smallest element) using binary search.
   - Adjust the array indices to map to the unrotated array and perform standard binary search.
   - Time Complexity: O(log n)
   - Space Complexity: O(1)
The modified binary search approach is preferred for its simplicity, as it combines pivot handling and target search in a single pass, avoiding the need to explicitly find the pivot.
