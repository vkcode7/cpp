//https://leetcode.com/problems/contains-duplicate/

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        int result = 0;
        sort(nums.begin(),nums.end());
        for(int i =0; i < nums.size()-1; i++)
        {
            if((nums[i]^nums[i+1]) == 0)
                return true;
        }
          
        return false;
    }
};