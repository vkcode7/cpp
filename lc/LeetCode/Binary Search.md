```bash
# 704. Binary Search [Super Easy]
# 33. Search in Rotated Sorted Array [Easy]
# 278. First Bad Version [Easy]
```
# 704. Binary Search
https://leetcode.com/problems/binary-search/

Given a sorted integer array `nums` (in ascending order) and an integer `target`, return the index of `target` in `nums`. If `target` does not exist in the array, return `-1`. You must implement an algorithm with O(log n) time complexity.

### Example
```
Input: nums = [-1,0,3,5,9,12], target = 9
Output: 4
Explanation: 9 exists in nums and its index is 4.

Input: nums = [-1,0,3,5,9,12], target = 2
Output: -1
Explanation: 2 does not exist in nums so return -1
```

## Solution
Below is the C++ solution to perform binary search on a sorted array.
```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0;
        int r = nums.size() - 1;
        while(l < r)
        {
            int m = l + (r-l) / 2;
            if(nums[m] == target)
                return m;

            if(nums[m] < target)
                l = m + 1;
            else
                r = m - 1;
        }

        return -1;    
    }
};
```

- **Time Complexity**: O(log n), where `n` is the length of the array, as the search space is halved in each step.
- **Space Complexity**: O(1), as only a constant amount of extra space is used for pointers.


# 33. Search in Rotated Sorted Array
https://leetcode.com/problems/search-in-rotated-sorted-array/description/

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


# 278. First Bad Version
https://leetcode.com/problems/first-bad-version/description/

You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad. Given `n` versions numbered from `1` to `n`, and an API `isBadVersion(version)` that returns whether a version is bad, find the first bad version. You should minimize the number of calls to the API.

### Example
```
Input: n = 5, bad = 4
Output: 4
Explanation: isBadVersion(3) -> false, isBadVersion(4) -> true, isBadVersion(5) -> true. The first bad version is 4.
```

## Solution
Below is the C++ solution to find the first bad version using binary search.

```cpp
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        auto start = 1;
        auto end = n;
        int lastKnownBadVersion = n;
        while(start <= end)
        {
            int mid = start + (end-start)/2;
            if(isBadVersion(mid))
            {
                end = mid-1;  
                lastKnownBadVersion = min(mid, lastKnownBadVersion);
            }     
            else
                start = mid + 1;         
        }
        
        return lastKnownBadVersion;
    }
};


class Solution {
public:
    int firstBadVersion(int n) {
        int left = 1, right = n;
        
        while (left < right) {
            int mid = left + (right - left) / 2; // Avoid integer overflow
            if (isBadVersion(mid)) {
                right = mid; // Bad version found, search left half including mid
            } else {
                left = mid + 1; // No bad version, search right half
            }
        }
        
        return left; // left == right, points to the first bad version
    }
};
```

## Explanation
1. **Binary Search Approach**:
   - Use two pointers, `left` (starting at 1) and `right` (starting at `n`), to represent the search range.
   - While `left < right`:
     - Compute the midpoint `mid` using `left + (right - left) / 2` to avoid integer overflow.
     - If `isBadVersion(mid)` is `true`, the first bad version is at `mid` or earlier, so set `right = mid`.
     - If `isBadVersion(mid)` is `false`, the first bad version is after `mid`, so set `left = mid + 1`.
   - When `left == right`, it points to the first bad version.
2. **Minimizing API Calls**:
   - Binary search ensures logarithmic time complexity, minimizing the number of calls to `isBadVersion`.
3. **Return**:
   - Return `left`, which is the first bad version.

## Time and Space Complexity
- **Time Complexity**: O(log n), where `n` is the number of versions. Binary search halves the search space in each step.
- **Space Complexity**: O(1), as only a constant amount of extra space is used for pointers.

## Edge Cases
- `n = 1`: If the only version is bad, return 1.
- First version is bad: `isBadVersion(1) = true`, returns 1.
- Last version is bad: Correctly identifies `n` as the first bad version.
- Large `n`: Handles up to `2^31 - 1` without overflow using safe midpoint calculation.
