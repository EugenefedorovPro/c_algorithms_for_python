#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

Stack *create_stack_item(Node *node) {
    Stack *item = malloc(sizeof(Stack));
    item->node = node;
    item->next = NULL;
    return item;
}

void free_stack(Stack **stack) {
    while (*stack) {
        s_pop(stack);
    }
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

void stack_size_recurse(Stack **stack, size_t *size) {
    if (is_stack_empty(stack)) {
        return;
    }

    (*size)++;
    stack_size_recurse(&((*stack)->next), size);
}

size_t get_stack_size(Stack **stack) {
    size_t size = 0;
    stack_size_recurse(stack, &size);
    return size;
}

void print_stack_recurse(Stack **stack) {
    if (is_stack_empty(stack)) {
        printf("\n*** end of the stack ***\n");
        return;
    }

    printf("\ndata = %d, color = %d\n", (*stack)->node->key, (*stack)->node->color);
    print_stack_recurse(&((*stack)->next));
}

void print_all_stack(Stack **stack) {
    printf("\n*** print all stack elements from top to bottom ***\n");
    print_stack_recurse(stack);
    printf("***\n");
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

Node *s_peek(Stack **stack) {
    if (is_stack_empty(stack)) {
        return NULL;
    }
    Node *node_to_peek = (*stack)->node;
    return node_to_peek;
}
