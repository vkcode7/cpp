
# 451. Sort Characters By Frequency - Hash Table, Sorting, Heap (Priority Queue), Bucket Sort, Counting

This document describes the solution to the "Sort Characters By Frequency" problem (LeetCode #451).

## Problem Description
Given a string `s`, sort it in decreasing order based on the frequency of the characters. The frequency of a character is the number of times it appears in the string. If two characters have the same frequency, their relative order in the output is not specified.

### Example
```
Input: s = "tree"
Output: "eert"
Explanation: 'e' appears twice, while 'r' and 't' appear once. Thus, "eert" is valid (as is "eetr").

Input: s = "cccaaa"
Output: "aaaccc"
Explanation: Both 'c' and 'a' appear three times, so "aaaccc" is valid (as is "cccaaa").

Input: s = "Aabb"
Output: "bbAa"
Explanation: 'b' appears twice, 'A' and 'a' appear once. Case is preserved.
```

### Constraints
- `1 <= s.length <= 5 * 10^5`
- `s` consists of uppercase and lowercase English letters and digits.

## Solution Approach
The problem can be solved using a frequency map and sorting, or a bucket sort approach for efficiency.

### Frequency Map and Sorting Approach
1. Count the frequency of each character using a hash map.
2. Create a list of character-frequency pairs and sort it by frequency in descending order.
3. Build the result string by repeating each character by its frequency.

### Example Implementation (C++)
```cpp
class Solution {
public:
    string frequencySort(string s) {
        string sorted = "";
        map<char,int> freq;
        for(auto c : s)
            freq[c]++;
        
        vector<vector<char>> vbucket(s.size()+1);
        
        for(auto it : freq)
            vbucket[it.second].push_back(it.first);    
        
        for(int i = vbucket.size()-1; i > 0; i--)
        {
            if(vbucket[i].size() == 0)
                continue;
            
            for(auto ch : vbucket[i]) {
                for(int j=0; j < i; j++)
                    sorted += ch;
            }
        }
        
        /*
        for(int i = 1; i < vbucket.size(); i++)
        {
            if(vbucket[i].size() == 0)
                continue;
            
            for(auto ch : vbucket[i]) {
                for(int j=0; j < i; j++)
                    sorted = ch + sorted;
            }
        }
        */
        return sorted;
    }
};
```

```cpp
class Solution {
public:
    string frequencySort(string s) {
        // Step 1: Count frequency of each character
        unordered_map<char, int> freq;
        for (char c : s) {
            freq[c]++;
        }
        
        // Step 2: Create vector of pairs and sort by frequency
        vector<pair<char, int>> freqVec(freq.begin(), freq.end());
        sort(freqVec.begin(), freqVec.end(), 
             [](const pair<char, int>& a, const pair<char, int>& b) {
                 return a.second > b.second;
             });
        
        // Step 3: Build result string
        string result = "";
        for (auto& p : freqVec) {
            result += string(p.second, p.first);
        }
        
        return result;
    }
};
```

### How It Works
- **Frequency Counting**: Use an `unordered_map` to count how many times each character appears.
- **Sorting**:
  - Convert the map to a vector of pairs `(character, frequency)`.
  - Sort the vector by frequency in descending order using a lambda function.
- **String Construction**: Iterate through the sorted vector, appending each character repeated by its frequency.
- **Edge Cases**:
  - Single character: Returns the character itself.
  - Characters with equal frequency: Order doesn’t matter, handled by sorting.
- **Result**: The string is sorted by character frequency, preserving character case.

### Time and Space Complexity
- **Time Complexity**: O(n + k log k), where `n` is the length of the string and `k` is the number of unique characters (up to 128 for ASCII). The sorting step dominates for small `n`.
- **Space Complexity**: O(k), for the hash map and vector of pairs, plus O(n) for the output string.

### Alternative Approach (Bucket Sort)
1. Count character frequencies using a hash map.
2. Group characters by frequency into buckets (max frequency is `n`).
3. Iterate through buckets in descending order, appending characters.
- **Time Complexity**: O(n), as bucket sort avoids comparison-based sorting.
- **Space Complexity**: O(n) for buckets and output.
The bucket sort approach is more efficient for large strings but slightly more complex to implement.


# 2262. Substring with Largest Variance - Dynamic Programming

This document describes the solution to the "Substring with Largest Variance" problem (LeetCode #2262).

## Problem Description
The variance of a string is defined as the largest difference between the number of occurrences of any two distinct characters in the string. Given a string `s`, return the largest variance possible among all substrings of `s`. A substring is a contiguous sequence of characters within `s`.

### Example
```
Input: s = "aababbb"
Output: 3
Explanation: The substring "babbb" has 3 'b's and 1 'a', so the variance is 3 - 1 = 2. Another substring "abbb" has 3 'b's and 0 'a', variance is 3 - 0 = 3 (after considering 'a' and 'b').

Input: s = "abcde"
Output: 0
Explanation: No two characters appear more than once in any substring, so the variance is 0.
```

### Constraints
- `1 <= s.length <= 10^5`
- `s` consists of lowercase English letters.

```py
Hint 1
Think about how to solve the problem if the string had only two distinct characters.
Hint 2
If we replace all occurrences of the first character by +1 and those of the second character by -1, can we efficiently calculate the largest possible variance of a string with only two distinct characters?
Hint 3
Now, try finding the optimal answer by taking all possible pairs of characters into consideration.
```

## Solution Approach
The problem can be solved by considering all pairs of distinct characters and using a Kadane-like algorithm to find the maximum variance for each pair in substrings.

### Modified Kadane’s Algorithm Approach
1. Iterate over all pairs of characters `(c1, c2)` (e.g., 'a' and 'b') in the string.
2. For each pair, convert the string into a sequence where:
   - `c1` is counted as `+1`.
   - `c2` is counted as `-1`.
   - Other characters are ignored.
3. Use a Kadane-like algorithm to find the maximum subarray sum (representing `count(c1) - count(c2)`), but with a constraint:
   - The substring must contain at least one `c2` (to ensure a valid variance).
4. Track the global maximum variance across all pairs.

### Example Implementation (C++)
```cpp
class Solution {
public:
    int largestVariance(string s) {
        int maxVariance = 0;
        unordered_set<char> unique(s.begin(), s.end());
        
        // Try all pairs of distinct characters
        for (char c1 : unique) {
            for (char c2 : unique) {
                if (c1 == c2) continue;
                
                // Kadane-like algorithm for c1 (+1) and c2 (-1)
                int currVariance = 0; // Current sum of +1/-1
                bool hasC2 = false;   // Tracks if c2 is in current substring
                bool hadC2 = false;   // Tracks if c2 was in a previous substring
                int firstC2 = 0;      // Tracks variance after first c2
                
                for (char c : s) {
                    if (c == c1) {
                        currVariance++;
                    } else if (c == c2) {
                        hasC2 = true;
                        hadC2 = true;
                        currVariance--;
                    }
                    
                    if (hasC2) {
                        // Valid substring with at least one c2
                        maxVariance = max(maxVariance, currVariance);
                    }
                    
                    if (currVariance < firstC2 && hadC2) {
                        // Reset to consider new substring with at least one c2
                        currVariance = firstC2;
                        hasC2 = false;
                    }
                }
            }
        }
        
        return maxVariance;
    }
};
```

### How It Works
- **Character Pairs**: Iterate over all pairs of distinct characters (up to 26 * 25 pairs for lowercase letters).
- **Sequence Conversion**: For each pair `(c1, c2)`, treat `c1` as `+1`, `c2` as `-1`, and ignore others.
- **Kadane-like Algorithm**:
  - Track `currVariance` (sum of `+1`/`-1` for the current substring).
  - Ensure the substring contains at least one `c2` (`hasC2`).
  - Use `hadC2` and `firstC2` to handle cases where a negative sum can be reset to include a prior `c2`.
- **Edge Cases**:
  - Single character type: Variance is 0 (no valid pair).
  - No `c2` in substring: Invalid for variance calculation.
- **Result**: The maximum variance is the largest `count(c1) - count(c2)` across all pairs and substrings.

### Time and Space Complexity
- **Time Complexity**: O(n * k^2), where `n` is the length of the string and `k` is the number of unique characters (up to 26 for lowercase letters). We process the string for each pair of characters.
- **Space Complexity**: O(k), for the set of unique characters.

### Alternative Approach
A brute-force approach checking all substrings and calculating variance for each is infeasible (O(n^2 * k)). The modified Kadane’s algorithm is optimal for the given constraints, balancing efficiency and correctness.



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


# 1. Two Sum - HashTable

This document describes the solution to the "Two Sum" problem (LeetCode #1).

## Problem Description
Given an array of integers `nums` and an integer `target`, return the indices of the two numbers such that they add up to `target`. You may assume that each input has exactly one solution, and you may not use the same element twice. The answer can be returned in any order.

### Example
```
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: nums[0] + nums[1] = 2 + 7 = 9.

Input: nums = [3,2,4], target = 6
Output: [1,2]
Explanation: nums[1] + nums[2] = 2 + 4 = 6.

Input: nums = [3,3], target = 6
Output: [0,1]
Explanation: nums[0] + nums[1] = 3 + 3 = 6.
```

### Constraints
- `2 <= nums.length <= 10^4`
- `-10^9 <= nums[i] <= 10^9`
- `-10^9 <= target <= 10^9`
- Only one valid answer exists.

## Solution Approach
The problem can be solved efficiently using a hash map to store numbers and their indices, allowing for O(1) lookups.

### Hash Map Approach
1. Create an empty hash map to store numbers as keys and their indices as values.
2. Iterate through the array:
   - For each number `nums[i]`, compute the complement (`target - nums[i]`).
   - If the complement exists in the hash map, return the current index `i` and the complement's index.
   - Otherwise, add `nums[i]` and its index `i` to the hash map.
3. Since exactly one solution exists, the loop will find it.

### Example Implementation (C++)
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> numMap; // {number, index}
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            if (numMap.find(complement) != numMap.end()) {
                return {numMap[complement], i};
            }
            numMap[nums[i]] = i;
        }
        return {}; // Unreachable given problem constraints
    }
};
```

### How It Works
- **Hash Map**: Stores each number and its index as we iterate.
- **Lookup**: For each `nums[i]`, check if `target - nums[i]` is in the map.
  - If found, return the stored index and current index.
  - If not, add `nums[i]` and `i` to the map.
- **Edge Cases**:
  - The problem guarantees exactly one solution, so no need to handle cases with no solution or multiple solutions.
  - Duplicate numbers (e.g., `[3,3]`) are handled since we check the complement before adding the current number.
- **Result**: Returns the indices of the two numbers that sum to `target`.

### Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the array, as we traverse the array once with O(1) hash map operations (average case).
- **Space Complexity**: O(n), for storing up to `n` elements in the hash map.

### Alternative Approach
1. **Brute Force**:
   - Check every pair of numbers using nested loops.
   - Time Complexity: O(n²)
   - Space Complexity: O(1)
The hash map approach is preferred due to its linear time complexity.



# 1431. Kids With the Greatest Number of Candies

This document describes the solution to the "Kids With the Greatest Number of Candies" problem (LeetCode #1431).

## Problem Description
Given an array `candies` where `candies[i]` represents the number of candies the `i`-th kid has, and an integer `extraCandies`, determine whether each kid can have the greatest number of candies among all kids by giving them all the `extraCandies`. Return a boolean array `result` of length `n`, where `result[i]` is `true` if, after giving the `i`-th kid all the extra candies, they will have the greatest number of candies, and `false` otherwise. Multiple kids can have the greatest number of candies.

### Example
```
Input: candies = [2,3,5,1,3], extraCandies = 3
Output: [true,true,true,false,true]
Explanation: 
- Kid 0: 2 + 3 = 5 (equal to max, true)
- Kid 1: 3 + 3 = 6 (greater than max, true)
- Kid 2: 5 + 3 = 8 (greater than max, true)
- Kid 3: 1 + 3 = 4 (less than max, false)
- Kid 4: 3 + 3 = 6 (greater than max, true)

Input: candies = [4,2,1,1,2], extraCandies = 1
Output: [true,false,false,false,false]
Explanation: Max candies is 4. Only kid 0 (4 + 1 = 5) can reach or exceed it.

Input: candies = [12,1,12], extraCandies = 10
Output: [true,false,true]
Explanation: Kids 0 and 2 can reach 22 candies, but kid 1 can only reach 11.
```

### Constraints
- `n == candies.length`
- `2 <= n <= 100`
- `1 <= candies[i] <= 100`
- `1 <= extraCandies <= 50`

## Solution Approach
The problem can be solved by finding the maximum number of candies any kid has and checking if each kid can reach or exceed this maximum by adding `extraCandies`.

### Linear Scan Approach
1. Find the maximum number of candies in the `candies` array.
2. Iterate through the `candies` array:
   - For each kid, check if `candies[i] + extraCandies` is greater than or equal to the maximum.
   - Store `true` in the result array if the condition is met, `false` otherwise.
3. Return the result array.

### Example Implementation (C++)
```cpp
class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        if(candies.size() == 0)
            return vector<bool>();
            
        auto mx = INT_MIN;
        for(auto x: candies)
            mx = max(mx, x);

        vector<bool> result;
        result.reserve(candies.size());

        for(auto x: candies)
            if(x + extraCandies >= mx)
                result.push_back(true);
            else 
                result.push_back(false);

        return result;
    }
};
```

```cpp
class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        int maxCandies = *max_element(candies.begin(), candies.end());
        vector<bool> result(candies.size());
        
        for (int i = 0; i < candies.size(); i++) {
            result[i] = (candies[i] + extraCandies >= maxCandies);
        }
        
        return result;
    }
};
```

### How It Works
- **Find Maximum**: Use `max_element` to find the highest number of candies any kid has.
- **Check Each Kid**: For each kid, compute `candies[i] + extraCandies` and compare it to `maxCandies`.
  - If greater than or equal, set `result[i]` to `true` (they can have the greatest number of candies).
  - Otherwise, set `result[i]` to `false`.
- **Edge Cases**:
  - All kids have the same candies: All may become `true` if `extraCandies` is sufficient.
  - Small arrays (e.g., length 2): Handled naturally by the loop.
- **Result**: The boolean array indicates which kids can have the greatest number of candies.

### Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the `candies` array, as we scan the array twice (once for max, once for comparison).
- **Space Complexity**: O(n), for the output `result` array. (Excluding the output, it’s O(1).)

### Alternative Approach
1. **Manual Max Calculation**:
   - Iterate through the array once to find the maximum instead of using `max_element`.
   - Time Complexity: O(n)
   - Space Complexity: O(n) for output
The `max_element` approach is concise and equally efficient, making it preferable for clarity.




# 42. Trapping Rain Water - Two Pointers, Dynamic Programming, Stack, Monotonic Stack

This document describes the solution to the "Trapping Rain Water" problem (LeetCode #42).

## Problem Description
Given `n` non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining. The elevation map is represented by an array `height` where `height[i]` is the height of the bar at index `i`.

### Example
```
Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: Water is trapped at indices 2, 4, 5, 6, 9, and 10, totaling 6 units.

Input: height = [4,2,0,3,2,5]
Output: 9
Explanation: Water is trapped at indices 1, 2, 3, and 4, totaling 9 units.
```
<img src="../assets/rainwatertrap.png" width="30%">

### Constraints
- `n == height.length`
- `1 <= n <= 2 * 10^4`
- `0 <= height[i] <= 10^5`

## Solution Approach
The problem can be solved efficiently using a two-pointer technique to calculate the water trapped at each index by determining the minimum of the maximum heights on both sides.

### Two-Pointer Approach
1. Initialize two pointers: `left` at the start (0) and `right` at the end (`n-1`).
2. Maintain two variables: `leftMax` (maximum height on the left) and `rightMax` (maximum height on the right).
3. While `left < right`:
   - If `height[left] < height[right]`:
     - Update `leftMax` with `max(leftMax, height[left])`.
     - Add trapped water at `left` as `leftMax - height[left]`.
     - Move `left` right.
   - Else:
     - Update `rightMax` with `max(rightMax, height[right])`.
     - Add trapped water at `right` as `rightMax - height[right]`.
     - Move `right` left.
4. Return the total water trapped.

### Example Implementation (C++)
```cpp
class Solution {
public:
    int trap(vector<int>& height)
    {
        if(height.empty())
            return 0;
        int ans = 0;
        int size = height.size();
        vector<int> left_max(size), right_max(size);
        
        //[0,1,0,2,1,0,1,3,2,1,2,1]
        left_max[0] = height[0];
        right_max[size-1] = height[size-1];
        cout << right_max[size-1]<<endl;
        
        for (int i = 1; i < size; i++) {
            left_max[i] = max(height[i], left_max[i - 1]);
            right_max[size - (i+1)] = max(right_max[size-i], height[size - (i+1)]);
        }
        
        for (int i = 0; i < size; i++) {
            ans += min(left_max[i], right_max[i]) - height[i];
        }
        
        return ans;
    }
};
```

# 79. Word Search - Backtracking, Depth-First Search, Matrix

This document describes the solution to the "Word Search" problem (LeetCode #79).

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




# 394. Decode String - Stack, Recursion

This document describes the solution to the "Decode String" problem (LeetCode #394).

## Problem Description
Given an encoded string, return its decoded string. The encoding rule is: `k[encoded_string]`, where the `encoded_string` inside the square brackets is repeated exactly `k` times. `k` is a positive integer. The input string is guaranteed to be valid, with no extra white spaces, well-formed square brackets, and no digits in the original decoded string.

### Example
```
Input: s = "3[a]2[bc]"
Output: "aaabcbc"
Explanation: Decode "3[a]" to "aaa" and "2[bc]" to "bcbc", resulting in "aaabcbc".

Input: s = "3[a2[c]]"
Output: "accaccacc"
Explanation: First decode "2[c]" to "cc", then "3[a2[c]]" becomes "3[acc]" which decodes to "accaccacc".

Input: s = "2[abc]3[cd]ef"
Output: "abcabccdcdcdef"
Explanation: Decode "2[abc]" to "abcabc", "3[cd]" to "cdcdcd", then append "ef".
```

### Constraints
- `1 <= s.length <= 30`
- `s` consists of lowercase English letters, digits, and square brackets `[]`.
- `s` is guaranteed to be a valid input.
- All integers in `s` are in the range `[1, 300]`.

## Solution Approach
The problem can be solved using a stack-based approach to handle nested brackets and repetitions.

### Stack-Based Approach
1. Use two stacks:
   - One for counts (to store the number of repetitions).
   - One for strings (to store intermediate decoded strings).
2. Iterate through the input string:
   - If a digit is encountered, build the number (may be multi-digit).
   - If an opening bracket `[` is encountered, push the current number and current string onto their respective stacks, then reset them.
   - If a letter is encountered, append it to the current string.
   - If a closing bracket `]` is encountered:
     - Pop the string and count from the stacks.
     - Repeat the current string `count` times and append it to the popped string.
     - Update the current string with the result.
3. Return the final decoded string.

### Example Implementation (C++)
```cpp
class Solution {
public:
    string decodeString(string s) {
        stack<char> st;
        
        string enc;
        for(auto x : s)
        {
            if(x == ']')
            {
                string sub = "";
                while(st.top()!='[')
                {
                    sub += st.top();
                    st.pop();
                }  
                st.pop(); //throw the '['
                
                //get the number now
                int tens = 1;
                int num = 0;
                while(!st.empty() && isdigit(st.top()))
                {
                    char dig = st.top();
                    num = num + (tens * (dig - '0'));
                    tens = tens * 10;
                    st.pop();
                }
                //now dump it back in stack
                string encsub = "";
                //reverse sub
                string revsub = "";
                 for(int j = sub.length()-1; j >= 0; j--)
                    revsub += sub[j];
                for(int i = 0; i < num; i++)
                {
                    encsub += revsub;
                }
                
                for(auto y: encsub)
                    st.push(y);
            }
            else
                st.push(x);   
        }
                
        while(!st.empty())
        {
            enc += st.top();
            st.pop();  
        }  
        string revenc = "";
        for(int j = enc.length()-1; j >= 0; j--)
            revenc += enc[j];
            
        return revenc;
    }
};
```

```cpp
class Solution {
public:
    string decodeString(string s) {
        stack<int> countStack;
        stack<string> stringStack;
        string currString = "";
        int currCount = 0;
        
        for (char c : s) {
            if (isdigit(c)) {
                currCount = currCount * 10 + (c - '0'); // Build multi-digit number
            } else if (c == '[') {
                countStack.push(currCount);
                stringStack.push(currString);
                currCount = 0;
                currString = "";
            } else if (c == ']') {
                string temp = currString;
                currString = stringStack.top();
                stringStack.pop();
                int count = countStack.top();
                countStack.pop();
                for (int i = 0; i < count; i++) {
                    currString += temp;
                }
            } else {
                currString += c; // Append letter to current string
            }
        }
        
        return currString;
    }
};
```

### How It Works
- **Stacks**:
  - `countStack`: Stores the repetition counts for each bracket.
  - `stringStack`: Stores the partially decoded strings before entering a new bracket.
- **Processing**:
  - Digits: Accumulate to form multi-digit numbers (e.g., "10" as 10).
  - `[`: Save the current state (count and string) and reset for the new nested section.
  - Letters: Append to the current string.
  - `]`: Pop the count and previous string, repeat the current string, and append to the previous string.
- **Edge Cases**:
  - Nested brackets: Handled by the stack, which preserves the hierarchy.
  - No brackets: Treated as a simple string.
  - Multi-digit numbers: Built correctly by multiplying by 10.
- **Result**: The final `currString` is the fully decoded string.

### Time and Space Complexity
- **Time Complexity**: O(n * maxK), where `n` is the length of the input string and `maxK` is the maximum repetition count (up to 300). Each character is processed once, but string repetition may amplify the output size.
- **Space Complexity**: O(m), where `m` is the maximum nesting level of brackets, for the stacks. The output string is not counted in space complexity.

### Alternative Approach
1. **Recursive DFS**:
   - Parse the string recursively, treating each bracketed section as a subproblem.
   - Time Complexity: O(n * maxK)
   - Space Complexity: O(m) for the recursion stack
The stack-based approach is preferred for its iterative nature and clarity in handling nested structures.




# 9. Palindrome Number

This document describes the solution to the "Palindrome Number" problem (LeetCode #9).

## Problem Description
Given an integer `x`, return `true` if `x` is a palindrome, and `false` otherwise. An integer is a palindrome if it reads the same forward and backward.

### Example
```
Input: x = 121
Output: true
Explanation: 121 reads the same forward and backward.

Input: x = -121
Output: false
Explanation: -121 is not a palindrome as it reads 121- backward.

Input: x = 10
Output: false
Explanation: 10 reads as 01 backward, which is not the same.

Hint: Beware of overflow when you reverse the integer.
```

### Constraints
- `-2^31 <= x <= 2^31 - 1`

## Solution Approach
The problem can be solved by reversing the integer and comparing it with the original number, while handling edge cases like negative numbers and potential overflow.

### Reverse Integer Approach
1. If the number is negative, return `false` (negative numbers cannot be palindromes due to the sign).
2. Initialize a variable to store the reversed number.
3. While the input number is not zero:
   - Extract the last digit using modulo (`x % 10`).
   - Append the digit to the reversed number by multiplying the current reversed number by 10 and adding the digit.
   - Remove the last digit from the input number by integer division (`x / 10`).
4. Compare the reversed number with the original number to determine if it’s a palindrome.

### Example Implementation (C++)
```cpp
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0 || (x % 10 == 0 && x != 0)) return false;
        int rev = 0;
        while (rev < x) {
            rev = rev * 10 + x % 10;
            x /= 10;
            cout << rev<<endl;
        }
        
        return x == rev || x == rev / 10;
    }
};
``

```cpp
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        }
        
        long long reversed = 0; // Use long long to handle potential overflow
        int original = x;
        
        while (x > 0) {
            int digit = x % 10;
            reversed = reversed * 10 + digit;
            x /= 10;
        }
        
        return reversed == original;
    }
};
```

### How It Works
- **Negative Check**: Negative numbers are not palindromes due to the leading minus sign.
- **Reversal**:
  - Extract digits from the end using modulo.
  - Build the reversed number by shifting digits left (multiplying by 10) and adding the new digit.
- **Comparison**: Check if the reversed number equals the original.
- **Edge Cases**:
  - Zero: Is a palindrome (handled correctly).
  - Large numbers: Use `long long` for `reversed` to prevent overflow.
  - Single digit: Always a palindrome (e.g., 5).
- **Result**: Returns `true` if the number is a palindrome, `false` otherwise.

### Time and Space Complexity
- **Time Complexity**: O(log x), where `x` is the input number, as we process each digit (number of digits is proportional to log x base 10).
- **Space Complexity**: O(1), as we only use a constant amount of extra space (excluding the input).

### Alternative Approach
1. **Convert to String**:
   - Convert the integer to a string and check if it reads the same forward and backward.
   - Time Complexity: O(log x) for conversion, O(log x) for comparison
   - Space Complexity: O(log x) for the string
The reverse integer approach is preferred as it avoids string conversion and uses constant space.

https://leetcode.com/submissions/#/3
