#pragma once
#include "pch.h"

#define BPSIZE 4

typedef struct bpnode
{
    struct bpnode* parent;
    int used;
    int keys[BPSIZE];
    struct bpnode* childs[BPSIZE+1];
} bpnode;

bpnode* get_val(bpnode* node);

bpnode* bpnode_create();

void bpnode_add_val(bpnode** _Ret_opt_count_, int val);

void bpnode_print_current(bpnode* node);

void bpnode_print_tree(bpnode* node);

void bpnode_childs_current(bpnode* node);

void free_bpnode(bpnode* root);

bool bpnode_search(bpnode* node, int val);