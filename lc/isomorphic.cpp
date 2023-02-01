#include <iostream>
#include <set>
#include <map>

using namespace std;

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        
        if(s.length() != t.length())
            return false;
        
        map<char, char> mapEnc;
        set<char> setUsed;
        
        for(int i =0; i < t.length(); i++)
        {
            if(mapEnc.find(s[i]) != mapEnc.end())
            {
                if(mapEnc[s[i]] != t[i])
                    return false;
                
                continue;           
            }
         
            if(setUsed.count(t[i]))
            {
                return false;
            }
            
            mapEnc[s[i]] = t[i];
            setUsed.insert(t[i]);
        }
        
        return true;       
    }
};

int main() {
    Solution s;
    s.isIsomorphic("foo", "bar");

    return 0;
}