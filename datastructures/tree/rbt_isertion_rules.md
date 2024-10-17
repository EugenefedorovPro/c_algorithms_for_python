# Insertion in a Red-Black Tree

To insert a node into a red-black tree, you must follow specific rules and steps to ensure the tree maintains its balancing properties.

## General Properties of a Red-Black Tree

Before diving into the insertion rules, here are the key properties that a red-black tree must satisfy:

- **Red/Black Property:** Every node is either red or black.
- **Root Property:** The root node is always black.
- **Leaf Property:** All leaf nodes (NULL nodes) are black.
- **Red Property:** If a node is red, then both its children must be black.
- **Depth Property:** For any node, all paths from the node to its descendant leaves contain the same number of black nodes.

## Steps for Insertion in a Red-Black Tree

### 1. Check if the Tree is Empty

- If the tree is empty, insert the new node as the root node and color it black.

### 2. Perform Standard BST Insertion

- Insert the new node as a leaf node using the standard binary search tree (BST) insertion algorithm.
- Color the new node red.

### 3. Assign Parent and Children

- Assign the parent of the leaf node as the parent of the new node.
- If the leaf key is greater than the new key, make the new node the left child; otherwise, make it the right child.
- Assign NULL to the left and right children of the new node.

### 4. Check and Fix Red-Black Properties

After insertion, check if the red-black properties are violated. Specifically, check if the parent of the new node is red.

#### Case 1: Parent is Black

- If the parent of the new node is black, the tree is still valid, and no further action is needed.

#### Case 2: Parent is Red

- If the parent of the new node is red, this violates the red property.
  - **Case 2a: Uncle is Red**
    - If the uncle of the new node (the sibling of the parent) is red, recolor the parent and the uncle to black, and recolor the grandparent to red.
    - Move up the tree by setting the new node to the grandparent and repeat the process if necessary.
  - **Case 2b: Uncle is Black or NULL**
    - If the uncle is black or NULL, there are two subcases based on the position of the new node relative to its parent and grandparent.
      - **Left-Left Case:**
        - If the new node is the left child of its parent and the parent is the left child of the grandparent, perform a right rotation at the grandparent.
        - Recolor the parent to black and the grandparent to red.
      - **Left-Right Case:**
        - If the new node is the right child of its parent and the parent is the left child of the grandparent, perform a left rotation at the parent followed by a right rotation at the grandparent.
        - Recolor the new node (which is now the left child of the grandparent) to black and the grandparent to red.
      - **Right-Right Case:**
        - If the new node is the right child of its parent and the parent is the right child of the grandparent, perform a left rotation at the grandparent.
        - Recolor the parent to black and the grandparent to red.
      - **Right-Left Case:**
        - If the new node is the left child of its parent and the parent is the right child of the grandparent, perform a right rotation at the parent followed by a left rotation at the grandparent.
        - Recolor the new node (which is now the right child of the grandparent) to black and the grandparent to red.

### 5. Final Check and Adjustment

After fixing any violations, ensure the root of the tree is black. If it is not, recolor it to black.

## Algorithm Summary

Here is a concise summary of the steps:

### 1. Check if Tree is Empty
   - If empty, insert as root and color black.

### 2. Perform BST Insertion
   - Insert as a red leaf node.

### 3. Assign Parent and Children
   - Set parent and children accordingly.

### 4. Check and Fix Red-Black Properties
   - If parent is black, exit.
   - If parent is red, handle violations using Cases 2a and 2b.

### 5. Final Check and Adjustment
   - Ensure the root is black.

By following these steps, you ensure that the red-black tree remains balanced and satisfies all its properties after each insertion.

## Example Walkthrough

To illustrate this process, consider inserting the elements 1, 2, 3, 4, 5, 6, and 7 into an empty red-black tree.

### Inserting 1
- The tree is empty, so insert 1 as the root node and color it black.
