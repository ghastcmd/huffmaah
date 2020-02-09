#pragma once
#include "pch.h"

#define BPSIZE 4

#define bpnode_print(node) if (node) {\
    bpnode_print_current(node);\
    puts("");\
}

typedef struct bpnode
{
    struct bpnode* parent;
    int used;
    int keys[BPSIZE];
    struct bpnode* childs[BPSIZE+1];
} bpnode;

bpnode* bpnode_create();

void bpnode_add_val(bpnode** root, int val);

void bpnode_print_current(bpnode* node);

void bpnode_print_tree(bpnode* node);

void bpnode_get_qnt(bpnode* node, int* qnt);

void bpnode_childs_current(bpnode* node);

void free_bpnode(bpnode* root);

bool bpnode_search(bpnode* node, int val);

bpnode* bpnode_find_node(bpnode* node, int val);

void bpnode_remove(bpnode** root, int val);