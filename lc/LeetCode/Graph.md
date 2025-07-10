```bash
# 56. Merge Intervals [Easy]
# 253. Meeting Rooms II [Easy]
# 210. Course Schedule II - Depth-First Search - Breadth-First Search, Graph, Topological Sort [Easy]
# 1971. Find if Path Exists in Graph - BFS [Easy]
# 797. All Paths From Source to Target - BFS [Easy]
# 133. Clone Graph [Easy via BFS and a map of visited nodes]
# 269. Alien Dictionary [Medium]
# 317. Shortest Distance from All Buildings [Medium, Revisit]
# 721. Accounts Merge
# 785. Is Graph Bipartite? [Medium]
```

```cpp
#include <vector>
#include <iostream>
using namespace std;

/*
ADJACENCY MATRIX BASICS:

What is it?
- A 2D array/matrix to represent connections between nodes in a graph
- If there are N nodes, matrix size is N×N
- matrix[i][j] = 1 means there's an edge from node i to node j
- matrix[i][j] = 0 means no edge from node i to node j

For weighted graphs:
- matrix[i][j] = weight of edge from i to j
- matrix[i][j] = 0 or infinity means no edge
*/

class AdjacencyMatrix {
private:
    vector<vector<int>> matrix;
    int numNodes;
    bool isDirected;
    
public:
    // Constructor
    AdjacencyMatrix(int n, bool directed = false) : numNodes(n), isDirected(directed) {
        // Initialize matrix with all zeros (no edges)
        matrix.resize(n, vector<int>(n, 0));
    }
    
    // Add an edge between two nodes
    void addEdge(int from, int to, int weight = 1) {
        if (from >= numNodes || to >= numNodes || from < 0 || to < 0) {
            cout << "Invalid node indices!" << endl;
            return;
        }
        
        matrix[from][to] = weight;
        
        // If undirected graph, add edge in both directions
        if (!isDirected) {
            matrix[to][from] = weight;
        }
        
        cout << "Added edge: " << from << " -> " << to;
        if (weight != 1) cout << " (weight: " << weight << ")";
        cout << endl;
    }
    
    // Remove an edge
    void removeEdge(int from, int to) {
        if (from >= numNodes || to >= numNodes || from < 0 || to < 0) {
            cout << "Invalid node indices!" << endl;
            return;
        }
        
        matrix[from][to] = 0;
        
        if (!isDirected) {
            matrix[to][from] = 0;
        }
        
        cout << "Removed edge: " << from << " -> " << to << endl;
    }
    
    // Check if edge exists
    bool hasEdge(int from, int to) {
        if (from >= numNodes || to >= numNodes || from < 0 || to < 0) {
            return false;
        }
        return matrix[from][to] != 0;
    }
    
    // Get edge weight
    int getWeight(int from, int to) {
        if (from >= numNodes || to >= numNodes || from < 0 || to < 0) {
            return 0;
        }
        return matrix[from][to];
    }
    
    // Print the matrix
    void printMatrix() {
        cout << "\nAdjacency Matrix:" << endl;
        cout << "   ";
        for (int i = 0; i < numNodes; i++) {
            cout << i << " ";
        }
        cout << endl;
        
        for (int i = 0; i < numNodes; i++) {
            cout << i << ": ";
            for (int j = 0; j < numNodes; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    
    // Get all neighbors of a node
    vector<int> getNeighbors(int node) {
        vector<int> neighbors;
        for (int i = 0; i < numNodes; i++) {
            if (matrix[node][i] != 0) {
                neighbors.push_back(i);
            }
        }
        return neighbors;
    }
    
    // Get degree of a node
    int getDegree(int node) {
        int degree = 0;
        for (int i = 0; i < numNodes; i++) {
            if (matrix[node][i] != 0) degree++;
        }
        
        // For undirected graphs, also count incoming edges (if different)
        if (!isDirected) {
            for (int i = 0; i < numNodes; i++) {
                if (i != node && matrix[i][node] != 0) degree++;
            }
        }
        
        return degree;
    }
};

// Example: Building adjacency matrix step by step
void demonstrateBuilding() {
    cout << "=== BUILDING ADJACENCY MATRIX STEP BY STEP ===" << endl;
    
    // Create a graph with 5 nodes (0, 1, 2, 3, 4)
    AdjacencyMatrix graph(5, false); // undirected graph
    
    cout << "Step 1: Created empty 5x5 matrix" << endl;
    graph.printMatrix();
    
    cout << "Step 2: Adding edges one by one" << endl;
    graph.addEdge(0, 1);  // Connect node 0 to node 1
    graph.printMatrix();
    
    graph.addEdge(1, 2);  // Connect node 1 to node 2
    graph.printMatrix();
    
    graph.addEdge(2, 3);  // Connect node 2 to node 3
    graph.printMatrix();
    
    graph.addEdge(0, 4);  // Connect node 0 to node 4
    graph.printMatrix();
    
    graph.addEdge(1, 3);  // Connect node 1 to node 3
    graph.printMatrix();
    
    cout << "Final graph structure:" << endl;
    cout << "0 -- 1 -- 2" << endl;
    cout << "|    |    |" << endl;
    cout << "4    3 ---+" << endl;
}

// Example: Weighted graph
void demonstrateWeightedGraph() {
    cout << "=== WEIGHTED GRAPH EXAMPLE ===" << endl;
    
    AdjacencyMatrix weightedGraph(4, true); // directed weighted graph
    
    cout << "Building a weighted directed graph:" << endl;
    weightedGraph.addEdge(0, 1, 5);   // 0 -> 1 with weight 5
    weightedGraph.addEdge(0, 2, 3);   // 0 -> 2 with weight 3
    weightedGraph.addEdge(1, 2, 2);   // 1 -> 2 with weight 2
    weightedGraph.addEdge(1, 3, 4);   // 1 -> 3 with weight 4
    weightedGraph.addEdge(2, 3, 1);   // 2 -> 3 with weight 1
    
    weightedGraph.printMatrix();
    
    cout << "Graph visualization:" << endl;
    cout << "0 --5--> 1 --4--> 3" << endl;
    cout << "|        |        ^" << endl;
    cout << "3        2        |" << endl;
    cout << "|        |        1" << endl;
    cout << "v        v        |" << endl;
    cout << "2 ---------------+" << endl;
}

/*
STEP-BY-STEP MATRIX BUILDING PROCESS:

1. INITIALIZATION:
   - Create N×N matrix filled with zeros
   - All matrix[i][j] = 0 means no edges initially

2. ADDING EDGES:
   For each edge (u, v):
   - Set matrix[u][v] = 1 (or weight for weighted graphs)
   - If undirected: also set matrix[v][u] = 1

3. EXAMPLE WALKTHROUGH:
   
   Graph: 0-1-2
   
   Step 1: Initialize 3×3 matrix
   [0 0 0]
   [0 0 0]
   [0 0 0]
   
   Step 2: Add edge 0-1
   [0 1 0]
   [1 0 0]  (undirected, so both directions)
   [0 0 0]
   
   Step 3: Add edge 1-2
   [0 1 0]
   [1 0 1]
   [0 1 0]

MATRIX PROPERTIES:

1. UNDIRECTED GRAPH:
   - Matrix is symmetric: matrix[i][j] = matrix[j][i]
   - Diagonal is usually 0 (no self-loops)

2. DIRECTED GRAPH:
   - Matrix may not be symmetric
   - matrix[i][j] = 1 doesn't mean matrix[j][i] = 1

3. WEIGHTED GRAPH:
   - Store weights instead of just 1/0
   - 0 or infinity typically means no edge

SPACE COMPLEXITY: O(N²) where N is number of nodes
TIME COMPLEXITY: 
- Add edge: O(1)
- Remove edge: O(1)
- Check edge: O(1)
- Get all neighbors: O(N)
*/

int main() {
    demonstrateBuilding();
    cout << "\n" << string(50, '=') << "\n" << endl;
    demonstrateWeightedGraph();
    
    // Additional examples
    cout << "=== CHECKING OPERATIONS ===" << endl;
    AdjacencyMatrix graph(3, false);
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    
    cout << "Has edge 0->1: " << (graph.hasEdge(0, 1) ? "Yes" : "No") << endl;
    cout << "Has edge 0->2: " << (graph.hasEdge(0, 2) ? "Yes" : "No") << endl;
    cout << "Weight of edge 0->1: " << graph.getWeight(0, 1) << endl;
    
    vector<int> neighbors = graph.getNeighbors(1);
    cout << "Neighbors of node 1: ";
    for (int neighbor : neighbors) {
        cout << neighbor << " ";
    }
    cout << endl;
    
    return 0;
}
```

# 56. Merge Intervals [Easy]

Given an array of intervals where `intervals[i] = [start_i, end_i]`, merge all overlapping intervals and return an array of the non-overlapping intervals that cover all the intervals in the input.

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


# 253. Meeting Rooms II [Easy]


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


# 210. Course Schedule II - BFS [Easy]

## Problem Description
There are a total of `numCourses` courses labeled from `0` to `numCourses - 1`. You are given an array `prerequisites` where `prerequisites[i] = [a_i, b_i]` indicates that you must take course `b_i` first before taking course `a_i`. Return the ordering of courses you should take to finish all courses. If there are multiple valid orderings, return any one. If it is impossible to finish all courses, return an empty array.

### Example
```
Input: numCourses = 2, prerequisites = [[1,0]]
Output: [0,1]
Explanation: Take course 0 first, then course 1.

Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
Output: [0,2,1,3]
Explanation: One valid order is to take course 0, then 2, then 1, then 3.

Input: numCourses = 1, prerequisites = []
Output: [0]
Explanation: No prerequisites, so take course 0.

Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: []
Explanation: A cycle exists, so it’s impossible to take all courses.
```

### Constraints
- `1 <= numCourses <= 2000`
- `0 <= prerequisites.length <= numCourses * (numCourses - 1)`
- `prerequisites[i].length == 2`
- `0 <= a_i, b_i < numCourses`
- All pairs `[a_i, b_i]` are distinct.

## Solution Approach
The problem can be solved using a topological sort with depth-first search (DFS) to detect cycles and determine a valid course order. The prerequisites form a directed graph where an edge from `b_i` to `a_i` means `b_i` must be taken before `a_i`.

### Topological Sort with DFS Approach
1. Build an adjacency list representation of the graph from the prerequisites.
2. Use DFS to perform a topological sort:
   - For each unvisited course, explore its prerequisites recursively.
   - Track visited nodes and nodes in the current recursion stack to detect cycles.
   - If a cycle is detected (a node is revisited in the current stack), return an empty array.
   - After exploring all prerequisites of a course, add it to the result.
3. Reverse the result to get the correct order (since DFS adds nodes post-exploration).
4. Return the result if all courses are included; otherwise, return an empty array.

### Example Implementation (C++)
```cpp
class Solution {
public:    
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        //Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
        //build adj list
        vector<int> courses(numCourses,0);
        vector<int> courseList;
        queue<int> q;

        if(prerequisites.size() == 0) {
            for(int i = 0; i < numCourses; i++)
                courseList.push_back(i);
            
            return courseList;
        }

        vector<vector<int>> adj_list(numCourses, vector<int>());
        for(auto v : prerequisites) {
            cout << v[1]<<" "<<v[0]<<endl;
            adj_list[v[1]].push_back(v[0]);   
            ++courses[v[0]];
        }
        
        for(int i = 0; i < numCourses; i++) {
            if(courses[i] == 0)
                q.push(i);
        }
        
        while(!q.empty())
        {
            int node = q.front();
            q.pop();
            courseList.push_back(node);
            
            auto depends = adj_list[node];
            for(auto course : depends) {
                --courses[course]; //decrement the dependency
                if(courses[course] == 0)
                    q.push(course);
            }
        }
        
        return courseList.size() == numCourses ? courseList : vector<int>(); //cyclical
    }
};
```

```cpp
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        // Build adjacency list
        vector<vector<int>> graph(numCourses);
        for (const auto& prereq : prerequisites) {
            graph[prereq[1]].push_back(prereq[0]);
        }
        
        vector<int> result;
        vector<bool> visited(numCourses, false);
        vector<bool> recStack(numCourses, false);
        
        // Perform DFS for each unvisited course
        for (int i = 0; i < numCourses; i++) {
            if (!visited[i]) {
                if (!dfs(i, graph, visited, recStack, result)) {
                    return {}; // Cycle detected
                }
            }
        }
        
        // Reverse the result to get correct order
        reverse(result.begin(), result.end());
        return result;
    }
    
private:
    bool dfs(int course, vector<vector<int>>& graph, vector<bool>& visited, 
             vector<bool>& recStack, vector<int>& result) {
        visited[course] = true;
        recStack[course] = true;
        
        // Explore all prerequisites
        for (int nextCourse : graph[course]) {
            if (!visited[nextCourse]) {
                if (!dfs(nextCourse, graph, visited, recStack, result)) {
                    return false; // Cycle detected
                }
            } else if (recStack[nextCourse]) {
                return false; // Cycle detected
            }
        }
        
        recStack[course] = false;
        result.push_back(course);
        return true;
    }
};
```

### How It Works
- **Graph Construction**:
  - Create an adjacency list where `graph[b_i]` includes `a_i` for each prerequisite `[a_i, b_i]`.
- **DFS**:
  - For each course, mark it as visited and add it to the recursion stack.
  - Recursively explore its prerequisites.
  - If a prerequisite is in the recursion stack, a cycle exists, so return an empty array.
  - After exploring all prerequisites, add the course to the result.
- **Cycle Detection**:
  - The `recStack` tracks nodes in the current DFS path. A node revisited in `recStack` indicates a cycle.
- **Result**:
  - Reverse the result to get a valid topological order (courses with no prerequisites come first).
  - If a cycle exists, return an empty array.
- **Edge Cases**:
  - No prerequisites: Return `[0, 1, ..., numCourses-1]`.
  - Single course: Return `[0]`.
  - Disconnected components: DFS from each unvisited course ensures all are processed.
- **Result**: Returns a valid course order or an empty array if impossible.

### Time and Space Complexity
- **Time Complexity**: O(V + E), where `V` is `numCourses` and `E` is the number of prerequisites. Building the graph is O(E), and DFS visits each node and edge once.
- **Space Complexity**: O(V + E) for the adjacency list, plus O(V) for the visited and recursion stack arrays, and O(V) for the output.

### Alternative Approach
1. **Kahn’s Algorithm (BFS)**:
   - Build the graph and compute in-degrees for each course.
   - Start with courses having no prerequisites (in-degree 0) and use a queue to process them.
   - Reduce in-degrees of dependent courses and add them to the queue when their in-degree becomes 0.
   - If all courses are processed, return the order; otherwise, a cycle exists.
   - Time Complexity: O(V + E)
   - Space Complexity: O(V + E)
The DFS approach is chosen for its clarity in cycle detection and straightforward implementation, but Kahn’s algorithm is equally valid and may be preferred for iterative solutions.


# 1971. Find if Path Exists in Graph - Breadth-First Search [Easy]

You are given an undirected graph with `n` nodes labeled from `0` to `n-1` and a list of undirected edges (each edge is a pair of nodes). Write a function to check whether there is a valid path from node `source` to node `destination` in the graph. A valid path is a sequence of nodes where each consecutive pair is connected by an edge.

```
Input: n = 3, edges = [[0,1],[1,2],[2,0]], source = 0, destination = 2
Output: true
Explanation: There is a path 0 -> 1 -> 2 or 0 -> 2.
```
<img src="../assets/validpath-ex1.png" width="20%">

```
Input: n = 6, edges = [[0,1],[0,2],[3,5],[5,4],[4,3]], source = 0, destination = 5
Output: false
Explanation: No path exists from 0 to 5 as the graph is disconnected.
```
<img src="../assets/validpath-ex2.png" width="20%">


### Constraints
- `1 <= n <= 2 * 10^5`
- `0 <= edges.length <= 2 * 10^5`
- `edges[i].length == 2`
- `0 <= u_i, v_i <= n - 1`
- `u_i != v_i`
- `0 <= source, destination <= n - 1`
- There are no parallel edges or self-loops.

## Solution Approach
The problem can be solved using a depth-first search (DFS) to explore all possible paths from the `source` to the `destination` in the undirected graph.

### DFS Approach
1. Build an adjacency list representation of the undirected graph from the edges.
2. Use DFS to explore paths starting from the `source` node:
   - Mark visited nodes to avoid cycles.
   - Recursively visit all unvisited neighbors of the current node.
   - Return `true` if the `destination` node is reached.
3. Return `false` if no path is found after exploring all possibilities.

### Example Implementation (C++)
```cpp
class Solution {
public:
        
    bool dfs(vector<vector<int>>& adjacency_list, vector<bool>& visited, int current, int end) {
        if(current == end)
            return true;
        
        if(visited[current])
            return false;
        
        visited[current] = 1;
        
        for(auto neighbor : adjacency_list[current])
            if(dfs(adjacency_list, visited, neighbor, end))
                return true;
                
        return false;
    }
    
    bool validPath(int n, vector<vector<int>>& edges, int start, int end) {
        vector<vector<int>> adjacency_list(n);
        
        //build an adjacency list of each vertex
        for (vector<int> edge : edges) {
            adjacency_list[edge[0]].push_back(edge[1]);
            adjacency_list[edge[1]].push_back(edge[0]);
        }
        
        vector<bool> seen(n); //tells if a vertex is visited or not
        
        //Below is DFS using recusrion
        //return dfs(adjacency_list, seen, start, end);
        
        //BFS method using queue
        queue<int> q;
        q.push(start);
        while(!q.empty())
        {
            int node = q.front();
            q.pop();
            
            if(node == end)
                return true;
            
            if(seen[node]) //dont add its kids
                continue;
            
            seen[node] = true;
            
            for(auto neighbor : adjacency_list[node])
                q.push(neighbor);
        }
        
        return false;
        
        /*
        //DFS method using stack
        stack<int> st;
        st.push(start);
        
        while (!st.empty()) {
            // Get the current node.
            int node = st.top();
            st.pop();
            
            // Check if we have reached the target node.
            if (node == end) {
                return true;
            }
            
            // Check if we've already visited this node.
            if (seen[node]) {
                continue;
            }
            seen[node] = true;
            
            // Add all neighbors to the stack.
            for (int neighbor : adjacency_list[node]) {
                st.push(neighbor);
            }
        }
        
        return false;
        */
    }
};
```

```cpp
class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        // Build adjacency list
        vector<vector<int>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]); // Undirected graph
        }
        
        // Initialize visited array
        vector<bool> visited(n, false);
        
        // Perform DFS
        return dfs(source, destination, graph, visited);
    }
    
private:
    bool dfs(int current, int destination, vector<vector<int>>& graph, vector<bool>& visited) {
        // If destination is reached
        if (current == destination) {
            return true;
        }
        
        // Mark current node as visited
        visited[current] = true;
        
        // Explore all neighbors
        for (int neighbor : graph[current]) {
            if (!visited[neighbor]) {
                if (dfs(neighbor, destination, graph, visited)) {
                    return true;
                }
            }
        }
        
        return false;
    }
};
```

### How It Works
- **Graph Construction**:
  - Create an adjacency list where `graph[u]` includes `v` and `graph[v]` includes `u` for each edge `[u, v]`.
- **DFS**:
  - Start from the `source` node and mark it as visited.
  - Recursively explore each unvisited neighbor.
  - Return `true` if the `destination` is reached.
  - Return `false` if all paths from the current node are exhausted without reaching the destination.
- **Visited Array**:
  - Prevents revisiting nodes, avoiding infinite loops in cycles.
- **Edge Cases**:
  - `n = 1`: If `source == destination`, return `true` (no edges needed).
  - No edges: Only returns `true` if `source == destination`.
  - Disconnected graph: Returns `false` if no path exists.
- **Result**: Returns `true` if a path exists from `source` to `destination`, `false` otherwise.

### Time and Space Complexity
- **Time Complexity**: O(V + E), where `V` is the number of nodes (`n`) and `E` is the number of edges. Building the graph takes O(E), and DFS visits each node and edge at most once.
- **Space Complexity**: O(V + E) for the adjacency list, plus O(V) for the visited array and recursion stack, totaling O(V + E).

### Alternative Approach
1. **BFS (Breadth-First Search)**:
   - Use a queue to explore nodes level by level starting from `source`.
   - Mark visited nodes and enqueue unvisited neighbors.
   - Return `true` if `destination` is reached, `false` if the queue empties.
   - Time Complexity: O(V + E)
   - Space Complexity: O(V + E)
The DFS approach is chosen for its simplicity and recursive elegance, but BFS is equally valid and may be preferred for finding the shortest path in an unweighted graph.


# 797. All Paths From Source to Target - Breadth-First Search [Easy]

This document describes the solution to the "All Paths From Source to Target" problem (LeetCode #797).

## Problem Description
Given a directed acyclic graph (DAG) of `n` nodes labeled from `0` to `n-1`, find all possible paths from node `0` to node `n-1` and return them in any order. The graph is given as an adjacency list `graph`, where `graph[i]` is a list of nodes that node `i` has directed edges to.

### Example
```
Input: graph = [[1,2],[3],[3],[]]
Output: [[0,1,3],[0,2,3]]
Explanation: The graph has 4 nodes. Paths from node 0 to node 3 are:
- 0 -> 1 -> 3
- 0 -> 2 -> 3
```
<img src="../assets/all_1.jpg" width="20%">

```
Input: graph = [[4,3,1],[3,2,4],[3],[4],[]]
Output: [[0,4],[0,3,4],[0,1,3,4],[0,1,2,3,4],[0,1,4]]
Explanation: All paths from node 0 to node 4 are listed.

Input: graph = [[1],[]]
Output: [[0,1]]
Explanation: Only one path from node 0 to node 1.
```
<img src="../assets/all_2.jpg" width="20%">

### Constraints
- `n == graph.length`
- `2 <= n <= 15`
- `0 <= graph[i][j] < n`
- `graph[i][j] != i` (no self-loops)
- All elements in `graph[i]` are unique.
- The graph is a directed acyclic graph (DAG).

## Solution Approach
The problem can be solved using a breadth-first search (BFS) to explore all possible paths from the source node (0) to the target node (n-1) in the DAG, tracking the path for each node explored.

### BFS with Path Tracking Approach
1. Use a queue to perform BFS, where each element is a pair of the current node and the path taken to reach it.
2. Initialize the queue with node 0 and its path `[0]`.
3. While the queue is not empty:
   - Dequeue the current node and its path.
   - If the current node is the target (n-1), add the path to the result.
   - For each neighbor of the current node, create a new path by appending the neighbor and enqueue it.
4. Return the list of all valid paths.

### Example Implementation (C++)
```cpp
class Solution {
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) { //BFS SOlutuion
        vector<vector<int>> result;
        int n = graph.size();
        queue<pair<int, vector<int>>> q;
        
        // Start with node 0 and its path
        q.push({0, {0}});
        
        while (!q.empty()) {
            auto [current, path] = q.front(); 
            q.pop(); //DISCARD
            
            // If target node is reached, add path to result
            if (current == n - 1) {
                result.push_back(path);
                continue;
            }
            
            // Explore all neighbors
            for (int next : graph[current]) {
                vector<int> newPath = path; //<--- USE THE PATH SO FAR TO CONTINUE
                newPath.push_back(next);
                q.push({next, newPath});
            }
        }
        
        return result;
    }
};

class Solution {
public:
    // DFS
    void dfs(vector<vector<int>>& graph, int node, vector<int>& path,
             vector<vector<int>>& paths) {
        
        path.push_back(node);
        if (node == graph.size() - 1) {
            paths.push_back(path);
            return;
        }
        vector<int> nextNodes = graph[node];
        for (int nextNode : nextNodes) {
            dfs(graph, nextNode, path, paths);
            path.pop_back();
        }
    }

    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        //the graph is basically an adj list where each index points to the direction to nodes
        //graph = [[1,2],[3],[3],[]]
        //-----------0,   1,  2,  3  <-- from 3 no direction is going out
        //since this is a directed graph we dont need visited or seen tracking as same node wont be
        //visited again
        
        vector<vector<int>> paths;
        if (graph.size() == 0) {
            return paths;
        }
        vector<int> path;
        dfs(graph, 0, path, paths);
        return paths;
    }
};

//DFS with backtracking
class Solution {
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        vector<vector<int>> result;
        vector<int> path = {0}; // Start with node 0
        dfs(0, graph.size() - 1, graph, path, result);
        return result;
    }
    
private:
    void dfs(int current, int target, vector<vector<int>>& graph, 
             vector<int>& path, vector<vector<int>>& result) {
        // If target node is reached, add path to result
        if (current == target) {
            result.push_back(path);
            return;
        }
        
        // Explore all neighbors
        for (int next : graph[current]) {
            path.push_back(next);
            dfs(next, target, graph, path, result);
            path.pop_back(); // Backtrack
        }
    }
};
```

### How It Works
- **BFS**:
  - Use a queue to explore nodes level by level, storing the current node and the path to it.
  - Start with node 0 and path `[0]`.
- **Path Tracking**:
  - For each node dequeued, check if it’s the target (n-1). If so, add the path to the result.
  - For each neighbor, create a new path by copying the current path and appending the neighbor.
- **Queue Processing**:
  - Enqueue each neighbor with its updated path.
  - Continue until the queue is empty, ensuring all paths are explored.
- **Edge Cases**:
  - Single path: Correctly captures paths like `[0,1]` for `[[1],[]]`.
  - Multiple paths: All valid paths are collected.
  - Small graph (`n=2`): Handles cases like `[[1],[]]`.
- **Result**: Returns a vector of all paths from node 0 to node `n-1`.

### Time and Space Complexity
- **Time Complexity**: O(2^n * n), where `n` is the number of nodes. The number of paths can be up to 2^(n-1) in a complete DAG, and copying each path takes O(n). Given `n <= 15`, this is feasible.
- **Space Complexity**: O(2^n * n) for the queue and output, as the queue may store multiple paths, each of length up to `n`. The output space is also O(2^n * n).

### Alternative Approach
1. **DFS with Backtracking**:
   - Recursively explore paths from node 0, maintaining a current path and backtracking after exploring each neighbor.
   - Time Complexity: O(2^n * n)
   - Space Complexity: O(n) for the recursion stack and current path, excluding output.
The BFS approach is provided here as an alternative to the previously shared DFS solution, offering a different perspective. BFS may be less memory-efficient due to storing multiple paths in the queue but is intuitive for level-by-level exploration.


# 133. Clone Graph Solution [Easy]
https://leetcode.com/problems/clone-graph/

Given a reference of a node in a connected undirected graph, return a deep copy (clone) of the graph. Each node in the graph contains a value (`int`) and a list of its neighbors. The graph is represented using an adjacency list, and you must ensure the cloned graph has the same structure and values but uses new nodes.

```
Example 1
Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
Output: [[2,4],[1,3],[2,4],[1,3]]
Explanation: The graph has 4 nodes. Node 1's neighbors are nodes 2 and 4, node 2's neighbors are nodes 1 and 3, etc. The output is a deep copy of this graph.
```
<img src="../assets/133_clone_graph_question.png" width="20%">

```
Example 2
Input: adjList = [[]]
Output: [[]]
Explanation: Note that the input contains one empty list. The graph consists of only one node with val = 1 and it does not have any neighbors.

Example 3
Input: adjList = []
Output: []
Explanation: This an empty graph, it does not have any nodes.
```

## Solution
```cpp
//using BFS
class Solution {
public:
    Node* cloneGraph(Node* node) {
        if(!node)
            return node;

        map<Node*, Node*> v;

        queue<Node*> q;
        q.push(node);

        v[node] = new Node(node->val);
        //start BFS traversal
        while(!q.empty())
        {
            Node *n = q.front();
            for(auto x: n->neighbors)
            {
                if(v.count(x) == 0)
                {
                    Node * nx = new Node(x->val);
                    v[x] = nx;
                    q.push(x);
                }

                v[n]->neighbors.push_back(v[x]);
            }
            q.pop();
        }

        return v[node];
    }
};
```

Below is the C++ solution to clone a graph using a depth-first search (DFS) approach.

```cpp
//DFS
class Solution {
public:
    unordered_map<Node*, Node*> v;

    Node* cloneGraph(Node* node) {
        if(!node)
            return node;

        queue<Node*> q;
        if(v.count(node) == 0)
            v[node] = new Node(node->val);

        for(auto x: node->neighbors)
        {
            if(v.count(x) == 0) //not visited yet
                cloneGraph(x);

            v[node]->neighbors.push_back(v[x]);
        }

        return v[node];
    }
};
```

## Time and Space Complexity
- **Time Complexity**: O(V + E), where `V` is the number of vertices (nodes) and `E` is the number of edges (neighbor connections). Each node and edge is processed once.
- **Space Complexity**: O(V), for the `visited` map and the recursion stack, where `V` is the number of nodes.

## Edge Cases
- Empty graph (`node = nullptr`): Return `nullptr`.
- Single node with no neighbors: Return a new node with the same value and empty neighbor list.
- Cyclic graph: The `visited` map ensures cycles are handled correctly.
- Disconnected graph: The problem guarantees a connected graph, so no need to handle disconnected cases.
- Large graph: The solution efficiently handles graphs within the constraint of up to 100 nodes.


# 269. Alien Dictionary [Medium, Revisit]

There is a new alien language that uses the English alphabet. However, the order of the letters is unknown to you.

You are given a list of strings words from the alien language's dictionary. Now it is claimed that the strings in words are sorted lexicographically by the rules of this new language.

If this claim is incorrect, and the given arrangement of string in words cannot correspond to any order of letters, return "".

Otherwise, return a string of the unique letters in the new alien language sorted in lexicographically increasing order by the new language's rules. If there are multiple solutions, return any of them.

```
Example 1:

Input: words = ["wrt","wrf","er","ett","rftt"]
Output: "wertf"
Example 2:

Input: words = ["z","x"]
Output: "zx"
Example 3:

Input: words = ["z","x","z"]
Output: ""
Explanation: The order is invalid, so return "".
```

A few things to keep in mind:

- The letters within a word don't tell us anything about the relative order. For example, the presence of the word kitten in the list does not tell us that the letter k is before the letter i.
- The input can contain words followed by their prefix, for example, abcd and then ab. These cases will never result in a valid alphabet (because in a valid alphabet, prefixes are always first). You'll need to make sure your solution detects these cases correctly.
- There can be more than one valid alphabet ordering. It is fine for your algorithm to return any one of them.
- Your output string must contain all unique letters that were within the input list, including those that could be in any position within the ordering. It should not contain any additional letters that were not in the input.

```cpp
class Solution {
public:
    string alienOrder(vector<string>& words) {
        map<char, vector<char>> adjList;
        map<char, int> counts;

        for(auto s: words)
        {
            for(auto c: s)
            {
                if(counts.count(c) == 0) {
                    counts[c] = 0;
                    adjList[c] = vector<char>();
                }
            }
        }

        cout<< "test 1"<<endl;
        //find edges
        for(int i=0; i < words.size() - 1; i++) {
            string w1 = words[i];
            string w2 = words[i+1];

            int n1 = w1.size();
            int n2 = w2.size();
            //check if word 2 is not a prefix of word 1
            //prefixes should always be first
            if(n1 > n2 && w1.substr(0, n2) == w2)
                return ""; //bail out

            for(int j=0; j < min(n1, n2); j++)
                if (w1[j] != w2[j]) {
                    adjList[w1[j]].push_back(w2[j]);
                    counts[w2[j]]++;
                    break;
                }
        }

        //print adjList
        for(auto [k, v]: adjList) {
            cout<<k<<": ";
            for(auto c: v)
                cout<<c<<", ";
            cout<<endl;
        }

        for (auto [k, v] : counts) {
            cout<<k<<": "<<v<<endl;
            /*
            e: 1
            f: 1
            r: 1
            t: 1
            w: 0
            */
        }
        //["wrt","wrf","er","ett","rftt"]
        /* Above prints:
        e: r, 
        f: 
        r: t, 
        t: f, 
        w: e, 
        */

        string ans = "";
        queue<char> q;

        for (auto [k, v] : counts)
            if(v == 0)
                q.push(k);

        while(!q.empty())
        {
            char c = q.front();
            q.pop();

            ans += c;
            for(char next : adjList[c])
            {
                counts[next]--;
                if(counts[next] == 0)
                    q.push(next);
            }
        }
        
        if(ans.size() < counts.size())
            return "";
  
        return ans;
    }
};
```

# 317. Shortest Distance from All Buildings

You are given an m x n grid grid of values 0, 1, or 2, where:

- each 0 marks an empty land that you can pass by freely,
- each 1 marks a building that you cannot pass through, and
- each 2 marks an obstacle that you cannot pass through.
You want to build a house on an empty land that reaches all buildings in the shortest total travel distance. You can only move up, down, left, and right.

Return the shortest travel distance for such a house. If it is not possible to build such a house according to the above rules, return -1.

The total travel distance is the sum of the distances between the houses of the friends and the meeting point.
```
1-0-2-0-1
0-0-0-0-0
0-0-1-0-0

Input: grid = [[1,0,2,0,1],[0,0,0,0,0],[0,0,1,0,0]]
Output: 7
Explanation: Given three buildings at (0,0), (0,4), (2,2), and an obstacle at (0,2).
The point (1,2) is an ideal empty land to build a house, as the total travel distance of 3+3+1=7 is minimal.
So return 7.
```

### Approach 1: BFS from Empty Land to All Houses [Medium, Revisit]

Our goal is to find the empty land cell with the shortest total distance to all houses, so we must first find the shortest total distance to all houses from each empty land cell.
As previously mentioned, this can be accomplished using BFS. For each empty cell (cell value equals 0) in the grid, start a BFS and sum all the distances to houses (cell value equals 1) from this cell. We will also keep track of the number of houses we have reached from this source cell (empty cell).
If we cannot reach all the houses from the current empty cell, then it is not a valid empty cell. Furthermore, we can be certain that any cell visited during this BFS also cannot reach all of the houses. So we will mark all cells visited during this BFS as obstacles to ensure that we do not start another BFS from this region.

### Algorithm

- For each empty cell (grid[i][j] equals 0), start a BFS:
   - In the BFS, traverse all 4-directionally adjacent cells that are not blocked or visited and keep track of the distance from the start cell. Each iteration adds 1 to the distance.
   - Every time we reach a house, increment houses reached counter housesReached by 1, and increase the total distance distanceSum by the current distance (i.e., the distance from the start cell to the house).
   - If housesReached equals totalHouses, then return the total distance.
   - Otherwise, the starting cell (and every cell visited during this BFS) cannot reach all of the houses. So set every visited empty land cell equal to 2 so that we do not start a new BFS from that cell and return INT_MAX.
- Each time a total distance is returned from a BFS call, update the minimum distance (minDistance).
- If it is possible to reach all houses from any empty land cell, then return the minimum distance found. Otherwise, return -1.

```cpp
class Solution {
private:
    int bfs(vector<vector<int>>& grid, int row, int col, int totalHouses) {
        // Next four directions.
        int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        
        int rows = grid.size();
        int cols = grid[0].size();
        int distanceSum = 0;
        int housesReached = 0;

        // Queue to do a bfs, starting from (r,c) cell
        queue<pair<int, int>> q;
        q.push({ row, col });

        // Keep track of visited cells
        vector<vector<bool>> vis(rows, vector<bool> (cols, false));
        vis[row][col] = true;

        int steps = 0;

        while (!q.empty() && housesReached != totalHouses) {
            for (int i = q.size(); i > 0; --i) {
                auto curr = q.front();
                q.pop();

                row = curr.first;
                col = curr.second;

                // If this cell is a house, then add the distance from the source to this cell
                // and we go past from this cell.
                if (grid[row][col] == 1) {
                    distanceSum += steps;
                    housesReached++;
                    continue;
                }

                // This cell was an empty cell, hence traverse the next cells which is not a blockage.
                for (auto& dir : dirs) {
                    int nextRow = row + dir[0];
                    int nextCol = col + dir[1];

                    if (nextRow >= 0 && nextCol >= 0 && nextRow < rows && nextCol < cols) {
                        if (!vis[nextRow][nextCol] && grid[nextRow][nextCol] != 2) {
                            vis[nextRow][nextCol] = true;
                            q.push({nextRow, nextCol});
                        }
                    }
                }
            }
            
            // After traversing one level cells, increment the steps by 1 to reach to next level.
            steps++;
        }

        // If we did not reach all houses, then any cell visited also cannot reach all houses.
        // Set all cells visted to 2 so we do not check them again and return INT_MAX.
        if (housesReached != totalHouses) {
            for (row = 0; row < rows; row++) {
                for (col = 0; col < cols; col++) {
                    if (grid[row][col] == 0 && vis[row][col]) {
                        grid[row][col] = 2;
                    }
                }
            }
            return INT_MAX;
        }
        // If we have reached all houses then return the total distance calculated.
        return distanceSum;
    }

public:
    int shortestDistance(vector<vector<int>>& grid) {
        int minDistance = INT_MAX;
        int rows = grid.size();
        int cols = grid[0].size();
        int totalHouses = 0;

        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (grid[row][col] == 1) { 
                    totalHouses++;
                }
            }
        }

        // Find the min distance sum for each empty cell.
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (grid[row][col] == 0) {
                    minDistance = min(minDistance, bfs(grid, row, col, totalHouses));
                }
            }
        }

        // If it is impossible to reach all houses from any empty cell, then return -1.
        if (minDistance == INT_MAX) {
            return -1;
        }
        return minDistance;
    }
};
```

### Another approach:

The intuition behind the code is to find the point which is closest to all the buildings. The idea is to first find the total number of buildings in the grid and then, for each empty cell, calculate the distance to all the buildings. We keep a running total of these distances in a 2D array dist. After calculating the distance to all the buildings for each empty cell, we find the cell with the minimum sum of distances and return that distance as the result.


Let's understand why we need bfs to this problem, why we are not using manhattan distance to solve this problem?


Answer - Suppose in this grid, obstacle wouldn't have given, then in this case for each empty land i.e. grid[i][j] = 0, we traverse all houses i.e. grid[i][j] = 1, and add the Manhattan Distance:
distance = |x1 - x2| + |y1 - y2|, where (x1, y1) are the coordinates of empty land and (x2, y2) are the coordinates of a house.We keep a running total of these manhattan distances in a 2D array. After calculating the manhattan distance to all the buildings for each empty cell, we find the cell with the minimum sum of distances and return that distance as the result. But due to obstacle present in the grid we will get wrong distance using manhattan formula. See below image how it is wrong.


To calculate the distances, we use Breadth-First Search (BFS) starting from each building. This allows us to traverse the grid in all four directions (left, right, up, down) to reach every empty cell. The distance to each empty cell is stored in the dist array and updated as we traverse the grid.


Finally, we return the minimum sum of distances as the result. If there is no empty cell with a minimum sum of distances, we return -1, indicating that it is not possible to build a house that reaches all the buildings.

#### Algo used:
- Initialize two 2D arrays, sum and reach, of the same size as the grid. sum[i][j] stores the sum of distances from the cell (i, j) to all the buildings, and reach[i][j] stores the number of buildings that are reachable from the cell (i, j).
- Traverse the grid and for every building, perform a BFS from the building to find all the empty cells that are reachable from the building. For each reachable cell, update sum[i][j] and reach[i][j].
- After the BFS, traverse dist and reach arrays and find the cell (i, j) such that reach[i][j] is equal to the number of buildings and sum[i][j] is minimum. If such a cell does not exist, return -1.
- Return the value stored in sum[i][j].

#### Time Complexity and Space Complexity:
Time complexity: O(m * n * (m * n)), where m is the number of rows in the grid and n is the number of columns in the grid. This is because for each building, we need to perform a BFS, which takes O(m * n) time, and we need to perform BFS for all the buildings and in worst case there are m*n buildings. Hence, the total time complexity would be O(m * n * (m * n)).

Space complexity: O(m * n), as we need to store the dist and reach arrays, which are of size m * n.

```cpp
class Solution {

public:
    int shortestDistance(vector<vector<int>>& grid) {
        int m = grid.size(); //rows
        int n = grid[0].size(); //cols

        //sum[i][j] stores the sum of distances from the cell (i, j) to all the buildings
        vector<vector<int>> sum(m, vector<int>(n, 0));
        //reach[i][j] stores the number of buildings that are reachable from the cell (i, j).
        vector<vector<int>> reach(m, vector<int>(n, 0));
        //find the total number of buildings in the grid
        int building_count = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    building_count++;
                    queue<pair<int, int>> q;
                    q.push({i, j});
                    vector<vector<bool>> visited(m, vector<bool>(n, false));
                    visited[i][j] = true;
                    //totalDistance is help us to find total distance between the house(cell (i, j)) and all the buildings
                    int totalDistance = 0;
                    vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
                    
                    while (!q.empty()) {
                        int size = q.size();
                        totalDistance++;
                        while (size--) {
                            auto [x, y] = q.front();
                            q.pop();
                            for (auto [dx, dy] : dirs) {
                                int i = x + dx;
                                int j = y + dy;
                                if (i >= 0 && i < m && j >= 0 && j < n && grid[i][j] == 0 && !visited[i][j]) {
                                    q.push({i, j});
                                    visited[i][j] = true;
                                    sum[i][j] += totalDistance;
                                    reach[i][j]++;
                                }
                            }
                        }
                    }
                }
            }
        }
        
        int res = INT_MAX;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0 && reach[i][j] == building_count) {
                    res = min(res, sum[i][j]);
                }
            }
        }
        
        return res == INT_MAX ? -1 : res;
    }
};
```

# 721. Accounts Merge
https://leetcode.com/problems/accounts-merge/description/

### Algorithm - Disjoint Set Union (DSU)

- Traverse over each account, and for each account, traverse over all of its emails. If we see an email for the first time, then set the group of the email as the index of the current account in emailGroup .
- Otherwise, if the email has already been seen in another account, then we will union the current group (i) and the group the current email belongs to (emailGroup[email]).
- After traversing over every account and merging the accounts that share a common email, we will now traverse over every email once more. Each email will be added to a map (components) where the key is the email's representative, and the value is a list of emails with that representative.
- Traverse over components, here the keys are the group indices and the value is the list of emails belonging to this group (person). Since the emails must be "in sorted order" we will sort the list of emails for each group. Lastly, we can get the account name using the accountList[group][0]. In accordance with the instructions, we will insert this name at the beginning of the email list.
- Store the list created in step 4 in our final result (mergedAccount).

```cpp
class DSU {
public:
    vector<int> representative;
    vector<int> size;
    
    DSU(int sz) : representative(sz), size(sz) {
        for (int i = 0; i < sz; ++i) {
            // Initially each group is its own representative
            representative[i] = i;
            // Intialize the size of all groups to 1
            size[i] = 1;
        }
    }
    
    // Finds the representative of group x
    int findRepresentative(int x) {
        if (x == representative[x]) {
            return x;
        }
        
        // This is path compression
        return representative[x] = findRepresentative(representative[x]);
    }
    
    // Unite the group that contains "a" with the group that contains "b"
    void unionBySize(int a, int b) {
        int representativeA = findRepresentative(a);
        int representativeB = findRepresentative(b);
        
        // If nodes a and b already belong to the same group, do nothing.
        if (representativeA == representativeB) {
            return;
        }
        
        // Union by size: point the representative of the smaller
        // group to the representative of the larger group.
        if (size[representativeA] >= size[representativeB]) {
            size[representativeA] += size[representativeB];
            representative[representativeB] = representativeA;
        } else {
            size[representativeB] += size[representativeA];
            representative[representativeA] = representativeB;
        }
    }
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accountList) {
        int accountListSize = accountList.size();
        DSU dsu(accountListSize);
        
        // Maps email to their component index
        unordered_map<string, int> emailGroup;
        
        for (int i = 0; i < accountListSize; i++) {
            int accountSize = accountList[i].size();

            for (int j = 1; j < accountSize; j++) {
                string email = accountList[i][j];
                string accountName = accountList[i][0];
                
                // If this is the first time seeing this email then
                // assign component group as the account index
                if (emailGroup.find(email) == emailGroup.end()) {
                    emailGroup[email] = i;
                } else {
                    // If we have seen this email before then union this
                    // group with the previous group of the email
                    dsu.unionBySize(i, emailGroup[email]);
                }
            }
        }
    
        // Store emails corresponding to the component's representative
        unordered_map<int, vector<string>> components;
        for (auto emailIterator : emailGroup) {
            string email = emailIterator.first;
            int group = emailIterator.second;
            components[dsu.findRepresentative(group)].push_back(email);
        }

        // Sort the components and add the account name
        vector<vector<string>> mergedAccounts;
        for (auto componentIterator : components) {
            int group = componentIterator.first;
            vector<string> component = {accountList[group][0]};
            component.insert(component.end(), componentIterator.second.begin(), 
                             componentIterator.second.end());
            sort(component.begin() + 1, component.end());
            mergedAccounts.push_back(component);
        }
        
        return mergedAccounts;
    }
};
```

# 785. Is Graph Bipartite? [Medium, revisit]

There is an undirected graph with n nodes, where each node is numbered between 0 and n - 1. You are given a 2D array graph, where graph[u] is an array of nodes that node u is adjacent to. More formally, for each v in graph[u], there is an undirected edge between node u and node v. The graph has the following properties:

```
There are no self-edges (graph[u] does not contain u).
There are no parallel edges (graph[u] does not contain duplicate values).
If v is in graph[u], then u is in graph[v] (the graph is undirected).
The graph may not be connected, meaning there may be two nodes u and v such that there is no path between them.
A graph is bipartite if the nodes can be partitioned into two independent sets A and B such that every edge in the graph connects a node in set A and a node in set B.
```

Return true if and only if it is bipartite.
```cpp
class Solution {
public:
    bool isBipartite(vector<vector<int>>& gr) {
        int n = gr.size();
        vector<int> colour(n, 0);

        for(int node = 0; node < n; node++){
            if(colour[node] != 0) 
                continue; //already processed

            queue<int> q;
            q.push(node);
            colour[node] = 1;

            while(!q.empty()){
                int cur = q.front();
                q.pop();

                for(int ne : gr[cur]){
                    if(colour[ne] == 0){
                        colour[ne] = -colour[cur];
                        q.push(ne);
                    }else if(colour[ne] != -colour[cur]){
                        return false;
                    }
                }
            }
        }

        return true;
    }
};
```
