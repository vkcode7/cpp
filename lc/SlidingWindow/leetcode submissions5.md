# 283. Move Zeroes Solution - Two Pointers

## Problem Description
Given an integer array `nums`, move all `0`'s to the end of it while maintaining the relative order of the non-zero elements. The operation must be done in-place without making a copy of the array.

### Example
```
Input: nums = [0,1,0,3,12]
Output: [1,3,12,0,0]
```

## Solution
Below is the C++ solution to move all zeroes to the end of the array.

```cpp
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int np = 0;
        int n = nums.size();
        for(int zp = 0;zp < n-1;)
        {
            if(nums[zp] != 0) {
                zp++;
                continue;
            }
            
            //zp
            for(np = zp+1; np < n; np++)
            {
                if(nums[np])
                {
                    swap(nums[zp], nums[np]);
                    zp++;
                    break;
                }                
            } 
            
            if(np == n) // no more non zero left
                break;
        }
    }
};

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        // Step 1: Move all non-zero elements to the front
        int nonZeroPos = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != 0) {
                nums[nonZeroPos++] = nums[i];
            }
        }
        
        // Step 2: Fill the rest with zeroes
        while (nonZeroPos < nums.size()) {
            nums[nonZeroPos++] = 0;
        }
    }
};
```

## Explanation
1. **Two-Pointer Approach**:
   - Use `nonZeroPos` to track the position where the next non-zero element should be placed.
   - Iterate through the array, copying non-zero elements to `nonZeroPos` and incrementing it.
2. **Fill Zeroes**:
   - After all non-zero elements are moved to the front, fill the remaining positions from `nonZeroPos` to the end with zeroes.
3. **In-Place**: The solution modifies the array directly without using extra space.

## Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the array. We traverse the array once to move non-zero elements and once to fill zeroes.
- **Space Complexity**: O(1), as we only use a constant amount of extra space.

## Edge Cases
- Empty array: No operation needed.
- Array with all zeroes: All elements remain zero, no change in order.
- Array with no zeroes: Array remains unchanged.
- Single element: No change needed.
