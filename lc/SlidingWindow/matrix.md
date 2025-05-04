```bash
# 118. Pascal's Triangle Solution
# 54. Spiral Matrix Solution
# 200. Number of Islands - Array, Depth-First Search, Breadth-First Search, Union Find, Matrix
# 73. Set Matrix Zeroes - Hash Table, Matrix
# 79. Word Search - Backtracking, Depth-First Search, Matrix
# 733. Flood Fill Solution
```

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


# 200. Number of Islands - Array, Depth-First Search, Breadth-First Search, Union Find, Matrix
https://leetcode.com/problems/number-of-islands/description/

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


# 73. Set Matrix Zeroes - Hash Table, Matrix

This document describes the solution to the "Set Matrix Zeroes" problem (LeetCode #73).

## Problem Description
Given an `m x n` integer matrix `matrix`, if an element is `0`, set its entire row and column to `0`. You must do it in-place.

### Example
```
Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
Output: [[1,0,1],[0,0,0],[1,0,1]]
Explanation: The element at [1,1] is 0, so row 1 and column 1 are set to 0.

Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
Explanation: Zeros at [0,0] and [0,3] set row 0 and columns 0 and 3 to 0.

Hint 1
If any cell of the matrix has a zero we can record its row and column number using additional memory. But if you don't want to use extra memory then you can manipulate the array instead. i.e. simulating exactly what the question says.
Hint 2
Setting cell values to zero on the fly while iterating might lead to discrepancies. What if you use some other integer value as your marker? There is still a better approach for this problem with 0(1) space.
Hint 3
We could have used 2 sets to keep a record of rows/columns which need to be set to zero. But for an O(1) space solution, you can use one of the rows and and one of the columns to keep track of this information.
Hint 4
We can use the first cell of every row and column as a flag. This flag would determine whether a row or column has been set to zero.
```

### Constraints
- `m == matrix.length`
- `n == matrix[0].length`
- `1 <= m, n <= 200`
- `-2^31 <= matrix[i][j] <= 2^31 - 1`

## Solution Approach
To solve this in-place, we can use the first row and first column of the matrix as markers to indicate which rows and columns need to be set to zero, minimizing extra space.

### In-Place Marking Approach
1. Use two flags to track if the first row and first column originally contain any zeros.
2. Scan the matrix (excluding the first row and column) to mark rows and columns:
   - If `matrix[i][j] == 0`, set `matrix[i][0]` and `matrix[0][j]` to 0.
3. Use the markers in the first row and column to set the corresponding rows and columns to zero.
4. Based on the flags, set the first row and column to zero if needed.

### Example Implementation (C++)
```cpp
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();
                
        set<int> zcols;
        
        for(int row=0; row < rows; row++)
        {
            vector<int>& vrow = matrix[row];
            bool bZeroFound = false;
            for(int c=0; c < vrow.size(); c++)
            {
                if(vrow[c] == 0)
                {
                    zcols.insert(c);
                    bZeroFound = true;
                }
            }
            
            if(bZeroFound)
            {
                //set entire row to 0
                for(int c=0; c < vrow.size(); c++) {
                    matrix[row][c] = 0;
                }
            }  
        }
        //set entire col to 0
        for(auto& col: zcols) {
            for(int row = 0; row < rows; row++)
                matrix[row][col] = 0;
        }
    }
};
```

```cpp
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        bool firstRowZero = false;
        bool firstColZero = false;
        
        // Check if first row has any zero
        for (int j = 0; j < n; j++) {
            if (matrix[0][j] == 0) {
                firstRowZero = true;
                break;
            }
        }
        
        // Check if first column has any zero
        for (int i = 0; i < m; i++) {
            if (matrix[i][0] == 0) {
                firstColZero = true;
                break;
            }
        }
        
        // Use first row and column as markers
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0; // Mark first cell of row
                    matrix[0][j] = 0; // Mark first cell of column
                }
            }
        }
        
        // Set rows to zero based on first column markers
        for (int i = 1; i < m; i++) {
            if (matrix[i][0] == 0) {
                for (int j = 1; j < n; j++) {
                    matrix[i][j] = 0;
                }
            }
        }
        
        // Set columns to zero based on first row markers
        for (int j = 1; j < n; j++) {
            if (matrix[0][j] == 0) {
                for (int i = 1; i < m; i++) {
                    matrix[i][j] = 0;
                }
            }
        }
        
        // Set first row to zero if needed
        if (firstRowZero) {
            for (int j = 0; j < n; j++) {
                matrix[0][j] = 0;
            }
        }
        
        // Set first column to zero if needed
        if (firstColZero) {
            for (int i = 0; i < m; i++) {
                matrix[i][0] = 0;
            }
        }
    }
};
```

### How It Works
- **Flags**: `firstRowZero` and `firstColZero` track if the first row/column need to be zeroed, as they are used as markers.
- **Marking**:
  - Scan the matrix (excluding markers) for zeros.
  - Mark the first cell of the corresponding row (`matrix[i][0]`) and column (`matrix[0][j]`) as 0.
- **Zeroing**:
  - Use markers in `matrix[i][0]` to zero out rows (excluding first column).
  - Use markers in `matrix[0][j]` to zero out columns (excluding first row).
- **Final Step**: Zero the first row and column based on the flags.
- **Edge Cases**:
  - Single row or column: Handled by checking first row/column separately.
  - All zeros: All markers are set, and the entire matrix is zeroed.

### Time and Space Complexity
- **Time Complexity**: O(m * n), where `m` and `n` are the dimensions of the matrix, as we traverse the matrix a constant number of times.
- **Space Complexity**: O(1), as we only use two boolean variables and modify the matrix in-place.

### Alternative Approach
1. **Extra Space**:
   - Use two arrays to track rows and columns that need to be zeroed.
   - Time Complexity: O(m * n)
   - Space Complexity: O(m + n)
The in-place approach is preferred as it meets the problem's requirement to minimize extra space.


# 79. Word Search - Backtracking, Depth-First Search, Matrix

## Problem Description
Given an `m x n` grid of characters `board` and a string `word`, return `true` if `word` exists in the grid, and `false` otherwise. The word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.

### Example
```
Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
Output: true
Explanation: The word "ABCCED" can be formed by following the path A->B->C->C->E->D.
```
<img src="../assets/word2.jpg" width="30%">


```
Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
Output: true
Explanation: The word "SEE" can be formed by following the path S->E->E.
```
<img src="../assets/word1.jpg" width="30%">

```
Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
Output: false
Explanation: The word "ABCB" cannot be formed as it requires reusing the cell at [0,1].
```

### Constraints
- `m == board.length`
- `n == board[i].length`
- `1 <= m, n <= 6`
- `1 <= word.length <= 15`
- `board` and `word` consist of only uppercase and lowercase English letters.

## Solution Approach
The problem can be solved using a depth-first search (DFS) with backtracking to explore all possible paths in the grid.

### DFS with Backtracking Approach
1. Iterate through each cell in the grid as a potential starting point.
2. For each cell, use DFS to check if the word can be formed starting from that cell:
   - Check if the current character matches the current position in the word.
   - Temporarily mark the cell as visited (e.g., by changing its value).
   - Recursively explore all four adjacent cells (up, down, left, right).
   - Restore the cell’s original value after exploration (backtracking).
3. Return `true` if the entire word is found, `false` otherwise.

### Example Implementation (C++)
```cpp
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        for (unsigned int i = 0; i < board.size(); i++) 
            for (unsigned int j = 0; j < board[0].size(); j++) 
                if (found(board, i, j, word))
                    return true;
        return false;
    }

    bool found(vector<vector<char>>& board, int i, int j, string& word) {
        if (i<0 || i>=board.size() || j<0 || j>=board[0].size() || board[i][j] != word[0])  
            return false;
        
        if(word.length() == 1) // this was the last charater in word and matched, so return
            return true;
   
        char c = board[i][j];
        board[i][j] = '*';
        
        string s = word.substr(1);
        bool ret = found(board, i-1, j, s) || found(board, i+1, j, s) || found(board, i, j-1, s) || found(board, i, j+1, s);
        board[i][j] = c;
        return ret;
    }
};
```

```cpp
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();
        
        // Try each cell as starting point
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (dfs(board, word, 0, i, j)) {
                    return true;
                }
            }
        }
        
        return false;
    }
    
private:
    bool dfs(vector<vector<char>>& board, string& word, int index, int i, int j) {
        // If all characters are matched
        if (index == word.length()) {
            return true;
        }
        
        // Check bounds and character match
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() || 
            board[i][j] != word[index]) {
            return false;
        }
        
        // Temporarily mark cell as visited
        char temp = board[i][j];
        board[i][j] = '#';
        
        // Explore all four directions
        bool found = dfs(board, word, index + 1, i + 1, j) ||
                     dfs(board, word, index + 1, i - 1, j) ||
                     dfs(board, word, index + 1, i, j + 1) ||
                     dfs(board, word, index + 1, i, j - 1);
        
        // Restore cell
        board[i][j] = temp;
        
        return found;
    }
};
```

### How It Works
- **Starting Points**: Iterate over all cells to find a starting point where `board[i][j] == word[0]`.
- **DFS**:
  - Match the current character and index in the word.
  - Mark the cell as visited to prevent reuse.
  - Recursively check all four adjacent cells for the next character.
  - Backtrack by restoring the cell’s value.
- **Termination**:
  - Return `true` if all characters in the word are matched.
  - Return `false` if the current path fails (out of bounds, mismatch, or no valid path).
- **Edge Cases**:
  - Single cell: Check if it matches a one-character word.
  - Word longer than grid: Handled by DFS failing to match all characters.
- **Result**: Returns `true` if the word is found, `false` otherwise.

### Time and Space Complexity
- **Time Complexity**: O(m * n * 4^L), where `m` and `n` are the dimensions of the grid, and `L` is the length of the word. Each cell can start a DFS, and each DFS may explore up to 4 directions for each character.
- **Space Complexity**: O(L) for the recursion stack, where `L` is the length of the word. The board is modified in-place.

### Alternative Approach
1. **DFS with Visited Array**:
   - Use a separate `visited` array to track used cells instead of modifying the board.
   - Time Complexity: O(m * n * 4^L)
   - Space Complexity: O(m * n) for the visited array
The in-place modification approach is preferred to minimize space usage.
```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int leftMax = 0, rightMax = 0;
        int water = 0;
        
        while (left < right) {
            if (height[left] < height[right]) {
                leftMax = max(leftMax, height[left]);
                water += leftMax - height[left];
                left++;
            } else {
                rightMax = max(rightMax, height[right]);
                water += rightMax - height[right];
                right--;
            }
        }
        
        return water;
    }
};
```

### How It Works
- **Two Pointers**: Process the array from both ends, moving toward the center.
- **Water Calculation**:
  - Water at an index is determined by the minimum of the maximum heights on both sides minus the height at that index.
  - By processing the smaller height first, we ensure the water calculation is valid (bounded by the opposite side’s max).
- **Max Tracking**:
  - `leftMax` tracks the tallest bar from the left.
  - `rightMax` tracks the tallest bar from the right.
- **Edge Cases**:
  - Single element: No water can be trapped (handled by `left < right`).
  - Monotonic array: No water trapped (algorithm correctly yields 0).
- **Result**: The total water trapped is accumulated in `water`.

### Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the `height` array, as we traverse the array once with two pointers.
- **Space Complexity**: O(1), as we only use a constant amount of extra space.

### Alternative Approaches
1. **Two Arrays**:
   - Precompute `leftMax` and `rightMax` for each index using two arrays.
   - Time Complexity: O(n)
   - Space Complexity: O(n)
2. **Stack**:
   - Use a stack to track indices of decreasing heights, calculating water when a taller bar is found.
   - Time Complexity: O(n)
   - Space Complexity: O(n)
The two-pointer approach is preferred for its optimal space complexity and simplicity.


# 733. Flood Fill Solution

## Problem Description
Given an `m x n` integer grid `image` representing an image, where `image[i][j]` is a pixel value, perform a flood fill starting from pixel `(sr, sc)`. Replace the color of all connected pixels with the same color as `(sr, sc)` with a new color `newColor`. Two pixels are connected if they are adjacent (up, down, left, or right) and have the same color. Return the modified image.

### Example
```
Input: image = [[1,1,1],[1,1,0],[1,0,1]], sr = 1, sc = 1, newColor = 2
Output: [[2,2,2],[2,2,0],[2,0,1]]
Explanation: Starting at image[1][1] = 1, all connected pixels with value 1 are changed to 2.
```

<img src="../assets/flood1-grid.jpg” width="20%">


## Solution
Below is the C++ solution to perform flood fill using depth-first search (DFS).

```cpp
class Solution {
public:
    void floodFillColor(vector<vector<int>>& grid, int row, int col, int rows, int cols, int startColor, int color)
    {
        if(row < 0 || col < 0 || row == rows || col == cols) return;
        
        if(grid[row][col]==startColor) {
            grid[row][col] = color;
            floodFillColor(grid, row-1, col, rows, cols, startColor, color);
            floodFillColor(grid, row+1, col, rows, cols, startColor, color);
            floodFillColor(grid, row, col-1, rows, cols, startColor, color);
            floodFillColor(grid, row, col+1, rows, cols, startColor, color);
        }
        
        return;     
    }
    
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int startColor = image[sr][sc];   
        if(startColor == color)
            return image;
        
        floodFillColor(image, sr, sc, (int)image.size(), (int)image[0].size(), startColor, color);       
        return image;
    }
};


class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        // If the starting pixel is already the new color, no change needed
        if (image[sr][sc] == newColor) {
            return image;
        }
        
        // Perform DFS to flood fill
        dfs(image, sr, sc, image[sr][sc], newColor);
        return image;
    }
    
private:
    void dfs(vector<vector<int>>& image, int r, int c, int oldColor, int newColor) {
        // Check boundaries and if the current pixel has the old color
        if (r < 0 || r >= image.size() || c < 0 || c >= image[0].size() || image[r][c] != oldColor) {
            return;
        }
        
        // Change the current pixel to newColor
        image[r][c] = newColor;
        
        // Recursively flood fill in all four directions
        dfs(image, r + 1, c, oldColor, newColor); // Down
        dfs(image, r - 1, c, oldColor, newColor); // Up
        dfs(image, r, c + 1, oldColor, newColor); // Right
        dfs(image, r, c - 1, oldColor, newColor); // Left
    }
};
```

## Explanation
1. **Edge Case**:
   - If the starting pixel `(sr, sc)` already has the `newColor`, return the image unchanged to avoid redundant processing.
2. **DFS Approach**:
   - Start at the given pixel `(sr, sc)` and get its original color (`oldColor`).
   - Use a recursive `dfs` function to:
     - Check if the current position is within bounds and has the `oldColor`.
     - If valid, change the pixel to `newColor`.
     - Recursively apply the same process to the four adjacent pixels (up, down, left, right).
3. **In-Place Modification**:
   - The image is modified directly by updating pixel values during DFS.
4. **Return**:
   - Return the modified image after the flood fill is complete.

## Time and Space Complexity
- **Time Complexity**: O(m * n), where `m` is the number of rows and `n` is the number of columns. In the worst case, we visit every pixel once (e.g., when the entire image is the same color).
- **Space Complexity**: O(m * n) in the worst case due to the recursion stack, which can go as deep as the number of pixels if the entire image is connected.

## Edge Cases
- Single pixel (`m = 1, n = 1`): Change the pixel if it differs from `newColor`.
- `newColor` same as starting pixel: Return unchanged image.
- Empty image: Not applicable due to constraints (`m, n >= 1`).
- Entire image same color: All pixels changed to `newColor`.
- No connected pixels: Only the starting pixel changes if its neighbors have different colors.
  
