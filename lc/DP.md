## Dynamic Programming (DP) - Choice and Optimal => Recursion + Storage

- Just an enhanced recursion (there will be choice)
- If you need to make 2 calls in the recursion, most likely DP will be used
- You save the results in a table and use that in your recursive solution
- Usually optimal is asked in questions

- Parent of DP is recursion
- Write recursive function first <- This is must
- Memoize or use Top-down next
  

### Type of Problems
Most of them are just variations of these
	1.	Dynamic Programming<br>
	2.	0-1 knapsack (6)<br>
	3.	Unbounded knapsack (5)<br>
	4.	Fibonacci (+)<br>
	5.	LCS (15)<br>
	6.	LIS (10)<br>
	7.	Kadane's Algorithm (6)<br>
	8.	Matrix chain multiplication (7)<br>
	9.	DP on Trees (4)<br>
	10.	DP on Grid (14)<br>
	11.	Others (5)<br>

### KnapSack Problem
Here's an explanation of each variation mentioned:
- Subset Sum:<br>
Problem: Given a set of integers and a target sum, determine if there exists a subset of the integers that sums to the target.<br>
Relation to Knapsack: Similar to the 0-1 Knapsack where instead of maximizing value, you're checking if you can achieve a specific sum with a subset of items (weights).
- Equal Sum Partition:<br>
Problem: Determine if the given set of integers can be partitioned into two subsets with equal sum.<br>
Relation to Knapsack: This is a special case of the Subset Sum problem where the target sum is half of the total sum of the set.
- Count of Subset Sum:<br>
Problem: Count the number of subsets of a given set of integers that sum to a target value.<br>
Relation to Knapsack: Instead of finding if there's a solution, this counts how many solutions exist for the subset sum problem.
- Minimum Subset Sum Difference:<br>
Problem: Find the minimum possible difference between the sums of two subsets of a given set of integers.<br>
Relation to Knapsack: This can be approached by considering all possible subset sums and finding the closest sum to half the total sum, which minimizes the difference.
- Target Sum:<br>
Problem: Given a list of integers and a target sum, find the number of ways to assign '+' or '-' signs to the integers such that their sum equals the target.<br>
Relation to Knapsack: This can be transformed into a subset sum problem by considering the positive and negative contributions as different subsets.
- Number of Subsets Given:<br>
Problem: This seems to be a general note or might refer to problems where you need to find or count subsets with specific properties or constraints.<br>
Relation to Knapsack: Could relate to variations where the number of items in subsets is considered, like finding subsets with a specific count of elements.

**0/1 Knapsack Problem**
https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/
Given N items where each item has some weight and profit associated with it and also given a bag with capacity W, [i.e., the bag can hold at most W weight in it]. The task is to put the items into the bag such that the sum of profits associated with them is the maximum possible. 

Note: The constraint here is we can either put an item completely into the bag or cannot put it at all [It is not possible to put a part of an item into the bag].

