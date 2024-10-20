#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

Stack *create_stack_item(Node *node) {
    Stack *item = malloc(sizeof(Stack));
    item->node = node;
    item->next = NULL;
    return item;
}

void s_append(Stack **stack, Node *node) {
    if (*stack == NULL) {
        *stack = create_stack_item(node);
        return;
    }

    Stack *item = create_stack_item(node);
    item->next = *stack;
    *stack = item;
}

int is_stack_empty(Stack **stack) {
    return *stack == NULL;
}

Node *s_pop(Stack **stack) {
    if (is_stack_empty(stack)) {
        return NULL;
    }
    Stack *temp = *stack;
    Node *node_to_pop = (*stack)->node;
    *stack = temp->next;
    free(temp);
    return node_to_pop;
}
