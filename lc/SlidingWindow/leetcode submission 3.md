# 295. Find Median from Data Stream - Two Pointers, Design, Sorting, Heap (Priority Queue), Data Stream

This document describes the solution to the "Find Median from Data Stream" problem (LeetCode #295).

## Problem Description
The median is the middle value in an ordered integer list. If the list size is even, the median is the average of the two middle values. Design a data structure that supports:
- Adding a number to the data stream.
- Finding the median of all numbers added so far.

### Example
```
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // Stream: [1]
medianFinder.addNum(2);    // Stream: [1, 2]
medianFinder.findMedian(); // Returns 1.5 (average of 1 and 2)
medianFinder.addNum(3);    // Stream: [1, 2, 3]
medianFinder.findMedian(); // Returns 2.0 (middle value)
```

### Constraints
- `-10^5 <= num <= 10^5`
- There will be at least one element in the data structure before calling `findMedian`.
- At most `5 * 10^4` calls will be made to `addNum` and `findMedian`.

## Solution Approach
The problem can be solved using two heaps: a max heap for the lower half of the numbers and a min heap for the upper half. This ensures the median can be found efficiently by accessing the top elements of the heaps.

### Two Heaps Approach
1. Use a max heap (`small`) to store the smaller half of the numbers.
2. Use a min heap (`large`) to store the larger half of the numbers.
3. Maintain the heaps such that:
   - The size of `small` is equal to or one greater than the size of `large`.
   - All numbers in `small` are less than or equal to all numbers in `large`.
4. For `addNum(num)`:
   - Add the number to the appropriate heap based on its value.
   - Rebalance the heaps if the size difference exceeds 1.
5. For `findMedian()`:
   - If the heaps have equal size, return the average of the tops of both heaps.
   - Otherwise, return the top of the `small` heap (which has one extra element).

### Example Implementation (C++)
```cpp
class MedianFinder {
public:
    priority_queue<int, vector<int>, less<int>> qMax; // Max priority queue
    priority_queue<int, vector<int>, greater<int>> qMin; //Min priority queue
    
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        int nMin = qMin.size();
        int nMax = qMax.size();
        
        if (nMax == 0 || qMax.top() > num) {
			qMax.push(num);
		} else {
			qMin.push(num);
		}

        //rebalance
		if (qMax.size() > qMin.size() + 1) {
			qMin.push(qMax.top());
			qMax.pop();
		} else if (qMin.size() > qMax.size() + 1) {
			qMax.push(qMin.top());
			qMin.pop();
		}
        
        return;
    }
    
    double findMedian() {
        int nMin = qMin.size();
        int nMax = qMax.size();
        
        if(nMin > nMax)
            return qMin.top();
        else if(nMin < nMax)
            return qMax.top();

        return (double)(qMin.top() + qMax.top()) / 2.0;   
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
```

```cpp
class MedianFinder {
public:
    priority_queue<int> small; // Max heap for lower half
    priority_queue<int, vector<int>, greater<int>> large; // Min heap for upper half
    
    MedianFinder() {
    }
    
    void addNum(int num) {
        if (small.empty() || num < small.top()) {
            small.push(num);
        } else {
            large.push(num);
        }
        
        // Rebalance: small can have at most one more element than large
        if (small.size() > large.size() + 1) {
            large.push(small.top());
            small.pop();
        } else if (large.size() > small.size()) {
            small.push(large.top());
            large.pop();
        }
    }
    
    double findMedian() {
        if (small.size() > large.size()) {
            return small.top();
        }
        return (small.top() + large.top()) / 2.0;
    }
};
```

### How It Works
- **Heaps**:
  - `small` (max heap): Stores the smaller half, with the largest number at the top.
  - `large` (min heap): Stores the larger half, with the smallest number at the top.
- **addNum**:
  - Add to `small` if the number is less than the largest in `small`, otherwise add to `large`.
  - Rebalance by moving elements between heaps to maintain size constraints.
- **findMedian**:
  - If `small` has one more element, its top is the median.
  - If sizes are equal, average the tops of both heaps.
- **Edge Cases**:
  - Single number: Added to `small`, returned as median.
  - Large numbers: Heaps handle the range `[-10^5, 10^5]` efficiently.
- **Result**: The median is computed in O(1) after each insertion.

### Time and Space Complexity
- **Time Complexity**:
  - `addNum`: O(log n), where `n` is the number of elements, due to heap operations (push/pop).
  - `findMedian`: O(1), as it only accesses the top elements.
- **Space Complexity**: O(n), to store all elements in the two heaps.

### Alternative Approach
1. **Sorted List**:
   - Maintain a sorted list and insert numbers in the correct position.
   - `addNum`: O(n) for insertion in a sorted list.
   - `findMedian`: O(1) by accessing the middle element(s).
   - Less efficient due to linear insertion time.
The two-heaps approach is preferred for its logarithmic insertion time and constant-time median retrieval.


# 138. Copy List with Random Pointer - Hash Table, Linked List

This document describes the solution to the "Copy List with Random Pointer" problem (LeetCode #138).

## Problem Description
A linked list of length `n` is given such that each node contains an additional random pointer, which could point to any node in the list or null. Construct a deep copy of the list, where the deep copy should consist of exactly `n` new nodes, each with its value set to the value of its corresponding original node. Both the `next` and `random` pointers of the new nodes should point to new nodes in the copied list, preserving the same list structure.

### Example
```
Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]
Explanation: The copied list has the same structure, with new nodes and pointers adjusted to point to the corresponding new nodes.
```
<img src="../assets/e1.png" width="70%">

```
Input: head = [[1,1],[2,1]]
Output: [[1,1],[2,1]]
Explanation: The random pointers point to nodes within the copied list.
```
<img src="../assets/e2.png" width="70%">

```
Input: head = [[3,null],[3,0],[3,null]]
Output: [[3,null],[3,0],[3,null]]
Explanation: The structure, including null random pointers, is preserved.
```
<img src="../assets/e3.png" width="70%">

```
Hint 1
Just iterate the linked list and create copies of the nodes on the go. Since a node can be referenced from multiple nodes due to the random pointers, ensure you are not making multiple copies of the same node.
Hint 2
You may want to use extra space to keep old_node ---> new_node mapping to prevent creating multiple copies of the same node.
Hint 3
We can avoid using extra space for old_node ---> new_node mapping by tweaking the original linked list. Simply interweave the nodes of the old and copied list. For example: Old List: A --> B --> C --> D InterWeaved List: A --> A' --> B --> B' --> C --> C' --> D --> D'
Hint 4
The interweaving is done using next pointers and we can make use of interweaved structure to get the correct reference nodes for random pointers.
```

### Constraints
- `0 <= n <= 1000`
- `-10^4 <= Node.val <= 10^4`
- `Node.random` is null or points to a node in the linked list.

## Solution Approach
The problem can be solved efficiently using an interleaved approach that avoids extra space for mapping, by weaving copied nodes into the original list.

### Interleaved Nodes Approach
1. **Interleave Copied Nodes**:
   - For each node in the original list, create a copy and place it between the original node and its next node (e.g., `1 -> 2` becomes `1 -> 1' -> 2 -> 2'`).
2. **Set Random Pointers**:
   - For each original node, if its `random` pointer points to a node, set the copied node’s `random` pointer to the copy of that node (accessible as `original->random->next`).
3. **Separate Lists**:
   - Extract the copied list by adjusting the `next` pointers to separate the original and copied nodes.
4. Return the head of the copied list.

### Node Structure
```cpp
class Node {
public:
    int val;
    Node* next;
    Node* random;
    Node(int _val) : val(_val), next(nullptr), random(nullptr) {}
};
```

### Example Implementation (C++)
```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(!head)
            return head;
        
        Node * c = head;
        
        //creat a copy
        while(c)
        {
            Node *cc = new Node(c->val);
            cc->next = c->next;
            c->next = cc;
            c = cc->next;
        }
            
        //1-1`-2-2`-3-3`....
        //set the random pointers next
        c = head;
        while(c)
        {
            Node * rc= (c->random) ? c->random->next : nullptr;
            Node * cc = c->next;
            cc->random = rc;
            c = cc->next;
        }
        
        //splice the copy and original
        c = head;
        Node * chead = head->next;
        
        Node * cc = chead;
        while(cc)
        {
            Node * next = cc->next;
            c->next = next;
            c = c->next;
            if(next)
                cc->next = next->next;
            
            cc = cc->next;
        }
        
        return chead;
    }
};
```

```cpp
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;
        
        // Step 1: Interleave copied nodes
        Node* curr = head;
        while (curr) {
            Node* copy = new Node(curr->val);
            copy->next = curr->next;
            curr->next = copy;
            curr = copy->next;
        }
        
        // Step 2: Set random pointers for copied nodes
        curr = head;
        while (curr) {
            if (curr->random) {
                curr->next->random = curr->random->next;
            }
            curr = curr->next->next;
        }
        
        // Step 3: Separate the lists
        Node* dummy = new Node(0);
        Node* copyCurr = dummy;
        curr = head;
        while (curr) {
            // Extract copied node
            copyCurr->next = curr->next;
            copyCurr = copyCurr->next;
            
            // Restore original list
            curr->next = copyCurr->next;
            curr = curr->next;
        }
        
        return dummy->next;
    }
};
```

### How It Works
- **Interleaving**:
  - Insert a copy of each node right after the original (e.g., `1 -> 2` becomes `1 -> 1' -> 2 -> 2'`).
- **Random Pointers**:
  - For an original node’s `random` pointer, the copied node’s `random` is the node after the original’s `random` (since copies are interleaved).
- **Separation**:
  - Use a dummy node to build the copied list.
  - Adjust `next` pointers to separate the lists, restoring the original list and linking the copied nodes.
- **Edge Cases**:
  - Empty list: Return `nullptr`.
  - Single node: Copy node with `random` pointing to itself or `nullptr`.
  - Null random pointers: Handled by checking `curr->random`.
- **Result**: Returns the head of the deep-copied list.

### Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the number of nodes, as we traverse the list three times (interleave, set random pointers, separate).
- **Space Complexity**: O(1), excluding the space needed for the output list, as we only use a constant amount of extra space (pointers and dummy node).

### Alternative Approach
1. **Hash Map**:
   - Use a hash map to map original nodes to their copies.
   - First pass: Create all copied nodes.
   - Second pass: Set `next` and `random` pointers using the map.
   - Time Complexity: O(n)
   - Space Complexity: O(n) for the hash map
The interleaved approach is preferred as it achieves O(1) space complexity (excluding output).


# 114. Flatten Binary Tree to Linked List - Linked List, Stack, Tree, Depth-First Search, Binary Tree

This document describes the solution to the "Flatten Binary Tree to Linked List" problem (LeetCode #114).

## Problem Description
Given the root of a binary tree, flatten the tree into a "linked list" in-place:
- The "linked list" should use the same `TreeNode` class, where the `right` child pointer points to the next node in the list, and the `left` child pointer is set to `null`.
- The nodes should be in the same order as a pre-order traversal of the binary tree.

### Example
```
Input: root = [1,2,5,3,4,null,6]
Output: [1,null,2,null,3,null,4,null,5,null,6]
Explanation: The tree is flattened into a linked list: 1 -> 2 -> 3 -> 4 -> 5 -> 6.

Input: root = []
Output: []
Explanation: An empty tree remains empty.

Input: root = [0]
Output: [0]
Explanation: A single node is already a valid linked list.

Hint 1
If you notice carefully in the flattened tree, each node's right child points to the next node of a pre-order traversal.
```

<img src="../assets/flaten.jpg" width="50%">


### Constraints
- The number of nodes in the tree is in the range `[0, 2000]`.
- `-100 <= Node.val <= 100`

## Solution Approach
The problem can be solved using a recursive approach that performs a pre-order traversal and rewires the tree in-place to form a linked list.

### Recursive Pre-Order Approach
1. Use a recursive function to flatten the tree:
   - For each node, process the left subtree, then the right subtree.
   - Rewire the current node’s pointers:
     - Set the `left` pointer to `null`.
     - Set the `right` pointer to the flattened left subtree.
     - Append the flattened right subtree to the end of the current list.
2. Track the last node in the flattened list to connect subtrees correctly.
3. Modify the tree in-place without creating new nodes.

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
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:    
    void flatten(TreeNode* root) {        
        while (root) {
            if (root->left && root->right) {
                TreeNode* t = root->left; //2
                while (t->right)
                    t = t->right;
                t->right = root->right;
            }

            if(root->left)
                root->right = root->left;
            root->left = NULL;
            root = root->right;
        }
    }
};
```


```cpp
class Solution {
public:
    void flatten(TreeNode* root) {
        if (!root) return;
        
        // Store the right subtree
        TreeNode* rightSubtree = root->right;
        
        // Make left subtree the right child
        root->right = root->left;
        root->left = nullptr;
        
        // Move to the end of the new right subtree (originally left)
        TreeNode* curr = root;
        while (curr->right) {
            curr = curr->right;
        }
        
        // Append the original right subtree
        curr->right = rightSubtree;
        
        // Recursively flatten the new right subtree
        flatten(root->right);
    }
};
```

### How It Works
- **Recursion**:
  - For each node, save the right subtree.
  - Move the left subtree to the right and set `left` to `null`.
  - Find the end of the new right subtree (originally the left subtree).
  - Attach the saved right subtree to the end.
  - Recursively flatten the new right subtree.
- **Pre-Order Order**:
  - The process ensures nodes are linked in pre-order (root, left, right).
- **In-Place**:
  - No new nodes are created; existing pointers are rewired.
- **Edge Cases**:
  - Empty tree: Return immediately.
  - Single node: No changes needed (already a valid list).
  - No left child: Right subtree is flattened directly.
- **Result**: The tree is flattened into a linked list with `left` pointers set to `null` and `right` pointers forming the list.

### Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the number of nodes, as each node is processed once.
- **Space Complexity**: O(h), where `h` is the height of the tree, due to the recursion stack. In the worst case (skewed tree), this is O(n); in a balanced tree, it’s O(log n).

### Alternative Approaches
1. **Iterative with Stack**:
   - Use a stack to simulate pre-order traversal and rewire pointers iteratively.
   - Time Complexity: O(n)
   - Space Complexity: O(h)
2. **Morris Traversal-Inspired**:
   - Find the predecessor in the left subtree to connect to the right subtree without extra space.
   - Time Complexity: O(n)
   - Space Complexity: O(1)
The recursive approach is preferred for its clarity and straightforward implementation, though the Morris-inspired approach optimizes space.



# 430. Flatten a Multilevel Doubly Linked List - Linked List, Depth-First Search, Doubly-Linked List

This document describes the solution to the "Flatten a Multilevel Doubly Linked List" problem (LeetCode #430).

## Problem Description
You are given a doubly linked list, which contains nodes that have a next pointer, a previous pointer, and an additional child pointer. This child pointer may point to a separate doubly linked list, forming a multilevel structure. Flatten the list so that all nodes appear in a single-level, doubly linked list. The nodes should appear in the order of a pre-order traversal of the multilevel structure. Return the head of the flattened list.

### Example
```
Input: head = [1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]
```
<img src="../assets/flatten11.jpg" width="20%">

```
Output: [1,2,3,7,8,11,12,9,10,4,5,6]
Explanation: The multilevel list with child pointers (e.g., 3->7, 8->11) is flattened into a single list in pre-order.
```
<img src="../assets/flatten12.jpg" width="20%">

```
Input: head = [1,2,null,3]
Output: [1,3,2]
Explanation: The child list [3] from node 1 is integrated into the main list.
```
<img src="../assets/flatten2.jpg" width="20%">

```
Input: head = []
Output: []
Explanation: An empty list remains empty.
```



### Constraints
- The number of nodes in the list is in the range `[0, 1000]`.
- `1 <= Node.val <= 10^5`

## Solution Approach
The problem can be solved using a recursive approach that processes each node and its child list, integrating the child list into the main list while maintaining the doubly linked list properties.

### Recursive Flattening Approach
1. Traverse the list starting from the head.
2. For each node:
   - If it has a child, recursively flatten the child list.
   - Integrate the flattened child list between the current node and its next node.
   - Update the `prev` and `next` pointers accordingly.
   - Set the `child` pointer to `null`.
3. Continue processing the next node in the list.
4. Return the head of the flattened list.

### Node Structure
```cpp
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
    Node() : val(0), prev(nullptr), next(nullptr), child(nullptr) {}
    Node(int _val) : val(_val), prev(nullptr), next(nullptr), child(nullptr) {}
    Node(int _val, Node* _prev, Node* _next, Node* _child) :
        val(_val), prev(_prev), next(_next), child(_child) {}
};
```

### Example Implementation (C++)
```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

class Solution {
public:
    Node* flatten(Node* head) {
        Node * current = head;
        
        while (current) {
            if (current->child) {
                
                // Save the current next and connect the child to next
                Node * tmp_next = current->next;
                current->next = current->child;
                current->next->prev = current;
                current->child = NULL;
                
                // Run till the end of the current list and connect last node to saved next
                Node * runner = current->next; //basically child
                while (runner->next) 
                    runner = runner->next;
                
                runner->next = tmp_next;
                if (runner->next) 
                    runner->next->prev = runner;
            }
            
            current = current->next;
        }
        
        return head;
    }
};
```

```cpp
class Solution {
public:
    Node* flatten(Node* head) {
        flattenHelper(head);
        return head;
    }
    
private:
    Node* flattenHelper(Node* head) {
        Node* curr = head;
        while (curr) {
            if (curr->child) {
                // Flatten the child list
                Node* childTail = flattenHelper(curr->child);
                
                // Connect child list to current node
                Node* nextNode = curr->next;
                curr->next = curr->child;
                curr->child->prev = curr;
                curr->child = nullptr;
                
                // Connect child tail to next node
                childTail->next = nextNode;
                if (nextNode) {
                    nextNode->prev = childTail;
                }
                
                // Move to the next node after child integration
                curr = childTail->next;
            } else {
                curr = curr->next;
            }
        }
        
        // Return the tail of the flattened list starting from head
        curr = head;
        while (curr && curr->next) {
            curr = curr->next;
        }
        return curr ? curr : head;
    }
};
```

### How It Works
- **Traversal**:
  - Process each node in the list.
  - If a node has a child, flatten the child list recursively.
- **Integration**:
  - Connect the flattened child list between the current node and its `next` node.
  - Update `prev` and `next` pointers to maintain doubly linked list properties.
  - Set `child` to `null` after integration.
- **Tail Tracking**:
  - The helper function returns the tail of the flattened list to facilitate connections.
- **Edge Cases**:
  - Empty list: Return `nullptr`.
  - No child pointers: List remains unchanged.
  - Single node with child: Child list is appended after the node.
- **Result**: The list is flattened in pre-order, with all nodes in a single-level doubly linked list.

### Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the total number of nodes in the multilevel list, as each node is processed once.
- **Space Complexity**: O(h), where `h` is the maximum depth of the multilevel structure, due to the recursion stack. In the worst case (deeply nested), this is O(n).

### Alternative Approach
1. **Iterative with Stack**:
   - Use a stack to store nodes and process them in pre-order, adjusting pointers iteratively.
   - Time Complexity: O(n)
   - Space Complexity: O(h) for the stack
The recursive approach is preferred for its clarity and natural handling of the pre-order traversal required for flattening.


# 239. Sliding Window Maximum - Queue, Sliding Window, Heap (Priority Queue), Monotonic Queue

This document describes the solution to the "Sliding Window Maximum" problem (LeetCode #239).

## Problem Description
Given an array `nums` and an integer `k`, return the maximum value in each sliding window of size `k` as the window moves from left to right. The sliding window moves one position to the right at each step, and there are `n - k + 1` windows, where `n` is the length of the array.

### Example
```
Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation:
Window position                Max
[1 3 -1] -3 5 3 6 7           3
 1 [3 -1 -3] 5 3 6 7          3
 1 3 [-1 -3 5] 3 6 7          5
 1 3 -1 [-3 5 3] 6 7          5
 1 3 -1 -3 [5 3 6] 7          6
 1 3 -1 -3 5 [3 6 7]          7

Input: nums = [1], k = 1
Output: [1]
Explanation: Single element window has max 1.

Hint 1
How about using a data structure such as deque (double-ended queue)?
Hint 2
The queue size need not be the same as the window’s size.
Hint 3
Remove redundant elements and the queue should store only elements that need to be considered.
```

### Constraints
- `1 <= nums.length <= 10^5`
- `-10^4 <= nums[i] <= 10^4`
- `1 <= k <= nums.length`

## Solution Approach
The problem can be solved efficiently using a deque to maintain indices of potential maximum values in the sliding window, ensuring the front of the deque always holds the index of the maximum.

### Deque-Based Approach
1. Use a deque to store indices of elements in the current window, maintaining a decreasing order of values (front has the largest value).
2. For each index `i` in the array:
   - Remove indices from the front of the deque if they are outside the current window (`i - k`).
   - Remove indices from the back of the deque if their values are less than `nums[i]`, as they cannot be the maximum in future windows.
   - Add the current index `i` to the back of the deque.
3. After processing the first `k` elements, the front of the deque gives the maximum for each window. Store it in the result array for each subsequent step.

### Example Implementation (C++)
```cpp
class Solution {
public:   
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> result;
        if (k == 0) return result;
        deque<int> w;
        for (int i = 0, n = (int)nums.size(); i < n; i++) {
            while (!w.empty() && w.front() <= i-k) {
                w.pop_front();
            }
            
            while (!w.empty() && nums[w.back()] <= nums[i])
                w.pop_back();
            w.push_back(i);
            
            if (i >= k-1)
                result.push_back(nums[w.front()]);
        }
        return result;
    }
};
```

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq; // Stores indices of potential max values
        vector<int> result;
        
        for (int i = 0; i < nums.size(); i++) {
            // Remove indices outside the current window
            while (!dq.empty() && dq.front() <= i - k) {
                dq.pop_front();
            }
            
            // Remove indices of smaller values as they can't be max
            while (!dq.empty() && nums[dq.back()] < nums[i]) {
                dq.pop_back();
            }
            
            // Add current index
            dq.push_back(i);
            
            // After first k elements, front of deque is the max
            if (i >= k - 1) {
                result.push_back(nums[dq.front()]);
            }
        }
        
        return result;
    }
};
```

### How It Works
- **Deque**:
  - Stores indices of elements in decreasing order of their values.
  - Front always holds the index of the maximum element in the current window.
- **Processing**:
  - Remove out-of-window indices from the front (`i - k` or earlier).
  - Remove indices of smaller elements from the back, as they’re irrelevant for future maxima.
  - Add the current index to the back.
- **Result**:
  - After processing `k` elements, the front of the deque gives the maximum for each window.
  - Store `nums[dq.front()]` in the result starting from index `k-1`.
- **Edge Cases**:
  - `k = 1`: Each element is its own window maximum.
  - `k = nums.length`: Single window, return the maximum of the array.
  - Single element: Deque handles it correctly.
- **Result**: Returns an array of maximum values for each sliding window.

### Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the array. Each element is pushed and popped at most once from the deque.
- **Space Complexity**: O(k), for the deque, which stores at most `k` indices, plus O(n-k+1) for the output array.

### Alternative Approaches
1. **Brute Force**:
   - Compute the maximum for each window by scanning all `k` elements.
   - Time Complexity: O(n * k)
   - Space Complexity: O(1) (excluding output)


  
# 253. Meeting Rooms II

This document describes the solution to the "Meeting Rooms II" problem (LeetCode #253).

## Problem Description
Given an array of meeting time intervals `intervals` where `intervals[i] = [start_i, end_i]`, return the minimum number of conference rooms required to accommodate all meetings without conflicts.

### Example
```
Input: intervals = [[0,30],[5,10],[15,20]]
Output: 2
Explanation: Two rooms are needed as [5,10] and [15,20] overlap with [0,30].

Input: intervals = [[7,10],[2,4]]
Output: 1
Explanation: No overlap, so only one room is needed.
```

### Constraints
- `1 <= intervals.length <= 10^4`
- `0 <= start_i < end_i <= 10^6`

## Solution Approach
The problem can be solved efficiently using a chronological ordering approach by separating start and end times, sorting them, and tracking the maximum number of overlapping meetings.

### Chronological Ordering Approach
1. Create two arrays: one for start times and one for end times.
2. Sort both arrays independently.
3. Use two pointers to scan the sorted arrays:
   - Increment a counter when encountering a start time (new meeting begins).
   - Decrement the counter when encountering an end time (meeting ends).
   - Track the maximum value of the counter, which represents the maximum number of simultaneous meetings.
4. Return the maximum counter value as the number of rooms needed.

### Example Implementation (C++)
```cpp
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        
        int rooms = 0;
        priority_queue<int, vector<int>, std::greater<int>> q;
        for(int i = 0; i < intervals.size(); i++)
        {
            vector<int> m = intervals[i];
            if(q.empty()) {
                q.push(m[1]);
                rooms++;
                continue;
            }
            
            int top = q.top();
            if(top <= m[0]) {
                q.pop();
                q.push(m[1]);
            }
            else
            {
                rooms++;
                q.push(m[1]);
            }        
        }
        
        return rooms;
    }
};
```

```cpp
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        vector<int> startTimes, endTimes;
        for (const auto& interval : intervals) {
            startTimes.push_back(interval[0]);
            endTimes.push_back(interval[1]);
        }
        
        sort(startTimes.begin(), startTimes.end());
        sort(endTimes.begin(), endTimes.end());
        
        int maxRooms = 0, currentRooms = 0;
        int start = 0, end = 0;
        
        while (start < startTimes.size()) {
            if (startTimes[start] < endTimes[end]) {
                currentRooms++;
                maxRooms = max(maxRooms, currentRooms);
                start++;
            } else {
                currentRooms--;
                end++;
            }
        }
        
        return maxRooms;
    }
};
```

### How It Works
- **Separate Times**:
  - Extract start and end times into separate arrays.
- **Sorting**:
  - Sort start times and end times to process events chronologically.
- **Two Pointers**:
  - Compare the next start time with the next end time.
  - If the start time is earlier, a new meeting begins (`currentRooms++`).
  - If the end time is earlier or equal, a meeting ends (`currentRooms--`).
  - Update `maxRooms` to track the peak number of simultaneous meetings.
- **Edge Cases**:
  - Single interval: Requires one room.
  - Non-overlapping intervals: Requires one room.
  - All overlapping intervals: Requires as many rooms as intervals.
- **Result**: The maximum number of rooms needed is the peak value of `currentRooms`.

### Time and Space Complexity
- **Time Complexity**: O(n log n), where `n` is the number of intervals, due to sorting the start and end times.
- **Space Complexity**: O(n), for storing the start and end times arrays.

### Alternative Approach
1. **Priority Queue (Min Heap)**:
   - Sort intervals by start time.
   - Use a min heap to track end times of active meetings.
   - For each interval, remove ended meetings (end time <= current start time) and add the new meeting’s end time.
   - Track the maximum size of the heap.
   - Time Complexity: O(n log n) for sorting and heap operations
   - Space Complexity: O(n) for the heap
The chronological ordering approach is preferred for its simplicity and clarity, avoiding the need for a heap while maintaining the same time complexity.


# 4. Median of Two Sorted Arrays

This document describes the solution to the "Median of Two Sorted Arrays" problem (LeetCode #4).

## Problem Description
Given two sorted arrays `nums1` and `nums2` of sizes `m` and `n` respectively, return the median of the two sorted arrays. The overall run time complexity should be O(log(min(m,n))). The median is the middle value in the merged sorted array. If the total number of elements is even, the median is the average of the two middle values.

### Example
```
Input: nums1 = [1,3], nums2 = [2]
Output: 2.0
Explanation: Merged array = [1,2,3], median is 2.

Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.5
Explanation: Merged array = [1,2,3,4], median is (2 + 3) / 2 = 2.5.

Input: nums1 = [], nums2 = [1]
Output: 1.0
Explanation: Merged array = [1], median is 1.
```

### Constraints
- `nums1.length == m`
- `nums2.length == n`
- `0 <= m <= 1000`
- `0 <= n <= 1000`
- `1 <= m + n <= 2000`
- `-10^6 <= nums1[i], nums2[i] <= 10^6`

## Solution Approach
The problem can be solved using a binary search approach to find the correct partition point that divides the merged array into two equal halves, ensuring the elements on the left are less than or equal to those on the right.

### Binary Search on Partition Approach
1. Ensure `nums1` is the shorter array to minimize the binary search space (swap if necessary).
2. Perform binary search on the smaller array to find a partition point `i` (number of elements from `nums1` in the left half).
3. Compute the corresponding partition point `j` for `nums2` such that `i + j = (m + n + 1) / 2`.
4. Check if the partition is valid:
   - Left half: `nums1[0..i-1]` and `nums2[0..j-1]`.
   - Right half: `nums1[i..m-1]` and `nums2[j..n-1]`.
   - Valid if `nums1[i-1] <= nums2[j]` and `nums2[j-1] <= nums1[i]`.
5. If valid, compute the median:
   - If total length is odd, median is the maximum of the left half.
   - If even, median is the average of the maximum of the left half and the minimum of the right half.
6. If the partition is invalid, adjust the binary search range.

### Example Implementation (C++)
```cpp
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size();
        int n2 = nums2.size();
        
        vector<int> nums;
        
        int i = 0;
        int j = 0;
        while(i < n1 && j < n2)
        {
            if(nums1[i] <= nums2[j])
                nums.push_back(nums1[i++]);
            else
                nums.push_back(nums2[j++]);
        }
        
        while(i<n1) 
            nums.push_back(nums1[i++]);
        
        while(j<n2) 
            nums.push_back(nums2[j++]);
        
        int mid = ( n1 + n2 ) / 2;
        if( (n1+n2) % 2 == 0)
        { 
            return (nums[mid -1] + nums[mid])/2.0;
            //0-1-2-3-4-5
        }
        
        return nums[mid];         
    }
};
```

```cpp
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1); // Ensure nums1 is shorter
        }
        
        int m = nums1.size(), n = nums2.size();
        int left = 0, right = m;
        
        while (left <= right) {
            int i = left + (right - left) / 2; // Partition point for nums1
            int j = (m + n + 1) / 2 - i;      // Partition point for nums2
            
            // Get left and right elements for both arrays
            int left1 = (i == 0) ? INT_MIN : nums1[i - 1];
            int right1 = (i == m) ? INT_MAX : nums1[i];
            int left2 = (j == 0) ? INT_MIN : nums2[j - 1];
            int right2 = (j == n) ? INT_MAX : nums2[j];
            
            // Check if partition is valid
            if (left1 <= right2 && left2 <= right1) {
                // If total length is odd
                if ((m + n) % 2 == 1) {
                    return max(left1, left2);
                }
                // If total length is even
                return (max(left1, left2) + min(right1, right2)) / 2.0;
            } else if (left1 > right2) {
                right = i - 1; // Move partition left in nums1
            } else {
                left = i + 1;  // Move partition right in nums1
            }
        }
        
        return 0.0; // Unreachable due to problem constraints
    }
};
```

### How It Works
- **Swap Arrays**: Ensure `nums1` is the shorter array to reduce binary search space.
- **Binary Search**:
  - Search for `i` (elements from `nums1` in left half) in range `[0, m]`.
  - Compute `j` to balance the left half: `i + j = (m + n + 1) / 2`.
- **Partition Validation**:
  - Check if the left elements (`nums1[i-1]`, `nums2[j-1]`) are less than or equal to the right elements (`nums2[j]`, `nums1[i]`).
  - Use `INT_MIN` and `INT_MAX` for edge cases (empty partitions).
- **Median Calculation**:
  - Odd total length: Median is `max(left1, left2)`.
  - Even total length: Median is `(max(left1, left2) + min(right1, right2)) / 2`.
- **Edge Cases**:
  - Empty array: Handled by swapping or boundary conditions.
  - Single element: Correctly partitions to include the element.
  - Equal-sized arrays: Binary search works regardless of size.
- **Result**: Returns the median of the merged sorted arrays.

### Time and Space Complexity
- **Time Complexity**: O(log(min(m, n))), as binary search is performed on the smaller array.
- **Space Complexity**: O(1), as only a constant amount of extra space is used.

### Alternative Approach
1. **Merge and Find Median**:
   - Merge the two sorted arrays until the median position is reached.
   - Time Complexity: O(m + n)
   - Space Complexity: O(1) (if only tracking median elements)
The binary search approach is preferred for its logarithmic time complexity, meeting the problem’s requirement.


# 56. Merge Intervals

This document describes the solution to the "Merge Intervals" problem (LeetCode #56).

## Problem Description
Given an array of intervals where `intervals[i] = [start_i, end_i]`, merge all overlapping intervals and return an array of the non-overlapping intervals that cover all the intervals in the input.

### Example
```
Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Intervals [1,3] and [2,6] overlap, so they are merged into [1,6].

Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] touch at 4, so they are merged into [1,5].

Input: intervals = [[1,4],[0,4]]
Output: [[0,4]]
Explanation: Intervals [0,4] and [1,4] overlap, so they are merged into [0,4].
```

### Constraints
- `1 <= intervals.length <= 10^4`
- `intervals[i].length == 2`
- `0 <= start_i <= end_i <= 10^4`

## Solution Approach
The problem can be solved by sorting the intervals by start time and then merging overlapping intervals in a single pass.

### Sort and Merge Approach
1. Sort the intervals based on their start times.
2. Initialize a result array with the first interval.
3. Iterate through the sorted intervals starting from the second interval:
   - If the current interval overlaps with the last interval in the result (i.e., `start_i <= end_last`), merge them by updating the end time of the last interval to the maximum of their end times.
   - Otherwise, add the current interval to the result as a new non-overlapping interval.
4. Return the result array.

### Example Implementation (C++)
```cpp
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> ans;
        int start = INT_MAX;
        int end = INT_MIN;
        sort(intervals.begin(), intervals.end());
        for(int i=0; i < intervals.size(); i++) {
            start = min(start, intervals[i][0]);
            end = max(end, intervals[i][1]);
            
            if(i == intervals.size()-1 || end < intervals[i+1][0]) {
                ans.push_back(vector<int>({start, end}));
                start = INT_MAX;
                end = INT_MIN;
            }                
        }
        
        return ans;
    }
};
```

```cpp
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        // Sort intervals by start time
        sort(intervals.begin(), intervals.end());
        
        vector<vector<int>> result;
        result.push_back(intervals[0]);
        
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] <= result.back()[1]) {
                // Overlap: Merge by updating the end time
                result.back()[1] = max(result.back()[1], intervals[i][1]);
            } else {
                // No overlap: Add new interval
                result.push_back(intervals[i]);
            }
        }
        
        return result;
    }
};
```

### How It Works
- **Sorting**:
  - Sort intervals by start time to ensure we process them in order, making it easier to detect overlaps.
- **Merging**:
  - Start with the first interval in the result.
  - For each subsequent interval, check if its start time is less than or equal to the end time of the last interval in the result.
  - If overlapping, update the end time to the maximum of the two end times.
  - If not overlapping, append the interval to the result.
- **Edge Cases**:
  - Single interval: Returned as is.
  - Non-overlapping intervals: Each added to the result.
  - All overlapping: Merged into one interval.
  - Touching intervals (e.g., `[1,4],[4,5]`): Considered overlapping and merged.
- **Result**: Returns the array of merged, non-overlapping intervals.

### Time and Space Complexity
- **Time Complexity**: O(n log n), where `n` is the number of intervals, due to the sorting step. The merging step is O(n).
- **Space Complexity**: O(n) for the output array. If sorting in-place is not considered, additional O(log n) space may be used by the sorting algorithm.

### Alternative Approach
1. **Sweep Line**:
   - Treat start and end times as events (+1 for start, -1 for end) and sort them.
   - Scan events to track active intervals and construct merged intervals.
   - Time Complexity: O(n log n)
   - Space Complexity: O(n)
The sort and merge approach is preferred for its simplicity and direct handling of intervals without needing to process events separately.


# 346. Moving Average from Data Stream

This document describes the solution to the "Moving Average from Data Stream" problem (LeetCode #346).

## Problem Description
Given a stream of integers and a window size `size`, calculate the moving average of all integers in the sliding window. The moving average is the sum of the last `size` numbers divided by the number of elements in the window.

### Example
```
MovingAverage movingAverage = new MovingAverage(3);
movingAverage.next(1); // Returns 1.0 (window: [1])
movingAverage.next(10); // Returns 5.5 (window: [1,10], (1+10)/2)
movingAverage.next(3); // Returns 4.67 (window: [1,10,3], (1+10+3)/3)
movingAverage.next(5); // Returns 6.0 (window: [10,3,5], (10+3+5)/3)
```

### Constraints
- `1 <= size <= 1000`
- `-10^5 <= val <= 10^5`
- At most `10^4` calls will be made to `next`.

## Solution Approach
The problem can be solved using a queue to maintain the sliding window of the last `size` elements, updating the sum as elements are added and removed.

### Queue-Based Approach
1. Use a queue to store the elements in the sliding window.
2. Maintain a running sum of the elements in the queue.
3. For each call to `next(val)`:
   - Add the new value to the queue and update the sum.
   - If the queue size exceeds the window size, remove the oldest element from the queue and subtract it from the sum.
   - Return the average as the sum divided by the current queue size.
4. Ensure the queue never exceeds the specified window size.

### Example Implementation (C++)
```cpp
class MovingAverage {
    int winSize = 1;
    double winSum = 0;
    queue<int> q;
public:
    MovingAverage(int size) {
        winSize = size;
    }
    
    double next(int val) {
        winSum += val;
        if(q.size() == winSize) {
            winSum -= q.front();
            q.pop();
        }
        
        q.push(val);
        
        return winSum / q.size();
    }
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */
```

```cpp
class MovingAverage {
public:
    MovingAverage(int size) : windowSize(size), sum(0) {
    }
    
    double next(int val) {
        window.push(val);
        sum += val;
        
        // If window size is exceeded, remove oldest element
        if (window.size() > windowSize) {
            sum -= window.front();
            window.pop();
        }
        
        return sum / window.size();
    }
    
private:
    queue<int> window;
    int windowSize;
    double sum;
};
```

### How It Works
- **Initialization**:
  - Set the window size and initialize an empty queue and sum.
- **next(val)**:
  - Push the new value to the queue and add it to the sum.
  - If the queue size exceeds `windowSize`, pop the oldest element and subtract it from the sum.
  - Compute the average as `sum / window.size()`.
- **Edge Cases**:
  - Window not full: Average is computed with fewer than `size` elements.
  - Single element: Returns the element itself as the average.
  - Large values: `sum` is a `double` to handle the range `[-10^5, 10^5]`.
- **Result**: Returns the moving average for the current window.

### Time and Space Complexity
- **Time Complexity**: O(1) amortized for `next`, as queue operations (push and pop) are O(1).
- **Space Complexity**: O(size), where `size` is the window size, for storing up to `size` elements in the queue.

### Alternative Approach
1. **Circular Array**:
   - Use a fixed-size array and a pointer to track the oldest element.
   - Update the sum by subtracting the overwritten element and adding the new one.
   - Time Complexity: O(1)
   - Space Complexity: O(size)
The queue-based approach is preferred for its simplicity and clarity, as it naturally handles the sliding window without manual index management.


# 7. Reverse Integer

This document describes the solution to the "Reverse Integer" problem (LeetCode #7).

## Problem Description
Given a 32-bit signed integer `x`, return `x` with its digits reversed. If reversing `x` causes the value to go outside the signed 32-bit integer range `[-2^31, 2^31 - 1]`, then return `0`. Assume the environment does not allow storing 64-bit integers.

### Example
```
Input: x = 123
Output: 321
Explanation: The digits of 123 are reversed to 321.

Input: x = -123
Output: -321
Explanation: The digits of -123 are reversed to -321, preserving the sign.

Input: x = 120
Output: 21
Explanation: The digits of 120 are reversed to 021, which is 21.

Input: x = 1534236469
Output: 0
Explanation: The reversed number exceeds 2^31 - 1, so return 0.
```

### Constraints
- `-2^31 <= x <= 2^31 - 1`

## Solution Approach
The problem can be solved by extracting digits from the input number, building the reversed number, and checking for overflow within the 32-bit signed integer range.

### Digit-by-Digit Reversal Approach
1. Initialize a variable `result` to store the reversed number.
2. While the input number `x` is not zero:
   - Extract the last digit using modulo (`x % 10`).
   - Check if adding the digit to `result` would cause overflow:
     - If `result > INT_MAX / 10` or `result < INT_MIN / 10`, return 0.
   - Append the digit to `result` by multiplying `result` by 10 and adding the digit.
   - Remove the last digit from `x` by integer division (`x / 10`).
3. Return the reversed number.

### Example Implementation (C++)
```cpp
class Solution {
public:
    int reverse(int x) {
        int rev = 0;
        while (x != 0) {
            int pop = x % 10;
            x /= 10;
            if (rev > INT_MAX/10 || (rev == INT_MAX / 10 && pop > 7)) return 0;
            if (rev < INT_MIN/10 || (rev == INT_MIN / 10 && pop < -8)) return 0;
            rev = rev * 10 + pop;
        }
        
        return rev;
    }
};
```

```cpp
class Solution {
public:
    int reverse(int x) {
        int result = 0;
        
        while (x != 0) {
            int digit = x % 10;
            
            // Check for overflow before multiplying
            if (result > INT_MAX / 10 || result < INT_MIN / 10) {
                return 0;
            }
            
            result = result * 10 + digit;
            x /= 10;
        }
        
        return result;
    }
};
```

### How It Works
- **Reversal**:
  - Extract digits from the end using `x % 10`.
  - Build `result` by shifting digits left (multiplying by 10) and adding the new digit.
- **Overflow Check**:
  - Before adding a digit, ensure `result * 10` won’t exceed `INT_MAX` (2^31 - 1) or go below `INT_MIN` (-2^31).
- **Sign Handling**:
  - The modulo and division operations preserve the sign, so negative numbers are handled automatically.
- **Edge Cases**:
  - Zero: Returns 0.
  - Single digit: Returns the digit itself.
  - Numbers ending in zero: Leading zeros are dropped naturally.
  - Overflow: Returns 0 if the reversed number is out of range.
- **Result**: Returns the reversed integer or 0 if overflow occurs.

### Time and Space Complexity
- **Time Complexity**: O(log x), where `x` is the input number, as the number of digits is proportional to log x (base 10).
- **Space Complexity**: O(1), as only a constant amount of extra space is used.

### Alternative Approach
1. **Convert to String**:
   - Convert the integer to a string, reverse it, and convert back to an integer, checking for overflow.
   - Time Complexity: O(log x)
   - Space Complexity: O(log x) for the string
The digit-by-digit approach is preferred as it avoids string conversion, uses constant space, and is more efficient.


# 230. Kth Smallest Element in a BST - Tree, Depth-First Search, Binary Search Tree, Binary Tree

This document describes the solution to the "Kth Smallest Element in a BST" problem (LeetCode #230).

## Problem Description
Given the root of a binary search tree (BST) and an integer `k`, return the `k`-th smallest element in the BST (1-indexed). A BST has the property that for any node, all values in the left subtree are less than the node’s value, and all values in the right subtree are greater.

### Example
```
Input: root = [3,1,4,null,2], k = 1
Output: 1
Explanation: Inorder traversal is [1,2,3,4], so the 1st smallest is 1.
```
<img src="../assets/kthtree1.jpg" width="20%">

```
Input: root = [5,3,6,2,4,null,null,1], k = 3
Output: 3
Explanation: Inorder traversal is [1,2,3,4,5,6], so the 3rd smallest is 3.
```
<img src="../assets/kthtree2.jpg" width="20%">

```
Try to utilize the property of a BST.
Hint 2
Try in-order traversal. (Credits to @chan13)
Hint 3
What if you could modify the BST node's structure?
Hint 4
The optimal runtime complexity is O(height of BST).
```

### Constraints
- The number of nodes in the tree is `n`.
- `1 <= k <= n <= 10^4`
- `0 <= Node.val <= 10^4`

## Solution Approach
The problem can be solved using an inorder traversal of the BST, which visits nodes in ascending order, and tracking the count of visited nodes to find the `k`-th element.

### Inorder Traversal Approach
1. Perform an inorder traversal (left, root, right) of the BST.
2. Keep a counter to track the number of nodes visited.
3. When the counter reaches `k`, the current node’s value is the `k`-th smallest element.
4. Use recursion to traverse the tree and stop once the `k`-th element is found.

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
public:
    
    void traversal(TreeNode* root, vector<int>& ans) {
        if(!root)
            return;
        
        traversal(root->left, ans);
        ans.push_back(root->val);  
        traversal(root->right, ans);
    }
    
    int kthSmallest(TreeNode* root, int k) {
        vector<int> ans;
        traversal(root, ans);

        return ans[k-1];        
    }
};
```

```cpp
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        int count = 0;
        int result = 0;
        inorder(root, k, count, result);
        return result;
    }
    
private:
    void inorder(TreeNode* node, int k, int& count, int& result) {
        if (!node) return;
        
        // Traverse left subtree
        inorder(node->left, k, count, result);
        
        // Process current node
        count++;
        if (count == k) {
            result = node->val;
            return;
        }
        
        // Traverse right subtree
        inorder(node->right, k, count, result);
    }
};
```

### How It Works
- **Inorder Traversal**:
  - Visit the left subtree, then the current node, then the right subtree.
  - This ensures nodes are visited in ascending order due to BST properties.
- **Counting**:
  - Increment `count` for each node visited.
  - When `count` equals `k`, store the current node’s value in `result`.
- **Early Termination**:
  - Stop traversal once the `k`-th element is found to optimize performance.
- **Edge Cases**:
  - Single node: If `k = 1`, return the node’s value.
  - `k = n`: Returns the largest value in the BST.
  - Empty tree: Not applicable due to constraints (`1 <= k <= n`).
- **Result**: Returns the `k`-th smallest element in the BST.

### Time and Space Complexity
- **Time Complexity**: O(h + k), where `h` is the height of the tree. In the worst case (skewed tree), this is O(n). For a balanced BST, it’s O(log n + k).
- **Space Complexity**: O(h) for the recursion stack, where `h` is the tree height (O(n) for skewed, O(log n) for balanced).

### Alternative Approach
1. **Iterative Inorder with Stack**:
   - Use a stack to perform inorder traversal iteratively, tracking the count of visited nodes.
   - Time Complexity: O(h + k)
   - Space Complexity: O(h)
2. **Augmented BST**:
   - Modify the BST to store the size of each subtree, then find the `k`-th smallest using subtree sizes.
   - Time Complexity: O(log n) for balanced trees, but requires tree modification.
The recursive inorder approach is preferred for its simplicity and because the BST is not modified, making it suitable for the given constraints.



# 199. Binary Tree Right Side View - Depth-First Search, Breadth-First Search, Binary Tree

This document describes the solution to the "Binary Tree Right Side View" problem (LeetCode #199).

## Problem Description
Given the root of a binary tree, imagine standing on the right side of the tree. Return the values of the nodes visible from the right side, ordered from top to bottom. These are the rightmost nodes at each level of the tree.

### Example
```
Input: root = [1,2,3,null,5,null,4]
Output: [1,3,4]
Explanation: From the right side, the visible nodes are 1 (root), 3 (right child at level 1), and 4 (rightmost at level 2).
```
<img src="../assets/tree1_199.png" width="20%">

```
Input: root = [1,2,3,4,null,null,null,5]

Output: [1,3,4,5]
```
<img src="../assets/tree1_199.png" width="20%">


```
Input: root = [1,null,3]
Output: [1,3]
Explanation: Only the root and its right child are visible.

Input: root = []
Output: []
Explanation: An empty tree has no visible nodes.
```

### Constraints
- The number of nodes in the tree is in the range `[0, 100]`.
- `-100 <= Node.val <= 100`

## Solution Approach
The problem can be solved using a level-order traversal (breadth-first search, BFS) to process nodes level by level, collecting the rightmost node at each level.

### BFS (Level-Order Traversal) Approach
1. Use a queue to perform a level-order traversal of the tree.
2. For each level:
   - Track the number of nodes in the current level.
   - Process all nodes in the level, keeping track of the last node (rightmost).
   - Add the value of the last node to the result.
3. Return the result array containing the rightmost node values for each level.

### TreeNode Structure
```cpp
//Definition for a binary tree node.
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
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        if(root) {
            queue<TreeNode*> q;
            q.push(root);
            while(!q.empty()) {
                int n = q.size();
                for(int i = 0; i < n; i++)
                {
                    TreeNode * tn = q.front();
                    q.pop();
                    if( i == n-1)
                        ans.push_back(tn->val);

                    if(tn->left)
                        q.push(tn->left);

                    if(tn->right)
                        q.push(tn->right);
                }  
            }
        }
        
        
        return ans;
    }
};
```

```cpp
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        if (!root) return result;
        
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            int levelSize = q.size();
            TreeNode* rightmost = nullptr;
            
            // Process all nodes at the current level
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                rightmost = node; // Last node in level is rightmost
                
                // Add children to queue
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            
            // Add rightmost node's value to result
            result.push_back(rightmost->val);
        }
        
        return result;
    }
};
```

### How It Works
- **BFS**:
  - Use a queue to traverse the tree level by level.
  - For each level, process all nodes and track the last one (rightmost).
- **Level Processing**:
  - Record the size of the current level (`levelSize`).
  - Pop each node, update `rightmost`, and enqueue its children (left then right).
  - After processing the level, add the `rightmost` node’s value to the result.
- **Edge Cases**:
  - Empty tree: Return empty vector.
  - Single node: Return vector with that node’s value.
  - Skewed tree: Correctly captures the only node at each level.
- **Result**: Returns the values of the rightmost nodes at each level, from top to bottom.

### Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the number of nodes, as each node is processed exactly once.
- **Space Complexity**: O(w), where `w` is the maximum width of the tree (maximum number of nodes at any level). For a balanced tree, this is O(n/2) ≈ O(n); for a skewed tree, it’s O(1).

### Alternative Approach
1. **DFS (Pre-Order with Level Tracking)**:
   - Perform a right-to-left pre-order traversal (root, right, left).
   - Track the depth of each node and add the first node encountered at each depth to the result.
   - Time Complexity: O(n)
   - Space Complexity: O(h) for the recursion stack, where `h` is the tree height (O(log n) for balanced, O(n) for skewed).
The BFS approach is preferred for its intuitive level-by-level processing, which aligns naturally with the problem’s requirement to capture the rightmost node per level.


# 116. Populating Next Right Pointers in Each Node

This document describes the solution to the "Populating Next Right Pointers in Each Node" problem (LeetCode #116).

## Problem Description
Given a perfect binary tree where all leaves are on the same level, and every parent has two children, populate each node's `next` pointer to point to its next right node on the same level. If there is no next right node, the `next` pointer should be set to `nullptr`. The tree is modified in-place.

### Example
```
Input: root = [1,2,3,4,5,6,7]
Output: [1,#,2,3,#,4,5,6,7,#]
Explanation: 
- Level 1: 1->null
- Level 2: 2->3->null
- Level 3: 4->5->6->7->null
The next pointers connect nodes at the same level.

Input: root = []
Output: []
Explanation: An empty tree has no nodes to connect.
```
<img src="../assets/116_sample.png" width="30%">


### Constraints
- The number of nodes in the tree is in the range `[0, 2^12 - 1]`.
- `-1000 <= Node.val <= 1000`

## Solution Approach
The problem can be solved using a level-order traversal (BFS) to connect nodes at each level, leveraging the perfect binary tree property to ensure all levels are fully populated.

### BFS (Level-Order Traversal) Approach
1. Use a queue to perform a level-order traversal of the tree.
2. For each level:
   - Track the number of nodes in the current level.
   - Process each node, setting its `next` pointer to the next node in the queue (if it exists).
   - Enqueue the children (left then right) of each node for the next level.
3. Continue until all levels are processed.

### Node Structure
```cpp
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;
    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
```

### Example Implementation (C++)
```cpp
/* //recursive
class Solution {
public:
Node* connect(Node* root) {
    //base case
    if(root == NULL) return NULL;
    //connects the left subtree of same level with right subtree of that same level 
    
    if(root->left) 
        root->left->next = root->right;
    //connect the rightmost node of a level to the leftmost node of the next level.
    if(root->right && root->next) 
        root->right->next = root->next->left;
    
    //recursive calls for left and right subtrees.
    connect(root->left);
    connect(root->right);
    return root;
   }
};
*/

/* //iterative
void connect(TreeLinkNode *root) {
    if(!root)
        return;
    while(root -> left)
    {
        TreeLinkNode *p = root;
        while(p)
        {
            p -> left -> next = p -> right;
            if(p -> next)
                p -> right -> next = p -> next -> left;
            p = p -> next;
        }
        root = root -> left;
    }
}
*/


//queue
class Solution {
public:
    Node* connect(Node* root) {
        if(!root)return root;
        queue<Node*> q;
        q.push(root);
        while(!q.empty()){
            int n=q.size();
            for(int i=0;i<n;i++){
                Node* curr_node = q.front(); //left //1-2-3-4
                q.pop();
                
                if(i!=n-1) //this is not last node
                    curr_node->next=q.front(); //next node is right node to it
                    
                if(curr_node->left) q.push(curr_node->left);
                if(curr_node->right) q.push(curr_node->right);
            }
        }
        return root;
    }
};
```

```cpp
class Solution {
public:
    Node* connect(Node* root) {
        if (!root) return nullptr;
        
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            int levelSize = q.size();
            
            // Process all nodes at the current level
            for (int i = 0; i < levelSize; i++) {
                Node* node = q.front();
                q.pop();
                
                // Set next pointer to the next node in queue (if not the last node)
                if (i < levelSize - 1) {
                    node->next = q.front();
                }
                
                // Enqueue children
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        
        return root;
    }
};
```

### How It Works
- **BFS**:
  - Use a queue to traverse the tree level by level.
  - For each level, process all nodes and set their `next` pointers.
- **Level Processing**:
  - Record the size of the current level (`levelSize`).
  - For each node, set its `next` pointer to the next node in the queue (the next node at the same level), unless it’s the last node in the level.
  - Enqueue the left and right children of each node.
- **Edge Cases**:
  - Empty tree: Return `nullptr`.
  - Single node: No `next` pointer to set (handled by `levelSize - 1` check).
  - Perfect binary tree: Ensures all nodes at each level have children (except leaves).
- **Result**: The `next` pointers are set to connect nodes at the same level, and the modified tree’s root is returned.

### Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the number of nodes, as each node is processed exactly once.
- **Space Complexity**: O(w), where `w` is the maximum width of the tree. For a perfect binary tree, this is O(n/2) ≈ O(n) at the bottom level.

### Alternative Approach
1. **Constant Space (Using Next Pointers)**:
   - Leverage the already-set `next` pointers of the current level to connect the next level.
   - For each node in the current level, set `node->left->next = node->right` and `node->right->next = node->next->left` (if `node->next` exists).
   - Time Complexity: O(n)
   - Space Complexity: O(1)
The BFS approach is presented for its clarity and general applicability, but the constant-space approach is optimal for this specific problem due to the perfect binary tree structure and the availability of `next` pointers.


# 117. Populating Next Right Pointers in Each Node II - Linked List, Tree, Depth-First Search, Breadth-First Search, Binary Tree


This document describes the solution to the "Populating Next Right Pointers in Each Node II" problem (LeetCode #117).

## Problem Description
Given a binary tree (not necessarily perfect), populate each node's `next` pointer to point to its next right node on the same level. If there is no next right node, the `next` pointer should be set to `nullptr`. The tree is modified in-place.

### Example
```
Input: root = [1,2,3,4,5,null,7]
Output: [1,#,2,3,#,4,5,7,#]
Explanation:
- Level 1: 1->null
- Level 2: 2->3->null
- Level 3: 4->5->7->null
The next pointers connect nodes at the same level.

Input: root = []
Output: []
Explanation: An empty tree has no nodes to connect.
```
<img src="../assets/117_sample.png" width="30%">


### Constraints
- The number of nodes in the tree is in the range `[0, 6000]`.
- `-100 <= Node.val <= 100`

## Solution Approach
The problem can be solved using a constant-space approach by leveraging the `next` pointers of the current level to connect the nodes of the next level, without assuming a perfect binary tree.

### Constant-Space Approach Using Next Pointers
1. Traverse the tree level by level, using the `next` pointers of the current level to access nodes.
2. For each level:
   - Use a pointer to iterate through the nodes of the current level.
   - Connect the children of these nodes to form the `next` pointers of the next level.
   - Handle cases where nodes may have only one child or no children.
3. Move to the next level by finding the first node of the next level.
4. Continue until no more levels exist.

### Node Structure
```cpp
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;
    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
```

### Example Implementation (C++)
```cpp
class Solution {
public:
    Node* connect(Node* root) {
        if(!root)
            return root;
        
        queue<Node*> q;
        q.push(root);
        while(!q.empty())
        {
            int n = q.size();
            
            for(int i = 0; i < n; i++)
            {
                Node * curr = q.front(); //1-2-3-4
                q.pop();
                if(i < n-1) //not the last node in this group (!4)
                {
                    curr->next = q.front();
                }
                
                if(curr->left)
                    q.push(curr->left);
                
                if(curr->right)
                    q.push(curr->right);
            }
        }
        
        return root;
    }
};
```

```cpp
class Solution {
public:
    Node* connect(Node* root) {
        if (!root) return nullptr;
        
        Node* curr = root; // Points to the start of the current level
        
        while (curr) {
            Node* nextLevel = nullptr; // Head of the next level
            Node* prev = nullptr;      // Tracks the previous node in the next level
            
            // Process all nodes in the current level
            while (curr) {
                // Process left child
                if (curr->left) {
                    if (!nextLevel) nextLevel = curr->left;
                    if (prev) prev->next = curr->left;
                    prev = curr->left;
                }
                
                // Process right child
                if (curr->right) {
                    if (!nextLevel) nextLevel = curr->right;
                    if (prev) prev->next = curr->right;
                    prev = curr->right;
                }
                
                curr = curr->next; // Move to next node in current level
            }
            
            curr = nextLevel; // Move to the next level
        }
        
        return root;
    }
};
```

### How It Works
- **Level Traversal**:
  - Use `curr` to traverse nodes in the current level via `next` pointers.
- **Connecting Next Level**:
  - For each node in the current level, process its left and right children.
  - Link children using the `prev` pointer to set `next` pointers for the next level.
  - Track the head of the next level (`nextLevel`) with the first child encountered.
- **Level Transition**:
  - After processing a level, move `curr` to `nextLevel` to process the next level.
- **Edge Cases**:
  - Empty tree: Return `nullptr`.
  - Single node: No `next` pointer to set.
  - Sparse tree: Handles missing children or unbalanced levels.
  - Single child: Connects only the existing child to the next node.
- **Result**: The `next` pointers are set to connect nodes at the same level, and the modified tree’s root is returned.

### Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the number of nodes, as each node is processed exactly once.
- **Space Complexity**: O(1), as only a constant amount of extra space is used (pointers), excluding the implicit space of the output.

### Alternative Approach
1. **BFS (Level-Order Traversal)**:
   - Use a queue to process nodes level by level, setting `next` pointers for each level.
   - Time Complexity: O(n)
   - Space Complexity: O(w), where `w` is the maximum width of the tree.
The constant-space approach is preferred for its O(1) space complexity, leveraging the `next` pointers to avoid using a queue, and it handles non-perfect binary trees effectively.
