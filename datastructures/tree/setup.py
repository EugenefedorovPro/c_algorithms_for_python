from setuptools import setup, Extension

# Define the module
tree_module = Extension(
    'tree_module',  # Name of the module
    sources=[
        '../../sorting/functions/quick.c',
        './functions/free_tree_debug.c',
        './functions/copy_array_int.c',
        './functions/initiate_tree_debug.c',
        './functions/copy_tree.c',
        './functions/rbt_utils.c',
        './functions/remove_rbt.c',
        './functions/insert_bst.c',
        './functions/create_node.c',
        './functions/create_binary_search_tree.c',
        './functions/queue.c',
        './functions/create_binary_tree.c',
        './functions/free_tree.c',
        './functions/traverse_preorder.c',
        './functions/heapify.c',
        './functions/traverse_level_order.c',
        './functions/tree_to_dot.c',
        './functions/insert_rbt.c',
        './functions/stack.c',
        './functions/search_rbt.c',
        'python_api.c'
    ],
    # include_dirs=['.'],  # Include directory for `declarations.h`
)

# Setup function
setup(
    name='tree_module',
    version='1.0',
    description='Python wrapper for a Red-Black Tree implementation in C',
    ext_modules=[tree_module],
)
