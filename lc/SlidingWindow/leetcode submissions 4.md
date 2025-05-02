# 443. String Compression - Two Pointers

This document describes the solution to the "String Compression" problem (LeetCode #443).

## Problem Description
Given an array of characters `chars`, compress it using the following algorithm:
- For each group of consecutive repeating characters:
  - If the group's length is 1, append the character to the result.
  - Otherwise, append the character followed by the group's length.
- The compressed string is stored in the input `chars` array, and the new length of the array is returned.
- The solution must be in-place, and only the first `new length` elements of `chars` are considered after compression.

### Example
```
Input: chars = ["a","a","b","b","c","c","c"]
Output: 6, chars = ["a","2","b","2","c","3"]
Explanation: "aa" is compressed to "a2", "bb" to "b2", and "ccc" to "c3". The new length is 6.

Input: chars = ["a"]
Output: 1, chars = ["a"]
Explanation: Single character remains unchanged.

Input: chars = ["a","b","b","b","b","b","b","b","b","b","b","b","b"]
Output: 4, chars = ["a","b","1","2"]
Explanation: "a" remains "a", "bbbbbbbbbbbb" is compressed to "b12". The new length is 4.
```

### Constraints
- `1 <= chars.length <= 2000`
- `chars[i]` is a lowercase English letter, uppercase English letter, digit, or symbol.

## Solution Approach
The problem can be solved by iterating through the array, counting consecutive repeating characters, and writing the compressed result in-place.

### Two-Pointer Approach
1. Use a pointer `write` to track the position where the next character or count should be written.
2. Iterate through the array with a pointer `read`:
   - Count consecutive occurrences of the same character.
   - Write the character at the `write` position.
   - If the count is greater than 1, convert the count to a string and write its digits.
3. Return the final `write` position as the new length.

### Example Implementation (C++)
```cpp
class Solution {
public:
    int compress(vector<char>& chars) {
        queue<char> q;
        
        if(chars.size() <= 1)
            return chars.size();
        
        for(int i = 0; i < chars.size(); i++)
        {
            int count = 1;
            
            q.push(chars[i]);
            while(i+1 < chars.size() && chars[i] == chars[i+1]) {
                count++;
                i++;
            }
            
            if(count > 1)
            {
                string scount = to_string(count);
                for(auto c: scount)
                    q.push(c);
            }  
        }
        
        chars.clear();
        while(!q.empty())
        {
            chars.push_back(q.front());
            q.pop();
        }
        
        return chars.size();
    }
};
```

```cpp
class Solution {
public:
    int compress(vector<char>& chars) {
        int write = 0; // Position to write the compressed result
        int read = 0;  // Position to read the input
        
        while (read < chars.size()) {
            char currentChar = chars[read];
            int count = 0;
            
            // Count consecutive occurrences
            while (read < chars.size() && chars[read] == currentChar) {
                count++;
                read++;
            }
            
            // Write the character
            chars[write++] = currentChar;
            
            // Write the count if greater than 1
            if (count > 1) {
                string countStr = to_string(count);
                for (char c : countStr) {
                    chars[write++] = c;
                }
            }
        }
        
        return write;
    }
};
```

### How It Works
- **Pointers**:
  - `write`: Tracks where to place the next character or digit in the compressed array.
  - `read`: Scans the array to count consecutive characters.
- **Compression**:
  - For each group of identical characters, count their occurrences.
  - Write the character once.
  - If the count is greater than 1, convert the count to a string and write each digit.
- **In-Place**:
  - Overwrite the original array starting at `write`, ensuring the compressed result fits within the first `write` positions.
- **Edge Cases**:
  - Single character: Written as is, length 1.
  - All same characters: Compressed to one character plus count digits (e.g., "aaaaa" to "a5").
  - No consecutive repeats: Each character written once, length unchanged.
- **Result**: The array is modified in-place, and the new length (`write`) is returned.

### Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of `chars`, as we traverse the array once and handle counts in linear time.
- **Space Complexity**: O(1), excluding the output array modification, as we only use a constant amount of extra space (temporary string for counts is small and bounded).

### Alternative Approach
1. **Two-Pass with Extra Space**:
   - First pass: Compute the compressed string in a temporary array.
   - Second pass: Copy back to the input array.
   - Time Complexity: O(n)
   - Space Complexity: O(n)
  The in-place approach is preferred as it meets the problem’s requirement for in-place modification and minimizes space usage.


# 387. First Unique Character in a String - Hash Table, Queue


This document describes the solution to the "First Unique Character in a String" problem (LeetCode #387).

## Problem Description
Given a string `s`, find the first non-repeating character in it and return its index. If no such character exists, return `-1`.

### Example
```
Input: s = "leetcode"
Output: 0
Explanation: The first unique character is 'l' at index 0.

Input: s = "loveleetcode"
Output: 2
Explanation: The first unique character is 'v' at index 2.

Input: s = "aabb"
Output: -1
Explanation: No character appears exactly once.
```

### Constraints
- `1 <= s.length <= 10^5`
- `s` consists of only lowercase English letters.

## Solution Approach
The problem can be solved using a frequency map to count character occurrences, followed by a second pass to find the first character with a count of 1.

### Two-Pass Frequency Map Approach
1. Create a frequency map to count the occurrences of each character in the string.
2. Iterate through the string again to find the first character whose frequency is 1.
3. Return the index of that character, or `-1` if no such character exists.

### Example Implementation (C++)
```cpp
class Solution {
public:
    int firstUniqChar(string s) {
        if(s.empty())
            return -1;
        
        unordered_map<char, int> unique;
        int index = 0;
        for(auto x : s)
        {
            if(unique.find(x) != unique.end())
                unique[x] = -1;
            else
                unique[x] = index;
            
            index++;
        }
        
        index = s.size();
        for(auto it : unique)
        {
            if(it.second == -1)
                continue;
            
            index = min(index, it.second);
        }
        
        return index == s.size() ? -1 : index;
    }
};
```

```cpp
class Solution {
public:
    int firstUniqChar(string s) {
        // Frequency map for lowercase letters
        vector<int> freq(26, 0);
        
        // Count occurrences of each character
        for (char c : s) {
            freq[c - 'a']++;
        }
        
        // Find first character with frequency 1
        for (int i = 0; i < s.length(); i++) {
            if (freq[s[i] - 'a'] == 1) {
                return i;
            }
        }
        
        return -1;
    }
};
```

### How It Works
- **Frequency Map**:
  - Use a vector of size 26 (for lowercase letters) to store the count of each character.
  - Iterate through the string and increment the count for each character (`c - 'a'` maps 'a' to  créditos: 0, 'b' to 1, etc.).
- **Second Pass**:
  - Iterate through the string and check the frequency of each character.
  - Return the index of the first character with a frequency of 1.
- **Edge Cases**:
  - Single character: Returns 0 (frequency is 1).
  - No unique character: Returns -1 (e.g., "aabb").
  - Long string: Vector handles up to 10^5 characters efficiently.
- **Result**: Returns the index of the first unique character or -1 if none exists.

### Time and Space Complexity
- **Time Complexity**: O(n), where `n` is the length of the string, as we perform two passes through the string.
- **Space Complexity**: O(1), as the frequency vector has a fixed size of 26 (constant for lowercase letters).

### Alternative Approach
1. **Hash Map with Indices**:
   - Use a hash map to store character frequencies and their first indices.
   - Iterate through the string once to populate the map.
   - Find the smallest index of a character with frequency 1.
   - Time Complexity: O(n)
   - Space Complexity: O(k), where `k` is the number of unique characters (up to 26).
The vector-based approach is preferred for its simplicity and guaranteed O(1) space due to the fixed alphabet size.


# 273. Integer to English Words

This document describes the solution to the "Integer to English Words" problem (LeetCode #273).

## Problem Description
Convert a non-negative integer `num` to its English words representation.

### Example
```
Input: num = 123
Output: "One Hundred Twenty Three"
Explanation: 123 is written as "One Hundred" for 100, "Twenty" for 20, and "Three" for 3.

Input: num = 12345
Output: "Twelve Thousand Three Hundred Forty Five"
Explanation: 12345 is broken into groups: 12 (Twelve Thousand), 345 (Three Hundred Forty Five).

Input: num = 1234567
Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
Explanation: 1234567 is broken into groups: 1 (One Million), 234 (Two Hundred Thirty Four Thousand), 567 (Five Hundred Sixty Seven).

Input: num = 0
Output: "Zero"
Explanation: 0 is simply "Zero".
```

### Constraints
- `0 <= num <= 2^31 - 1`

## Solution Approach
The problem can be solved by processing the number in groups of three digits (thousands, millions, billions) and converting each group to words using predefined mappings for numbers 1-19, tens, and larger units.

### Group-by-Three Approach
1. Define arrays for:
   - Numbers 1-19 (e.g., "One", "Two", ..., "Nineteen").
   - Tens (e.g., "Twenty", "Thirty", ..., "Ninety").
   - Large units (e.g., "Thousand", "Million", "Billion").
2. Handle the special case of `num = 0` by returning "Zero".
3. Process the number in groups of three digits from right to left:
   - Extract the last three digits using modulo (`num % 1000`).
   - Convert the three-digit number to words (hundreds, tens, ones).
   - Append the appropriate unit (Thousand, Million, Billion) based on the group position.
   - Divide `num` by 1000 to process the next group.
4. Combine the words for each group, ensuring proper spacing and trimming.

### Example Implementation (C++)
```cpp
class Solution {
public:
    vector<string> below20 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    
    vector<string> tens = {"", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety", "Hundred"};
    
    string convert(int n)
    {
        if(n >= 1000000000)
            return convert(n / 1000000000) + " Billion" + convert(n % 1000000000);
        
        if(n >= 1000000)
            return convert(n / 1000000) + " Million" + convert(n % 1000000);

        if(n >= 1000)
            return convert(n / 1000) + " Thousand" + convert(n % 1000);

        if(n >= 100)
            return convert(n / 100) + " Hundred" + convert(n % 100);

        if(n >= 20)
            return " " + tens[n/10] + convert(n % 10);
        
        if(n >= 1)
            return " " + below20[n];
            
        return "";
    }
    
    string numberToWords(int num) {
        if(num == 0)
            return "Zero";
        return convert(num).substr(1);
    }
};
```

```cpp
class Solution {
public:
    string numberToWords(int num) {
        if (num == 0) return "Zero";
        
        // Define word mappings
        vector<string> below20 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", 
                                 "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", 
                                 "Seventeen", "Eighteen", "Nineteen"};
        vector<string> tens = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
        vector<string> thousands = {"", "Thousand", "Million", "Billion"};
        
        string result = "";
        int groupIndex = 0;
        
        while (num > 0) {
            int threeDigits = num % 1000;
            if (threeDigits > 0) {
                string group = convertThreeDigits(threeDigits, below20, tens);
                if (!group.empty()) {
                    if (!result.empty()) result = " " + result;
                    result = group + (thousands[groupIndex].empty() ? "" : " " + thousands[groupIndex]) + result;
                }
            }
            num /= 1000;
            groupIndex++;
        }
        
        return result;
    }
    
private:
    string convertThreeDigits(int num, const vector<string>& below20, const vector<string>& tens) {
        string result = "";
        
        // Handle hundreds
        if (num >= 100) {
            result += below20[num / 100] + " Hundred";
            num %= 100;
            if (num > 0) result += " ";
        }
        
        // Handle tens and ones
        if (num >= 20) {
            result += tens[num / 10];
            num %= 10;
            if (num > 0) result += " " + below20[num];
        } else if (num > 0) {
            result += below20[num];
        }
        
        return result;
    }
};
```

### How It Works
- **Zero Case**: If `num = 0`, return "Zero" directly.
- **Group Processing**:
  - Extract three digits at a time (`num % 1000`).
  - Convert the three-digit number to words using `convertThreeDigits`:
    - Hundreds: Add the word for `num / 100` followed by "Hundred".
    - Tens and Ones: If `num >= 20`, add the tens word and optionally the ones word; otherwise, use the `below20` word.
  - Append the appropriate unit (Thousand, Million, Billion) based on the group index.
- **Combining**:
  - Prepend each group’s words to the result, adding spaces as needed.
  - Skip empty groups (e.g., 1000 has no words for the last three digits).
- **Edge Cases**:
  - Single digit: Handled by `below20` in `convertThreeDigits`.
  - Numbers like 100: Only "One Hundred" is added.
  - Large numbers: Processed group by group up to billions.
- **Result**: Returns the English words representation of the number.

### Time and Space Complexity
- **Time Complexity**: O(log n), where `n` is the input number, as we process up to 4 groups of three digits (since `n <= 2^31 - 1` has at most 10 digits).
- **Space Complexity**: O(1), as the storage for word mappings and the result string is bounded by a constant (output string excluded).

### Alternative Approach
1. **Recursive**:
   - Recursively break the number into groups and convert each group.
   - Time Complexity: O(log n)
   - Space Complexity: O(log n) due to recursion stack.
The iterative approach is preferred for its simplicity and constant space usage, avoiding recursion while clearly handling each group.


# 210. Course Schedule II - Depth-First Search - Breadth-First Search, Graph, Topological Sort

This document describes the solution to the "Course Schedule II" problem (LeetCode #210).

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


# 1971. Find if Path Exists in Graph - Depth-First Search, Breadth-First Search, Union Find, Graph

This document describes the solution to the "Find if Path Exists in Graph" problem (LeetCode #1971).

## Problem Description
You are given an undirected graph with `n` nodes labeled from `0` to `n-1` and a list of undirected edges (each edge is a pair of nodes). Write a function to check whether there is a valid path from node `source` to node `destination` in the graph. A valid path is a sequence of nodes where each consecutive pair is connected by an edge.

### Example
```
Input: n = 3, edges = [[0,1],[1,2],[2,0]], source = 0, destination = 2
Output: true
Explanation: There is a path 0 -> 1 -> 2 or 0 -> 2.
```
<img src="../assets/validpath-ex1.jpg" width="20%">

```
Input: n = 6, edges = [[0,1],[0,2],[3,5],[5,4],[4,3]], source = 0, destination = 5
Output: false
Explanation: No path exists from 0 to 5 as the graph is disconnected.
```
<img src="../assets/validpath-ex2.jpg" width="20%">


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


# 797. All Paths From Source to Target - Backtracking, Depth-First Search, Breadth-First Search, Graph

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
            q.pop();
            
            // If target node is reached, add path to result
            if (current == n - 1) {
                result.push_back(path);
                continue;
            }
            
            // Explore all neighbors
            for (int next : graph[current]) {
                vector<int> newPath = path;
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




