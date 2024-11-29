import tree_module

# Create a new Red-Black Tree
tree = tree_module.create_tree()
print("Tree created:", tree)

# Insert some nodes into the tree
tree_module.insert_rbt(tree, 10, "Value10")
tree_module.insert_rbt(tree, 20, "Value20")
tree_module.insert_rbt(tree, 15, "Value15")

# Search for a node
result = tree_module.search_rbt(tree, 15)
print("Search for key 15:", result)

# Traverse the tree in level order
print("Level order traversal:")
tree_module.traverse_level_order(tree)

# Remove a node
tree_module.remove_rbt(tree, 15)
print("Key 15 removed.")

# Traverse again to see the changes
print("Level order traversal after removal:")
tree_module.traverse_level_order(tree)
