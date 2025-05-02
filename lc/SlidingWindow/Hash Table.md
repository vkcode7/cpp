# 409. Longest Palindrome Solution

## Problem Description
Given a string `s` which consists of lowercase or uppercase letters, return the length of the longest palindrome that can be built with those letters. Letters are case-sensitive (e.g., `'Aa'` is not considered a palindrome).

### Example
```
Input: s = "abccccdd"
Output: 7
Explanation: One longest palindrome that can be built is "dccaccd", which has length 7.
```

## Solution
Below is the C++ solution to find the length of the longest palindrome that can be built from the given string.

```cpp
class Solution {
public:
    int longestPalindrome(string s) {
        map<char, int> chars;
        for(auto x: s)
        {
            chars[x]++;
        }
        
        char odd = '\0';    
        int total = 0;
        
        for(auto it = chars.begin(); it != chars.end(); it++) {
            if(it->second %2 == 1) {
                odd = it->first;
                it->second -= 1;
            }
            
            total += it->second;
        }
        
        if(odd != '\0')
            total++;
        
        return total;
    }
};

class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int> charCount;
        
        // Count frequency of each character
        for (char c : s) {
            charCount[c]++;
        }
        
        int length = 0;
        bool hasOdd = false;
        
        // Calculate palindrome length
        for (const auto& pair : charCount) {
            int count = pair.second;
            length += (count / 2) * 2; // Add even count of characters
            if (count % 2 == 1) {
                hasOdd = true; // Track if there's any character with odd count
            }
        }
        
        // Add 1 to length if there is any character with odd count (for center)
        if (hasOdd) {
            length += 1;
        }
        
        return length;
    }
};
```

## Explanation
1. **Character Frequency**:
   - Use a hash map (`charCount`) to count the frequency of each character in the string `s`.
2. **Palindrome Construction**:
   - For a palindrome, characters must be paired (except possibly one character in the center for odd-length palindromes).
   - For each character count:
     - Add the largest even number of occurrences (`(count / 2) * 2`) to the palindrome length, as these can form symmetric pairs.
     - Track if there is any character with an odd count (`hasOdd`), indicating a potential center character.
3. **Odd Count Handling**:
   - If any character has an odd count (`hasOdd = true`), add 1 to the length to account for placing one such character in the center of the palindrome.
4. **Return**:
   - Return the computed length of the longest palindrome.

## Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the string. We iterate through the string once to build the hash map and once through the hash map (which has at most 52 entries for uppercase and lowercase letters).
- **Space Complexity**: O(1), since the hash map stores at most 52 characters (26 lowercase + 26 uppercase), which is constant.

## Edge Cases
- Empty string: Return 0.
- Single character: Return 1 (e.g., `"a"`).
- All same characters: Return the string length (e.g., `"aaaa"` returns 4).
- No pairs possible: Return 1 if string has distinct characters (e.g., `"abc"` returns 1).
- Case sensitivity: `"Aa"` treats `'A'` and `'a'` as different, so returns 2.


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



## 217. Contains Duplicate - Array, Hash Table, Sorting

This document describes the solution to the "Contains Duplicate" problem from LeetCode.

## Problem Description
Given an integer array `nums`, return `true` if any value appears at least twice in the array, and return `false` if every element is distinct.

### Example
```
Input: nums = [1,2,3,1]
Output: true
Explanation: The element 1 appears twice.

Input: nums = [1,2,3,4]
Output: false
Explanation: All elements are distinct.

Input: nums = [1,1,1,3,3,4,3,2,4,2]
Output: true
Explanation: Multiple elements (1, 2, 3, 4) appear more than once.
```

### Constraints
- `1 <= nums.length <= 10^5`
- `-10^9 <= nums[i] <= 10^9`

```c++
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
    sort(nums.begin(),nums.end());
        int i=0;
        while(i<nums.size()-1){
            if((nums[i]^nums[i+1])==0){
                return true;
                break;
            }
            else{
                i++;
            }
        }
        return false;
    }
};
```

## Solution Approach
The most efficient way to check for duplicates is to use a hash set to track seen elements.

### Hash Set Approach
1. Create an empty hash set to store encountered numbers.
2. Iterate through the array:
   - If the current number is already in the set, return `true` (duplicate found).
   - Otherwise, add the number to the set.
3. If the loop completes without finding a duplicate, return `false`.

### Example Implementation (C++)
```cpp
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> seen;
        for (int num : nums) {
            if (seen.count(num) > 0) {
                return true;
            }
            seen.insert(num);
        }
        return false;
    }
};
```

### How It Works
- **Hash Set**: The `unordered_set` provides O(1) average-case time complexity for lookups and insertions.
- **Iteration**: For each element, check if it exists in the set. If it does, a duplicate is found. If not, add it to the set.
- **Edge Case**: The array is guaranteed to have at least one element, so no additional checks are needed for empty arrays.

### Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the array, as we traverse the array once.
- **Space Complexity**: O(n), as the hash set may store up to `n` elements in the worst case (no duplicates).

### Alternative Approaches
1. **Sorting**:
   - Sort the array and check adjacent elements for equality.
   - Time Complexity: O(n log n)
   - Space Complexity: O(1) (if sorting in-place)
2. **Brute Force**:
   - Compare each element with every other element.
   - Time Complexity: O(n²)
   - Space Complexity: O(1)
The hash set approach is preferred due to its optimal time complexity.



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




