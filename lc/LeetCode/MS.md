# 1 Buffer Cache Multiplier

Microsoft's SQL Server database engine optimization team needs to determine the most efficient execution plan for data replication operations. You have a limited number of execution steps (N) to maximize the amount of data that can be processed through the replication pipeline.
The replication system supports four operations, each consuming exactly one execution step:
		FETCH: Retrieve one data record from the source table
		SELECT_ALL: Mark all current records in the working buffer for processing
		CACHE: Store the selected records in the replication cache
		REPLICATE: Copy all cached records to the target database and append them to the working buffer
Find the optimal sequence of these operations that maximizes the total number of records processed within exactly N execution steps. The system starts with an empty working buffer and cache.


# 2 Elastic Capacity Balancer
Find the VM memory configuration in Azure resource tree that most closely matches a customer memory request. The VM configurations are organized in a binary search tree where smaller memory sizes branch left and larger sizes branch right. Given a customer floating-point memory requirement, efficiently traverse this tree and return the configuration that minimizes the absolute difference with the requested amount.

```py
def find_closest_vm_recursive(node, target, best_match):
    if node is None:
        return best_match

    # Calculate current absolute difference
    current_diff = abs(node.memory - target)
    
    # Update the closest match if this one is better
    if best_match is None or current_diff < abs(best_match.memory - target):
        best_match = node
    elif current_diff == abs(best_match.memory - target):
        # Tie-breaker: prefer the smaller configuration or prioritize based on logic
        pass

    # Traverse the BST
    if target < node.memory:
        return find_closest_vm_recursive(node.left, target, best_match)
    else:
        return find_closest_vm_recursive(node.right, target, best_match
```

# 3 Candidate Finder
Microsoft's HR system maintains employee hierarchies using a structured organizational tree where each employee has a unique performance rating. The system needs to implement a promotion workflow that identifies the next employee in line for advancement based on performance ratings.
Given an organizational hierarchy represented as a binary tree (where left children have lower ratings and right children have higher ratings) and a specific employee, find the employee with the next higher performance rating who would be considered for the next promotion opportunity.
The promotion system follows a strict ordering: employees are considered for advancement in ascending order of their performance ratings. Your task is to find the immediate next employee in this promotion sequence.

Conceptual Approach

The key insight is leveraging the binary search tree property where in-order traversal visits nodes in ascending order. The successor of any node is the next node in in-order traversal. Two scenarios exist: if target employee has right subtree, successor is leftmost node there. If not, successor is first ancestor where target employee falls in left subtree.

Strategy to Solve

Check for right subtree first: If target employee has right subtree, find leftmost node in that subtree. This represents employee with smallest rating that is still higher than target. Handle leftmost traversal: When right subtree exists, keep going left until you reach leaf node. This gives minimum value in right subtree. Search for ancestor successor: If no right subtree exists, traverse up hierarchy to find appropriate ancestor. Successor will be first ancestor where target employee lies in left subtree. Track search path: As you navigate from root to target, maintain variable that holds most recent node where you took left turn. This represents best successor candidate. Return null for maximum element: If you reach target without finding successor candidates and there is no right subtree, return null

Sample Execution
```text
Let us trace through hierarchy = [120,80,150,60,100], target_employee = 80:

Tree Structure:
120
/ \
80 150
/ \
60 100

Step 1: Navigate to target employee (rating 80)
Start at root (120): 80 < 120, go left
At node (80): Found target employee
Track potential successors: Since we went left from 120, mark 120 as potential successor

Step 2: Check for right subtree
Employee 80 has right subtree containing node 100
Since right subtree exists, successor must be leftmost node in this subtree

Step 3: Find leftmost in right subtree
Start at right child (100)
100 has no left child, so 100 is leftmost node
Return 100 as successor

Result: Next promotion candidate after 80 is 100
Performance Analysis
Time Complexity
O(h)
Space Complexity
O(1)
```

# 4 Design Distributed Lock Grid Manager
Microsoft's distributed computing platform uses a grid-based resource locking system where multiple processes compete for exclusive access to computational resources arranged in an n×n matrix. The system needs to efficiently track lock acquisitions and determine when a process achieves sufficient resource control to execute critical operations.

A process wins control when it successfully acquires locks for n resources that form a complete line (horizontal, vertical, or diagonal) across the grid. The lock manager must efficiently process lock requests and immediately detect winning conditions without scanning the entire grid after each operation.

Your task is to design a LockGridManager that can handle lock acquisition requests and efficiently determine if a process has achieved winning control over a complete resource line.

Design a class that supports acquireLock(row, col, processId) operations and returns the winning process ID when a process achieves complete line control, or 0 if no process has won yet.

Examples
```
Example 1
Input: n=3, Operations: acquireLock(0,0,1), acquireLock(0,2,2), acquireLock(2,2,1), acquireLock(1,1,2), acquireLock(2,0,1), acquireLock(2,1,1)

Sample Execution
Let's trace through a 3×3 grid with moves leading to a row win:

Initialize LockGridManager(3):
Player 1 counters: rows=[0,0,0], cols=[0,0,0], diag1=0, diag2=0
Player 2 counters: rows=[0,0,0], cols=[0,0,0], diag1=0, diag2=0

Move 1: acquireLock(0, 0, 1) - Player 1 at (0,0)
Update Player 1 counters:
- rows[0] = 1 (row 0 progress)
- cols[0] = 1 (column 0 progress)
- diag1 = 1 (main diagonal: 0 == 0)
- diag2 = 0 (anti-diagonal: 0+0 != 2)
Check: max(1,1,1,0) < 3, no winner → return 0

Move 2: acquireLock(0, 1, 1) - Player 1 at (0,1)
Update Player 1 counters:
- rows[0] = 2 (row 0 progress)
- cols[1] = 1 (column 1 progress)
- diag1 = 1 (not on main diagonal: 0 != 1)
- diag2 = 0 (not on anti-diagonal: 0+1 != 2)
Check: max(2,1,1,0) < 3, no winner → return 0

Move 3: acquireLock(0, 2, 1) - Player 1 at (0,2)
Update Player 1 counters:
- rows[0] = 3 (row 0 complete!)
- cols[2] = 1 (column 2 progress)
- diag1 = 1 (not on main diagonal: 0 != 2)
- diag2 = 1 (anti-diagonal: 0+2 == 2)
Check: rows[0] == 3 → Player 1 wins! → return 1

Final state: Player 1 controls entire row 0
```

# 5 Locate Deepest Available Computing Node

Microsoft's Azure cloud infrastructure uses hierarchical node management where computing resources are organized in a tree-like structure based on data center topology. Each node represents a computing resource with specific capabilities, and the system needs to identify the leftmost available resource at the deepest level of the hierarchy for optimal workload placement.

The resource allocation algorithm prioritizes nodes at the deepest level to maximize resource utilization efficiency, and when multiple nodes exist at the same depth, it selects the leftmost node to maintain consistent allocation patterns across the data center infrastructure.

Your task is to implement a resource discovery algorithm that traverses the computing hierarchy and identifies the leftmost resource node at the maximum depth level.

Given a binary tree representing the computing resource hierarchy, find the value of the leftmost node at the deepest level of the tree.

```
Implement level-order traversal using BFS: Use a queue to process nodes level by level from left to right. For each level, process all nodes currently in the queue before adding their children, ensuring you handle complete levels atomically.

Track level progression and identify deepest level: Maintain awareness of which level you're currently processing. Since BFS processes levels sequentially, the last level you process will be the deepest level of the tree.

Identify leftmost node at deepest level: Within each level, the first node you encounter (leftmost) is the candidate for that level. Since you process levels sequentially, the leftmost node of the final level becomes your answer.
```

```
Sample Execution
Let's trace through BFS approach on the tree:
1
/ \
2 3
/ / \
4 5 6
/
7

BFS Level-by-Level Processing:

Initialize:
queue = [1]
level = 0

Level 0:
Process queue: [1]
- Process node 1, add children: queue = [2, 3]
- Leftmost at level 0: 1

Level 1:
Process queue: [2, 3]
- Process node 2, add children: queue = [4]
- Process node 3, add children: queue = [4, 5, 6]
- Leftmost at level 1: 2

Level 2:
Process queue: [4, 5, 6]
- Process node 4, no children: queue = []
- Process node 5, add children: queue = [7]
- Process node 6, no children: queue = [7]
- Leftmost at level 2: 4

Level 3:
Process queue: [7]
- Process node 7, no children: queue = []
- Leftmost at level 3: 7

Final Result:
Deepest level reached: Level 3
Leftmost node at deepest level: 7
```

# 6. Filter Commands by Terminal Key Zon

Microsoft's terminal application includes an ergonomic typing assistant that helps developers identify commands that can be typed efficiently using keys from a single zone of the keyboard. This feature reduces finger movement and improves typing speed during development workflows, especially for frequently used command sequences.

The terminal organizes keyboard keys into three ergonomic zones based on finger positioning: the upper zone (number row area), middle zone (home row area), and lower zone (bottom row area). The typing assistant filters command lists to show only those commands that require keys from a single zone, promoting better typing ergonomics.

Your task is to implement a command filter that identifies which terminal commands can be typed using keys from only one keyboard zone, helping developers optimize their typing efficiency.

Given an array of terminal command strings, return the commands that can be typed using letters from only one keyboard zone.

Problem Statement

You need to filter a list of words to find those that can be typed using keys from only one row of a QWERTY keyboard. The challenge involves mapping each character to its corresponding keyboard row and then validating that all characters in a word belong to the same row, while handling case-insensitive comparison. This problem tests your understanding of hash map usage, set operations, and string processing with character classification.

Conceptual Approach
The solution involves creating a mapping from each letter to its keyboard row, then for each word, checking if all characters belong to the same row. You can optimize this by using sets for O(1) lookup or by mapping characters to row numbers and ensuring all characters in a word have the same row number. The key insight is that you need to establish which row a word belongs to (based on its first character) and then validate that all subsequent characters belong to the same row.


Sample Execution
```
Let's trace through filtering ["Hello", "Alaska", "Dad", "Peace"]:

Step 1: Set up keyboard row mappings
Row 1 (upper): {q,w,e,r,t,y,u,i,o,p}
Row 2 (middle): {a,s,d,f,g,h,j,k,l}
Row 3 (lower): {z,x,c,v,b,n,m}

Character to row mapping:
q→1, w→1, e→1, r→1, t→1, y→1, u→1, i→1, o→1, p→1
a→2, s→2, d→2, f→2, g→2, h→2, j→2, k→2, l→2
z→3, x→3, c→3, v→3, b→3, n→3, m→3

Step 2: Process each word

Word: "Hello"
- Convert to lowercase: "hello"
- First character 'h' → row 2
- Check all characters: h(2), e(1), l(2), l(2), o(1)
- Mixed rows (1 and 2) → Exclude from result

Word: "Alaska"
- Convert to lowercase: "alaska"
- First character 'a' → row 2
- Check all characters: a(2), l(2), a(2), s(2), k(2), a(2)
- All characters in row 2 → Include in result

Word: "Dad"
- Convert to lowercase: "dad"
- First character 'd' → row 2
- Check all characters: d(2), a(2), d(2)
- All characters in row 2 → Include in result

Word: "Peace"
- Convert to lowercase: "peace"
- First character 'p' → row 1
- Check all characters: p(1), e(1), a(2), c(3), e(1)
- Mixed rows (1, 2, and 3) → Exclude from result
```



# 7. Binary Digit Counter Algorithm

You are given a 32-bit integer and need to count how many '1' digits appear in its binary representation. This operation is also known as calculating the population count or Hamming weight of a number.

Your task is to implement an efficient algorithm that examines the binary form of the input number and returns the total count of set bits (bits with value 1). The input is treated as an unsigned 32-bit integer regardless of how it's represented in your programming language.

This problem tests your understanding of bitwise operations, number system conversions, and algorithmic optimization techniques.


Strategy to Solve

Basic Bit Checking Approach - Loop through all 32 bit positions, using bitwise AND with powers of 2 to check if each position contains a '1'. This is straightforward but always examines all positions regardless of how many '1' bits exist.

Bit Shifting Method - Use right shift operations to move each bit into the least significant position, then check if it's '1' using bitwise AND with 1. Continue until the number becomes zero.

Brian Kernighan's Algorithm - Use the property that n & (n-1) removes the rightmost '1' bit from n. Repeatedly apply this operation while counting iterations until n becomes zero. This is optimal because it only performs as many operations as there are '1' bits.

```
Let us trace through Brian Kernighan's algorithm with Example 1: n = 11 (binary: 1011)

Initial: n = 11 (binary: 1011), count = 0

Iteration 1:
- n = 11 (1011 in binary)
- n - 1 = 10 (1010 in binary)
- n & (n-1) = 1011 & 1010 = 1010 (removes rightmost '1')
- n = 10, count = 1

Iteration 2:
- n = 10 (1010 in binary)
- n - 1 = 9 (1001 in binary)
- n & (n-1) = 1010 & 1001 = 1000 (removes rightmost '1')
- n = 8, count = 2

Iteration 3:
- n = 8 (1000 in binary)
- n - 1 = 7 (0111 in binary)
- n & (n-1) = 1000 & 0111 = 0000 (removes rightmost '1')
- n = 0, count = 3

Loop termination: n = 0, return count = 3
```
