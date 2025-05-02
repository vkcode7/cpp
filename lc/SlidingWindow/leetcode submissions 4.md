# 443. String Compression - Two Pointers

This document describes the solution to the "String Compression" problem (LeetCode #443).

## Problem Description
Given an array of characters `chars`, compress it using the following algorithm:
- For each group of consecutive repeating characters:
  - If the group's length is 1, append the character to the result.
  - Otherwise, append the character followed by the group's length.
- The compressed string is stored in the input `chars` array, and the new length of the array is returned.
- The solution must be in-place, and only the first `new length` elements of `chars` are considered after compression.

### Example
```
Input: chars = ["a","a","b","b","c","c","c"]
Output: 6, chars = ["a","2","b","2","c","3"]
Explanation: "aa" is compressed to "a2", "bb" to "b2", and "ccc" to "c3". The new length is 6.

Input: chars = ["a"]
Output: 1, chars = ["a"]
Explanation: Single character remains unchanged.

Input: chars = ["a","b","b","b","b","b","b","b","b","b","b","b","b"]
Output: 4, chars = ["a","b","1","2"]
Explanation: "a" remains "a", "bbbbbbbbbbbb" is compressed to "b12". The new length is 4.
```

### Constraints
- `1 <= chars.length <= 2000`
- `chars[i]` is a lowercase English letter, uppercase English letter, digit, or symbol.

## Solution Approach
The problem can be solved by iterating through the array, counting consecutive repeating characters, and writing the compressed result in-place.

### Two-Pointer Approach
1. Use a pointer `write` to track the position where the next character or count should be written.
2. Iterate through the array with a pointer `read`:
   - Count consecutive occurrences of the same character.
   - Write the character at the `write` position.
   - If the count is greater than 1, convert the count to a string and write its digits.
3. Return the final `write` position as the new length.

### Example Implementation (C++)
```cpp
class Solution {
public:
    int compress(vector<char>& chars) {
        queue<char> q;
        
        if(chars.size() <= 1)
            return chars.size();
        
        for(int i = 0; i < chars.size(); i++)
        {
            int count = 1;
            
            q.push(chars[i]);
            while(i+1 < chars.size() && chars[i] == chars[i+1]) {
                count++;
                i++;
            }
            
            if(count > 1)
            {
                string scount = to_string(count);
                for(auto c: scount)
                    q.push(c);
            }  
        }
        
        chars.clear();
        while(!q.empty())
        {
            chars.push_back(q.front());
            q.pop();
        }
        
        return chars.size();
    }
};
```

```cpp
class Solution {
public:
    int compress(vector<char>& chars) {
        int write = 0; // Position to write the compressed result
        int read = 0;  // Position to read the input
        
        while (read < chars.size()) {
            char currentChar = chars[read];
            int count = 0;
            
            // Count consecutive occurrences
            while (read < chars.size() && chars[read] == currentChar) {
                count++;
                read++;
            }
            
            // Write the character
            chars[write++] = currentChar;
            
            // Write the count if greater than 1
            if (count > 1) {
                string countStr = to_string(count);
                for (char c : countStr) {
                    chars[write++] = c;
                }
            }
        }
        
        return write;
    }
};
```

### How It Works
- **Pointers**:
  - `write`: Tracks where to place the next character or digit in the compressed array.
  - `read`: Scans the array to count consecutive characters.
- **Compression**:
  - For each group of identical characters, count their occurrences.
  - Write the character once.
  - If the count is greater than 1, convert the count to a string and write each digit.
- **In-Place**:
  - Overwrite the original array starting at `write`, ensuring the compressed result fits within the first `write` positions.
- **Edge Cases**:
  - Single character: Written as is, length 1.
  - All same characters: Compressed to one character plus count digits (e.g., "aaaaa" to "a5").
  - No consecutive repeats: Each character written once, length unchanged.
- **Result**: The array is modified in-place, and the new length (`write`) is returned.

### Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of `chars`, as we traverse the array once and handle counts in linear time.
- **Space Complexity**: O(1), excluding the output array modification, as we only use a constant amount of extra space (temporary string for counts is small and bounded).

### Alternative Approach
1. **Two-Pass with Extra Space**:
   - First pass: Compute the compressed string in a temporary array.
   - Second pass: Copy back to the input array.
   - Time Complexity: O(n)
   - Space Complexity: O(n)
  The in-place approach is preferred as it meets the problem’s requirement for in-place modification and minimizes space usage.


# 387. First Unique Character in a String - Hash Table, Queue


This document describes the solution to the "First Unique Character in a String" problem (LeetCode #387).

## Problem Description
Given a string `s`, find the first non-repeating character in it and return its index. If no such character exists, return `-1`.

### Example
```
Input: s = "leetcode"
Output: 0
Explanation: The first unique character is 'l' at index 0.

Input: s = "loveleetcode"
Output: 2
Explanation: The first unique character is 'v' at index 2.

Input: s = "aabb"
Output: -1
Explanation: No character appears exactly once.
```

### Constraints
- `1 <= s.length <= 10^5`
- `s` consists of only lowercase English letters.

## Solution Approach
The problem can be solved using a frequency map to count character occurrences, followed by a second pass to find the first character with a count of 1.

### Two-Pass Frequency Map Approach
1. Create a frequency map to count the occurrences of each character in the string.
2. Iterate through the string again to find the first character whose frequency is 1.
3. Return the index of that character, or `-1` if no such character exists.

### Example Implementation (C++)
```cpp
class Solution {
public:
    int firstUniqChar(string s) {
        if(s.empty())
            return -1;
        
        unordered_map<char, int> unique;
        int index = 0;
        for(auto x : s)
        {
            if(unique.find(x) != unique.end())
                unique[x] = -1;
            else
                unique[x] = index;
            
            index++;
        }
        
        index = s.size();
        for(auto it : unique)
        {
            if(it.second == -1)
                continue;
            
            index = min(index, it.second);
        }
        
        return index == s.size() ? -1 : index;
    }
};
```

```cpp
class Solution {
public:
    int firstUniqChar(string s) {
        // Frequency map for lowercase letters
        vector<int> freq(26, 0);
        
        // Count occurrences of each character
        for (char c : s) {
            freq[c - 'a']++;
        }
        
        // Find first character with frequency 1
        for (int i = 0; i < s.length(); i++) {
            if (freq[s[i] - 'a'] == 1) {
                return i;
            }
        }
        
        return -1;
    }
};
```

### How It Works
- **Frequency Map**:
  - Use a vector of size 26 (for lowercase letters) to store the count of each character.
  - Iterate through the string and increment the count for each character (`c - 'a'` maps 'a' to  créditos: 0, 'b' to 1, etc.).
- **Second Pass**:
  - Iterate through the string and check the frequency of each character.
  - Return the index of the first character with a frequency of 1.
- **Edge Cases**:
  - Single character: Returns 0 (frequency is 1).
  - No unique character: Returns -1 (e.g., "aabb").
  - Long string: Vector handles up to 10^5 characters efficiently.
- **Result**: Returns the index of the first unique character or -1 if none exists.

### Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the string, as we perform two passes through the string.
- **Space Complexity**: O(1), as the frequency vector has a fixed size of 26 (constant for lowercase letters).

### Alternative Approach
1. **Hash Map with Indices**:
   - Use a hash map to store character frequencies and their first indices.
   - Iterate through the string once to populate the map.
   - Find the smallest index of a character with frequency 1.
   - Time Complexity: O(n)
   - Space Complexity: O(k), where `k` is the number of unique characters (up to 26).
The vector-based approach is preferred for its simplicity and guaranteed O(1) space due to the fixed alphabet size.


# 273. Integer to English Words

This document describes the solution to the "Integer to English Words" problem (LeetCode #273).

## Problem Description
Convert a non-negative integer `num` to its English words representation.

### Example
```
Input: num = 123
Output: "One Hundred Twenty Three"
Explanation: 123 is written as "One Hundred" for 100, "Twenty" for 20, and "Three" for 3.

Input: num = 12345
Output: "Twelve Thousand Three Hundred Forty Five"
Explanation: 12345 is broken into groups: 12 (Twelve Thousand), 345 (Three Hundred Forty Five).

Input: num = 1234567
Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
Explanation: 1234567 is broken into groups: 1 (One Million), 234 (Two Hundred Thirty Four Thousand), 567 (Five Hundred Sixty Seven).

Input: num = 0
Output: "Zero"
Explanation: 0 is simply "Zero".
```

### Constraints
- `0 <= num <= 2^31 - 1`

## Solution Approach
The problem can be solved by processing the number in groups of three digits (thousands, millions, billions) and converting each group to words using predefined mappings for numbers 1-19, tens, and larger units.

### Group-by-Three Approach
1. Define arrays for:
   - Numbers 1-19 (e.g., "One", "Two", ..., "Nineteen").
   - Tens (e.g., "Twenty", "Thirty", ..., "Ninety").
   - Large units (e.g., "Thousand", "Million", "Billion").
2. Handle the special case of `num = 0` by returning "Zero".
3. Process the number in groups of three digits from right to left:
   - Extract the last three digits using modulo (`num % 1000`).
   - Convert the three-digit number to words (hundreds, tens, ones).
   - Append the appropriate unit (Thousand, Million, Billion) based on the group position.
   - Divide `num` by 1000 to process the next group.
4. Combine the words for each group, ensuring proper spacing and trimming.

### Example Implementation (C++)
```cpp
class Solution {
public:
    vector<string> below20 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    
    vector<string> tens = {"", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety", "Hundred"};
    
    string convert(int n)
    {
        if(n >= 1000000000)
            return convert(n / 1000000000) + " Billion" + convert(n % 1000000000);
        
        if(n >= 1000000)
            return convert(n / 1000000) + " Million" + convert(n % 1000000);

        if(n >= 1000)
            return convert(n / 1000) + " Thousand" + convert(n % 1000);

        if(n >= 100)
            return convert(n / 100) + " Hundred" + convert(n % 100);

        if(n >= 20)
            return " " + tens[n/10] + convert(n % 10);
        
        if(n >= 1)
            return " " + below20[n];
            
        return "";
    }
    
    string numberToWords(int num) {
        if(num == 0)
            return "Zero";
        return convert(num).substr(1);
    }
};
```

```cpp
class Solution {
public:
    string numberToWords(int num) {
        if (num == 0) return "Zero";
        
        // Define word mappings
        vector<string> below20 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", 
                                 "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", 
                                 "Seventeen", "Eighteen", "Nineteen"};
        vector<string> tens = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
        vector<string> thousands = {"", "Thousand", "Million", "Billion"};
        
        string result = "";
        int groupIndex = 0;
        
        while (num > 0) {
            int threeDigits = num % 1000;
            if (threeDigits > 0) {
                string group = convertThreeDigits(threeDigits, below20, tens);
                if (!group.empty()) {
                    if (!result.empty()) result = " " + result;
                    result = group + (thousands[groupIndex].empty() ? "" : " " + thousands[groupIndex]) + result;
                }
            }
            num /= 1000;
            groupIndex++;
        }
        
        return result;
    }
    
private:
    string convertThreeDigits(int num, const vector<string>& below20, const vector<string>& tens) {
        string result = "";
        
        // Handle hundreds
        if (num >= 100) {
            result += below20[num / 100] + " Hundred";
            num %= 100;
            if (num > 0) result += " ";
        }
        
        // Handle tens and ones
        if (num >= 20) {
            result += tens[num / 10];
            num %= 10;
            if (num > 0) result += " " + below20[num];
        } else if (num > 0) {
            result += below20[num];
        }
        
        return result;
    }
};
```

### How It Works
- **Zero Case**: If `num = 0`, return "Zero" directly.
- **Group Processing**:
  - Extract three digits at a time (`num % 1000`).
  - Convert the three-digit number to words using `convertThreeDigits`:
    - Hundreds: Add the word for `num / 100` followed by "Hundred".
    - Tens and Ones: If `num >= 20`, add the tens word and optionally the ones word; otherwise, use the `below20` word.
  - Append the appropriate unit (Thousand, Million, Billion) based on the group index.
- **Combining**:
  - Prepend each group’s words to the result, adding spaces as needed.
  - Skip empty groups (e.g., 1000 has no words for the last three digits).
- **Edge Cases**:
  - Single digit: Handled by `below20` in `convertThreeDigits`.
  - Numbers like 100: Only "One Hundred" is added.
  - Large numbers: Processed group by group up to billions.
- **Result**: Returns the English words representation of the number.

### Time and Space Complexity
- **Time Complexity**: O(log n), where `n` is the input number, as we process up to 4 groups of three digits (since `n <= 2^31 - 1` has at most 10 digits).
- **Space Complexity**: O(1), as the storage for word mappings and the result string is bounded by a constant (output string excluded).

### Alternative Approach
1. **Recursive**:
   - Recursively break the number into groups and convert each group.
   - Time Complexity: O(log n)
   - Space Complexity: O(log n) due to recursion stack.
The iterative approach is preferred for its simplicity and constant space usage, avoiding recursion while clearly handling each group.




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





