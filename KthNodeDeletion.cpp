
Delete the kth node from the end of a singly linked list

Input: 1 -> 2 -> 3 -> 4 -> 5 -> null.    k = 2

Result: 1 -> 2 -> 3 -> 5 -> null

```cpp
struct ListNode {
  int val;
  ListNode * next;
  ListNode() : val(0), next(nullptr) {}
};


ListNode * reverse(ListNode * head)
{
  ListNode * prev = nullptr;
  ListNode * fwd = nullptr;
  ListNode * curr = head;

  //1-2-3-4-5

  while(curr != nullptr)
  {
      fwd = curr->next; //2-3
      curr->next = prev; //2-1-null
      prev = curr; //1-2
      curr = fwd; //2
  }

  return prev;

}

ListNode * RemoveNodeFromEnd(ListNode * head, int k)
{
  ListNode * newhead = reverse(head);
  newhead = RemoveNode(newhead, k);
  return reverse(newhead);
}

ListNode * RemoveNode(ListNode * head, int k)
{
  if(!head)
    return head;

  if(k == 1)
    return head->next;

  ListNode * prev = nullptr;
  ListNode * curr = head;
  int node_count = 1;

  while(node_count < k && curr != nullptr)
  {
    prev = curr;
    curr = curr->next;
    node_count++;
  }

  //1-2-3-4-5
  prev->next = curr->next;

  return head;
}
```
