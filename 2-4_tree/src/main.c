#include "pch.h"
#include "bptree.h"

#define deb_print(ptr, msg) if (ptr) {\
    puts(msg);\
    bpnode_print_current(ptr);\
    puts("");\
}

int main()
{
    bpnode* tree = bpnode_create();

    bpnode_add_val(&tree, 10);
    bpnode_add_val(&tree, 20);
    bpnode_add_val(&tree, 5);
    bpnode_add_val(&tree, 4);
    bpnode_add_val(&tree, 2);
    bpnode_add_val(&tree, 30);
    bpnode_add_val(&tree, 40);
    bpnode_add_val(&tree, 21);
    bpnode_add_val(&tree, 12);
    bpnode_add_val(&tree, 50);
    bpnode_add_val(&tree, 28);
    bpnode_add_val(&tree, 14);
    bpnode_add_val(&tree, 24);
    bpnode_add_val(&tree, 44);
    bpnode_add_val(&tree, 17);
    bpnode_add_val(&tree, 18);

    deb_print(tree, "root");

    deb_print(tree->childs[0], "first");
    deb_print(tree->childs[1], "second");
    deb_print(tree->childs[2], "third");
    deb_print(tree->childs[3], "fourth");

    bpnode_childs_current(tree);

    puts("");
    bpnode_print_tree(tree);
    printf("\b\n"); 

    free_bptree(tree);
    puts("working...");
}