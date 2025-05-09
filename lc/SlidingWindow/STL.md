# STL Containers and Classes for LeetCode

## 1. std::vector
- **Initialization:** `vector<int> v = {1, 2, 3}; or vector<int> v(n, 0);`
- **Description**: Dynamic array with random access.
- **Key Methods**:
  - `push_back(value)`, `pop_back()`: O(1) amortized.
  - `insert(pos, value)`, `erase(iterator pos)`: O(n).
  - `size()`, `empty()`, `front()`, `back()`: O(1).
  - `clear()`
  - `std::reverse(v.begin(), v.end())`: O(n).
- **sorting:** `std::sort(v.begin(), v.end());`. O(n log n)
- **LeetCode Use**:
-   Array manipulation, DP tables: `vector<int> dp(n + 1, 0);`
-   two-pointer techniques (`int left = 0, right = v.size() - 1; while (left < right) {...}.`).

## 2. std::set
- **Initialization:** `set<int> s = {1, 2, 3}; or set<int> s;.`
- **Description**: Sorted container of unique elements (balanced BST).
- **Key Methods**:
  - `insert(value)`, `erase(value)`, `find(value)`, `count(value)`: O(log n).
  - `lower_bound(value)`, `upper_bound(value)`: O(log n).
  - `size()`, `empty()`, `clear()`: O(1).
- **Example**: `set<int> s = {1, 2, 3}; s.insert(4); if (s.count(2)) {...}`.
- **LeetCode Use**: Deduplication, sorted unique elements (e.g., Contains Duplicate, Intersection).

## 3. std::map
- **Initialization:** `map<int, int> m = {{1, 10}, {2, 20}}; or map<int, int> m;`
- **Description**: Sorted key-value pairs (balanced BST).
- **Key Methods**:
  - `m[key] = value`, `insert({key, value})`, `erase(key)`, `find(key)`, `count(key)`: O(log n).
  - `lower_bound(key)`, `upper_bound(key)`: O(log n).
  - `size()`, `empty()`, `clear()`: O(1).
- **Check Existence:** `if (m.count(1)), Time Complexity: O(log n).`
- **Iteration:** `for (auto [key, value] : m), uses begin()/end().`
- **Example**: `map<int, int> m; m[1] = 10; if (m.find(1) != m.end()) {...}`.
- **LeetCode Use**: Key-value storage, frequency counting (e.g., Two Sum, Group Anagrams).

## 4. std::unordered_set
- **Description**: Hash-based container for unique elements, unsorted.
- **Key Methods**:
  - `insert(value)`, `erase(value)`, `find(value)`, `count(value)`: O(1) average.
  - `size()`, `empty()`: O(1).
- **Example**: `unordered_set<int> s; s.insert(5); if (s.count(5)) {...}`.
- **LeetCode Use**: Fast lookups, deduplication (e.g., Valid Sudoku, Contains Duplicate).

## 5. std::unordered_map
- **Description**: Hash-based key-value pairs, unsorted.
- **Key Methods**:
  - `m[key] = value`, `insert({key, value})`, `erase(key)`, `find(key)`, `count(key)`: O(1) average.
  - `size()`, `empty()`: O(1).
- **Example**: `unordered_map<int, int> m; m[1] = 10; if (m.find(2) != m.end()) {...}`.
- **LeetCode Use**: Fast key-value lookups, frequency counting (e.g., Two Sum, LRU Cache).

## 6. std::priority_queue
- **Description**: Heap-based container, max-heap by default.
- **Key Methods**:
  - `push(value)`, `pop()`: O(log n).
  - `top()`: O(1).
  - `size()`, `empty()`: O(1).
- **Example**: `priority_queue<int> pq; pq.push(5); int top = pq.top();` (Min-heap: `priority_queue<int, vector<int>, greater<int>>`).
- **LeetCode Use**: Top-k elements, greedy algorithms (e.g., Kth Largest Element, Merge K Sorted Lists).
```cpp
    // Use a max-heap to maintain the k smallest elements
    std::priority_queue<int> max_heap; //LARGEST value is at TOP, hence max_heap; std::less<int> by default
    for (int num : arr) {
        max_heap.push(num); //PUSH
        if (max_heap.size() > static_cast<size_t>(k)) {
            max_heap.pop(); // Remove the largest element as LARGEST is on top
        }
    }

    // Use a min-heap to maintain the k largest elements
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap; //MIN value on top; they are in incrasing order
    for (int num : arr) {
        min_heap.push(num);
        if (min_heap.size() > static_cast<size_t>(k)) {
            min_heap.pop(); // Remove the smallest element
        }
    }

    // Extract elements from the heap
    std::vector<int> result;
    while (!min_heap.empty()) {
        result.push_back(min_heap.top());
        min_heap.pop();
    }
```


## 7. std::queue
- **Description**: FIFO container.
- **Key Methods**:
  - `push(value)`, `pop()`, `front()`, `back()`: O(1).
  - `size()`, `empty()`: O(1).
- **Example**: `queue<int> q; q.push(5); int front = q.front();`.
- **LeetCode Use**: BFS, level-order traversal (e.g., Binary Tree Level Order Traversal, Rotten Oranges).

## 8. std::stack
- **Description**: LIFO container.
- **Key Methods**:
  - `push(value)`, `pop()`, `top()`: O(1).
  - `size()`, `empty()`: O(1).
- **Example**: `stack<int> s; s.push(5); int top = s.top();`.
- **LeetCode Use**: DFS, parentheses matching (e.g., Valid Parentheses, Next Greater Element).

## 9. std::deque
- **Description**: Double-ended queue, fast at both ends.
- **Key Methods**:
  - `push_back()`, `push_front()`, `pop_back()`, `pop_front()`: O(1).
  - `front()`, `back()`, `operator[]`: O(1).
  - `size()`, `empty()`: O(1).
- **Example**: `deque<int> dq; dq.push_back(5); dq.push_front(10);`.
- **LeetCode Use**: Sliding window, flexible queues (e.g., Sliding Window Maximum).

## 10. std::list
- **Description**: Doubly-linked list, fast insertions/deletions.
- **Key Methods**:
  - `push_back()`, `push_front()`, `pop_back()`, `pop_front()`: O(1).
  - `insert(pos, value)`, `erase(pos)`: O(1).
  - `size()`, `empty()`: O(1) or O(n).
- **Example**: `list<int> l; l.push_back(5); l.push_front(10);`.
- **LeetCode Use**: Frequent insertions/deletions (e.g., LRU Cache, Merge K Sorted Lists).

## 11. std::array
- **Description**: Fixed-size array, stack-allocated.
- **Key Methods**:
  - `operator[]`, `at()`, `front()`, `back()`: O(1).
  - `size()`, `empty()`, `fill(value)`: O(1) or O(n) for `fill`.
- **Example**: `array<int, 5> arr = {1, 2, 3, 4, 5}; arr[0] = 10;`.
- **LeetCode Use**: Fixed-size inputs (e.g., Rotate Array, Matrix problems).

## 12. std::bitset
- **Description**: Fixed-size bit sequence for compact boolean storage.
- **Key Methods**:
  - `set(pos)`, `reset(pos)`, `flip(pos)`, `test(pos)`: O(1).
  - `count()`: O(1).
  - `size()`: O(1).
- **Example**: `bitset<32> b; b.set(0); if (b.test(0)) {...}`.
- **LeetCode Use**: Bit manipulation (e.g., Counting Bits, Single Number).

## General Notes
- **Choosing Containers**:
  - **Fast Lookups**: `unordered_set`, `unordered_map` (O(1) average).
  - **Sorted Data**: `set`, `map` (O(log n)).
  - **Dynamic Arrays**: `vector`, `deque`.
  - **Priority-Based**: `priority_queue`.
  - **Sequential**: `queue` (BFS), `stack` (DFS).
  - **Fixed Size**: `array`, `bitset`.
- **Patterns**: Use `std::sort`, `std::lower_bound`, or custom comparators with `priority_queue`.
- **Performance**: Reserve memory for `vector`/`unordered_map`; prefer `unordered_` containers for speed when order isn’t needed.
