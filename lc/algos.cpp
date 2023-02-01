//142. Linked List Cycle II
//https://leetcode.com/problems/linked-list-cycle-ii/
//Floyd's algo to detect cycle


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


//https://leetcode.com/problems/longest-palindromic-substring/
//5. Longest Palindromic Substring

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

//https://leetcode.com/problems/contains-duplicate/
//217. Contains Duplicate
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
    sort(nums.begin(),nums.end());
        int i=0;
        while(i<nums.size()-1){
            if((nums[i]^nums[i+1])==0){
                return true;
                break;
            }
            else{
                i++;
            }
        }
        return false;
    }
};


/*
Sliding Window problem
Given an array of positive integers and a number ‘S,’ find the length of the smallest contiguous subarray 
whose sum is greater than or equal to ‘S’. Return 0 if no such subarray exists.
*/

using namespace std;

#include <iostream>
#include <limits>
#include <vector>

class MinSizeSubArraySum {
 public:
  static int findMinSubArray(int S, const vector<int>& arr) {
    int minLength = numeric_limits<int>::max();
    int windowSum = 0;
      int windowStart = 0;
    for (int windowEnd = 0; windowEnd < arr.size(); windowEnd++) {
      windowSum += arr[windowEnd];
      // shrink the window as small as possible until the 'windowSum' is smaller than 'S'
      while (windowSum >= S) {
        minLength = min(minLength, windowEnd - windowStart + 1);
        windowSum -= arr[windowStart];
        windowStart++;
        }      
      }
    return minLength == numeric_limits<int>::max() ? 0 : minLength;
  }
};

//Given a string, find the length of the longest substring in it with no more than K distinct characters.
/*
Input: String="araaci", K=2
Output: 4
Explanation: The longest substring with no more than '2' distinct characters is "araa".
*/

using namespace std;

#include <iostream>
#include <string>
#include <unordered_map>

class LongestSubstringKDistinct {
 public:
  static int findLength(const string& str, int k) {
    int maxLength = 0;
    
    int wStart = 0;
    int wLen = 0;
    unordered_map<char, int> uomap;

    for (int wEnd = 0; wEnd < str.length(); wEnd++)
    {
        char right = str[wEnd];
        if(uomap.find(right) == uomap.end())
          uomap[right] = 1;
        else
          uomap[right] = uomap[right] + 1;

        while(uomap.size() > k) {
            //take the char out from beginning
            char left = str[wStart];
            if(uomap.find(left) != uomap.end())
            {
                uomap[left] = uomap[left] - 1;
                if(uomap[left] == 0)
                  uomap.erase(left);

                wStart++;
            }
        }

        maxLength = max(maxLength, wEnd - wStart + 1);
    }

    return maxLength;
  }
};

//3. Longest Substring Without Repeating Characters
//Given a string s, find the length of the longest substring without repeating characters.
//https://leetcode.com/problems/longest-substring-without-repeating-characters/

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        set<char> cs;
        
        int maxL = 0;
        int start = 0;
        
        for(int i =0; i < s.length(); i++)
        {
            char ch = s[i];
            if(cs.count(ch) == 1)
            {
                //already exists
                while(cs.count(ch) != 0)
                {
                    cs.erase(s[start]);
                    start++;
                }
            }
            
            cs.insert(ch);
            maxL = max(maxL, i - start + 1);
        }
        
        return maxL;
    }
};

//https://leetcode.com/problems/reverse-linked-list/submissions/
//resversing a linked list
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(!head)
            return head;
        
        ListNode * current = head;
        ListNode * prev = nullptr;
        ListNode * next = nullptr;
        
        while(current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;    
            current = next;
        }
        
        return prev;
    }
};

//102. Binary Tree Level Order Traversal
//https://leetcode.com/problems/binary-tree-level-order-traversal/submissions/
//Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right, level by level).
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> vOut;
        if(root)
        {
            queue<TreeNode*> q;
            q.push(root); //add root node to queue

            while(q.size() > 0) {
                int qSize = q.size(); //gives num of nodes at same level
                 
                vector<int> val(qSize, 0);
                
                //iterate through all nodes and add their kids
                for(int i = 0; i < qSize; i++) 
                {
                    TreeNode * node = q.front();
                    val[i] = node->val;

                    if(node->left)
                        q.push(node->left);

                    if(node->right)
                        q.push(node->right);

                    //pop the node just processed
                    q.pop(); //removes the node from Q
                }

                vOut.push_back(val);         
            } 
        }
        
        return vOut;
    }
};

//https://leetcode.com/problems/binary-tree-level-order-traversal-ii/submissions/
//Given the root of a binary tree, return the bottom-up level order traversal of its nodes' values. 
//(i.e., from left to right, level by level from leaf to root).
//Print a Q in reverse
class Solution {
public:
    
    int getTreeHeight(TreeNode *node) {
        if(!node)
            return 0;
        
        int leftH = getTreeHeight(node->left);
        int rightH = getTreeHeight(node->right);
 
        return max(leftH, rightH) + 1;       
    }
    
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> ans;
        
        if(!root)
            return ans;
        
        int levels = getTreeHeight(root);
        
        queue<TreeNode*> q;
        
        q.push(root);
               
        ans.resize(levels);
        int cur_index = levels - 1;
        
        while(q.size()>0)
        {
            int qSize = q.size(); //gives num of nodes at same level

            vector<int> val(qSize, 0);

            //iterate through all nodes and add their kids
            for(int i = 0; i < qSize; i++) 
            {
                TreeNode * node = q.front();
                val[i] = node->val;

                if(node->left)
                    q.push(node->left);

                if(node->right)
                    q.push(node->right);

                //pop the node just processed
                q.pop(); //removes the node from Q
            }

            ans[cur_index]= val; 
            cur_index--;
        }
        
        return ans;
    }
};

//recursive (nop queue) solution of above

class Solution {
public:
    void rec(TreeNode* root, int level) {
        if (!root) return;
        res[depth - level - 1].push_back(root->val);
        rec(root->left, level+1);
        rec(root->right, level+1);
    }
    
    int getDepth(TreeNode* root) {
        if (!root) return 0;
        return max(getDepth(root->left), getDepth(root->right)) + 1;
    }
    
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        depth = getDepth(root);
        res.assign(depth, {});
        rec(root, 0);
        return res;
    }
    
private:
    vector<vector<int>> res;
    int depth;
};

//Two Heaps
//https://leetcode.com/problems/find-median-from-data-stream/
class MedianFinder {
public:
    priority_queue<int, vector<int>, less<int>> qMax; // Max priority queue
    priority_queue<int, vector<int>, greater<int>> qMin; //Min priority queue
    
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        int nMin = qMin.size();
        int nMax = qMax.size();
        
        if (nMin == 0 || qMax.top() > num) {
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