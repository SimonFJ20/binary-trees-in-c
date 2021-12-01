#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

typedef struct 
{
    int value;
    void* left;
    void* right;
}
Node;

Node* newNode(int value, Node* left, Node* right)
{
    Node* n     = (Node *) malloc(sizeof(Node));
    n->value    = value;
    n->left     = left;
    n->right    = right; 
    return n;
}

void print_node(Node* n, int depth)
{
    if (n == NULL) return;
    for (int i = 0; i < depth; i++) putc(' ', stdout);
    printf("%d\n", n->value);
    print_node(n->left, depth + 1);
    print_node(n->right, depth + 1);
}

/*
same thing expressed in Python

def sfj_stringifyNode(node: Node, lines: List[str], prefix: str = ''):
    if node.right:
        p = prefix.replace('└─', '│ ', -1).replace('┌─', '  ', -1) + '┌─'
        sfj_stringifyNode(node.right, lines, p)
    lines.append(prefix + str(node.value))
    if node.left:
        p = prefix.replace('└─', '  ', -1).replace('┌─', '│ ', -1) + '└─'
        sfj_stringifyNode(node.left, lines, p)

def sfj_printTree(tree: Node):
    lines = []
    sfj_stringifyNode(tree, lines)
    print('\n'.join(lines))
*/

typedef enum { LEFT = 1, RIGHT = 0 } Sides;

void stringify_node(Node* n, Stack* lines, char* prefix);

void replace_prefix_occurence(char* p, int i, Sides side)
{
    if (p[i] == '\\' && p[i + 1] == '-')
    {
        p[i] = side ? ' ' : '|';
        p[i + 1] = ' ';
    }
    else if (p[i] == '/' && p[i + 1] == '-')
    {
        p[i] = side ? '|' : ' ';
        p[i + 1] = ' ';
    }
}

void stringify_child_node(Node* n, Stack* lines, char* prefix, Sides side)
{
    size_t plen = strlen(prefix) + 2;
    char* p = malloc(sizeof(char) * plen);
    strcpy(p, prefix);
    for (int i = 0; i < plen - 1; i++) replace_prefix_occurence(p, i, side);
    side ? strcat(p, "\\-") : strcat(p, "/-");
    stringify_node(side ? n->left : n->right, lines, p);
    free(p);
}

void stringify_node(Node* n, Stack* lines, char* prefix)
{
    if (n->right != NULL) stringify_child_node(n, lines, prefix, RIGHT);
    char* p = malloc(sizeof(char) * (strlen(prefix) + 16));
    sprintf(p, "%s%d", prefix, n->value);
    stack_push(lines, p);
    if (n->left != NULL) stringify_child_node(n, lines, prefix, LEFT);
}

void print_tree_fancy(Node* tree)
{
    Stack* lines = newStack(1000);
    stringify_node(tree, lines, "");
    for (int i = 1; i < lines->index+1; i++)
        printf("%s\n", (char*) lines->stack[i]);
    stack_free(lines);
}

void swap_children(Node* n)
{
    Node* tmp = n->left;
    n->left = n->right;
    n->right = tmp;
}

void recursive_revert(Node* n)
{
    if (n == NULL) return;
    swap_children(n);
    recursive_revert(n->left);
    recursive_revert(n->right);
}

void stack_revert(Node* tree)
{
    Stack* s = newStack(1000);
    stack_push(s, tree);
    while (s->index > 0) 
    {
        Node* n = (Node *) stack_pop(s);
        if (n == NULL) continue;
        swap_children(n);
        stack_push(s, n->left);
        stack_push(s, n->right);
    }
}

void* free_node(Node* n)
{
    if (n == NULL) return NULL;
    n->left = free_node(n->left);
    n->right = free_node(n->right);
    free(n);
    return NULL;
}

int main()
{

    Node* tree = newNode(5,
        newNode(4, NULL, NULL),
        newNode(6,
            newNode(5, NULL, NULL),
            newNode(7, NULL, NULL)
        )    
    );
    
    print_node(tree, 0);
    recursive_revert(tree);
    print_node(tree, 0);
    stack_revert(tree);
    print_node(tree, 0);
    print_node(tree, 0);
    print_tree_fancy(tree);
    free_node(tree);
}



