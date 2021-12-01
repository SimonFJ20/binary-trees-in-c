#include <stdio.h>

#include "tree.h"

int main()
{

    Node* tree = node_new(5,
        node_new(4, NULL, NULL),
        node_new(6,
            node_new(5, NULL, NULL),
            node_new(7, NULL, NULL)
        )    
    );
    
    node_print(tree, 0);
    node_recursive_revert(tree);
    node_print(tree, 0);
    node_stack_revert(tree);
    node_print(tree, 0);
    node_print(tree, 0);
    node_print_fancy(tree);
    node_free(tree);
}



