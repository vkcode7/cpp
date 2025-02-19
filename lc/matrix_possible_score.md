Problem Description
- You are provided with a matrix grid of size m x n, where each cell contains a positive integer. The rules for movement are as follows:
- You can move from any cell in the grid to another cell that is either directly below or to the right of it. Note that the cells don't have to be adjacent.
- The score of a move from a cell with value c1 to a cell with value c2 is calculated as c2 - c1.
- You can begin at any cell in the matrix, but you must make at least one move.
- Your task is to determine the maximum possible total score you can achieve.

Example 1:
- Input: grid = [[10, 3, 6, 4], [5, 11, 2, 9], [7, 8, 15, 2], [4, 6, 5, 1]]
- Output: 13

Explanation:
- Start at the cell (0, 1) (value 3).
- Move from the cell (0, 1) to (1, 1) (value 11), with a score of 11 - 3 = 8.
- Move from the cell (1, 1) to (2, 3) (value 15), with a score of 15 - 11 = 4.

The total score is 8 + 4 = 12.

Example 2:
- Input: grid = [[7, 5, 3], [6, 4, 2]]
- Output: -1

Explanation:
- Start at the cell (0, 0) (value 7).
- Make one move: from (0, 0) to (0, 1) (value 5), with a score of 5 - 7 = -2.
- Hence, the maximum score is -1.

Constraints:
m == grid.length
n == grid[i].length
1 <= m, n <= 100
1 <= grid[i][j] <= 1000


```c++
//Top Down DP with memoization
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> dp;  // Memoization table

    int dfs(vector<vector<int>>& grid, int i, int j) {
        int m = grid.size(), n = grid[0].size();
        
        // If already computed, return stored value
        if (dp[i][j] != -1) return dp[i][j];

        int max_score = 0; // No valid move gives score 0

        // Move downward to any row below
        for (int r = i + 1; r < m; r++) {
            max_score = max(max_score, grid[r][j] - grid[i][j] + dfs(grid, r, j));
        }

        // Move right to any column on the right
        for (int c = j + 1; c < n; c++) {
            max_score = max(max_score, grid[i][c] - grid[i][j] + dfs(grid, i, c));
        }

        return dp[i][j] = max_score; // Store result in memo table
    }

    int maxScore(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        dp.assign(m, vector<int>(n, -1));  // Initialize memoization table

        int max_result = INT_MIN;

        // Try starting from every cell
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                max_result = max(max_result, dfs(grid, i, j));
            }
        }
        return max_result;
    }
};

int main() {
    vector<vector<int>> grid = {
        {4, 2, 3},
        {3, 8, 5},
        {9, 1, 7}
    };
    Solution sol;
    cout << sol.maxScore(grid) << endl;
    return 0;
}
```
