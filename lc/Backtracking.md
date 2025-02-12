## Backtracking

1.
![text](assets/s4.png)

2.
![text](assets/s5.png)

3.
![text](assets/s6.png)

4.
![text](assets/s7.png)

5.
![text](assets/s8.png)

Problem: 
https://www.geeksforgeeks.org/problems/permutations-of-a-given-string2041/1<br>
Given a string s, which may contain duplicate characters, your task is to generate and return an array of all unique permutations of the string. You can return your answer in any order.

The below solution uses Recurion not BT.
```c++
#include<vector>
#include<string>
#include<unordered_set>
#include <iostream>

using namespace std;

void permute(string ip, string op, vector<string> &v)
{
    if (ip.size() == 0) //<== controlled recursion
    {
        v.push_back(op);
        return;
    }

    unordered_set<char> mp;
    for (int i = 0; i < ip.size(); i++) //<== for Choices loop
    {
        if (mp.find(ip[i]) == mp.end()) //<== controlled condition
        {
            mp.insert(ip[i]);
            string newip = ip.substr(0, i) + ip.substr(i + 1);

            string newop = op + ip[i];
            cout << i << ", ip: " << ip << ", newip: " << newip << ", newop: " << newop << endl;
            permute(newip, newop, v); //<== passing by value so not a BackTracking solution; if we pass ip as reference and not use op, it will turn into a BT solution
        }
    }
}

vector<string> find_permutation(string S)
{
    // Code here there
    vector<string> v;
    permute(S, "", v);
    return v;
}

int main() {
    // Write C++ code here
    std::cout << "Welcome" << endl;
    auto v = find_permutation("abc");
    for(auto s: v)
        cout << s << endl;
    return 0;
}
```

### Time complexity of Recursive Tree in above code

Time complxity = Time complexity of one node X number of nodes in the tree

Above tree will have nodes like this which comes out to be n!
![text](assets/s1.png)

A balance tree will be 2 pow n.
![text](assets/s3.png)

### Using BackTracking for above problme

simple solution:
```c++
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

class Solution {
private:
    void backtrack(std::string& s, int start, std::set<std::string>& result) {
        if (start == s.length() - 1) {
            result.insert(s);
            return;
        }
        
        for (int i = start; i < s.length(); ++i) {
            // Swap characters to generate permutation
            std::swap(s[start], s[i]);
            backtrack(s, start + 1, result);
            // Undo the swap to backtrack
            std::swap(s[start], s[i]);
        }
    }

public:
    std::vector<std::string> permutation(std::string s) {
        std::set<std::string> uniquePermutations;
        backtrack(s, 0, uniquePermutations);
        
        // Convert set to vector because the return type is vector<string>
        return std::vector<std::string>(uniquePermutations.begin(), uniquePermutations.end());
    }
};

int main() {
    Solution solution;
    std::string s = "aba";
    std::vector<std::string> permutations = solution.permutation(s);
    
    for (const auto& perm : permutations) {
        std::cout << perm << std::endl;
    }
    
    return 0;
}
```


```c++
class Solution
{
public:
	vector<string>find_permutation(string S)
	{
	    // Code here there
	    set<string> ans;
	    permutations(S,0,ans);
	    vector<string> vc(ans.begin(), ans.end());
	    
	    return vc;
	}
	void permutations(string &s, int start, set<string> &ans){
	    if(start == s.size()-1){
		ans.insert(s);
		return;
	    }
	    
	    unordered_map<char,int> mp;
	    for(int i = start; i < s.size(); i++){
		if(mp.find(s[i]) == mp.end()){
		    mp[s[i]]++;
		    
		    if(s[i] != s[start]){
			swap(s[i],s[start]);
			permutations(s,start+1,ans);
		    	// backtracking step
		    	swap(s[i],s[start]);
		    }
		    else
		       permutations(s,start+1,ans);
		}
	    }
	}
};
```

solution by Grok:
```c++
#include <string>
#include <vector>
#include <set>
#include <algorithm>

class Solution {
public:
    vector<string>find_permutation(string S) {
        set<string> ans;
        permutations(S, 0, ans);
        return vector<string>(ans.begin(), ans.end());
    }

private:
    void permutations(string &s, int start, set<string> &ans) {
        if(start == s.size() - 1) {
            ans.insert(s);
            return;
        }
        
        vector<bool> used(256, false);  // Assuming ASCII
        for(int i = start; i < s.size(); i++) {
            if(!used[s[i]]) {
                used[s[i]] = true;
                swap(s[start], s[i]);
                permutations(s, start + 1, ans);
                swap(s[start], s[i]); // backtrack
            }
        }
    }
};

// Main or test function if needed
int main() {
    Solution sol;
    string S = "abc";
    vector<string> result = sol.find_permutation(S);
    for(const auto& perm : result) {
        cout << perm << " ";
    }
    cout << endl;
    return 0;
}
```

### Problem:
Given a number K and string str of digits denoting a positive integer, build the largest number possible by performing swap operations on the digits of str at most K times.
![text](assets/s9.png)

Approach:

Backtracking with swapping:

- Swap any two digits and recursively check if it leads to a larger number.
- Keep track of the maximum number found.
- Decrement K on each swap and backtrack after exploring.

Optimizations:

- If K == 0, stop further recursion.
- Swap only when it results in a larger number to reduce redundant computations.
- Store visited states to avoid unnecessary recomputation.

```c++
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void findMaxNumber(string &str, int k, string &maxNum, int index) {
    if (k == 0) return; // No more swaps left

    int n = str.size();
    char maxDigit = str[index];

    // Find the maximum digit from the remaining string
    for (int i = index + 1; i < n; i++) {
        if (str[i] > maxDigit) {
            maxDigit = str[i];
        }
    }

    // If the current digit is already the largest, no need to swap
    if (maxDigit != str[index]) k--;

    // Explore all swaps with maxDigit found
    for (int i = index + 1; i < n; i++) {
        if (str[i] == maxDigit) {
            swap(str[index], str[i]); // Swap

            // Update maxNum if we found a larger number
            if (str > maxNum) {
                maxNum = str;
            }

            findMaxNumber(str, k, maxNum, index + 1);

            swap(str[index], str[i]); // Backtrack
        }
    }

    // Move to the next index without swapping
    findMaxNumber(str, k, maxNum, index + 1);
}

string largestNumber(string str, int k) {
    string maxNum = str;
    findMaxNumber(str, k, maxNum, 0);
    return maxNum;
}

int main() {
    string str = "129814999";
    int k = 4;
    
    cout << "Largest possible number: " << largestNumber(str, k) << endl;
    
    return 0;
}
```



