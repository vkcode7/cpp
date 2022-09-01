#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
    public:
        vector<int> twoSum(vector<int>& nums, int target) {
            vector<int> result;
            unordered_map<int, int> uo_nums;
            int i = 0;
            
            for(auto& x: nums) {
                auto it = uo_nums.find(target-x);
                if(it != uo_nums.end()) {
                    int index = it->second;
                    result.push_back(index);
                    result.push_back(i);
                    break;
                }
                
                uo_nums[x] = i;
                i++;
            }  
            
            return result;
        }
};