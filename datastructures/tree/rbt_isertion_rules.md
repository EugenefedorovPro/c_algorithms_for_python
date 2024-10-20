# Balancing a Red-Black Tree After Insertion

In the Red-Black Tree, after inserting a new node, you must balance the tree if any of the Red-Black Tree properties are violated. Here’s a high-level overview of the next steps to balance the Red-Black Tree after insertion:

## Key Red-Black Tree Properties to Maintain:

1. **Property 1**: Every node is either red or black.
2. **Property 2**: The root is always black.
3. **Property 3**: All leaves (null nodes) are black.
4. **Property 4**: Red nodes cannot have red children (no two consecutive red nodes).
5. **Property 5**: Every path from a node to its descendant leaves has the same number of black nodes.

## Steps to Balance the Tree After Insertion:

When a new node is inserted, it is always red. To maintain the Red-Black Tree properties, especially the no two consecutive red nodes rule, you may need to perform the following steps:

### Case 1: Parent is Black

If the parent of the new node is black, the tree remains valid, and no further actions are needed.

### Case 2: Parent is Red, and Uncle is Red

- **Recoloring**: If the parent and the uncle of the new node are both red, you recolor the parent and the uncle to black, and recolor the grandparent to red. This may cause a violation further up the tree (if the grandparent's parent is also red), so you may need to recursively check and balance the tree from the grandparent upwards.

  This process ensures that no two consecutive red nodes exist but may propagate a violation up to the root.

### Case 3: Parent is Red, and Uncle is Black (or NULL)

- **Rotations**: If the parent is red and the uncle is black (or does not exist), you will need to perform rotations to fix the violation.

  - **Left-Left Case**: If the new node is a left child of its parent, and its parent is also a left child of the grandparent, a **right rotation** around the grandparent is required.
  - **Right-Right Case**: If the new node is a right child of its parent, and its parent is also a right child of the grandparent, a **left rotation** around the grandparent is required.
  - **Left-Right or Right-Left Case**: If the new node is on the opposite side of its parent (e.g., the new node is a right child of a left parent), you perform a **double rotation**: first rotate the parent and child, and then rotate the grandparent and new parent.

### Recoloring After Rotations

After performing rotations, you typically recolor the nodes to maintain the Red-Black Tree properties. This usually involves coloring the parent black and the grandparent red.

### Ensure the Root is Black

After all adjustments, if the root has been recolored to red during balancing, you need to recolor it black to satisfy **Property 2**.

## Example

From the `tree.dot` file you provided, let’s consider inserting a new node with data `25`:

- The parent (`n20`) is red, and the uncle (`null2`) is black (a null pointer is considered black).
- You will need to perform a rotation at the grandparent (`n15`) to fix the violation of two consecutive red nodes.
- After this, the tree will be balanced, and recoloring will occur based on the rotations performed.

## Conclusion

To balance a Red-Black Tree after insertion, you must check the color of the parent and uncle, and then either recolor or rotate depending on the scenario. These steps ensure that the Red-Black Tree properties are maintained, keeping the tree balanced for efficient operations.
