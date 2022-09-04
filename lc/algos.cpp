//142. Linked List Cycle II
//https://leetcode.com/problems/linked-list-cycle-ii/
//Floyd's algo to detect cycle

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class Solution {
public:
    ListNode *detectCycle(ListNode *head) { 
        if(!head || !head->next)
            return nullptr;
            
        ListNode * slow = head;
        ListNode * fast = head;
        ListNode * match = head;
        
        while(slow->next && fast->next && fast->next->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            
            if(slow == fast)
            {
                while(match != slow)
                {
                    match = match->next;
                    slow = slow->next;
                }

                return match;
            }
        }
        
        return nullptr;
    }
};

//53. Maximum Subarray
//https://leetcode.com/problems/maximum-subarray/
//Kadane's algorithm
class Solution {
public:
	int maxSubArray(vector<int>& nums) {
		int curMax = 0, maxTillNow = INT_MIN;
		for (auto& x : nums) {
			curMax = max(x, curMax + x);
			maxTillNow = max(maxTillNow, curMax);
		}

		return maxTillNow;
	}
};
