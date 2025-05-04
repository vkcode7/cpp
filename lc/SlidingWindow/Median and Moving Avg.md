```bash
# 215. Kth Largest Element in an Array Solution
# 295. Find Median from Data Stream - Two Pointers, Design, Sorting, Heap (Priority Queue), Data Stream
# 4. Median of Two Sorted Arrays
# 346. Moving Average from Data Stream
# 7. Reverse Integer
# 1046. Last Stone Weight Solution
```

# 215. Kth Largest Element in an Array Solution

## Problem Description
Given an integer array `nums` and an integer `k`, return the `k`th largest element in the array. The `k`th largest element is the element that would appear in the `k`th position if the array were sorted in descending order. You must solve it without sorting the entire array for optimal performance.

### Example
```
Input: nums = [3,2,1,5,6,4], k = 2
Output: 5
Explanation: The second largest element is 5 (sorted in descending order: [6,5,4,3,2,1]).

Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
Output: 4
```

## Solution
Below is the C++ solution to find the `k`th largest element using a min-heap (priority queue).

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // Create a min-heap
        priority_queue<int, vector<int>, greater<int>> pq;
        
        // Process each element
        for (int num : nums) {
            pq.push(num);
            // If heap size exceeds k, remove the smallest element
            if (pq.size() > k) {
                pq.pop();
            }
        }
        
        // The top of the heap is the kth largest element
        return pq.top();
    }
};
```

## Explanation
1. **Min-Heap Approach**:
   - Use a min-heap (`priority_queue` with `greater<int>` for ascending order) to maintain the `k` largest elements.
   - Iterate through each element in `nums`:
     - Push the element into the heap.
     - If the heap size exceeds `k`, pop the smallest element to keep only the `k` largest elements.
   - After processing all elements, the heap contains the `k` largest elements, and the top (smallest of these) is the `k`th largest.
2. **Efficiency**:
   - The heap ensures we only keep track of the `k` largest elements, avoiding the need to sort the entire array.
3. **Result**:
   - Return `pq.top()`, which is the `k`th largest element.

## Time and Space Complexity
- **Time Complexity**: O(n log k), where `n` is the length of the array. Each push/pop operation on the heap takes O(log k), and we process `n` elements.
- **Space Complexity**: O(k), for storing at most `k` elements in the min-heap.

## Edge Cases
- `k = 1`: Return the maximum element.
- `k = nums.size()`: Return the minimum element.
- Single element: `nums = [1]`, `k = 1` returns 1.
- Duplicate elements: Correctly handles cases like `[3,3,3,3]`, `k = 2` (returns 3).
- Large array: Efficiently processes up to `n = 10^5` and `k` within constraints.
- Negative numbers: Works with any integer values (e.g., `[-1,-2,-3]`, `k = 1` returns -1).

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


# 1046. Last Stone Weight Solution

## Problem Description
You are given an array of integers `stones` where each element represents the weight of a stone. In each step, you choose the two heaviest stones and smash them together. If the weights are `x` and `y` (with `x <= y`), the result is:
- If `x == y`, both stones are destroyed.
- If `x != y`, the stone of weight `x` is destroyed, and the stone of weight `y` has new weight `y - x`.
Continue this process until there is at most one stone left. Return the weight of the last remaining stone (or 0 if no stones remain).

### Example
```
Input: stones = [2,7,4,1,8,1]
Output: 1
Explanation: Smash 8 and 7 (8-7=1), new array = [1,4,1,2]. Smash 4 and 2 (4-2=2), new array = [2,1,1]. Smash 2 and 1 (2-1=1), new array = [1,1]. Smash 1 and 1 (1-1=0), new array = [1]. Return 1.
```

## Solution
Below is the C++ solution to find the weight of the last remaining stone using a priority queue.

```cpp
class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> pq(stones.begin(), stones.end());
        
        while(pq.size() > 1)
        {
            int top = pq.top();
            pq.pop();
            int top2 = pq.top();
            pq.pop();
            if(top > top2)
            {
                pq.push(top-top2);
            }
        }
        
        return pq.empty()? 0: pq.top();
    }
};

class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        // Create a max-heap
        priority_queue<int> pq(stones.begin(), stones.end());
        
        // Process until 0 or 1 stone remains
        while (pq.size() > 1) {
            // Get the two heaviest stones
            int y = pq.top();
            pq.pop();
            int x = pq.top();
            pq.pop();
            
            // If stones are different weights, push back the remaining weight
            if (x != y) {
                pq.push(y - x);
            }
        }
        
        // Return the last stone weight or 0 if none remain
        return pq.empty() ? 0 : pq.top();
    }
};
```

## Explanation
1. **Max-Heap Initialization**:
   - Use a `priority_queue` (max-heap) to store the stones, allowing efficient access to the two heaviest stones.
   - Initialize the heap with all stone weights from the input array.
2. **Smashing Process**:
   - While there are at least two stones in the heap:
     - Extract the two heaviest stones (`y` and `x`, where `x <= y`).
     - If `x != y`, compute the new weight (`y - x`) and push it back to the heap.
     - If `x == y`, both stones are destroyed, so do nothing.
3. **Result**:
   - If the heap is empty, return 0 (no stones remain).
   - If one stone remains, return its weight (top of the heap).

## Time and Space Complexity
- **Time Complexity**: O(n log n), where `n` is the number of stones. Initial heap construction takes O(n), and each operation (pop or push) takes O(log n). There are up to `n` smash operations, leading to O(n log n).
- **Space Complexity**: O(n), for storing the stones in the priority queue.

## Edge Cases
- Single stone: Return its weight.
- Empty array: Return 0 (not applicable due to constraints, but handled as empty heap).
- All stones equal: All pairs cancel out (e.g., `[2,2]` returns 0).
- Two stones: Return their difference or 0 if equal.
- Large array: Efficiently handles up to 1000 stones within constraints.
