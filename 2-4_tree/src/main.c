#include "pch.h"
#include "bptree.h"

#define deb_print(ptr) if (ptr) {\
    bpnode_print_current(ptr);\
    puts("");\
}

#define deb_childs(ptr) if (ptr) {\
    bpnode_childs_current(ptr);\
}

#define deb_all_childs(ptr) {\
    for (int i = 0; i < BPSIZE; i++)\
    {\
        if (ptr->childs[i] != nullptr)\
        {\
            printf("%i node: ", i);\
            bpnode_print_current(ptr->childs[i]);\
            puts("");\
        }\
    }\
}

#if 0
int main()
{
    bpnode* tree = bpnode_create();

    for (int i = 1; i <= 10; i++)
    {
        bpnode_add_val(&tree, i);
    }

    bpnode_print_tree(tree);
    puts("");
    int qnt = 0;
    bpnode_get_qnt(tree, &qnt);
    for (int i = 1; i <= qnt; i++)
    {
        bpnode* node = bpnode_find_node(tree, i);
        if (node)
        printf("%2i: %p\n", i, node->parent);
    }

    puts("");
    bpnode_print_tree(tree);
    puts("");

    // for (int i = qnt; i >= 1; i--)
    // {
    //     bpnode_remove(&tree, i);
    //     bpnode_print_tree(tree);
    //     puts("");
    // }

    bpnode_childs_current(tree);
    bpnode_print(tree);
    bpnode_print(tree->childs[0]);
    bpnode_print(tree->childs[1]);
    bpnode_print(tree->childs[2]);
    bpnode_print(tree->childs[3]);

    for (int i = qnt; i >= 1; i--)
    {
        bpnode_remove(&tree, i);

        bpnode_childs_current(tree);
        deb_print(tree);
        deb_print(tree->childs[0]);
        deb_print(tree->childs[1]);
        deb_print(tree->childs[2]);
        deb_print(tree->childs[3]);

        bpnode_print_tree(tree);
        puts("");
    }

    puts("cleaning...");

    free_bpnode(tree);
}
#else
int main()
{
    bpnode* tree = bpnode_create();

    bpnode_add_val(&tree, 2);
    bpnode_add_val(&tree, 10);
    bpnode_add_val(&tree, 20);
    bpnode_add_val(&tree, 5);
    bpnode_add_val(&tree, 4);
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

    deb_print(tree);
    deb_print(tree->childs[0]);
    deb_print(tree->childs[1]);
    deb_print(tree->childs[2]);
    deb_print(tree->childs[3]);

    puts("finding test");
    int val = 2;
    printf("%i %i\n", val, bpnode_search(tree, val));

    puts("found node");
    bpnode* found = bpnode_find_node(tree, val);
    bpnode_print_current(found);

    puts("\nroot ptrs");
    bpnode_childs_current(tree);

    puts("inorder print");
    bpnode_print_tree(tree);
    printf("\b\n");

    puts(">> searching node");
    bpnode* tmp_node = bpnode_find_node(tree, 44);
    printf("tmp_node parent: %p\n", tmp_node->parent);
    deb_print(tmp_node);
    deb_childs(tmp_node);

    puts(">> removed val");
    bpnode_remove(&tree, 10);
    bpnode_remove(&tree, 50);
    bpnode_remove(&tree, 30);
    bpnode_remove(&tree, 21);
    bpnode_remove(&tree, 2);
    bpnode_remove(&tree, 5);
    bpnode_remove(&tree, 4);
    bpnode_remove(&tree, 14);
    bpnode_remove(&tree, 12);
    bpnode_remove(&tree, 20);

    puts("");
    bpnode_print_tree(tree);
    puts("<< out");

    bpnode_childs_current(tree);
    bpnode_print(tree);
    bpnode_print(tree->childs[0]);
    bpnode_print(tree->childs[1]);
    bpnode_print(tree->childs[2]);
    bpnode_print(tree->childs[3]);

    deb_childs(tree->childs[0]);
    deb_childs(tree->childs[1]);
    deb_childs(tree->childs[2]);
    deb_childs(tree->childs[3]);

    bpnode_remove(&tree, 24);

    bpnode_childs_current(tree);
    bpnode_print(tree);
    bpnode_print(tree->childs[0]);
    bpnode_print(tree->childs[1]);
    bpnode_print(tree->childs[2]);
    bpnode_print(tree->childs[3]);

    deb_childs(tree->childs[0]);
    deb_childs(tree->childs[1]);
    deb_childs(tree->childs[2]);
    deb_childs(tree->childs[3]);

    puts(">> before removing root");
    bpnode_childs_current(tree);
    bpnode_print(tree);
    bpnode_print(tree->childs[0]);
    bpnode_print(tree->childs[1]);
    bpnode_print(tree->childs[2]);
    bpnode_print(tree->childs[3]);

    puts("complete tree: ");
    bpnode_print_tree(tree);
    puts("");

    bpnode_remove(&tree, 28);

    bpnode* node44 = bpnode_find_node(tree, 44);
    bpnode_print_current(node44);
    puts("");

    bpnode_remove(&tree, 44);

    // bpnode_print_current(node44);
    // puts("");

    // bpnode* node00 = bpnode_find_node(tree, 0);
    // bpnode_print_current(node00);
    // puts("");

    // bpnode_remove(tree, 18);

    printf(">> %p\n", bpnode_find_node(tree, 44));

    puts("inorder print");
    bpnode_print_tree(tree);
    printf("\b\n");

    puts("root ptrs");
    bpnode_childs_current(tree);

    bpnode_print_current(tree);
    puts("");

    puts("printing childs");
    deb_print(tree->childs[0]);
    deb_print(tree->childs[1]);

    bpnode_print_tree(tree);
    puts("");

    puts("working...");
    free_bpnode(tree);
}
#endif