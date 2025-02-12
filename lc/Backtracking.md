## Backtracking

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
'''

### Time complexity of Recursive Tree in above code
//<== controlled recursion
![text](assets/example.png)

