# 1 Buffer Cache Multiplier

Microsoft's SQL Server database engine optimization team needs to determine the most efficient execution plan for data replication operations. You have a limited number of execution steps (N) to maximize the amount of data that can be processed through the replication pipeline.
The replication system supports four operations, each consuming exactly one execution step:
		FETCH: Retrieve one data record from the source table
		SELECT_ALL: Mark all current records in the working buffer for processing
		CACHE: Store the selected records in the replication cache
		REPLICATE: Copy all cached records to the target database and append them to the working buffer
Find the optimal sequence of these operations that maximizes the total number of records processed within exactly N execution steps. The system starts with an empty working buffer and cache.

```cpp
class Solution {
public:
    long long maxRecords(int N) {
        vector<long long> dp(N + 1, 0);

        for (int i = 1; i <= N; i++) {
            // Option 1: FETCH (linear growth)
            dp[i] = dp[i - 1] + 1;

            // Try switching point for replication
            for (int j = 1; j <= i - 3; j++) {
                long long base = dp[j];

                // remaining steps after j:
                int rem = i - j;

                // cost: SELECT_ALL + CACHE = 2 steps, then REPLICATE cycles
                long long cycles = rem - 2;

                if (cycles > 0) {
                    dp[i] = max(dp[i], base * cycles);
                }
            }
        }

        return dp[N];
    }
};
```

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

```C#
	static void PrintBits(int num)
	{
		const int IntSize = sizeof(int) * 8;
		for (int i = IntSize - 1; i >= 0; i--)
		{
			int mask = 1 << i;
			int bit = (num & mask) == 0 ? 0 : 1;
			Console.Write(bit);
		}
		Console.WriteLine("");
	}

	static Func<int, string> printBits = (int k) => {
		int numsetbits = 0;
		Stack<int> st = new();
		while (k > 0)
		{
			st.Push(k & 1);
			k >>= 1; //same as k = k / 2;
		}

		string bits = "";
		foreach (var number in st)
		{
			bits += number;
		}

		return bits;
	};

	static Func<int, int> setBitCounter = (int k) => {
		int numsetbits = 0;
		while (k > 0)
		{
			if ((k & 1) == 1)
				numsetbits++;

			k >>= 1; //same as k = k / 2;
		}
		return numsetbits;
	};

	static Func<int, int> allBitCounter = (int k) => {
		int numbits = 0;
		while (k > 0)
		{
			numbits++;

			k >>= 1;
		}
		return numbits;
	};
```


# 8. Circular Array Maximum Selection Problem

You are given an array of positive integers arranged in a circular pattern where the first and last elements are considered adjacent. Your task is to select a subset of elements such that no two selected elements are adjacent (including the circular adjacency between first and last elements) while maximizing the sum of selected values.

This constraint creates a circular dependency problem where selecting the first element prevents you from selecting the last element, and vice versa. You need to find the optimal selection strategy that respects the adjacency rules while achieving the maximum possible sum.

This problem tests your understanding of dynamic programming, constraint handling, and algorithmic problem decomposition techniques.

Explanation: You can select element at index 1 (value 3). You cannot select both index 0 and index 2 because they are adjacent in the circular arrangement, and neither alone gives a better result than index 1.

Example
```
Input: nums = [1,2,3,1]


Output: 4


Explanation: Select elements at indices 0 and 2 (values 1 and 3). Total sum = 1 + 3 = 4. This is optimal since you cannot select adjacent elements.
```

The key insight is to break the circular constraint by considering two separate linear cases: one where you exclude the first element (allowing potential selection of the last), and another where you exclude the last element (allowing potential selection of the first). The optimal solution is the maximum of these two scenarios. This approach transforms the circular problem into two familiar linear dynamic programming problems, making the solution both elegant and efficient.

Strategy to Solve
Problem decomposition approach - Split the circular problem into two linear subproblems: solve for elements [0...n-2] (excluding last) and [1...n-1] (excluding first). This eliminates the circular constraint by ensuring first and last elements are never both available for selection.

Linear DP for each subproblem - For each linear array, use the classic dynamic programming approach where dp[i] represents the maximum sum possible using elements from index 0 to i. The recurrence relation is: dp[i] = max(dp[i-1], dp[i-2] + nums[i]).

Handle edge cases first - Check for arrays with length 1 (return the single element) and length 2 (return the maximum of the two elements). These cases do not have meaningful circular constraints.

Optimize space complexity - Instead of maintaining full DP arrays, use only two variables to track the previous two states since each state only depends on the two preceding values. This reduces space from O(n) to O(1).

```
Sample Execution
Let us trace through Example 2: nums = [1,2,3,1]

Step 1: Handle edge cases
- Length = 4, not an edge case, proceed with decomposition

Step 2: Case 1 - Exclude last element, solve for [1,2,3]
Array: [1,2,3] (indices 0,1,2 from original)

Linear DP process:
- dp[0] = 1 (best using only first element)
- dp[1] = max(dp[0], nums[1]) = max(1, 2) = 2
- dp[2] = max(dp[1], dp[0] + nums[2]) = max(2, 1 + 3) = 4

Case 1 result: 4 (select indices 0 and 2 from subarray, which are original indices 0 and 2)

Step 3: Case 2 - Exclude first element, solve for [2,3,1]
Array: [2,3,1] (indices 1,2,3 from original)

Linear DP process:
- dp[0] = 2 (best using only first element of subarray)
- dp[1] = max(dp[0], nums[1]) = max(2, 3) = 3
- dp[2] = max(dp[1], dp[0] + nums[2]) = max(3, 2 + 1) = 3

Case 2 result: 3 (select index 1 from subarray, which is original index 2)

Step 4: Compare results
- Case 1: 4 (selecting original indices 0 and 2: values 1 + 3)
- Case 2: 3 (selecting original index 2: value 3)
- Maximum: 4

Final answer: 4
```

# 9. Custom Text-to-Number Parser

You need to implement a robust text parser that extracts the first valid integer from a given string. The parser should handle various edge cases including leading whitespace, optional signs, invalid characters, and overflow conditions.

The parsing algorithm follows these rules:
```
Skip all leading whitespace characters (spaces only)
Check for an optional '+' or '-' sign to determine number polarity
Read consecutive digit characters and convert them to an integer
Stop parsing when encountering the first non-digit character
Return 0 if no valid number can be formed
Clamp results to 32-bit signed integer range [-2³¹, 2³¹-1]
This problem tests your string processing skills, edge case handling, and understanding of integer overflow behavior.

Examples
Example 1
Input: s = "42"

Output: 42

Explanation: Direct conversion of numeric string to integer.

Example 2
Input: s = " -42"

Output: -42

Explanation: Skip leading spaces, detect negative sign, parse digits to get -42.

Example 3
Input: s = "4193 with words"

Output: 4193

Example 6
Input: s = "+123abc"

Output: 123

Sample Execution
Let us trace through Example 5: s = "-91283472332"

Initialize:
- result = 0, sign = 1, index = 0
- INT_MAX = 2147483647, INT_MIN = -2147483648

Phase 1: Skip whitespace
- s[0] = '-', not whitespace, proceed to sign detection

Phase 2: Detect sign
- s[0] = '-', valid negative sign
- sign = -1, index = 1

Phase 3: Parse digits
index = 1, s[1] = '9':
- Check overflow: result = 0, digit = 9
- New value would be: 0 * 10 + 9 = 9
- 9 ≤ INT_MAX, no overflow
- result = 9

[Continue for digits 1,2,8,3,4,7,2...]

index = 10, s[10] = '3':
- Check overflow: result = 912834723, digit = 3
- Would be: 912834723 * 10 + 3 = 9128347233
- Check: 9128347233 > INT_MAX (2147483647) → overflow detected
- Apply sign: negative overflow → return INT_MIN = -2147483648

Final result: -2147483648 (clamped to lower bound)
```


# 10. FIFO Container Using LIFO Components

You need to design a First-In-First-Out (FIFO) data container using only Last-In-First-Out (LIFO) data containers as building blocks. The FIFO container should support the standard operations: adding elements to the back, removing elements from the front, viewing the front element, and checking if the container is empty.

The constraint is that you can only use LIFO containers with their standard operations:
```
push(x) - Add element to the top
pop() - Remove and return the top element
top() - View the top element without removing it
empty() - Check if the container is empty

Your implementation should efficiently simulate FIFO behavior using these LIFO operations. This problem tests your understanding of data structure properties and how to combine simpler structures to create more complex behaviors.
```
Conceptual Approach

The key insight is using two LIFO containers: one for input operations and one for output operations. When adding elements, use the input container directly. When removing elements, transfer all elements from input to output (which reverses their order), then use the output container. This transformation converts the LIFO ordering into FIFO ordering. Think of it as having an "inbox" and an "outbox" where you periodically flip the inbox contents into the outbox to reverse the order.


Strategy to Solve
```
Two-container design - Use two LIFO containers: input_stack for enqueue operations and output_stack for dequeue operations. This separation allows you to manage the ordering transformation efficiently.

Lazy transfer strategy - Only transfer elements from input to output when the output container is empty and you need to perform a dequeue or front operation. This minimizes the number of transfer operations and provides good amortized performance.

Enqueue implementation - Always push new elements onto the input container. This operation is straightforward and maintains O(1) time complexity since no transfers are needed.

Dequeue implementation - If output container has elements, pop from it directly. If output container is empty but input container has elements, transfer all elements from input to output, then pop from output. Return appropriate values or handle empty cases.

Front element access - Similar to dequeue but without removing the element. Use the top of output container if available, otherwise transfer elements and use the top of output container.

Empty check optimization - The container is empty when both input and output containers are empty. This is a simple O(1) check that does not require any transfers.

Sample Execution
Let us trace through Example 1 operations with input_stack = [] and output_stack = [] initially.

Operation 1: enqueue(1) - We push 1 onto input_stack, making input_stack = [1] and output_stack = []. The container state is conceptually [1] with 1 at front.

Operation 2: enqueue(2) - We push 2 onto input_stack, making input_stack = [1, 2] and output_stack = []. The container state is conceptually [1, 2] with 1 at front and 2 at back.

Operation 3: front() - Since output_stack is empty, we need to transfer elements. We pop from input_stack to get 2 and push to output_stack, then pop from input_stack to get 1 and push to output_stack. After transfer we have input_stack = [] and output_stack = [2, 1]. We return the top of output_stack which is 1.

Operation 4: dequeue() - Since output_stack has elements [2, 1], we pop from output_stack to get 1. Now we have output_stack = [2] and input_stack = []. We return 1.

Operation 5: isEmpty() - We check both containers: input_stack = [] and output_stack = [2]. Since not both are empty, we return false.

The final state shows the container contains [2] with 2 at the front, demonstrating proper FIFO behavior using 
```

# 11. Azure Resource Efficiency Optimization

Microsoft Azure's Resource Manager tracks performance efficiency for consecutive time intervals throughout the day. Each interval represents a 15-minute window where Azure services either contribute positively to overall system efficiency (positive value) or create resource drain (negative value) based on workload patterns, auto-scaling decisions, and resource utilization.

The Azure optimization team wants to identify the optimal consecutive time window that would yield maximum cumulative efficiency gain. This analysis helps in understanding peak performance periods and optimizing future resource allocation strategies for better cost management and user experience.

Given an array of efficiency values for each time interval, determine the maximum efficiency achievable from any consecutive sequence of time intervals.

Task: Find the maximum sum from any consecutive subsequence of efficiency intervals.

Key Requirements:
```
Time window must include at least one interval
Intervals must be consecutive (adjacent time periods)
Handle large-scale Azure infrastructure data efficiently
Support both efficiency gains and resource drain scenarios
Optimize for real-time Azure resource management
This problem tests your understanding of dynamic programming, cloud resource optimization concepts, and efficient infrastructure data processing using Kadane's algorithm.
```

Problem Statement
You need to analyze Azure resource efficiency data to find the consecutive sequence of time intervals that yields maximum cumulative efficiency gain. This involves examining all possible consecutive time windows efficiently and identifying the one with highest efficiency potential. The challenge is processing large-scale cloud infrastructure data while maintaining optimal performance for real-time Azure resource management systems.

Conceptual Approach
The solution uses Kadane's algorithm adapted for cloud resource data: track the maximum efficiency achievable by either extending your current time window or starting a fresh window at each interval. 

```
Sample Execution
Let's analyze efficiency = [500, -1200, 800, 2000, -300, 1000] for Azure optimization:
```

```python
curMax = 0
maxTillNow = 0
for i in range(len(efficiency)):
    curMax = max(efficiency[i], curMax + efficiency[i])
    maxTillNow = max(maxTillNow, curMax)
return maxTillNow
```
Result: 3500 (optimal Azure resource window: intervals 3-6)

DP Efficiency: Each decision uses previously computed optimal values, avoiding redundant calculations for Azure's real-time processing requirements.

# 12. Document Processing Operation Optimizer

Microsoft Office's document processing engine supports batch operations that significantly improve productivity when handling large documents. The engine provides four fundamental operations:

Operation 1 (Type): Add one unit of content to the document. Operation 2 (Select All): Select all current document content. Operation 3 (Copy): Copy the selected content to clipboard buffer. Operation 4 (Paste): Paste the clipboard content, appending it to the current document.

The document processing team needs to optimize operation sequences to maximize content generation within a limited number of operations. This optimization is crucial for features like auto-generation, template expansion, and bulk document creation in Microsoft Word and other Office applications.

Given a limit of N operations, determine the maximum amount of content units that can be generated in a document. Each operation takes exactly one time unit, and the clipboard persists its content until overwritten by a new copy operation.


Problem Statement
You need to find the maximum number of content units that can be generated using N operations. The challenge is determining when to switch from typing to copy-paste operations to maximize output. This optimization problem reflects real-world scenarios in document processing where batch operations can significantly improve efficiency over sequential typing.

Conceptual Approach

The key insight is that copy-paste becomes beneficial only after accumulating enough content to multiply. For any remaining operations k, if you spend 3 operations on (Select All, Copy, Paste), you double your content. The optimal strategy involves finding the right balance between initial typing and subsequent copy-paste sequences. This is a classic dynamic programming problem where each state represents the maximum content achievable with i operations.

Strategy to Solve

Initialize base cases: With 0 operations, you have 0 content. With 1 operation, you can only type once.

Define state transition: For each number of operations i, consider two choices: - Type one more unit: dp[i] = dp[i-1] + 1 - Copy-paste from a previous state: Try all possible points j where you copy content from dp[j] and paste it multiple times

Copy-paste mechanics: If you copy at position j, you need 2 operations (Select All, Copy), then each paste operation multiplies the content by adding dp[j] units.

Optimization formula: For each i, check all j < i-2: - Remaining operations after copy: i - j - 2 - Number of pastes possible: (i - j - 2) - Total content: dp[j] * (i - j - 1)

Track maximum: At each step, keep the maximum content achievable across all strategies.

Handle edge cases: Ensure copy-paste is only considered when there are enough operations remaining (at least 3 operations needed for one complete copy-paste cycle).
```
Sample Execution
Let's trace through N = 7:

Base cases:
- dp[0] = 0 (no operations, no content)
- dp[1] = 1 (one type operation)
- dp[2] = 2 (two type operations)

dp[3] calculation:
- Option 1: Type → dp[2] + 1 = 3
- Option 2: Copy from dp[0] → Not beneficial
- Maximum: dp[3] = 3

dp[4] calculation:
- Option 1: Type → dp[3] + 1 = 4
- Option 2: Copy from dp[1] → 1 * (4-1-1) = 2
- Maximum: dp[4] = 4

dp[5] calculation:
- Option 1: Type → dp[4] + 1 = 5
- Option 2: Copy from dp[1] → 1 * 3 = 3
- Option 3: Copy from dp[2] → 2 * 2 = 4
- Maximum: dp[5] = 5

dp[6] calculation:
- Option 1: Type → dp[5] + 1 = 6
- Option 2: Copy from dp[2] → 2 * 3 = 6
- Option 3: Copy from dp[3] → 3 * 2 = 6
- Maximum: dp[6] = 6

dp[7] calculation:
- Option 1: Type → dp[6] + 1 = 7
- Option 2: Copy from dp[2] → 2 * 4 = 8
- Option 3: Copy from dp[3] → 3 * 3 = 9 ✓
- Option 4: Copy from dp[4] → 4 * 2 = 8
- Maximum: dp[7] = 9

Final answer: 9 content units

Time Complexity:
O(n²) - For each of the n operations, we check all previous states as potential copy points, resulting in nested iterations. The outer loop runs n times, and the inner loop runs up to i times for each i.

Space Complexity:
O(n) - We use a single dynamic programming array of size n+1 to store the maximum content achievable with each number of operations.
```
```cpp
class Solution {
public:
    long long maxRecords(int N) {
        vector<long long> dp(N + 1, 0);

        for (int i = 1; i <= N; i++) {

            // Option 1: linear build
            dp[i] = dp[i - 1] + 1;

            // Option 2: try current best breakpoint
			int j = 1;
            while (j <= i - 3) {
                long long val = dp[j] * (i - j - 2);
                dp[i] = max(dp[i], val);

                // heuristic: move j forward if it improves growth trend
                j++;
            }
        }

        return dp[N];
    }
};
```


# 13 Excel Formula Engine

Microsoft Excel processes billions of formulas daily across millions of spreadsheets worldwide. The formula engine is the heart of Excel, enabling users to create complex calculations that automatically update when dependent cells change. Your task is to design and implement a simplified version of Excel core formula engine focusing on the SUM function.

Design a system that supports:

Grid Initialization: Create a spreadsheet with specified dimensions. Excel uses letters for columns (A-Z) and numbers for rows, maintaining this familiar addressing system.

Cell Operations:
```
Set: Directly assign a value to a cell
Get: Retrieve the current value of a cell
Sum: Create a formula that calculates the sum of specified cells or ranges
Dependency Management: When a cell value changes, all formulas depending on it must automatically recalculate - this is Excel reactive computation model.

Range Support: Handle both individual cells (e.g., "A1") and rectangular ranges (e.g., "A1:B2") in formulas.

Implement the following functions:

Excel(int H, char W): Initialize a spreadsheet with H rows and width from column A to column W.

void Set(int row, char column, int val): Set the value of cell at (row, column).

int Get(int row, char column): Get the current value of cell at (row, column).

int Sum(int row, char column, List numbers): Create a SUM formula at (row, column) that adds values from cells/ranges specified in numbers.

Examples
Example 1
Input: Excel(3, "C")
Set(1, "A", 2)
Sum(3, "C", ["A1", "A1:B2"])
Set(2, "B", 2)
Get(3, "C")


Output: After Excel(3, "C"): 3x3 grid initialized
After Set(1, "A", 2): A1 = 2
After Sum(3, "C", ...): C3 = 4
After Set(2, "B", 2): B2 = 2
Get(3, "C") returns: 6


Explanation: Initial state: 3x3 grid with all zeros


Grid State After Excel(3, "C"):
A B C
1 [ 0][ 0][ 0]
2 [ 0][ 0][ 0]
3 [ 0][ 0][ 0]


After Set(1, "A", 2):
A B C
1 [ 2][ 0][ 0]
2 [ 0][ 0][ 0]
3 [ 0][ 0][ 0]


Sum(3, "C", ["A1", "A1:B2"]) calculation:

"A1" = 2

"A1:B2" range = A1 + B1 + A2 + B2 = 2 + 0 + 0 + 0 = 2

Total: 2 + 2 = 4, stored in C3


After Set(2, "B", 2):
A B C
1 [ 2][ 0][ 0]
2 [ 0][ 2][ 0]
3 [ 0][ 0][ 6]


C3 automatically updates to 6 because B2 changed:
New calculation: 2 + (2+0+0+2) = 6

Example 2
Input: Excel(4, "D")
Set(1, "A", 1)
Set(1, "B", 2)
Sum(1, "C", ["A1", "B1"])
Sum(1, "D", ["A1:C1"])
Set(1, "A", 5)
Get(1, "D")


Output: After initial sets: A1=1, B1=2
After Sum(1, "C"): C1=3
After Sum(1, "D"): D1=6
After Set(1, "A", 5): A1=5
Get(1, "D") returns: 12

Explanation: Dependency chain demonstration:

Initial Setup:
A B C D
1 [ 1][ 2][ 0][ 0]


After Sum(1, "C", ["A1", "B1"]):
C1 = A1 + B1 = 1 + 2 = 3
A B C D
1 [ 1][ 2][ 3][ 0]

After Sum(1, "D", ["A1:C1"]):
D1 = A1 + B1 + C1 = 1 + 2 + 3 = 6
A B C D
1 [ 1][ 2][ 3][ 6]


Dependency Graph:
A1 ──→ C1 ──→ D1
└──────────→ D1


When A1 changes to 5:

C1 updates: 5 + 2 = 7

D1 updates: 5 + 2 + 7 = 12


Final State:
A B C D
1 [ 5][ 2][ 7][12]

This demonstrates Excel cascading update mechanism.

Example 3
Input: Excel(5, "E")
Set(2, "B", 3)
Set(3, "C", 4)
Set(4, "D", 5)
Sum(5, "E", ["B2:D4"])
Get(5, "E")

Output: Initial sets create values
Sum(5, "E", ["B2:D4"]) creates formula
Get(5, "E") returns: 12


Explanation: Range B2:D4 forms a 3x3 rectangle:


Grid Layout:
A B C D E
1 [ 0][ 0][ 0][ 0][ 0]
2 [ 0][ 3][ 0][ 0][ 0]
3 [ 0][ 0][ 4][ 0][ 0]
4 [ 0][ 0][ 0][ 5][ 0]
5 [ 0][ 0][ 0][ 0][12]


Range B2:D4 contains:
B2=3, C2=0, D2=0
B3=0, C3=4, D3=0
B4=0, C4=0, D4=5


Sum calculation:
3 + 0 + 0 + 0 + 4 + 0 + 0 + 0 + 5 = 12


Excel efficiently calculates rectangular ranges, a common operation in financial modeling and data analysis.

Constraints
1 ≤ H ≤ 26 (number of rows)
A ≤ W ≤ Z (rightmost column)
1 ≤ row ≤ H
A ≤ column ≤ W
Cell values and sums fit in 32-bit integers
No circular references (Excel would show #REF! error)
Empty cells default to 0
```

Problem Statement
You need to implement a simplified version of Microsoft Excel formula engine that supports basic spreadsheet operations and the SUM formula. The key challenge is managing dependencies between cells so that when a cell value changes, all dependent formulas automatically recalculate. This reactive computation model is fundamental to how Excel provides real-time updates across complex spreadsheets.

Conceptual Approach
The solution requires two main components: a grid to store cell values and a dependency graph to track formula relationships. When a cell is updated, use topological traversal of the dependency graph to update all dependent cells in the correct order. Each cell can either store a direct value or a formula. Formula cells must maintain references to their dependencies and notify dependent cells when they change, implementing the observer pattern that Excel uses internally.

Strategy to Solve
```
Data Structure Design: Use 2D array for cell values, HashMap to store formula definitions, Graph structure for dependencies (adjacency list), Set to track which cells contain formulas.

Cell Addressing: Convert between (row, column_char) and internal indices, Parse cell references like "A1" and ranges like "A1:B2", Handle column letters (A=0, B=1, ..., Z=25).

Formula Storage: Store formula metadata - target cell and source cells/ranges, Maintain bidirectional dependency links, Differentiate between value cells and formula cells.

Update Propagation: When Set() is called, check if cell has dependents, Use BFS/DFS to find all affected formulas, Recalculate in dependency order (topological sort), Update each formula cell value.

Range Parsing: Split range string on colon delimiter, Extract row/column from each cell reference, Calculate all cells within rectangular bounds, Handle single cells as 1x1 ranges.

Sum Calculation: Parse each element in the numbers list, For each cell/range retrieve current values, Aggregate sum and store in target cell, Register dependencies for future updates.

Sample Execution
Let us trace through a complex example:

Step 1: Excel(4, "D") - Create 4x4 grid

Step 2: Set values
Set(1, "A", 10) → A1 = 10
Set(2, "A", 20) → A2 = 20
Set(1, "B", 30) → B1 = 30

Step 3: Sum(3, "A", ["A1", "A2"])
- Parse formula: A3 = A1 + A2
- Calculate: 10 + 20 = 30
- Store dependencies: A1→A3, A2→A3

Dependency Graph State:
A1 ──→ A3
A2 ──→ A3

Step 4: Sum(3, "B", ["A1:B2"])
- Parse range A1:B2 = {A1, B1, A2, B2}
- Calculate: 10 + 30 + 20 + 0 = 60
- Store dependencies: A1→B3, B1→B3, A2→B3, B2→B3

Updated Dependency Graph:
A1 ──→ A3
A1 ──→ B3
A2 ──→ A3
A2 ──→ B3
B1 ──→ B3

Step 5: Sum(4, "C", ["A3", "B3"])
- Calculate: 30 + 60 = 90
- Dependencies: A3→C4, B3→C4

Final Dependency Graph:
A1 ──→ A3 ──→ C4
A1 ──→ B3 ──→ C4
A2 ──→ A3
A2 ──→ B3
B1 ──→ B3

Step 6: Set(1, "A", 50)
- Direct update: A1 = 50
- Find dependents: {A3, B3}
- Update A3: 50 + 20 = 70
- Update B3: 50 + 30 + 20 + 0 = 100
- Find C4 depends on A3, B3
- Update C4: 70 + 100 = 170
```

```cpp
#include <bits/stdc++.h>
using namespace std;

using Pos = pair<int, char>;  // (row, column)

struct Cell {
    int value = 0;
    vector<string> formula;   // stores the raw list like {"A1", "B2:C3"}
    bool isFormula = false;
};

class Excel {
private:
    int rows, cols;
    vector<vector<Cell>> sheet;
    
    // Dependency Graph: cell -> list of cells that depend on it
    unordered_map<int, unordered_set<int>> dependents;
    
    // Flatten position for graph: row*100 + (col-'A')
    int getId(int r, char c) {
        return (r * 100) + (c - 'A');
    }

    Pos parsePos(const string& s) {
        return {stoi(s.substr(1)), s[0]};
    }

    // Parse range "A1:B3" into list of positions
    vector<Pos> getAllCellsInRange(const string& s) {
        vector<Pos> cells;
        if (s.find(':') == string::npos) {
            cells.push_back(parsePos(s));
        } else {
            size_t colon = s.find(':');
            string start = s.substr(0, colon);
            string end = s.substr(colon + 1);
            int r1 = stoi(start.substr(1)), r2 = stoi(end.substr(1));
            char c1 = start[0], c2 = end[0];
            for (int r = r1; r <= r2; ++r) {
                for (char c = c1; c <= c2; ++c) {
                    cells.emplace_back(r, c);
                }
            }
        }
        return cells;
    }

    // Calculate current sum of a formula
    int calculateSum(const vector<string>& formula) {
        int sum = 0;
        for (const string& s : formula) {
            for (Pos p : getAllCellsInRange(s)) {
                int r = p.first;
                char c = p.second;
                if (r >= 1 && r <= rows && c >= 'A' && c < 'A' + cols) {
                    sum += sheet[r-1][c-'A'].value;
                }
            }
        }
        return sum;
    }

    // Update all dependent cells using BFS
    void updateDependents(int startRow, char startCol) {
        queue<Pos> q;
        unordered_set<int> visited;
        
        q.emplace(startRow, startCol);
        visited.insert(getId(startRow, startCol));

        while (!q.empty()) {
            auto [r, c] = q.front(); q.pop();
            int id = getId(r, c);
            
            // Update this cell if it has a formula
            Cell& cell = sheet[r-1][c-'A'];
            if (cell.isFormula) {
                cell.value = calculateSum(cell.formula);
            }

            // Propagate to cells that depend on this one
            for (int depId : dependents[id]) {
                if (visited.find(depId) == visited.end()) {
                    visited.insert(depId);
                    int depR = depId / 100;
                    char depC = (depId % 100) + 'A';
                    q.emplace(depR, depC);
                }
            }
        }
    }

    // Remove old dependencies when setting new value or formula
    void removeOldDependencies(int row, char col) {
        int myId = getId(row, col);
        for (auto& [_, deps] : dependents) {
            deps.erase(myId);
        }
    }

public:
    Excel(int height, char widthChar) {
        rows = height;
        cols = widthChar - 'A' + 1;
        sheet.assign(height, vector<Cell>(cols));
    }

    void set(int row, char column, int val) {
        if (row < 1 || row > rows || column < 'A' || column >= 'A' + cols) return;
        
        removeOldDependencies(row, column);
        
        Cell& cell = sheet[row-1][column-'A'];
        cell.value = val;
        cell.isFormula = false;
        cell.formula.clear();

        updateDependents(row, column);
    }

    int get(int row, char column) {
        if (row < 1 || row > rows || column < 'A' || column >= 'A' + cols) return 0;
        return sheet[row-1][column-'A'].value;
    }

    int sum(int row, char column, vector<string> numbers) {
        if (row < 1 || row > rows || column < 'A' || column >= 'A' + cols) return 0;

        Cell& cell = sheet[row-1][column-'A'];
        
        // Remove old dependencies
        removeOldDependencies(row, column);
        
        cell.formula = numbers;
        cell.isFormula = true;
        cell.value = calculateSum(numbers);

        // Build new dependency graph
        int myId = getId(row, column);
        for (const string& s : numbers) {
            for (Pos p : getAllCellsInRange(s)) {
                int depId = getId(p.first, p.second);
                dependents[depId].insert(myId);
            }
        }

        updateDependents(row, column);  // Propagate if needed
        return cell.value;
    }
};
```

Test it:
```cpp
int main() {
    Excel excel(3, 'C');
    excel.set(1, 'A', 2);
    excel.set(1, 'B', 3);
    excel.sum(3, 'C', {"A1", "B1"});   // 5

    cout << excel.get(3, 'C') << endl; // 5

    excel.set(1, 'A', 10);
    cout << excel.get(3, 'C') << endl; // 13 (automatically updated via BFS)

    return 0;
}
```

# 14 Document Version History Navigator

Problem Description

You need to implement a VersionHistoryNavigator that can sequentially traverse all document versions across all users in chronological order. The navigator should provide functionality to check if more versions exist and retrieve the next version ID efficiently without loading the entire version history into memory at once.

Your implementation must handle the streaming nature of version data - you cannot assume all version histories are loaded upfront, and you should process versions lazily to optimize memory usage for documents with extensive edit histories.


Example
```python
Input: userVersions = [[501, 502], [503], [504]]
VersionHistoryNavigator navigator = new VersionHistoryNavigator(userVersions);


Output: navigator.getNext(); // return 501
navigator.getNext(); // return 502
navigator.getNext(); // return 503
navigator.hasMoreVersions(); // return true
navigator.getNext(); // return 504
navigator.hasMoreVersions(); // return false


Explanation: The navigator sequentially returns versions from user 0 (501, 502), then user 1 (503), then user 2 (504). After all versions are processed, hasMoreVersions() returns false.
```


Problem Statement

You need to build a navigator that traverses document version histories from multiple users sequentially. Each user has a chronological list of version IDs (which could be empty), and you must provide a way to retrieve the next version across all users in order, plus check if more versions exist. The key challenge is handling this efficiently without loading all version histories into memory at once.


Conceptual Approach

The core insight is implementing a stateful iterator using two pointers - one tracking the current user and another tracking the position within that user's version history. You maintain these pointers to know exactly where you are in the 2D structure at any given time. When you exhaust one user's versions, you advance to the next user with a non-empty history. This approach processes data lazily, making it memory-efficient for documents with extensive histories.

Strategy to Solve

Initialize tracking pointers: Set up currentUser and currentVersionIndex to track your location in the 2D structure. Start both at 0.

Implement smart advancement logic: Create a helper method that skips users with empty histories and positions you at the next valid version. This handles cases where multiple consecutive users might have no edits.

Build hasMoreVersions() efficiently: Use your advancement logic to check if there's a next valid version without actually consuming it. This requires careful state management to avoid side effects.

Implement getNext() with validation: First ensure there's a next version available, then return the current version and advance your pointers to the next position.

Handle edge cases gracefully: Account for documents where no users made edits, single-version scenarios, and boundary conditions when transitioning between users.

Maintain state consistency: Ensure your pointers always reflect the correct position, especially after consuming versions or checking availability.
```
Sample Execution
Let's trace through `userVersions = [[601], [], [602, 603], []]`:

Initialization:
- `currentUser = 0`, `currentVersionIndex = 0`
- `userVersions[0] = [601]` (valid)

First `hasMoreVersions()` call:
- Current position points to `userVersions[0][0] = 601`
- Returns `true`

First `getNext()` call:
- Returns `601`
- Advances: `currentVersionIndex = 1`
- Since `currentVersionIndex >= userVersions[0].length`, move to next user
- `currentUser = 1`, `currentVersionIndex = 0`
- `userVersions[1] = []` (empty), so advance again
- `currentUser = 2`, `currentVersionIndex = 0`

Second `getNext()` call:
- Returns `userVersions[2][0] = 602`
- Advances: `currentVersionIndex = 1`

Third `getNext()` call:
- Returns `userVersions[2][1] = 603`
- Advances: `currentVersionIndex = 2`
- Since `currentVersionIndex >= userVersions[2].length`, advance user
- `currentUser = 3`, but `userVersions[3] = []` (empty)
- `currentUser = 4` (out of bounds)

Final `hasMoreVersions()` call:
- `currentUser >= userVersions.length`, so return `false`
```
Performance Analysis

Time Complexity:

O(1) amortized for both operations - Each version is visited exactly once across all calls. The advancement logic might skip users with no edits, but total work is bounded by the number of users.

Space Complexity:

O(1) - Only storing two integer pointers regardless of input size. No additional data structures needed.


# 15 Office Add-in Dependency Resolver

Microsoft Office supports third-party add-ins that enhance productivity across Word, Excel, and PowerPoint. When users install multiple add-ins, the Office platform must determine the correct initialization sequence to ensure dependencies are loaded before dependent add-ins attempt to access their functionality.

Each add-in may depend on specific APIs or features provided by other add-ins that must be initialized first. The Office Add-in Manager needs to analyze dependency relationships and determine a valid loading order that satisfies all requirements, or detect when circular dependencies make initialization impossible.

Your task is to implement a dependency resolver that takes a list of add-in names and their dependency relationships, then determines a valid initialization sequence that ensures all dependencies are loaded before dependent add-ins.

Given a list of add-in names and dependency pairs, find a valid loading order for the add-ins, or return an empty result if circular dependencies exist.
```
Examples
Example 1
Input: addins = ["WordSpell", "ExcelChart", "PowerBI", "Translator"], dependencies = [["WordSpell", "Translator"], ["ExcelChart", "PowerBI"]]


Output: ["WordSpell", "ExcelChart", "Translator", "PowerBI"]


Explanation: Valid loading order: WordSpell loads first (no dependencies), then ExcelChart (no dependencies), then Translator (depends on WordSpell), finally PowerBI (depends on ExcelChart). All dependencies satisfied in correct sequence.


Dependency Analysis:
WordSpell → Translator
ExcelChart → PowerBI
Loading sequence satisfies all constraints ✓

Example 2
Input: addins = ["Base", "Extended"], dependencies = [["Base", "Extended"]]


Output: ["Base", "Extended"]


Explanation: Single dependency relationship: Extended add-in requires Base add-in to be loaded first. Valid loading sequence starts with Base, followed by Extended add-in.


Load Order:


Base (no dependencies)

Extended (depends on Base)
Sequence satisfies dependency requirement ✓

Example 3
Input: addins = ["AddinA", "AddinB", "AddinC"], dependencies = [["AddinA", "AddinB"], ["AddinB", "AddinC"], ["AddinC", "AddinA"]]


Output: []

Explanation: Circular dependency chain: AddinA → AddinB → AddinC → AddinA creates impossible loading requirements. No valid initialization sequence exists since each add-in depends on another in the cycle.

Circular Chain:
AddinA needs AddinB
AddinB needs AddinC

AddinC needs AddinA
Result: Impossible to resolve ✗
```


Notes
```
Build directed graph where edges represent dependency relationships
Use topological sorting to find valid initialization sequence
Detect cycles using DFS or in-degree counting to identify circular dependencies
Handle isolated add-ins (no dependencies) appropriately in loading order
Optimize for Office real-time add-in management during application startup
Consider integration with Office extensibility framework and COM interfaces
```

Problem Explanation

You need to determine a valid initialization sequence for Office add-ins based on their dependency relationships, or detect when circular dependencies make initialization impossible. The challenge involves building a dependency graph from add-in relationships and finding a topological ordering while detecting cycles that indicate unresolvable dependencies. This problem tests your understanding of dependency resolution algorithms crucial to Microsoft Office's add-in management system and extensibility framework.


Conceptual Approach

The solution involves creating a directed graph where add-ins are nodes and dependencies are edges pointing from prerequisites to dependent add-ins. A topological sort of this graph yields a valid loading sequence, while cycle detection identifies circular dependencies that make initialization impossible. The key insight is that add-in dependency relationships form a directed acyclic graph (DAG) when resolvable, and topological sorting provides an efficient way to find valid initialization orders for Office's add-in loading system.


Strategy to Solve

Build dependency graph from add-in relationships: Create a directed graph where each add-in is a node and each dependency creates an edge from prerequisite to dependent add-in. This graph represents all loading constraints that Office must satisfy during add-in initialization.

Initialize graph data structures efficiently: Set up adjacency lists for the dependency graph and in-degree counters for each add-in. The in-degree represents how many other add-ins must load before the current add-in can be initialized safely.

Identify add-ins with no prerequisites: Find all add-ins with zero in-degree (no dependencies), as these can be loaded immediately when Office starts. These form the starting points for the dependency resolution process.

Apply topological sorting using Kahn's algorithm: Process add-ins with zero in-degree first, then reduce in-degrees of their dependent add-ins. Continue until all add-ins are processed or no more zero in-degree add-ins remain available for processing.

Detect circular dependencies through completion check: If the topological sort doesn't process all add-ins, remaining add-ins form circular dependency cycles that prevent successful initialization. Return empty array to indicate impossible loading configuration.

Return valid loading sequence for Office initialization: If all add-ins are successfully processed, return the topological order as a valid initialization sequence that Office can use to load add-ins without dependency conflicts.

Sample Execution
```
Let's trace through addins = ["WordAPI", "ExcelExt", "PowerExt"], dependencies = [["WordAPI", "ExcelExt"], ["WordAPI", "PowerExt"]]:

Step 1: Build dependency graph for Office add-ins
Nodes: {WordAPI, ExcelExt, PowerExt}
Dependencies:
- WordAPI → ExcelExt (WordAPI must load before ExcelExt)
- WordAPI → PowerExt (WordAPI must load before PowerExt)

Step 2: Initialize in-degree counters
in_degree = {
WordAPI: 0, # No dependencies
ExcelExt: 1, # Depends on WordAPI
PowerExt: 1 # Depends on WordAPI
}

Step 3: Find add-ins with no prerequisites
zero_in_degree = [WordAPI] # Only WordAPI has no dependencies

Step 4: Apply topological sorting (Kahn's algorithm)

Iteration 1:
- Process: WordAPI
- Add to result: [WordAPI]
- Update dependent add-ins:
- ExcelExt in-degree: 1 → 0 (add to queue)
- PowerExt in-degree: 1 → 0 (add to queue)
- Queue: [ExcelExt, PowerExt]

Iteration 2:
- Process: ExcelExt
- Add to result: [WordAPI, ExcelExt]
- No dependent add-ins to update
- Queue: [PowerExt]

Iteration 3:
- Process: PowerExt
- Add to result: [WordAPI, ExcelExt, PowerExt]
- No dependent add-ins to update
- Queue: []

Step 5: Validate complete resolution
Processed add-ins: 3
Total add-ins: 3
All add-ins processed successfully ✓

Step 6: Return Office loading sequence
Valid initialization order: [WordAPI, ExcelExt, PowerExt]

Office Add-in Loading Analysis:
1. WordAPI loads first (provides base API functionality)
2. ExcelExt loads second (can safely access WordAPI features)
3. PowerExt loads third (can safely access WordAPI features)
```
This sequence ensures all Office add-ins initialize with their dependencies satisfied.


Performance Analysis

Time Complexity
O(V + E)

Space Complexity
O(V + E)


Time Complexity:
O(V + E) where V represents the number of add-ins and E represents the number of dependency relationships. The algorithm processes each add-in exactly once and examines each dependency relationship once during graph construction and topological sorting phases.

Space Complexity:
O(V + E) for storing the dependency graph adjacency lists, in-degree counters for each add-in, and the queue used during topological sorting. The space requirements scale linearly with the number of add-ins and their dependency relationships.

Analysis:
This approach provides optimal performance for Microsoft Office's add-in dependency resolution requirements. The linear time complexity ensures efficient initialization during Office application startup, even with complex add-in ecosystems. Topological sorting with Kahn's algorithm is the standard efficient method for dependency resolution, and the O(V + E) complexity cannot be improved since all add-ins and dependencies must be examined. This efficiency is crucial for Office's real-time add-in management system that must resolve dependencies quickly during application launch to maintain responsive user experience. The algorithm's performance characteristics support seamless integration with Office's extensibility framework and COM interfaces, enabling rapid dependency validation decisions that directly impact application startup time and add-in compatibility across Word, Excel, and PowerPoint.

```cpp
#include <bits/stdc++.h>
using namespace std;

class AddinManager {
public:
    vector<string> findOrder(vector<string>& addins, vector<vector<string>>& dependencies) {
        // Build graph and indegree map
        unordered_map<string, vector<string>> graph;        // prerequisite -> list of dependents
        unordered_map<string, int> indegree;
        
        // Initialize all add-ins with 0 indegree
        for (const string& addin : addins) {
            indegree[addin] = 0;
            graph[addin] = {};
        }
        
        // Build dependency graph: A depends on B → B must come before A
        for (const auto& dep : dependencies) {
            string dependent = dep[0];    // add-in that needs something
            string prereq    = dep[1];    // add-in that must load first
            
            graph[prereq].push_back(dependent);
            indegree[dependent]++;
        }
        
        // Kahn's Algorithm (BFS) for topological sort
        queue<string> q;
        vector<string> order;
        
        // Start with add-ins that have no dependencies
        for (const auto& [addin, deg] : indegree) {
            if (deg == 0) {
                q.push(addin);
            }
        }
        
        while (!q.empty()) {
            string curr = q.front();
            q.pop();
            order.push_back(curr);
            
            for (const string& next : graph[curr]) {
                indegree[next]--;
                if (indegree[next] == 0) {
                    q.push(next);
                }
            }
        }
        
        // If we couldn't process all add-ins → cycle exists
        if (order.size() == addins.size()) {
            return order;
        }
        return {};
    }
};

int main() {
    AddinManager manager;
    
    vector<string> addins = {"WordHelper", "ExcelCore", "PowerPointUI", "DataAnalyzer", "ChartEngine"};
    
    vector<vector<string>> dependencies = {
        {"ExcelCore", "WordHelper"},      // ExcelCore depends on WordHelper
        {"PowerPointUI", "ExcelCore"},
        {"DataAnalyzer", "ExcelCore"},
        {"ChartEngine", "DataAnalyzer"}
    };
    
    vector<string> order = manager.findOrder(addins, dependencies);
    
    if (order.empty()) {
        cout << "Circular dependency detected! Cannot initialize." << endl;
    } else {
        cout << "Valid initialization order:" << endl;
        for (const string& addin : order) {
            cout << addin << " → ";
        }
        cout << "Done" << endl;
    }
    
    return 0;
}
```
output:
```
Valid initialization order:
WordHelper → ExcelCore → PowerPointUI → DataAnalyzer → ChartEngine → Done
```

# 16 Azure Resource Dependency Optimization => Serialize or Deseialize a tree
```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    void tree2str(TreeNode* node, string& s)
    {
        if(!node)
            s += "null,";
        else
        {
            s += to_string(node->val);
            s += ",";
            tree2str(node->left, s);
            tree2str(node->right, s);
        }
    }

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string str = "";
        tree2str(root, str);
        return str;
    }

    TreeNode *build(string& data){
        int index = data.find(",");
        string val = data.substr(0, index);

        data = data.substr(index + 1);

        if(val=="null") 
            return nullptr;

        TreeNode * curr=new TreeNode(stoi(val));

        curr->left=build(data);
        curr->right=build(data);
        return curr;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        return build(data);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
```

# 17 Distributed Dictionary Search => Word Search in a Matrix
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

A Trie Node
```cpp
class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord = false;
    
    TrieNode() = default;
};

class Trie {
private:
    TrieNode* root;
    
public:
    Trie() {
        root = new TrieNode();
    }
    
    // Insert a word into the trie
    void insert(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (node->children.find(ch) == node->children.end()) {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->isEndOfWord = true;
    }
    
    // Search for a complete word
    bool search(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (node->children.find(ch) == node->children.end()) {
                return false;
            }
            node = node->children[ch];
        }
        return node->isEndOfWord;
    }
}
```

# 18 Teams Meeting Priority Scheduler

Microsoft Teams organizes meeting scheduling requests in a hierarchical priority structure where urgent meetings are escalated through management chains. Each node represents a meeting request with specific urgency levels, and the scheduling system needs to identify the highest-priority urgent meeting at the deepest escalation level for immediate processing.

The meeting scheduler prioritizes requests that have been escalated the most levels through the organizational hierarchy, and when multiple urgent meetings exist at the same escalation depth, it selects the earliest submitted request to maintain fair processing order across Teams users.

Your task is to implement a meeting priority algorithm that traverses the escalation hierarchy and identifies the earliest submitted urgent meeting at the maximum escalation level.

Given a binary tree representing the meeting escalation hierarchy, find the value of the earliest submitted meeting at the deepest escalation level.

Examples
Example 1
Input: Tree: [1001, 2001, 3001]


Output: 2001


Explanation: Meeting escalation: Level 0 has Meeting_1001, Level 1 has Meeting_2001 and Meeting_3001. Deepest escalation level is 1 with two meetings. Earliest submitted meeting at this level is Meeting_2001, scheduled for immediate processing.


Notes:
```
Implement using level-order traversal (BFS) for efficient escalation level processing
Process meetings left-to-right at each level to ensure earliest submission priority

For BFS solution, final level processed contains deepest escalations
First meeting in that level represents earliest submission at maximum escalation
```

# 19 [672]. Bulb Switcher II AKA Switchstorm
https://leetcode.com/problems/bulb-switcher-ii/description/

There is a room with n bulbs labeled from 1 to n that all are turned on initially, and four buttons on the wall. Each of the four buttons has a different functionality where:
```
Button 1: Flips the status of all the bulbs.
Button 2: Flips the status of all the bulbs with even labels (i.e., 2, 4, ...).
Button 3: Flips the status of all the bulbs with odd labels (i.e., 1, 3, ...).
Button 4: Flips the status of all the bulbs with a label j = 3k + 1 where k = 0, 1, 2, ... (i.e., 1, 4, 7, 10, ...).
```
You must make exactly presses button presses in total. For each press, you may pick any of the four buttons to press.

Given the two integers n and presses, return the number of different possible statuses after performing all presses button presses.

Intuition
The key insight is recognizing that pressing the same button twice cancels out its effect - each button toggles bulbs, so pressing it an even number of times returns bulbs to their original state. This means we only care about whether each button is pressed an odd or even number of times, not the exact sequence.

```cpp
class Solution {
public:
    int flipLights(int n, int presses) {
        n = min(n, 3);
        presses = min(presses, 3);

        if (n == 1) return presses == 0 ? 1 : 2;
        if (n == 2) return vector<int>{1, 3, 4, 4}[presses];
        return vector<int>{1, 4, 7, 8}[presses];
    }
};

Why this works:

There are 4 operations, but Op1 = Op2 XOR Op3 (flipping all = flip evens + flip odds). So only 3 are linearly independent.
3 independent binary operations → max 2³ = 8 distinct states.
With n=1, Op2/Op3/Op4 all behave identically to Op1, so you get just 2 states (on/off).
With n=2, Op3 and Op4 are equivalent, leaving 3 independent ops → max 4 states.
Once presses ≥ 3, you've exhausted all reachable states — extra presses just revisit them.
```

# 20 [419]. Battleships in a Board
https://leetcode.com/problems/battleships-in-a-board/description/

Microsoft's gaming division is developing a strategic game where an n x n matrix board represents a battlefield, with each cell being a battleship "X" or empty ".". Return the number of the battleships on board.

Battleships can only be placed horizontally or vertically on board. In other words, they can only be made of the shape 1 x k (1 row, k columns) or k x 1 (k rows, 1 column), where k can be of any size. At least one horizontal or vertical cell separates between two battleships (i.e., there are no adjacent battleships).

```
Examples
Example 1
Input: board = [["X",".",".","X"],[".",".",".","X"]]

Output: 2
```

```cpp
class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        int rows = board.size();
        int cols = board[0].size();
        int count = 0;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {

                if (board[i][j] == '.') {
                    continue;
                }

                // Skip if part of a battleship already counted
                if (i > 0 && board[i - 1][j] == 'X') {
                    continue;
                }

                if (j > 0 && board[i][j - 1] == 'X') {
                    continue;
                }

                count++;
            }
        }

        return count;
    }
};
```

# 21 Water Allocation Challenge
Microsoft is developing an advanced water management system for its Azure data centers, where water is used for cooling infrastructure. You are given two water jugs with capacities x liters and y liters, with access to an infinite water supply from a central reservoir. Your task is to determine whether it is possible to measure exactly target liters of water as the total amount across both jugs using the following operations: • Fill either jug completely with water from the reservoir. • Empty either jug completely. • Pour water from one jug into another until the receiving jug is full or the transferring jug is empty. This solution is critical for optimizing water usage in Microsoft's sustainable data center operations, ensuring precise allocation for cooling systems under varying demand.

This is the classic **Water and Jug Problem** (LeetCode 365).

### Key Observation (Bézout's Theorem)

It is possible to measure exactly `target` liters iff:

1. `target <= x + y`
2. `target` is a multiple of `gcd(x, y)`

Mathematically:

target % gcd(x, y) == 0

and

target <= x + y

---

### Why?

Using the allowed operations (fill, empty, pour), you can create any quantity that is a multiple of `gcd(x, y)`.

For example:

* `x = 3`, `y = 5`
* `gcd(3,5) = 1`

Since every number ≤ 8 is a multiple of 1, you can measure any target from 0 to 8.

---

### C++ Solution

```cpp
class Solution {
public:
    bool canMeasureWater(int x, int y, int target) {
        if (target == 0)
            return true;

        if (target > x + y)
            return false;

        return target % gcd(x, y) == 0;
    }

private:
    int gcd(int a, int b) {
        while (b) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
};
```

### Using STL

```cpp
#include <numeric>

class Solution {
public:
    bool canMeasureWater(int x, int y, int target) {
        if (target > x + y)
            return false;

        return target % std::gcd(x, y) == 0;
    }
};
```

---

### Examples

#### Example 1

```text
x = 3, y = 5, target = 4
```

* gcd(3,5) = 1
* 4 ≤ 8
* 4 % 1 = 0

✅ Answer: `true`

---

#### Example 2

```text
x = 2, y = 6, target = 5
```

* gcd(2,6) = 2
* 5 % 2 = 1

❌ Answer: `false`

---

### Complexity

* **Time:** `O(log(min(x, y)))`
* **Space:** `O(1)`

This is the optimal mathematical solution and is the expected answer for **LeetCode 365 - Water and Jug Problem**.

# 22 [179]. Optimal Resource Distribution Puzzle

During a recent Microsoft interview for a new graduate role, candidates were tasked with solving a resource allocation problem inspired by Azure’s cloud resource management. You are given an array representing the resource demands (in units) of n servers in a data center, and an integer k representing the maximum number of servers that can be grouped together for optimal load balancing. The goal is to partition the array into the minimum number of subarrays, where each subarray contains at most k servers, such that the maximum resource demand within each subarray does not exceed a given threshold x. Determine the smallest possible threshold x that allows such a partition.

This problem was designed to test your ability to optimize resource distribution, a key challenge in Microsoft’s cloud infrastructure.

Examples
Example 1
Input: demands = [2, 4, 6], k = 2

Output: 6

Explanation: With demands [2, 4, 6] and k = 2, the minimum threshold is 6. Partition into [2, 4] and [6], where max in each subarray (4 and 6) does not exceed 6.

Algorithm
```
Step 1: Binary search range
low = max(nums) (must fit at least one element)
high = sum(nums)
Step 2: Greedy check

For each mid:

simulate grouping
count required subarrays
```

```cpp
class Solution {
public:
    bool canPartition(vector<int>& nums, int k, long long x) {
        int countGroups = 1;
        long long currSum = 0;
        int currSize = 0;

        for (int num : nums) {
            // if single element > x → impossible
            if (num > x) return false;

            // if adding breaks constraints → new group
            if (currSize == k || currSum + num > x) {
                countGroups++;
                currSum = num;
                currSize = 1;
            } else {
                currSum += num;
                currSize++;
            }
        }

        return true;
    }

    long long minimumThreshold(vector<int>& nums, int k) {
        long long low = *max_element(nums.begin(), nums.end());
        long long high = accumulate(nums.begin(), nums.end(), 0LL);

        long long ans = high;

        while (low <= high) {
            long long mid = low + (high - low) / 2;

            if (canPartition(nums, k, mid)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return ans;
    }
};
```

# 23 Remove Comments problem (LeetCode 722)

We scan character-by-character while maintaining a state:

### States

* `inBlock = true/false`

### Tokens

* `//` → ignore rest of line
* `/*` → enter block comment
* `*/` → exit block comment

### Important behavior

* Everything inside `/* ... */` is ignored (even `//`)
* Everything after `//` is ignored (even `/*`)
* Block comments can span multiple lines
* Output lines are formed only from visible characters

---

# 💡 Approach

We:

1. Iterate line by line
2. Use a buffer for current output line
3. Scan each character
4. Handle:

   * block comment state
   * line comment break
5. Push non-empty results

---

# 💻 C++ Solution

```cpp id="sdl_remove_comments"
class Solution {
public:
    vector<string> removeComments(vector<string>& config_lines) {
        vector<string> result;
        string current;
        bool inBlock = false;

        for (string &line : config_lines) {
            int i = 0;
            int n = line.size();

            while (i < n) {

                if (!inBlock && i + 1 < n && line[i] == '/' && line[i + 1] == '/') {
                    // Line comment starts → ignore rest of line
                    break;
                }

                if (!inBlock && i + 1 < n && line[i] == '/' && line[i + 1] == '*') {
                    // Block comment starts
                    inBlock = true;
                    i += 2;
                    continue;
                }

                if (inBlock && i + 1 < n && line[i] == '*' && line[i + 1] == '/') {
                    // Block comment ends
                    inBlock = false;
                    i += 2;
                    continue;
                }

                if (!inBlock) {
                    current.push_back(line[i]);
                }

                i++;
            }

            // If not inside block comment, line ends here
            if (!inBlock && !current.empty()) {
                result.push_back(current);
                current.clear();
            }
        }

        return result;
    }
};
```

---

# 📊 Complexity

* Time: **O(total characters)**
* Space: **O(output size)**

---

# 🧠 Intuition Summary

We are basically simulating a **stream parser**:

* `//` = kill rest of line
* `/* ... */` = toggle “ignore mode”
* Everything else = keep

The tricky part is:

> block comments can merge lines logically

So we only push to result when we are **not inside a block comment**.

---

# 🏠 LeetCode 198 — House Robber

### Problem

You are given an array `nums` where `nums[i]` represents money in the i-th house.

You cannot rob **two adjacent houses**.

Return the **maximum amount of money** you can rob.

---

At each house, you have 2 choices:

### 1. Rob it

You cannot rob previous house:

nums[i] + dp[i-2]


### 2. Skip it


dp[i-1]


So recurrence:


dp[i] = max(dp[i-1], nums[i] + dp[i-2])


---

# ⚡ Optimized Insight

We only need:

* prev1 = dp[i-1]
* prev2 = dp[i-2]

So we reduce space to **O(1)**.

---

# 💻 C++ Solution (Optimized)

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        int prev2 = 0; // dp[i-2]
        int prev1 = 0; // dp[i-1]

        for (int num : nums) {
            int take = num + prev2;
            int skip = prev1;

            int curr = max(take, skip);

            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};
```

---

# 📊 Example

```text
nums = [2, 7, 9, 3, 1]
```

| House | Take | Skip | Best |
| ----- | ---- | ---- | ---- |
| 2     | 2    | 0    | 2    |
| 7     | 7    | 2    | 7    |
| 9     | 11   | 7    | 11   |
| 3     | 10   | 11   | 11   |
| 1     | 12   | 11   | 12   |

✅ Answer = **12**

---

# Microsoft Interview Process: 
Interview panelists
- Coding + Behavioral
- System Design + Behavioral

 
The goal of the Microsoft interview process is twofold: It’s not only an opportunity for us to get to know you, but also for you to know us. The interviews will include competency-based questions, as well as questions about your resume/experience.

Keep our Four Core Competencies in mind. Think of examples you can share or incorporate into your conversation.  

## Microsoft Core Competencies: 

### Adaptability
Demonstrates curiosity and actively explores options. Responds efficiently to changing demands and circumstances. Functions effectively in ambiguous situations. Maintains a constructive attitude in times of stress. 
 
### Collaboration
Drives alignment and teamwork within a team, department, or across organizational boundaries. Combines resources and joins efforts to achieve company-wide goals. 
 
### Customer Focus
Anticipates customer needs, and proactively meets and exceeds customer expectations. Recognizes the issues that customers want to resolve, and creates, or facilitates the creation of, products and services to address customer needs. 
 
### Drive for Results
Tenaciously pursues positive outcomes by using effective approaches to solve problems. Delivers on commitments and seeks increasingly challenging work. Takes responsibility and holds others accountable for actions, decisions, and goals. 
 
## Accelerate Our Culture: 
At Microsoft, we believe that living our culture is key to achieving our mission. Selecting people who have the right skills and mindset is important, not only for the company we are today, but also for the company we aspire to be. Our growth-mindset culture is designed to drive innovation and collaboration. Being a learn-it-all instead of a know-it-all fosters curiosity and prompts us to be inclusive and seek new and diverse perspectives. 

 
For our interview process, we focus on these key aspects of our culture: 

​​​​​​- Growth Mindset – True learners who can acquire new skills rapidly and connect with others to help bring big ideas to life. 
- Diverse & Inclusive – Being open to learning about your own biases and changing behaviors accordingly. Value differences, seek them out, and invite them in. 
- One Microsoft –  Actively seeks collaboration with others and looks for common ground across differences, contributes to and builds on success of others, and prioritizes for customer and team within their role. 
- Customer Obsession – The ability to learn about customers' perspectives, show empathy to their experiences, and incorporate these insights into their decisions and deliverables. 
- Values – When we come together, we treat each other with respect, we act with integrity, and we are accountable to one another for our words and actions. 
 

**Tips for your interview: **

Using the competencies and culture attributes listed above, prepare 1-2 examples that you can share with the interviewers that demonstrates how you’ve exemplified these traits in the past. 

 

Review the Job Description, what are the requirements of the role.  Are you able to articulate work you have done in that space? 

 

We use Behavioral Based interviewing.  This means we will focus on work that you have done historically as the best predictor of the work you will do in the future.  
