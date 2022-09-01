#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    void expandFromCenter(int left, int right, string& s, vector<string>& ps) 
    {
        bool found = false;
        for(; left >= 0 && right < s.length() && s[left] == s[right]; left--, right++)
            found = true;
        
        if ( found )
        {
            int len = right - (left+1);
            ps.push_back(s.substr(left+1, len));
        }
    }
    
    string longestPalindrome(string s) {
        if(s.length() == 1)
            return s;
        
        vector<string> pstrings; //collection of all pali strings
        
        //we are going to move from left to right
        //abccbxyz -- bccb - center is in between 
        //abcdcxy -- cdc - center is on a character
        for(int i = 1; i < s.length(); i++) {
            //check if there is a pali string around s[i], s[i] at center
            int left = i-1;
            int right = i+1;
                  
            expandFromCenter(left, right, s, pstrings);
            
            //check if there is a pali string where pali string has even characters
            //s[i-1] == s[i]
            right = i;
            expandFromCenter(left, right, s, pstrings);    
        }
            
        string answer = "";
        for(auto&x : pstrings) {
            if(x.length() > answer.length())
                answer = x;
        }
        
        if(answer.length() == 0)
            answer = s[0];
        
        return answer;     
    }
};

int main() {
    Solution s;
    cout << s.longestPalindrome("bb") << endl;

    int test;
    cin >> test;
}