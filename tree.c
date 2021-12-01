#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "stack.h"


Node* node_new(int value, Node* left, Node* right)
{
    Node* n     = (Node *) malloc(sizeof(Node));
    n->value    = value;
    n->left     = left;
    n->right    = right; 
    return n;
}

void node_print(Node* n, int depth)
{
    if (n == NULL) return;
    for (int i = 0; i < depth; i++) putc(' ', stdout);
    printf("%d\n", n->value);
    node_print(n->left, depth + 1);
    node_print(n->right, depth + 1);
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

void node_replace_prefix_occurence(char* p, int i, Sides side)
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

void node_stringify_child(Node* n, Stack* lines, char* prefix, Sides side)
{
    size_t plen = strlen(prefix) + 2;
    char* p = malloc(sizeof(char) * plen);
    strcpy(p, prefix);
    for (int i = 0; i < plen - 1; i++) node_replace_prefix_occurence(p, i, side);
    side ? strcat(p, "\\-") : strcat(p, "/-");
    node_stringify(side ? n->left : n->right, lines, p);
    free(p);
}

void node_stringify(Node* n, Stack* lines, char* prefix)
{
    if (n->right != NULL) node_stringify_child(n, lines, prefix, RIGHT);
    char* p = malloc(sizeof(char) * (strlen(prefix) + 16));
    sprintf(p, "%s%d", prefix, n->value);
    stack_push(lines, p);
    if (n->left != NULL) node_stringify_child(n, lines, prefix, LEFT);
}

void node_print_fancy(Node* tree)
{
    Stack* lines = stack_new(1000);
    node_stringify(tree, lines, "");
    for (int i = 1; i < lines->index+1; i++)
        printf("%s\n", (char*) lines->stack[i]);
    stack_free(lines);
}

void node_swap_children(Node* n)
{
    Node* tmp = n->left;
    n->left = n->right;
    n->right = tmp;
}

void node_recursive_revert(Node* n)
{
    if (n == NULL) return;
    node_swap_children(n);
    node_recursive_revert(n->left);
    node_recursive_revert(n->right);
}

void node_stack_revert(Node* tree)
{
    Stack* s = stack_new(1000);
    stack_push(s, tree);
    while (s->index > 0) 
    {
        Node* n = (Node *) stack_pop(s);
        if (n == NULL) continue;
        node_swap_children(n);
        stack_push(s, n->left);
        stack_push(s, n->right);
    }
}

void* node_free(Node* n)
{
    if (n == NULL) return NULL;
    n->left = node_free(n->left);
    n->right = node_free(n->right);
    free(n);
    return NULL;
}
