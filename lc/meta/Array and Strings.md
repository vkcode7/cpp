# Arrays and Strings

## 8. String to Integer (atoi)

```
Examples:
'___-043': -43
'1337c0d3': 1337
'0-1': 0
'words and 987': 0
```

```c++
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    int myAtoi(string s) {
        int i = 0, sign = 1;
        long res = 0; // Using long to handle overflow cases

        // Trim leading spaces
        while (i < s.size() && s[i] == ' ') i++;
        if (i == s.size()) return 0;

        // Check for sign
        if (s[i] == '-') { sign = -1; i++; }
        else if (s[i] == '+') i++;

        // Process numerical characters
        while (i < s.size() && isdigit(s[i])) {
            res = res * 10 + (s[i] - '0');

            // Handle overflow
            if (sign * res > INT_MAX) return INT_MAX;
            if (sign * res < INT_MIN) return INT_MIN;

            i++;
        }

        return (int)(sign * res);
    }
};
```

## 13. Roman to Integer

Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M., left to right.

- I can be placed before V (5) and X (10) to make 4 and 9. 
- X can be placed before L (50) and C (100) to make 40 and 90. 
- C can be placed before D (500) and M (1000) to make 400 and 900.

Given a roman numeral, convert it to an integer.


```bash
Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
```

```
Example 1:

Input: s = "III"
Output: 3
Explanation: III = 3.
Example 2:

Input: s = "LVIII"
Output: 58
Explanation: L = 50, V= 5, III = 3.
Example 3:

Input: s = "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
```

### Approach 1:

Left to Right scan: The simplest algorithm is to use a pointer to scan through the string, at each step deciding whether to add the current symbol and go forward 1 place, or add the difference of the next 2 symbols and go forward 2 places. Here is this algorithm in pseudocode.
```
total = 0
i = 0
while i < s.length:
    if at least 2 symbols remaining AND value of s[i] < value of s[i + 1]:
        total = total + (value of s[i + 1]) - (value of s[i])  
        i = i + 2
    else:
        total = total + (value of s[i])
        i = i + 1
return total
```

```c++
class Solution {
public:
    int romanToInt(string s) {
        map<char, int> values{{'I', 1},   {'V', 5},   {'X', 10},  {'L', 50},
                              {'C', 100}, {'D', 500}, {'M', 1000}};

        int sum = 0;
        int i = 0;
        while (i < s.length()) {
            char currentSymbol = s[i];
            int currentValue = values[currentSymbol];
            int nextValue = 0;
            // If a next value exists
            if (i + 1 < s.length()) {
                char nextSymbol = s[i + 1];
                nextValue = values[nextSymbol];
            }

            // If this is the subtractive case.
            if (currentValue < nextValue) {
                sum += (nextValue - currentValue);
                i += 2;
            }
            // else this is NOT the subtractive case.
            else {
                sum += currentValue;
                i += 1;
            }
        }
        return sum;
    }
};
```

### Approach 2: Left-to-Right Pass Improved
Intuition: Instead of viewing a Roman Numeral as having 7 unique symbols, we could instead view it as having 13 unique symbols—some of length-1 and some of length-2.

M M CM L X X X IX = 1000 + 1000 + 900 + 50 + 10 + 10 + 10 + 9 = 2989

After making a Map of String -> Integer with the 13 "symbols", we need to work our way down the string in the same way as before (we'll do left-to-right, however right-to-left will work okay too), firstly checking if we're at a length-2 symbol, and if not, then treating it as a length-1 symbol.

```c++
class Solution {
public:
    static map<string, int>
        values;  // static ensures map initialization only happens once instead
                 // of every object of the class

    Solution() {
        if (values.empty()) {
            values.insert(pair<string, int>("I", 1));
            values.insert(pair<string, int>("V", 5));
            values.insert(pair<string, int>("X", 10));
            values.insert(pair<string, int>("L", 50));
            values.insert(pair<string, int>("C", 100));
            values.insert(pair<string, int>("D", 500));
            values.insert(pair<string, int>("M", 1000));
            values.insert(pair<string, int>("IV", 4));
            values.insert(pair<string, int>("IX", 9));
            values.insert(pair<string, int>("XL", 40));
            values.insert(pair<string, int>("XC", 90));
            values.insert(pair<string, int>("CD", 400));
            values.insert(pair<string, int>("CM", 900));
        }
    }

    int romanToInt(string s) {
        int sum = 0;
        int i = 0;
        while (i < s.size()) {
            if (i < s.size() - 1) {
                string doubleSymbol = s.substr(i, 2);
                // check if this is the length-2 symbol case
                if (values.count(doubleSymbol)) {
                    sum += values[doubleSymbol];
                    i += 2;
                    continue;
                }
            }
            // otherwise, it must be the length-1 symbol case
            string singleSymbol = s.substr(i, 1);
            sum += values[singleSymbol];
            i += 1;
        }
        return sum;
    }
};

map<string, int> Solution::values;  // initalizing the map outside the class
```

## 31. Next Permutation
https://leetcode.com/problems/next-permutation/description/

The next permutation of an array of integers is the next lexicographically greater permutation of its integer. More formally, if all the permutations of the array are sorted in one container according to their lexicographical order, then the next permutation of that array is the permutation that follows it in the sorted container. If such arrangement is not possible, the array must be rearranged as the lowest possible order (i.e., sorted in ascending order).

- For example, the next permutation of arr = [1,2,3] is [1,3,2].
- Similarly, the next permutation of arr = [2,3,1] is [3,1,2].
- While the next permutation of arr = [3,2,1] is [1,2,3] because [3,2,1] does not have a lexicographical larger rearrangement.
Given an array of integers nums, find the next permutation of nums.

The replacement must be in place and use only constant extra memory.

First, we observe that for any given sequence that is in descending order, no next larger permutation is possible.
For example, no next permutation is possible for the following array:

[9, 5, 4, 3, 1]
```
Example 1:

Input: nums = [1,2,3]
Output: [1,3,2]
Example 2:

Input: nums = [3,2,1]
Output: [1,2,3]
Example 3:

Input: nums = [1,1,5]
Output: [1,5,1]
```


```c++
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int i = nums.size() - 2;
        while (i >= 0 && nums[i + 1] <= nums[i]) {
            i--;
        }
        if (i >= 0) {
            int j = nums.size() - 1;
            while (nums[j] <= nums[i]) {
                j--;
            }
            swap(nums, i, j);
        }
        reverse(nums.begin() + i + 1, nums.end());
    }

private:
    void swap(vector<int>& nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }
};
```

## 43. Multiply Strings

Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2, also represented as a string.

Note: You must not use any built-in BigInteger library or convert the inputs to integer directly.

```
Example 1:

Input: num1 = "2", num2 = "3"
Output: "6"
Example 2:

Input: num1 = "123", num2 = "456"
Output: "56088"
```

Let's look at an example. Consider 123∗456, it can be written as,

⟹(123∗(6+50+400))
⟹(123∗6)+(123∗50)+(123∗400)
⟹(123∗6)+(123∗5∗10)+(123∗4∗100)

The results of the multiplication of each digit of the second number with the first number can be stored in an array of strings, and then we can add all these strings to get the final product.

```
Let's walk through the steps one by one:

Reverse both numbers.
For each digit in secondNumber:
    Keep a carry variable, initially equal to 0.
    Initialize currentResult array beginning with the appropriate number of zeros according to the place of the secondNumber digit.
    For each digit in firstNumber:
        Multiply the secondNumber's digit and the firstNumber's digit and add carry to the multiplication.
        Take the remainder of multiplication with 10 to get the last digit.
        Append the last digit to the currentResult.
        Divide multiplication by 10 to get the new value for carry.
    Append the remaining value for carry (if any) to the currentResult.
    Push the currentResult into the results array.
Compute the cumulative sum over all the obtained arrays using the ans as an answer.
Reverse ans and return it.

```

```c++
class Solution {
private:
    // Calculate the sum of all of the results from multiplyOneDigit.
    string sumResults(vector<vector<int>>& results) {
        // Initialize answer as a number from results.
        vector<int> answer = results.back();
        vector<int> newAnswer;
        results.pop_back();

        // Sum each digit from answer and result
        for (vector<int> result : results) {
            newAnswer.clear();
            int carry = 0;

            for (int i = 0; i < answer.size() || i < result.size(); ++i) {
                // If answer is shorter than result or vice versa, use 0 as the
                // current digit.
                int digit1 = i < result.size() ? result[i] : 0;
                int digit2 = i < answer.size() ? answer[i] : 0;
                // Add current digits of both numbers.
                int sum = digit1 + digit2 + carry;
                // Set carry equal to the tens place digit of sum.
                carry = sum / 10;
                // Append the ones place digit of sum to answer.
                newAnswer.push_back(sum % 10);
            }

            if (carry) {
                newAnswer.push_back(carry);
            }
            answer = newAnswer;
        }

        // Convert answer to a string.
        string finalAnswer;
        for (int digit : answer) {
            finalAnswer.push_back(digit + '0');
        }
        return finalAnswer;
    }

    // Multiply the current digit of secondNumber with firstNumber.
    vector<int> multiplyOneDigit(string& firstNumber, char& secondNumberDigit,
                                 int numZeros) {
        // Insert zeros at the beginning based on the current digit's place.
        vector<int> currentResult(numZeros, 0);
        int carry = 0;

        // Multiply firstNumber with the current digit of secondNumber.
        for (char firstNumberDigit : firstNumber) {
            int multiplication =
                (secondNumberDigit - '0') * (firstNumberDigit - '0') + carry;
            // Set carry equal to the tens place digit of multiplication.
            carry = multiplication / 10;
            // Append last digit to the current result.
            currentResult.push_back(multiplication % 10);
        }

        if (carry) {
            currentResult.push_back(carry);
        }
        return currentResult;
    }

public:
    string multiply(string firstNumber, string secondNumber) {
        if (firstNumber == "0" || secondNumber == "0") {
            return "0";
        }

        // Reverse both numbers.
        reverse(firstNumber.begin(), firstNumber.end());
        reverse(secondNumber.begin(), secondNumber.end());

        // For each digit in secondNumber, multipy the digit by firstNumber and
        // store the multiplication result (reversed) in results.
        vector<vector<int>> results;
        for (int i = 0; i < secondNumber.size(); ++i) {
            results.push_back(
                multiplyOneDigit(firstNumber, secondNumber[i], i));
        }

        // Add all the results in the results array, and store the sum in the
        // answer string.
        string answer = sumResults(results);

        // answer is reversed, so reverse it to get the final answer.
        reverse(answer.begin(), answer.end());
        return answer;
    }
};
```

## 49. Group Anagrams
https://leetcode.com/problems/group-anagrams/description/

Given an array of strings strs, group the anagrams together. You can return the answer in any order.

```bash
Example 1:

Input: strs = ["eat","tea","tan","ate","nat","bat"]

Output: [["bat"],["nat","tan"],["ate","eat","tea"]]

Explanation:

There is no string in strs that can be rearranged to form "bat".
The strings "nat" and "tan" are anagrams as they can be rearranged to form each other.
The strings "ate", "eat", and "tea" are anagrams as they can be rearranged to form each other.
```
We can transform each string s into a character count, count, consisting of 26 non-negative integers representing the number of a's, b's, c's, etc. We use these counts as the basis for our hash map.

In c++, the hashable representation of our count will be a string delimited with '#' characters. For example, abbccc will be #1#2#3#0#0#0...#0 where there are 26 entries total. In python, the representation will be a tuple of the counts. For example, abbccc will be (1, 2, 3, 0, 0, ..., 0), where again there are 26 entries total.

An easy way is to sort each string and use the sorted string as key.

```c++
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        if (strs.size() == 0) return vector<vector<string>>();
        unordered_map<string, vector<string>> ans;
        int count[26];
        for (string s : strs) {
            fill(begin(count), end(count), 0);
            for (char c : s) count[c - 'a']++;
            string key = "";
            for (int i = 0; i < 26; i++) {
                key += "#";
                key += to_string(count[i]);
            }
            if (ans.find(key) == ans.end()) ans[key] = vector<string>();
            ans[key].push_back(s);
        }
        vector<vector<string>> result;
        for (auto itr = ans.begin(); itr != ans.end(); ++itr)
            result.push_back(itr->second);
        return result;
    }
};
```

```c++
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> mp;
        for (string s : strs) {
            mp[strSort(s)].push_back(s);
        }
        vector<vector<string>> anagrams;
        for (auto p : mp) { 
            anagrams.push_back(p.second);
        }
        return anagrams;
    }
private:
    string strSort(string s) {
        int n = s.size(), counter[26] = {0};
        for (char c : s) {
            counter[c - 'a']++;
        }
        string t;
        for (int c = 0; c < 26; c++) {
            t += string(counter[c], c + 'a');
        }
        return t;
    }
};
```

## 67. Add Binary
https://leetcode.com/problems/add-binary/description/

Given two binary strings a and b, return their sum as a binary string.

```
Example 1:

Input: a = "11", b = "1"
Output: "100"
Example 2:

Input: a = "1010", b = "1011"
Output: "10101"
```
### Approach 1: Bit-by-Bit Computation
```c++
     1010
    +1101
    ______
    10111
```

```c++
class Solution {
 public:
  string addBinary(string a, string b) {
    string ans;
    int carry = 0;
    int i = a.length() - 1;
    int j = b.length() - 1;

    while (i >= 0 || j >= 0 || carry) {
      if (i >= 0)
        carry += a[i--] - '0';
      if (j >= 0)
        carry += b[j--] - '0';
      ans += carry % 2 + '0';
      carry /= 2;
    }

    reverse(begin(ans), end(ans));
    return ans;
  }
};
```

### Approach 2: Bit Manipulation
Intuition

Here the input is more adapted to push towards Approach 1, but there is a popular Facebook variation of this problem when the interviewer provides you with two numbers and asks to sum them up without using the addition operation.

Now the problem is reduced: one has to find the sum of answers without carry and carry. It's the same problem - to sum two numbers, and hence one could solve it in a loop with the condition statement "while carry is not equal to zero".

Algorithm
- Convert a and b into integers x and y, x will be used to keep an answer, and y for the carry.

- While carry is nonzero: y != 0:
    - Current answer without carry is XOR of x and y: answer = x^y.
    - Current carry is left-shifted AND of x and y: carry = (x & y) << 1.
    - Job is done, prepare the next loop: x = answer, y = carry.
- Return x in the binary form.

```c++
class BigInt {
private:
    string binary;

    // Helper function to ensure strings are the same length
    static void equalizeLength(string& a, string& b) {
        int lengthDifference = a.size() - b.size();
        if (lengthDifference > 0)
            b.insert(0, lengthDifference, '0');
        else
            a.insert(0, -lengthDifference, '0');
    }

    // Helper function to remove leading zeros
    void removeLeadingZeros() {
        // Erase leading zeros while keeping at least one zero if the number is
        // zero
        auto firstNonZero = binary.find_first_not_of('0');
        if (firstNonZero != string::npos) {
            binary.erase(0, firstNonZero);
        } else {
            binary =
                "0";  // Adjust to maintain a minimum representation of zero
        }
    }

public:
    BigInt() : binary("0") {}

    // Constructor from a binary string
    BigInt(const string& bin) : binary(bin) { removeLeadingZeros(); }

    // Bitwise XOR
    BigInt operator^(const BigInt& other) const {
        string a = binary;
        string b = other.binary;
        equalizeLength(a, b);
        string result;
        for (size_t i = 0; i < a.size(); i++) {
            char xorChar = (a[i] == b[i] ? '0' : '1');
            result.push_back(xorChar);
        }
        return BigInt(result);
    }

    // Bitwise AND
    BigInt operator&(const BigInt& other) const {
        string a = binary;
        string b = other.binary;
        equalizeLength(a, b);
        string result;
        for (size_t i = 0; i < a.size(); i++) {
            char andChar = (a[i] == '1' && b[i] == '1' ? '1' : '0');
            result.push_back(andChar);
        }
        return BigInt(result);
    }

    // Left shift
    BigInt operator<<(int shift) const {
        string result = binary;
        result.append(shift, '0');
        return BigInt(result);
    }

    // Check if BigInt is zero
    bool isZero() const {
        for (char c : binary)
            if (c != '0') return false;
        return true;
    }

    // Getter for binary string
    string getBinary() const { return binary; }
};

class Solution {
public:
    string addBinary(string a, string b) {
        BigInt x(a);
        BigInt y(b);
        BigInt carry, answer;

        while (!y.isZero()) {
            answer = x ^ y;
            carry = (x & y) << 1;
            x = answer;
            y = carry;
        }
        return x.getBinary();
    }
};
```


## 314. Binary Tree Vertical Order Traversal
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
        
        if(!root) return res;
        
        map<int, vector<int>> map;
        
        queue<pair<TreeNode* , int>> q;
        
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


## 157. Read N Characters Given Read4

Given a file and assume that you can only read the file using a given method read4, implement a method to read n characters.

Method read4:
The API read4 reads four consecutive characters from file, then writes those characters into the buffer array buf4.

The return value is the number of actual characters read.

Note that read4() has its own file pointer, much like FILE *fp in C.

```
Definition of read4:

    Parameter:  char[] buf4
    Returns:    int

buf4[] is a destination, not a source. The results from read4 will be copied to buf4[].


Example 1:

Input: file = "abc", n = 4
Output: 3
Explanation: After calling your read method, buf should contain "abc". We read a total of 3 characters from the file, so return 3.
Note that "abc" is the file's content, not buf. buf is the destination buffer that you will have to write the results to.
Example 2:

Input: file = "abcde", n = 5
Output: 5
Explanation: After calling your read method, buf should contain "abcde". We read a total of 5 characters from the file, so return 5.
Example 3:

Input: file = "abcdABCD1234", n = 12
Output: 12
Explanation: After calling your read method, buf should contain "abcdABCD1234". We read a total of 12 characters from the file, so return 12.
```

```cpp
This solution causes TLE

/**
 * The read4 API is defined in the parent class Reader4.
 *     int read4(char *buf4);
 */

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    int read(char *buf, int n) {
        int read = 4;
        int totalRead = 0;

        while(n - totalRead >= 4) {
            read = read4(buf + totalRead);
            totalRead += read;
            if(read < 4)
                break;
        }

        if(n - totalRead < 4 && read) {
            char curr_buf[4];
            read = read4(buf + totalRead);
            *(buf + totalRead + read) = 0; 
            totalRead += read;
        }

        return min(n, totalRead);
    }
};
```

## 161. One Edit Distance
Given two strings s and t, return true if they are both one edit distance apart, otherwise return false.

A string s is said to be one distance apart from a string t if you can:

- Insert exactly one character into s to get t.
- Delete exactly one character from s to get t.
- Replace exactly one character of s with a different character to get t.
 
```
Example 1:

Input: s = "ab", t = "acb"
Output: true
Explanation: We can insert 'c' into s to get t.
Example 2:

Input: s = "", t = ""
Output: false
Explanation: We cannot get t from s by only one step.
```

```cpp
class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        int ns = s.size();
        int nt = t.size();

        // Ensure that s is shorter than t.
        if (ns > nt) return isOneEditDistance(t, s);

        // The strings are NOT one edit away distance
        // if the length diff is more than 1.
        if (nt - ns > 1) return false;

        for (int i = 0; i < ns; i++)
            if (s[i] != t[i])
                // if strings have the same length
                if (ns == nt) return s.substr(i + 1) == t.substr(i + 1);
                // If strings have different lengths
                else
                    return s.substr(i) == t.substr(i + 1);

        // If there are no diffs in ns distance
        // The strings are one edit away only if
        // t has one more character.
        return (ns + 1 == nt);
    }
};
```

## 340. Longest Substring with At Most K Distinct Characters

Given a string s and an integer k, return the length of the longest substring of s that contains at most k distinct characters.

```
Example 1:

Input: s = "eceba", k = 2
Output: 3
Explanation: The substring is "ece" with length 3.
Example 2:

Input: s = "aa", k = 1
Output: 2
Explanation: The substring is "aa" with length 2.
```

```cpp
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) 
    {
        int windowStart = 0; 
        unordered_map<int, int> map; 
        int maxLength = INT_MIN; 

        for(int windowEnd = 0; windowEnd < s.length(); windowEnd++)
        {
            //add everyelement to the map with frequency, 
            //if element exists, increase the frequency.
            map[s[windowEnd]]++; 

            //we found a substring with more than k distinct elments. 
            //at this point we will shrink the windowStart to elimiate distinct chars. 
            while(map.size() > k)
            {

                map[s[windowStart]]--;
                    
                //should be a separate if instead of else, as if after decreasing frequency
                //the final frequency is 0, the element should be removed form the map to reduce total distinct count. 
                if(map[s[windowStart]] == 0)
                {
                    map.erase(s[windowStart]);
                }

                //increament windowStart to keep srinking the window.
                windowStart++;
            }

            maxLength = max(maxLength, (windowEnd - windowStart + 1));
        }

        return maxLength;
    }
};
```

## 468. Validate IP Address
https://leetcode.com/problems/validate-ip-address/description/

Given a string queryIP, return "IPv4" if IP is a valid IPv4 address, "IPv6" if IP is a valid IPv6 address or "Neither" if IP is not a correct IP of any type.

```
A valid IPv4 address is an IP in the form "x1.x2.x3.x4" where 0 <= xi <= 255 and xi cannot contain leading zeros. For example, "192.168.1.1" and "192.168.1.0" are valid IPv4 addresses while "192.168.01.1", "192.168.1.00", and "192.168@1.1" are invalid IPv4 addresses.

A valid IPv6 address is an IP in the form "x1:x2:x3:x4:x5:x6:x7:x8" where:

1 <= xi.length <= 4
xi is a hexadecimal string which may contain digits, lowercase English letter ('a' to 'f') and upper-case English letters ('A' to 'F').
Leading zeros are allowed in xi.
For example, "2001:0db8:85a3:0000:0000:8a2e:0370:7334" and "2001:db8:85a3:0:0:8A2E:0370:7334" are valid IPv6 addresses, while "2001:0db8:85a3::8A2E:037j:7334" and "02001:0db8:85a3:0000:0000:8a2e:0370:7334" are invalid IPv6 addresses.

Example 1:

Input: queryIP = "172.16.254.1"
Output: "IPv4"
Explanation: This is a valid IPv4 address, return "IPv4".
Example 2:

Input: queryIP = "2001:0db8:85a3:0:0:8A2E:0370:7334"
Output: "IPv6"
Explanation: This is a valid IPv6 address, return "IPv6".
Example 3:

Input: queryIP = "256.256.256.256"
Output: "Neither"
Explanation: This is neither a IPv4 address nor a IPv6 address.
```

```c++
class Solution {
public:
    string validateIPv4(string IP) {
        IP.push_back('.');  // add extra . at end to handle last group
        stringstream ss(IP);
        string block;
        int count = 0;
        while (getline(ss, block, '.')) {
            count++;
            // Validate integer in range (0, 255):
            // 1. length of chunk is between 1 and 3
            if (block.length() == 0 || block.length() > 3) return "Neither";
            // 2. no extra leading zeros
            if (block[0] == '0' && block.length() != 1) return "Neither";
            for (char ch : block) {
                // 3. only digits are allowed
                if (!isdigit(ch)) return "Neither";
            }
            // 4. less than or equal to 255
            if (stoi(block) > 255) return "Neither";
        }
        return (count == 4 && ss.eof()) ? "IPv4" : "Neither";
    }

    string validateIPv6(string IP) {
        IP.push_back(':');  // add extra : at end to handle last group
        stringstream ss(IP);
        string block;
        int count = 0;
        while (getline(ss, block, ':')) {
            count++;
            // Validate hexadecimal in range (0, 2**16):
            // 1. at least one and not more than 4 hexdigits in one chunk
            if (block.length() == 0 || block.length() > 4) return "Neither";
            for (char ch : block) {
                // 2. only hexdigits are allowed: 0-9, a-f, A-F
                if (!isxdigit(ch)) return "Neither";
            }
        }
        return (count == 8 && ss.eof()) ? "IPv6" : "Neither";
    }

    string validIPAddress(string IP) {
        return (count(begin(IP), end(IP), '.') == 3)
                   ? validateIPv4(IP)
                   : (count(begin(IP), end(IP), ':') == 7 ? validateIPv6(IP)
                                                          : "Neither");
    }
};
```

## 680. Valid Palindrome II
Given a string s, return true if the s can be palindrome after deleting at most one character from it.

```
Example 1:

Input: s = "aba"
Output: true
Example 2:

Input: s = "abca"
Output: true
Explanation: You could delete the character 'c'.
Example 3:

Input: s = "abc"
Output: false
```

```c++
class Solution {
public:
    bool ispalindrome(string s, int i, int j){
        while(i < j){
            if(s.at(i) == s.at(j)){
                i++;
                j--;
            }else return false;
        }
        return true;
    }
    bool validPalindrome(string s) {
        int i  = 0;
        int j = s.size()-1;
        while(i < j){
            if(s.at(i) == s.at(j)){
                i++;
                j--;
            }else{
                return ispalindrome(s, i+1, j) || ispalindrome(s, i, j-1);
            }
        }
        return true;
    }
};

```

