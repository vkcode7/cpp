Find the VM memory configuration in Azure resource tree that most closely matches a customer memory request. The VM configurations are organized in a binary search tree where smaller memory sizes branch left and larger sizes branch right. Given a customer floating-point memory requirement, efficiently traverse this tree and return the configuration that minimizes the absolute difference with the requested amount.

```py
def find_closest_vm_recursive(node, target, best_match):
    if node is None:
        return best_match

    # Calculate current absolute difference
    current_diff = abs(node.memory - target)
    
    # Update the closest match if this one is better
    if best_match is None or current_diff < abs(best_match.memory - target):
        best_match = node
    elif current_diff == abs(best_match.memory - target):
        # Tie-breaker: prefer the smaller configuration or prioritize based on logic
        pass

    # Traverse the BST
    if target < node.memory:
        return find_closest_vm_recursive(node.left, target, best_match)
    else:
        return find_closest_vm_recursive(node.right, target, best_match
```
