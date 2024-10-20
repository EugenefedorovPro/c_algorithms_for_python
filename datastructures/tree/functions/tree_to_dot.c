#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

void print_nodes(Node *node, FILE *stream, size_t *idx) {
    if (node == NULL) return;

    // Determine the color and style for the node
    const char *color = (node->color == BLACK)? "black" : "red";
    const char *fillcolor = (node->color == BLACK)? "black" : "red";

    fprintf(stream, "    n%d [label=\"%d\", color=\"%s\", fillcolor=\"%s\", style=filled];\n",
            node->data, node->data, color, fillcolor);

    // Handle left child
    if (node->left) {
        fprintf(stream, "    n%d -> n%d\n", node->data, node->left->data);
        print_nodes(node->left, stream, idx);
    } else {
        fprintf(stream, "    null%zu [shape=point];\n", (*idx)++);
        fprintf(stream, "    n%d -> null%zu\n", node->data, *idx - 1);
    }

    // Handle right child
    if (node->right) {
        fprintf(stream, "    n%d -> n%d\n", node->data, node->right->data);
        print_nodes(node->right, stream, idx);
    } else {
        fprintf(stream, "    null%zu [shape=point];\n", (*idx)++);
        fprintf(stream, "    n%d -> null%zu\n", node->data, *idx - 1);
    }
}

void tree_to_dot(Node *root) {
    FILE *stream = fopen("tree.dot", "w");
    if (stream == NULL) {
        fprintf(stderr, "ERROR: stream failed to open");
        return;
    }

    fprintf(stream, "digraph BinaryTree {\n");
    fprintf(stream,
            "    node [shape=box, style=filled, fontname=Helvetica, fontweight=bold, "
            "fontcolor=white, fontsize=24];\n");

    size_t idx = 0;
    print_nodes(root, stream, &idx);

    fprintf(stream, "\n}");

    fclose(stream);
}
