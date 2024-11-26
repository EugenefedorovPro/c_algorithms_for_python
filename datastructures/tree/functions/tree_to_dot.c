#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../declarations.h"

// turn negative integer (-30) to string with prepending anderscore ("_30")
// if int is positive or 0 returns int as string
char *get_node_name(int number) {
    char *str = malloc(sizeof(char) * 30);
    if (str == NULL) {
        fprintf(stderr, "memory allocation failed for str");
        return NULL;
    }
    if (number < 0) {
        sprintf(str, "_%d", abs(number));
    } else {
        sprintf(str, "%d", number);
    }

    return str;
}

void print_nodes(Node *node, FILE *stream, size_t *idx) {
    if (node == NULL) return;

    // Determine the color and style for the node
    const char *color = (node->color == BLACK) ? "black" : "red";
    const char *fillcolor = (node->color == BLACK) ? "black" : "red";

    fprintf(stream,
            "    n%s [label=\"%d\", color=\"%s\", fillcolor=\"%s\", style=filled];\n",
            get_node_name(node->key),
            node->key,
            color,
            fillcolor);

    // Handle left child
    if (node->left) {
        fprintf(stream, "    n%s -> n%s\n", get_node_name(node->key), get_node_name(node->left->key));  //
        print_nodes(node->left, stream, idx);
    } else {
        fprintf(stream, "    null%zu [shape=point];\n", (*idx)++);
        fprintf(stream, "    n%s -> null%zu\n", get_node_name(node->key), *idx - 1);
    }

    // Handle right child
    if (node->right) {
        fprintf(stream, "    n%s -> n%s\n", get_node_name(node->key), get_node_name(node->right->key));  //
        print_nodes(node->right, stream, idx);
    } else {
        fprintf(stream, "    null%zu [shape=point];\n", (*idx)++);
        fprintf(stream, "    n%s -> null%zu\n", get_node_name(node->key), *idx - 1);
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
