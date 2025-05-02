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


# 118. Pascal's Triangle Solution

## Problem Description
Given an integer `numRows`, generate the first `numRows` of Pascal's triangle. In Pascal's triangle, each number is the sum of the two numbers directly above it.

### Example
```
Input: numRows = 5
Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
```

<img src="../assets/PascalTriangleAnimated2.gif" width="40%">


## Solution
Below is the C++ solution to generate Pascal's triangle.

```cpp
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ans;
        vector<int> top(1,1);
        ans.push_back(top);
        //1,2,3,4,5
        for(int i = 1; i < numRows; i++)
        {
            //num items = i+1
            vector<int> row(i+1, 1); //fill left and right most items with 1
            //iterate from 2 to 2nd last items
            for(int j = 1; j < i; j++)
                row[j] = top[j-1] + top[j];
            
            ans.push_back(row);
            top = row;
        }
        
        return ans;
    }
};

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> triangle;
        
        // Handle empty case
        if (numRows == 0) {
            return triangle;
        }
        
        // First row is always [1]
        triangle.push_back({1});
        
        // Generate subsequent rows
        for (int i = 1; i < numRows; ++i) {
            vector<int> row;
            const vector<int>& prevRow = triangle[i - 1];
            
            // First element is always 1
            row.push_back(1);
            
            // Compute middle elements
            for (int j = 1; j < i; ++j) {
                row.push_back(prevRow[j - 1] + prevRow[j]);
            }
            
            // Last element is always 1
            row.push_back(1);
            
            triangle.push_back(row);
        }
        
        return triangle;
    }
};
```

## Explanation
1. **Initialization**:
   - Create a vector of vectors (`triangle`) to store the result.
   - If `numRows` is 0, return an empty triangle.
   - Add the first row `[1]` to the triangle.
2. **Row Generation**:
   - For each row `i` (from 1 to `numRows - 1`):
     - Start with `1` as the first element.
     - Compute middle elements by summing adjacent elements from the previous row (`prevRow[j - 1] + prevRow[j]`).
     - End with `1` as the last element.
   - Add the row to the triangle.
3. **Output**: Return the completed triangle.

## Time and Space Complexity
- **Time Complexity**: O(numRows²), as we generate each element in the triangle, and the number of elements is the sum of the first `numRows` integers (1 + 2 + ... + numRows).
- **Space Complexity**: O(numRows²), to store the triangle. The space used for the output is not counted as extra space per LeetCode conventions.

## Edge Cases
- `numRows = 0`: Return an empty triangle.
- `numRows = 1`: Return `[[1]]`.
- `numRows = 2`: Return `[[1], [1,1]]`.
- Large `numRows`: The solution handles up to `numRows = 30` efficiently within constraints.


# 88. Merge Sorted Array Solution - Two Pointers

## Problem Description
Given two sorted integer arrays `nums1` and `nums2`, merge `nums2` into `nums1` as one sorted array. The number of elements initialized in `nums1` and `nums2` are `m` and `n` respectively. You may assume that `nums1` has a size equal to `m + n` such that it has enough space to hold additional elements from `nums2`. The merge must be done in-place.

### Example
```
Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
Output: [1,2,2,3,5,6]
```

## Solution
Below is the C++ solution to merge two sorted arrays in  `nums1` and `nums2` in-place.

```cpp
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if(m == 0)
        {
            int i = 0;
            for(auto x : nums2)
                nums1[i++] = x;
            
            return;
        }
        
        //make a copy
        vector<int> cp(nums1.begin(), nums1.begin() + m);
        
        int m1 = 0, n1 = 0, k = 0;
        while(m1 < m && n1 < n)
        {
            if(cp[m1] <= nums2[n1]) {
                nums1[k++] = cp[m1++];
            }
            else
                nums1[k++] = nums2[n1++];
        }
        
        while(m1 < m)
            nums1[k++] = cp[m1++];
        
        while(n1 < n)
            nums1[k++] = nums2[n1++];
            
        return;
    }
};

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1; // Pointer for nums1
        int j = n - 1; // Pointer for nums2
        int k = m + n - 1; // Pointer for merged array
        
        // Merge from the end to avoid overwriting
        while (j >= 0) {
            if (i >= 0 && nums1[i] > nums2[j]) {
                nums1[k--] = nums1[i--];
            } else {
                nums1[k--] = nums2[j--];
            }
        }
    }
};
```

## Explanation
1. **Three-Pointer Approach**:
   - Use `i` to track the last element of `nums1` (initially `m - 1`).
   - Use `j` to track the last element of `nums2` (initially `n - 1`).
   - Use `k` to track the position in `nums1` where the next element will be placed (initially `m + n - 1`).
2. **Merge from End**:
   - Compare elements from `nums1` and `nums2`.
   - Place the larger element at position `k` in `nums1` and decrement the corresponding pointer (`i` or `j`) and `k`.
   - Continue until all elements from `nums2` are placed (`j >= 0`).
   - If `nums1` has remaining elements, they are already in place.
3. **In-Place**: The solution modifies `nums1` directly without using extra space.

## Time and Space Complexity
- **Time Complexity**: O(m + n), as we process each element from both arrays once.
- **Space Complexity**: O(1), as we only use a constant amount of extra space for pointers.

## Edge Cases
- `m = 0`: `nums1` is empty, copy all elements from `nums2`.
- `n = 0`: `nums2` is empty, `nums1` remains unchanged.
- `m + n = 0`: Both arrays are empty, no operation needed.
- One array is much larger than the other: The solution handles uneven sizes correctly.


# 54. Spiral Matrix Solution

## Problem Description
Given an `m x n` matrix, return all elements of the matrix in spiral order (clockwise starting from the top-left).

### Example
```
Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,3,6,9,8,7,4,5]
```
<img src="../assets/spiral1.jpg" width="20%">

```
Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]
```
<img src="../assets/spiral2.jpg" width="20%">

## Solution
Below is the C++ solution to traverse a matrix in spiral order.

```cpp
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int n=matrix.size();
        int m=matrix[0].size();
        int left=0,right=m-1,bottom=n-1,top=0;
        int direction=1; //1 to right/2 to bottom/3 to left/4 to up
        vector<int> v;
        while(v.size() < n*m) //left<=right && top<=bottom
        {
            if(direction==1)
            {
                for(int i=left;i<=right;i++) v.push_back(matrix[top][i]);
                direction=2;
                top++;
            }
            
            else if(direction==2)
            {
                for(int i=top;i<=bottom;i++) v.push_back(matrix[i][right]);
                direction=3;
                right--;
            }
            
            else if(direction==3)
            {
                for(int i=right;i>=left;i--) v.push_back(matrix[bottom][i]);
                direction=4;
                bottom--;
            }
            
            else if(direction==4)
            {
                for(int i=bottom;i>=top;i--) v.push_back(matrix[i][left]);
                direction=1;
                left++;
            }
        }
        return v;
        
    }
};

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> result;
        if (matrix.empty() || matrix[0].empty()) {
            return result;
        }
        
        int m = matrix.size(); // Number of rows
        int n = matrix[0].size(); // Number of columns
        int top = 0, bottom = m - 1, left = 0, right = n - 1;
        
        while (top <= bottom && left <= right) {
            // Traverse right
            for (int j = left; j <= right; ++j) {
                result.push_back(matrix[top][j]);
            }
            top++;
            
            // Traverse down
            for (int i = top; i <= bottom; ++i) {
                result.push_back(matrix[i][right]);
            }
            right--;
            
            if (top <= bottom) {
                // Traverse left
                for (int j = right; j >= left; --j) {
                    result.push_back(matrix[bottom][j]);
                }
                bottom--;
            }
            
            if (left <= right) {
                // Traverse up
                for (int i = bottom; i >= top; --i) {
                    result.push_back(matrix[i][left]);
                }
                left++;
            }
        }
        
        return result;
    }
};
```

## Explanation
1. **Boundary Tracking**:
   - Use four pointers: `top`, `bottom`, `left`, and `right` to represent the current boundaries of the unvisited matrix.
   - `top` and `bottom` track the row boundaries, `left` and `right` track the column boundaries.
2. **Spiral Traversal**:
   - Traverse right: Process elements in the `top` row from `left` to `right`, then increment `top`.
   - Traverse down: Process elements in the `right` column from `top` to `bottom`, then decrement `right`.
   - Traverse left: If `top <= bottom`, process elements in the `bottom` row from `right` to `left`, then decrement `bottom`.
   - Traverse up: If `left <= right`, process elements in the `left` column from `bottom` to `top`, then increment `left`.
3. **Termination**: Continue until `top > bottom` or `left > right`.
4. **Edge Case Handling**: Return an empty vector if the matrix is empty or has no columns.

## Time and Space Complexity
- **Time Complexity**: O(m * n), where `m` is the number of rows and `n` is the number of columns, as we visit each element exactly once.
- **Space Complexity**: O(1), excluding the output array, as we only use a constant amount of extra space for pointers.

## Edge Cases
- Empty matrix (`matrix = []`): Return an empty vector.
- Single row (`matrix = [[1,2,3]]`): Traverse right only.
- Single column (`matrix = [[1],[2],[3]]`): Traverse down only.
- Single element (`matrix = [[1]]`): Return `[1]`.
- Rectangular matrix: Handles cases where `m != n`.
