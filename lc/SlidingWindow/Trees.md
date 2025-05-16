```bash
# 102. Binary Tree Level Order Traversal Solution [Easy]
# 107. Binary Tree Level Order Traversal II [Easy, Understand how to calc the tree height]
# 114. Flatten Binary Tree to Linked List - [Easy]
# 230. Kth Smallest Element in a BST - [Easy via in order traversal]
# 199. Binary Tree Right Side View - Depth-First Search, Breadth-First Search, Binary Tree [Easy]
# 116. Populating Next Right Pointers in Each Node [Easy]
# 117. Populating Next Right Pointers in Each Node II - [Easy]
# 105. Construct Binary Tree from Preorder and Inorder Traversal - Map, Recursion [Medium]
# 112. Path Sum - Tree, Depth-First Search, Breadth-First Search, Binary Tree [Easy]
# 107. Binary Tree Level Order Traversal II - BFS [Easy, once height is calculated]
# 589. N-ary Tree Preorder Traversal - Stack, Tree, Depth-First Search [Easy]
# 98. Validate Binary Search Tree Solution [Easy]

# 314. Binary Tree Vertical Order Traversal
# 124. Binary Tree Maximum Path Sum
# 236. Lowest Common Ancestor of a Binary Tree
# 257. Binary Tree Paths

# 543. Diameter of Binary Tree
# 426. Convert a Binary Search Tree to a sorted Circular Doubly-Linked List in place. (In-Order Traversal)
```

# 102. Binary Tree Level Order Traversal -[Easy]

## Problem Description
Given the root of a binary tree, return the level order traversal of its nodes' values (i.e., from left to right, level by level).

### Example
<img src="../assets/tree102.jpg" width="20%">

```
Input: root = [3,9,20,null,null,15,7]
Output: [[3],[9,20],[15,7]]
Explanation: Level 1: [3], Level 2: [9,20], Level 3: [15,7].

Example 2:
Input: root = [1]
Output: [[1]]

Example 3:
Input: root = []
Output: []
```

## Solution
Below is the C++ solution to perform level order traversal of a binary tree using a breadth-first search (BFS) approach with a queue.

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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) {
            return result;
        }
        
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            int levelSize = q.size();
            vector<int> level;
            
            // Process all nodes at the current level
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* node = q.front();

                level.push_back(node->val);
                
                // Add children to the queue
                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }

                q.pop(); //remove the node just processed
            }
            
            // Add the current level to the result
            result.push_back(level);
        }
        
        return result;
    }
};
```

## Time and Space Complexity 
- **Time Complexity**: O(n), where `n` is the number of nodes in the tree. Each node is processed exactly once.
- **Space Complexity**: O(w), where `w` is the maximum width of the tree (i.e., the maximum number of nodes at any level). The queue stores at most one level of nodes, and the `level` vector temporarily stores node values for each level. In a balanced binary tree, `w` is O(n/2), and in a skewed tree, `w` is O(1).


# 107. Binary Tree Level Order Traversal II [Easy, Understand how to calc the tree height]

## Problem Description
Given the root of a binary tree, return the bottom-up level order traversal of its nodes' values (i.e., from left to right, level by level, starting from the deepest level up to the root).

### Example
<img src="../assets/tree107.jpg" width="20%">

```
Input: root = [3,9,20,null,null,15,7]
Output: [[15,7],[9,20],[3]]
Explanation: Level 3: [15,7], Level 2: [9,20], Level 1: [3].

Example 2:
Input: root = [1]
Output: [[1]]

Example 3:
Input: root = []
Output: []
```

## Solution
Below is the C++ solution to perform bottom-up level order traversal of a binary tree using a breadth-first search (BFS) approach with a queue, followed by reversing the result.

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
    
    int getTreeHeight(TreeNode *node) {
        if(!node)
            return 0;
        
        int leftH = getTreeHeight(node->left);
        int rightH = getTreeHeight(node->right);
 
        return max(leftH, rightH) + 1;       
    }
    
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> ans;
        
        if(!root)
            return ans;
        
        int levels = getTreeHeight(root);
        
        queue<TreeNode*> q;
        
        q.push(root);
               
        ans.resize(levels);
        int cur_index = levels - 1;
        
        while(q.size()>0)
        {
            int qSize = q.size(); //gives num of nodes at same level

            vector<int> val(qSize, 0);

            //iterate through all nodes and add their kids
            for(int i = 0; i < qSize; i++) 
            {
                TreeNode * node = q.front();
                val[i] = node->val;

                if(node->left)
                    q.push(node->left);

                if(node->right)
                    q.push(node->right);

                //pop the node just processed
                q.pop(); //removes the node from Q
            }

            ans[cur_index]= val; 
            cur_index--;
        }
        
        return ans;
    }
};

class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) {
            return result;
        }
        
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            int levelSize = q.size();
            vector<int> level;
            
            // Process all nodes at the current level
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* node = q.front();
                q.pop();
                level.push_back(node->val);
                
                // Add children to the queue
                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
            
            // Add the current level to the result
            result.push_back(level);
        }
        
        // Reverse the result to get bottom-up order
        reverse(result.begin(), result.end());
        
        return result;
    }
};
```

## Explanation
1. **Edge Case**:
   - If the root is `nullptr`, return an empty vector.
2. **BFS with Queue**:
   - Use a queue to process nodes level by level, similar to standard level order traversal.
   - Initialize the queue with the root node.
   - While the queue is not empty:
     - Get the number of nodes at the current level (`levelSize`).
     - Create a vector `level` to store the values of the current level.
     - Process each node in the current level:
       - Pop the front node from the queue.
       - Add its value to `level`.
       - Push its left and right children (if they exist) to the queue.
     - Add `level` to the result.
3. **Bottom-Up Adjustment**:
   - After collecting levels in top-down order (root to leaves), reverse the `result` vector to achieve bottom-up order (leaves to root).
4. **Result**:
   - The `result` vector contains vectors of node values, each representing one level, ordered from the deepest level to the root.

## Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the number of nodes in the tree. Each node is processed exactly once during BFS, and reversing the result takes O(h) where `h` is the number of levels (h ≤ n).
- **Space Complexity**: O(w), where `w` is the maximum width of the tree (i.e., the maximum number of nodes at any level). The queue stores at most one level of nodes, and the `level` vector temporarily stores node values for each level. In a balanced binary tree, `w` is O(n/2); in a skewed tree, `w` is O(1). The output space is not counted as extra space.

## Edge Cases
- Empty tree: Return `[]`.
- Single node: Return `[[val]]` (e.g., `root = [1]` returns `[[1]]`).
- Skewed tree: `root = [1,null,2,null,3]` returns `[[3],[2],[1]]`.
- Complete binary tree: Handles large trees with up to `n = 2000` nodes.
- Unbalanced tree: Correctly processes levels with varying numbers of nodes.


# 114. Flatten Binary Tree to Linked List [Easy]

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

```bash
    1
   / \
  2   5
 / \   \
3   4   6


    1        4
   /          \
  2     =>     5
 / \            \
3   4            6


1
 \
  2
 / \
3   4
     \
      5
       \
        6

1
 \
  2
   \
    3
     \
      4
       \
        5
         \
          6
```


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
        if(!root)
            return;

        TreeNode * n = root;     
        while (n) {
            if(n->left && n->right)
            {
                TreeNode * ln = n->left; 
                while(ln->right)
                    ln = ln->right;

                ln->right = n->right;
                n->right = nullptr;
            }

            if(n->left)
                n->right = n->left;

            n->left = nullptr;
            n = n->right;
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




# 230. Kth Smallest Element in a BST - [Easy]

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



# 199. Binary Tree Right Side View - Breadth-First Search [Easy]

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
<img src="../assets/tree2_199.png" width="20%">


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

### How It Works
- **BFS**:
  - Use a queue to traverse the tree level by level.
  - For each level, process all nodes and track the last one (rightmost).

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



# 116. Populating Next Right Pointers in Each Node - [Easy]

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
    unordered_map<int, int> mapIn;
    int preorderIndex = 0;

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
         for (int i = 0; i < inorder.size(); i++)
            mapIn[inorder[i]] = i;
        
        preorderIndex = 0;

        //left and right of the inorder tree
        return splitTree(preorder, 0, preorder.size()-1);
    }
    
private:
    TreeNode* splitTree(vector<int>& P, int left, int right) {
        if( left > right )
            return nullptr;

        int rootValue = P[preorderIndex++];

        int inorderRootIndex = mapIn[rootValue]; //where is root located in inorder?
        
        TreeNode* root = new TreeNode(rootValue);  
        
        //build left and right tree
        root->left = splitTree(P, left, inorderRootIndex - 1); //skip root index
        root->right = splitTree(P, inorderRootIndex + 1, right); //skip root index
        
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


# 112. Path Sum - Tree, Depth-First Search, Breadth-First Search, Binary Tree
https://leetcode.com/problems/path-sum/description/

Given the root of a binary tree and an integer targetSum, return true if the tree has a root-to-leaf path such that adding up all the values along the path equals targetSum.

A leaf is a node with no children.
```py
Example 1:

Input: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
Output: true
Explanation: The root-to-leaf path with the target sum is shown.
```
<img src="../assets/pathsum1.jpg" width="40%">

```py
Example 2:

Input: root = [1,2,3], targetSum = 5
Output: false
Explanation: There are two root-to-leaf paths in the tree:
(1 --> 2): The sum is 3.
(1 --> 3): The sum is 4.
There is no root-to-leaf path with sum = 5.
```
<img src="../assets/pathsum2.jpg" width="20%">

```py
Example 3:

Input: root = [], targetSum = 0
Output: false
Explanation: Since the tree is empty, there are no root-to-leaf paths.
 
Constraints:

The number of nodes in the tree is in the range [0, 5000].
-1000 <= Node.val <= 1000
-1000 <= targetSum <= 1000
```
```c++
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
    bool hasPathSum(TreeNode* root, int targetSum) {        
        if(!root)
            return false;
        
        targetSum -= root->val;
        
        if(!root->left && !root->right) //if this is a leaf node check.
            return (targetSum ==0);
        
        return hasPathSum(root->left, targetSum) || hasPathSum(root->right, targetSum);
    }
};
```


# 107. Binary Tree Level Order Traversal II - Tree, Breadth-First Search, Binary Tree
https://leetcode.com/problems/binary-tree-level-order-traversal-ii/description/

Given the root of a binary tree, return the bottom-up level order traversal of its nodes' values. (i.e., from left to right, level by level from leaf to root).

```py
Example 1:

Input: root = [3,9,20,null,null,15,7]
Output: [[15,7],[9,20],[3]]
```
<img src="../assets/tree1.jpg" width="20%">

```py
Example 2:

Input: root = [1]
Output: [[1]]
Example 3:

Input: root = []
Output: []
 
Constraints:

The number of nodes in the tree is in the range [0, 2000].
-1000 <= Node.val <= 1000
```
```c++
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
    
    int getTreeHeight(TreeNode *node) {
        if(!node)
            return 0;
        
        int leftH = getTreeHeight(node->left);
        int rightH = getTreeHeight(node->right);
 
        return max(leftH, rightH) + 1;       
    }
    
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> ans;
        
        if(!root)
            return ans;
        
        int levels = getTreeHeight(root);
        
        queue<TreeNode*> q;
        
        q.push(root);
               
        ans.resize(levels);
        int cur_index = levels - 1;
        
        while(q.size()>0)
        {
            int qSize = q.size(); //gives num of nodes at same level

            vector<int> val(qSize, 0);

            //iterate through all nodes and add their kids
            for(int i = 0; i < qSize; i++) 
            {
                TreeNode * node = q.front();
                val[i] = node->val;

                if(node->left)
                    q.push(node->left);

                if(node->right)
                    q.push(node->right);

                //pop the node just processed
                q.pop(); //removes the node from Q
            }

            ans[cur_index]= val; 
            cur_index--;
        }
        
        return ans;
    }
};
```


# 589. N-ary Tree Preorder Traversal - Stack, Tree, Depth-First Search
https://leetcode.com/problems/n-ary-tree-preorder-traversal/description/

Given the root of an n-ary tree, return the preorder traversal of its nodes' values.

Nary-Tree input serialization is represented in their level order traversal. Each group of children is separated by the null value (See examples)
```py
Example 1:

Input: root = [1,null,3,2,4,null,5,6]
Output: [1,3,5,6,2,4]
```
<img src="../assets/narytreeexample.png" width="40%">

```py
Example 2:

Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
Output: [1,2,3,6,7,11,14,4,8,12,5,9,13,10]
 
Constraints:

The number of nodes in the tree is in the range [0, 104].
0 <= Node.val <= 104
The height of the n-ary tree is less than or equal to 1000.
 
Follow up: Recursive solution is trivial, could you do it iteratively?
```
<img src="../assets/sample_4_964.png" width="40%">

```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    void Traverse(Node *node, vector<int>& vOut) {
        if(!node)
            return;
        
        vOut.push_back(node->val);

        for(auto& n : node->children)
            Traverse(n, vOut);  
    }
    
    vector<int> preorder(Node* root) {
        vector<int> vOut;
        Traverse(root, vOut); 
        return vOut;
    }
};
```


# 98. Validate Binary Search Tree

## Problem Description
Given the root of a binary tree, determine if it is a valid binary search tree (BST). A valid BST is defined as follows:
- The left subtree of a node contains only nodes with keys less than the node's key.
- The right subtree of a node contains only nodes with keys greater than the node's key.
- Both the left and right subtrees must also be binary search trees.

### Example
```
Input: root = [2,1,3]
Output: true
Explanation: The tree is a valid BST (1 < 2 < 3).
```
<img src="../assets/bstree1.jpg" width="30%">

### Example
```
Input: root = [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.
```
<img src="../assets/bstree2.jpg" width="30%">


## Solution
Below is the C++ solution to validate a binary search tree using recursive inorder traversal.

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
    bool isValidBST(TreeNode* root) {
        return help(root, INT_MIN, INT_MAX);
    }
    
    bool help(TreeNode* node, long min, long max){
        if(!node)   
            return true;

        //left should always be between -inf and parent
        //right between parent and +inf
        if(node->val <= min || node->val >= max)  
            return false;

        return help(node->left, min, node->val) && help(node->right, node->val, max);
    }
};

```

## Explanation
1. **Recursive Validation with Range**:
   - Use a helper function `validate` that takes the current node and pointers to `minNode` and `maxNode` to define the valid range for the node's value.
   - For each node:
     - If the node is `nullptr`, return `true` (empty subtree is valid).
     - Check if the node's value is within the valid range:
       - Must be greater than `minNode->val` (if `minNode` exists).
       - Must be less than `maxNode->val` (if `maxNode` exists).
     - If the value is out of range, return `false`.
   - Recursively validate:
     - Left subtree: Update `maxNode` to the current node (all values must be < `node->val`).
     - Right subtree: Update `minNode` to the current node (all values must be > `node->val`).
2. **Initial Call**:
   - Start with `minNode` and `maxNode` as `nullptr` to allow any value at the root.
3. **Correctness**:
   - This approach ensures each node's value is strictly within the valid range for its position in the BST, handling cases where duplicate values are invalid.

## Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the number of nodes in the tree. Each node is visited exactly once.
- **Space Complexity**: O(h), where `h` is the height of the tree, due to the recursion stack. In the worst case (skewed tree), this is O(n); in a balanced tree, it is O(log n).

## Edge Cases
- Empty tree: Return `true`.
- Single node: Return `true` (valid BST).
- Invalid BST with duplicates: `node->val == minNode->val` or `node->val == maxNode->val` returns `false`.
- Deep skewed tree: Handled by recursive calls.
- Large valid BST: Efficiently validates within constraints.
- Invalid subtree: Detects cases like `[5,4,6,null,null,3,7]` where `3` violates the BST property in the right subtree.

# 314. Binary Tree Vertical Order Traversal
```
      3
    /  \
   9   20
      /  \
     15   7

     Output: [9], [3,15], [20], [7]
```
Given the root of a binary tree, return the vertical order traversal of its nodes' values. (i.e., from top to bottom, column by column).

If two nodes are in the same row and column, the order should be from left to right.

```c++
class Solution {
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        vector<vector<int>> res;
        
        if(!root)
            return res;
        
        map<int, vector<int>> map;
        
        queue<pair<TreeNode*, int>> q;
        
        q.push({root, 0});
        
        while(!q.empty()) {
            int size = q.size();
            
            for(int i = 0; i < size; i++) {
                TreeNode* curr = q.front().first;
                int dir = q.front().second;
                q.pop();
                map[dir].push_back(curr->val);
                if(curr->left) q.push({curr->left, dir - 1});
                if(curr->right) q.push({curr->right, dir + 1});
            }
        }
        
        for(auto i : map) {
            res.push_back(i.second);
        }
        return res;
    }
};
```

# 124. Binary Tree Maximum Path Sum
https://leetcode.com/problems/binary-tree-maximum-path-sum/description/

A path in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has an edge connecting them. A node can only appear in the sequence at most once. Note that the path does not need to pass through the root.

The path sum of a path is the sum of the node's values in the path.

Given the root of a binary tree, return the maximum path sum of any non-empty path.

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
    int maxPathSum(TreeNode* root) {
        maxSum = INT_MIN;
        maxPathSubTreeSum(root);
        return maxSum;
    }

private:
    int maxSum;
    // post order traversal of subtree rooted at `root`
    int maxPathSubTreeSum(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        // add the path sum from left subtree. Note that if the path
        // sum is negative, we can ignore it, or count it as 0.
        // This is the reason we use `max` here.
        int gainFromLeft = max(maxPathSubTreeSum(root->left), 0);
        // add the path sum from right subtree. 0 if negative
        int gainFromRight = max(maxPathSubTreeSum(root->right), 0);
        // if left or right path sum are negative, they are counted
        // as 0, so this statement takes care of all four scenarios
        maxSum = max(maxSum, gainFromLeft + gainFromRight + root->val);
        // return the max sum for a path starting at the root of subtree
        return max(gainFromLeft + root->val, gainFromRight + root->val);
    }
};
```


# 236. Lowest Common Ancestor of a Binary Tree
https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/description/


# 257. Binary Tree Paths

Given the root of a binary tree, return all root-to-leaf paths in any order.

A leaf is a node with no children.

```
Approach
Perform DFS starting from the root.
Maintain a current path string.
At each node:
 -Append the node's value.
- If it's a leaf, add the path to the result.
- Otherwise, recurse for its children.

Complexity
Time: O(n), where n is the number of nodes.
Space: O(h), where h is the tree height.
```

```cpp
class Solution {
public:
    void dfs(TreeNode* node ,string current,vector<string>& ans){
            
            current+=to_string(node->val);

            if(!node->left && !node->right){
                ans.push_back(current);
            }
            current+="->";
            if(node->left) dfs(node->left,current,ans);
            if(node->right) dfs(node->right,current,ans);
            current.pop_back();
    }
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> ans;
        if(!root) return ans;

    
        dfs(root,"",ans);
        return ans;
    }
};
```

OR

```cpp
class Solution {
public:
    void findPath(TreeNode* node, vector<string>& ans, string temp) {
        temp += to_string(node->val);  // Add the current node value to the path
        if (node->left) findPath(node->left, ans, temp + "->");  // Traverse left
        if (node->right) findPath(node->right, ans, temp + "->"); // Traverse right
        if (!node->left && !node->right) ans.push_back(temp);  // Add path if leaf node
    }

    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> ans;
        if (root) findPath(root, ans, "");  // Start traversal from the root
        return ans;
    }
};
```


# 543. Diameter of Binary Tree
https://leetcode.com/problems/diameter-of-binary-tree/description/

Given the root of a binary tree, return the length of the diameter of the tree.

The diameter of a binary tree is the length of the longest path between any two leaf nodes in a tree. This path may or may not pass through the root.

The length of a path between two leaf nodes is represented by the number of edges between them.

```cpp
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int diameter = 0;
        height(root, diameter);
        return diameter;
    }
    
private:
    int height(TreeNode* node, int& diameter) {
        if (!node) return 0;
        
        int leftHt = height(node->left, diameter);
        int rightHt = height(node->right, diameter);
        
        diameter = max(diameter, leftHt + rightHt);
        
        return 1 + max(leftHt, rightHt);
    }
};
```

# 426. Convert a Binary Search Tree to a sorted Circular Doubly-Linked List in place. (In-Order Traversal)

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/

class Solution {
  public:
  // the smallest (first) and the largest (last) nodes
  Node* first = NULL;
  Node* last = NULL;

  void helper(Node* node) {
    if (node) {
      // left
      helper(node->left);

      // node 
      if (last) {
        // link the previous node (last)
        // with the current one (node)
        last->right = node;
        node->left = last;
      }
      else {
        // keep the smallest node
        // to close DLL later on
        first = node;
      }
      last = node;

      // right
      helper(node->right);
    }
  }

  Node* treeToDoublyList(Node* root) {
    if (!root) return NULL;

    helper(root);

    // close DLL
    last->right = first;
    first->left = last;
    return first;
  }
};
