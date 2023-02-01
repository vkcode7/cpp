
 // Definition for singly-linked list.
  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode * result = nullptr;
        ListNode * answer = result;
        int carry = 0;
        while(l1 || l2 || carry)
        {
            int sumOfDigits = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;
            
            carry = (sumOfDigits / 10);
            sumOfDigits = sumOfDigits % 10;
            
            if(answer == nullptr) {
                answer = new ListNode(sumOfDigits, nullptr);
                result = answer;
            }
            else {
                result->next = new ListNode(sumOfDigits, nullptr);
                result = result->next;
            }        
            
            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;
        }
        
        return answer;
    }
};