# 14 LeetCode Patterns to Master Coding Interviews

This README summarizes the 14 essential LeetCode patterns for solving coding interview questions efficiently, as described in the article ["14 LeetCode Patterns to Solve Any Question"](https://medium.com/@shubhamkumarcode/14-leetcode-patterns-to-solve-any-question-1dcdcc650bfa). These patterns provide generalized strategies to tackle a wide range of problems, reducing the need to memorize hundreds of individual solutions. Each pattern is outlined below with its use case, benefits, and example LeetCode problems.

## Table of Contents
1. [Sliding Window](#sliding-window)
2. [Two Pointers](#two-pointers)
3. [Fast & Slow Pointers](#fast--slow-pointers)
4. [Binary Search](#binary-search)
5. [Depth First Search (DFS)](#depth-first-search-dfs)
6. [Breadth First Search (BFS)](#breadth-first-search-bfs)
7. [Backtracking](#backtracking)
8. [Dynamic Programming](#dynamic-programming)
9. [Topological Sort](#topological-sort)
10. [Union Find](#union-find)
11. [Trie](#trie)
12. [Bit Manipulation](#bit-manipulation)
13. [Greedy](#greedy)
14. [Intervals](#intervals)

## Sliding Window
**Use Case**: Find subarrays or substrings that satisfy a specific condition, such as the maximum sum of a subarray of size k or the longest substring without repeating characters.  
**Benefit**: Reduces time complexity from O(n²) to O(n) by maintaining a dynamic window that expands or shrinks based on conditions.  
**Example Problems**:  
- Maximum Average Subarray I (LeetCode #643)  
- Longest Substring Without Repeating Characters (LeetCode #3)  
- Minimum Window Substring (LeetCode #76)

**Technique: **In the sliding window, you have 2 pointers, i and j. Move j as far as you can until your condition is no longer valid, then move the i pointer closer to j until the condition is valid again to shrink the window. At every iteration, keep track of the min/max length of the subarray for the result. Without the sliding window technique, we would need to use a double for loop resulting in O(N²) time. The sliding window is O(N) time complexity.

### Dynamic Sliding Window
In the dynamic sliding window, the size of the window (subarray between i and j) changes throughout the algorithm. In this example, we scan the subarray “bacb” and find that we have a duplicate “b”, so we will move the i pointer to shrink the window and move on to letter “a”, resulting in “acb”, then we start moving j again.

## Two Pointers
**Use Case**: Solve problems involving sorted arrays or linked lists, such as finding pairs that sum to a target or removing duplicates.  
**Benefit**: Achieves O(n) time complexity by moving two pointers toward each other or in the same direction based on problem constraints.  
**Example Problems**:  
- Two Sum II - Input Array is Sorted (LeetCode #167)  
- Remove Duplicates from Sorted Array (LeetCode #26)  
- Container With Most Water (LeetCode #11)

## Fast & Slow Pointers
**Use Case**: Detect cycles, find midpoints, or identify specific positions in linked lists or arrays (e.g., cycle detection in a linked list).  
**Benefit**: Provides an efficient O(n) solution for cycle detection and related problems using two pointers moving at different speeds.  
**Example Problems**:  
- Linked List Cycle (LeetCode #141)  
- Find the Duplicate Number (LeetCode #287)  
- Middle of the Linked List (LeetCode #876)

## Binary Search
**Use Case**: Search for a target in a sorted array or find boundaries, such as the first or last occurrence of an element.  
**Benefit**: Reduces time complexity to O(log n) by halving the search space in each iteration.  
**Example Problems**:  
- Binary Search (LeetCode #704)  
- Find First and Last Position of Element in Sorted Array (LeetCode #34)  
- Search in Rotated Sorted Array (LeetCode #33)

## Depth First Search (DFS)
**Use Case**: Traverse trees or graphs to explore all possible paths, such as finding connected components or validating properties of a tree.  
**Benefit**: Ideal for problems requiring exhaustive exploration of paths or recursive solutions.  
**Example Problems**:  
- Number of Islands (LeetCode #200)  
- Validate Binary Search Tree (LeetCode #98)  
- Path Sum (LeetCode #112)

## Breadth First Search (BFS)
**Use Case**: Find the shortest path in unweighted graphs or perform level-order traversal in trees.  
**Benefit**: Guarantees the shortest path in unweighted graphs and handles level-by-level processing efficiently.  
**Example Problems**:  
- Binary Tree Level Order Traversal (LeetCode #102)  
- Word Ladder (LeetCode #127)  
- Rotten Oranges (LeetCode #994)

## Backtracking
**Use Case**: Solve combinatorial problems like generating permutations, combinations, or solving puzzles (e.g., N-Queens).  
**Benefit**: Systematically explores all possibilities while pruning invalid paths to optimize performance.  
**Example Problems**:  
- Permutations (LeetCode #46)  
- Combination Sum (LeetCode #39)  
- N-Queens (LeetCode #51)

## Dynamic Programming
**Use Case**: Solve optimization problems with overlapping subproblems, such as finding the longest common subsequence or solving knapsack problems.  
**Benefit**: Reduces time complexity by memoizing results of subproblems, avoiding redundant computations.  
**Example Problems**:  
- Climbing Stairs (LeetCode #70)  
- Longest Palindromic Substring (LeetCode #5)  
- 0/1 Knapsack (Not on LeetCode, but common in interviews)

## Topological Sort
**Use Case**: Schedule tasks with dependencies or resolve prerequisites, such as course scheduling in a directed acyclic graph (DAG).  
**Benefit**: Provides a linear ordering of nodes in a DAG, useful for dependency resolution.  
**Example Problems**:  
- Course Schedule (LeetCode #207)  
- Alien Dictionary (LeetCode #269)  
- Sequence Reconstruction (LeetCode #444)

## Union Find
**Use Case**: Manage disjoint sets to detect connected components or cycles in graphs (e.g., finding provinces in a graph).  
**Benefit**: Offers near-constant time operations for dynamic connectivity with path compression and union by rank.  
**Example Problems**:  
- Number of Provinces (LeetCode #547)  
- Redundant Connection (LeetCode #684)  
- Graph Valid Tree (LeetCode #261)

## Trie
**Use Case**: Handle string prefix-based problems, such as implementing autocomplete or searching a dictionary.  
**Benefit**: Efficiently stores and retrieves strings with common prefixes, reducing time complexity for prefix searches.  
**Example Problems**:  
- Implement Trie (Prefix Tree) (LeetCode #208)  
- Word Search II (LeetCode #212)  
- Add and Search Word (LeetCode #211)

## Bit Manipulation
**Use Case**: Solve problems using binary operations, such as finding a single number in an array or counting bits.  
**Benefit**: Reduces space complexity by operating at the bit level, ideal for low-level optimizations.  
**Example Problems**:  
- Single Number (LeetCode #136)  
- Number of 1 Bits (LeetCode #191)  
- Reverse Bits (LeetCode #190)

## Greedy
**Use Case**: Make locally optimal choices to achieve a global optimum, such as selecting activities or solving jump games.  
**Benefit**: Simplifies problems by avoiding exhaustive searches, often leading to efficient solutions.  
**Example Problems**:  
- Jump Game (LeetCode #55)  
- Best Time to Buy and Sell Stock II (LeetCode #122)  
- Minimum Number of Arrows to Burst Balloons (LeetCode #452)

## Intervals
**Use Case**: Handle scheduling or overlapping interval problems, such as merging intervals or scheduling meetings.  
**Benefit**: Efficiently processes time-based or range-based data by sorting and scanning intervals.  
**Example Problems**:  
- Merge Intervals (LeetCode #56)  
- Meeting Rooms II (LeetCode #253)  
- Non-overlapping Intervals (LeetCode #435)

## How to Use This Guide
To master these patterns for coding interviews:
1. **Understand the Pattern**: Study each pattern’s use case and benefits to recognize when it applies.
2. **Practice Example Problems**: Solve the listed LeetCode problems to gain hands-on experience with each pattern.
3. **Apply to New Problems**: During interviews, identify problem constraints that match a pattern (e.g., sorted array → Binary Search, dependencies → Topological Sort).
4. **Review and Reflect**: After solving a problem, analyze how the pattern reduced complexity or simplified the solution.

## Benefits of Learning Patterns
- **Efficiency**: Focus on 14 patterns instead of memorizing thousands of problems.
- **Flexibility**: Patterns are versatile and can be adapted to various problem types.
- **Confidence**: Familiarity with patterns helps you approach unfamiliar problems systematically.

## References
- Original Article: ["14 LeetCode Patterns to Solve Any Question"](https://medium.com/@shubhamkumarcode/14-leetcode-patterns-to-solve-any-question-1dcdcc650bfa)
- LeetCode Platform: [leetcode.com](https://leetcode.com)
