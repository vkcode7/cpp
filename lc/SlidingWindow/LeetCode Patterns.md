# 14 LeetCode Patterns to Master Coding Interviews

This README summarizes the 14 essential LeetCode patterns for solving coding interview questions efficiently, as described in the article ["14 LeetCode Patterns to Solve Any Question"](https://medium.com/@shubhamkumarcode/14-leetcode-patterns-to-solve-any-question-1dcdcc650bfa). These patterns provide generalized strategies to tackle a wide range of problems, reducing the need to memorize hundreds of individual solutions. Each pattern is outlined below with its use case, benefits, and example LeetCode problems.

## Table of Contents
1. [Sliding Window](#sliding-window)
2. [Two Pointers](#two-pointers)
3. [Fast & Slow Pointers](#fast--slow-pointers)
4. In Place Linked List Reversal
5. [Binary Search](#binary-search)
6. [Depth First Search (DFS)](#depth-first-search-dfs)
7. [Breadth First Search (BFS)](#breadth-first-search-bfs)
8. [Backtracking](#backtracking)
9. [Dynamic Programming](#dynamic-programming)
10. [Topological Sort](#topological-sort)
11. [Union Find](#union-find)
12. [Trie](#trie)
13. [Bit Manipulation](#bit-manipulation)
14. [Greedy](#greedy)
15. [Intervals](#intervals)

## Sliding Window
**Use Case**: Find subarrays or substrings that satisfy a specific condition, such as the maximum sum of a subarray of size k or the longest substring without repeating characters.  
**Benefit**: Reduces time complexity from O(n²) to O(n) by maintaining a dynamic window that expands or shrinks based on conditions.  
**Example Problems**:  
- Maximum Average Subarray I (LeetCode #643)  
- Longest Substring Without Repeating Characters (LeetCode #3)  
- Minimum Window Substring (LeetCode #76)

**Technique: **
### Fixed Window:

<img src="../assets/Snip_29.png” width="100%">

In the sliding window, you have 2 pointers, i and j. Move j as far as you can until your condition is no longer valid, then move the i pointer closer to j until the condition is valid again to shrink the window. At every iteration, keep track of the min/max length of the subarray for the result. Without the sliding window technique, we would need to use a double for loop resulting in O(N²) time. The sliding window is O(N) time complexity.

### Dynamic Sliding Window:

<img src="../assets/Snip_30.png” width="40%">

In the dynamic sliding window, the size of the window (subarray between i and j) changes throughout the algorithm. In this example, we scan the subarray “bacb” and find that we have a duplicate “b”, so we will move the i pointer to shrink the window and move on to letter “a”, resulting in “acb”, then we start moving j again.

```py
"""
A generic template for dynamic sliding window finding min window length
"""
def shortest_window(nums, condition):
    i = 0
    min_length = float('inf')
    result = None

    for j in range(len(nums)):
        # Expand the window
        # Add nums[j] to the current window logic

        # Shrink window as long as the condition is met
        while condition():  
            # Update the result if the current window is smaller
            if j - i + 1 < min_length:
                min_length = j - i + 1
                # Add business logic to update result

            # Shrink the window from the left
            # Remove nums[i] from the current window logic
            i += 1

    return result

"""
A generic template for dynamic sliding window finding max window length
"""
def longest_window(nums, condition):
    i = 0
    max_length = 0
    result = None

    for j in range(len(nums)):
        # Expand the window
        # Add nums[j] to the current window logic

        # Shrink the window if the condition is violated
        while not condition():  
            # Shrink the window from the left
            # Remove nums[i] from the current window logic
            i += 1

        # Update the result if the current window is larger
        if j - i + 1 > max_length:
            max_length = j - i + 1
            # Add business logic to update result

    return result

"""
A generic template for sliding window of fixed size
"""
def window_fixed_size(nums, k):
    i = 0
    result = None

    for j in range(len(nums)):
        # Expand the window
        # Add nums[j] to the current window logic

        # Ensure window has size of K
        if (j - i + 1) < k:
            continue

        # Update Result
        # Remove nums[i] from window
        # increment i to maintain fixed window size of length k
        i += 1

    return result
```

## Two Pointers
**Use Case**: Solve problems involving sorted arrays or linked lists, such as finding pairs that sum to a target or removing duplicates.  
**Benefit**: Achieves O(n) time complexity by moving two pointers toward each other or in the same direction based on problem constraints.  
**Example Problems**:  
- Two Sum II - Input Array is Sorted (LeetCode #167)  
- Remove Duplicates from Sorted Array (LeetCode #26)  
- Container With Most Water (LeetCode #11)

**Technique**:
Instead of scanning all possible subarrays or substrings, use two pointers i and j at the ends of a string or sorted array to be clever how you increment i or decrement j as you scan the input. This will lower your time complexity from O(N²) to O(N). In the example above, to detect if a string is a palindrome we scan the ends of the string one character at a time. If the characters are equal, move i and j closer together. If they are not equal, the string is not a palindrome.

###Is string a Palindrome? "RACECAR"
```py
def two_pointer_template(input):
    # Initialize pointers
    i = 0
    j = len(input) - 1
    result = None
     
    # Iterate while pointers do not cross
    while i < j:
        # Process the elements at both pointers
        # Adjust the pointers based on specific conditions
        # i += 1 or j -= 1
        # Break or continue based on a condition if required
    # Return the final result or process output
    return result
```


## Fast & Slow Pointers
**Use Case**: Detect cycles, find midpoints, or identify specific positions in linked lists or arrays (e.g., cycle detection in a linked list).  
**Benefit**: Provides an efficient O(n) solution for cycle detection and related problems using two pointers moving at different speeds.  
**Example Problems**:  
- Linked List Cycle (LeetCode #141)  
- Find the Duplicate Number (LeetCode #287)  
- Middle of the Linked List (LeetCode #876)

**Technique**:
Use two pointers, a slow and fast pointer. Slow moves once and fast moves twice at every iteration. Instead of using a data structure to store previous nodes to detect a cycle which requires O(N) space, using the two pointer technique will find a cycle with O(1) space if fast loops around the cycle and will eventually meet slow. You can also use this technique to find the middle of a linked list in O(1) space and 1 pass.

3 -> 2 -> [0] -> 4 -> [[1]]

```py
def slow_fast_pointers(head):
    # Initialize pointers
    slow = head
    fast = head
    result = None

    # move slow once, move fast twice
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
        # update result based on custom logic
        # Example: if fast == slow then cycle is detected
    return result
```

## In Place Linked List Reversal
<img src="../assets/snip_31.png” width="20%">

### When to use it?
- Reverse a linked list in 1 pass and O(1) space
- Reverse a specific portion of a linked list
- Reverse nodes in groups of K

### Technique
Use two pointers, prev and ptr which point to the previous and current nodes. To reverse a linked list, ptr.next = prev. Then, move prev to ptr and move ptr to the next node. At the end of the algorithm, prev will point to the head of the reversed list.

```py
def reverse_linked_list(head):
    prev = None
    ptr = head 
    
    while ptr:
        # Save the next node
        next_node = ptr.next
        # Reverse the current node's pointer
        ptr.next = prev
        # Move the pointers one step forward
        prev = ptr
        ptr = next_node
    # prev is the new head after the loop ends
    return prev
```

## Binary Search
**Use Case**: Search for a target in a sorted array or find boundaries, such as the first or last occurrence of an element.  
**Benefit**: Reduces time complexity to O(log n) by halving the search space in each iteration.  
**Example Problems**:  
- Binary Search (LeetCode #704)  
- Find First and Last Position of Element in Sorted Array (LeetCode #34)  
- Search in Rotated Sorted Array (LeetCode #33)

### Technique
Start left and right pointers at indices 0 and n-1, then find the mid point and see if that is equal to, less than, or greater than your target. If nums[mid] > target, go left by moving the right pointer to mid-1. If nums[mid] < target, go right by moving left to mid+1. Binary Search reduces search time complexity from O(N) to O(NLogN)

```py
"""
Classic binary search algorithm that finds a target value
"""
def classic_binary_search(array, target):
    left, right = 0, len(array)-1
    while left <= right:
        mid = left + (right - left) // 2
        if array[mid] == target:
            return mid
        elif array[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    return -1

"""
A generic template for binary search such that the returned value
is the minimum index where condition(k) is true
Example 1:
array = [1,2,2,2,3]
target = 2
binary_search(array, lambda mid: array[mid] >= target) --> 1
Example 2:
array = [1,2,2,2,3]
target = 2
binary_search(array, lambda mid: array[mid] > target) --> 4
"""
def binary_search(array, condition):
    left, right = 0, len(array)
    while left < right:
        mid = left + (right - left) // 2
        if condition(mid):
            right = mid
        else:
            left = mid + 1
    return left
"""
Binary search algorithm that can search a rotated array
by selected the appropriate half to scan at each iteration
"""
def binary_search_rotated_array(array, target):
    left, right = 0, len(array)-1
    while left <= right:
        mid = (left + right) // 2
        if array[mid] == target:
            return mid
        # left side sorted
        if array[left] <= array[mid]:
            # if target is contained in left sorted side, go left
            if array[left] <= target <= array[mid]:
                right = mid - 1
            else:
                left = mid + 1
        # right side sorted
        else:
            # if target is contained in right sorted side, go right
            if array[mid] <= target <= array[right]:
                left = mid + 1
            else:
                right = mid - 1
    return -1
```

## Top K Elements

### When to use it?
- Find the top k smallest or largest elements
- Find the kth smallest or largest element
- Find the k most frequent elements

### Technique
You can always sort an array and then take the first or last k elements, however the time complexity would be O(NLogN). A heap can pop and push elements in O(Log(K)) where K is the size of the heap. Therefore, instead of sorting, we can use a heap to hold the smallest or largest K values, and for every element in the array check whether to pop/push to the heap, resulting in a time complexity of O(NLogK).

```py
"""
A generic template for the Top K Smallest elements.  7 2 5 3 9 1 8
"""
import heapq
def top_k_smallest_elements(arr, k):
    if k <= 0 or not arr:
        return []

# Use a max heap to maintain the k smallest elements
    max_heap = []
    for num in arr:
        # Python does not have a maxHeap, only min Heap
        # Therefore, negate the num to simulate a max heap
        heapq.heappush(max_heap, -num)
        if len(max_heap) > k:
            heapq.heappop(max_heap)
    # Convert back to positive values and return
    return [-x for x in max_heap]
"""
A generic template for the Top K Largest elements.
"""
import heapq
def top_k_largest_elements(arr, k):
    if k <= 0 or not arr:
        return []
    # Use a min heap to maintain the k largest elements
    min_heap = []
    for num in arr:
        heapq.heappush(min_heap, num)
        if len(min_heap) > k:
            heapq.heappop(min_heap)
    return min_heap
```

### LeetCode Questions
215. Kth Largest Element in an Array
347. Top K Frequent Elements
23. Merge k Sorted Lists

## Binary Tree Traversal

### When to use it?
- Preorder: Serialize or deserialize a tree
- Inorder: Retrieve elements in sorted order (BSTs)
- Postorder: Process children before parent (bottom-up)
- BFS: Level by level scanning

### Technique
For the preorder, inorder, and postorder traversals use recursion (DFS). For the level by level scan use BFS iteratively with a queue.

<img src="../assets/snip_32.png” width="20%">

```py
"""
Preorder traversal: visit node, then left subtree, then right subtree.
"""
def preorder_traversal(node):
    if not node:
        return
    # visit node
    preorder_traversal(node.left)
    preorder_traversal(node.right)

"""
Inorder traversal: visit left subtree, then node, then right subtree.
"""
def inorder_traversal(node):
    if not node:
        return
    inorder_traversal(node.left)
    # visit node
    inorder_traversal(node.right)
"""
Postorder traversal: visit left subtree, then right subtree, then node
"""
def postorder_traversal(node):
    if not node:
        return
    postorder_traversal(node.left)
    postorder_traversal(node.right)
    # visit node
"""
BFS traversal: Visit all nodes level by level using a queue
"""
from collections import deque
def bfs_traversal(root):
    queue = deque([root])
    while queue:
        node = queue.popleft()
        if node:
            # visit node
            queue.append(node.left)
            queue.append(node.right)
```

### LeetCode Questions
104. Maximum Depth of Binary Tree
102. Binary Tree Level Order Traversal
105. Construct Binary Tree from Preorder and Inorder Traversal
124. Binary Tree Maximum Path Sum


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
