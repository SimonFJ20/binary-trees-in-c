#ifndef TREE_H
#define TREE_H

#include "stack.h"

typedef struct 
{
    int value;
    void* left;
    void* right;
}
Node;

typedef enum
{
    LEFT = 1,
    RIGHT = 0
} 
Sides;

Node*   node_new(int value, Node* left, Node* right);
void*   node_free(Node* n);

void    node_print(Node* n, int depth);
void    node_replace_prefix_occurence(char* p, int i, Sides side);
void    node_stringify_child(Node* n, Stack* lines, char* prefix, Sides side);
void    node_stringify(Node* n, Stack* lines, char* prefix);
void    node_print_fancy(Node* tree);
void    node_swap_children(Node* n);
void    node_recursive_revert(Node* n);
void    node_stack_revert(Node* tree);

#endif