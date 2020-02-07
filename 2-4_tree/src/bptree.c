#include "bptree.h"

#define EMPTY INT_MAX

#define set_emtpy(ptr) ptr = EMPTY

bpnode* bpnode_create()
{
    bpnode* node = (bpnode*)calloc(1, sizeof(bpnode));
    logerr_calloc(node);

    for (int i = 0; i < BPSIZE; i++) // setting memory to EMPTY
        node->keys[i] = EMPTY;
    
    return node;
}

bpnode* get_val(bpnode* node)
{
    return (void*)0;
}

bool is_leaf(bpnode* node)
{
    return node->childs[0] == nullptr ? 1 : 0;
}

bool bpnode_full(bpnode* node)
{
    return node->used >= BPSIZE;
}

bool no_parent(bpnode* node)
{
    return node->parent == nullptr;
}

void arr_shift_right(int arr[], int idx, int size)
{
    for (int j = size-1; j >= idx; j--)
    { // shifiting key values to right
        arr[j] = arr[j-1];
    }
}

void arr_shift_right_childs(bpnode** arr, int idx, int size)
{
    for (int i = size; i >= idx; i--)
    {
        arr[i] = arr[i-1];
    }
}

// insert value inside bptree leaf
int bpnode_insert_here(bpnode* node, int val)
{
    node->used++; // updating the used count

    int i = 0;
    if (val <= node->keys[0])
    { // cheking if it fits at start
        arr_shift_right(node->keys, 0, BPSIZE);
        node->keys[0] = val;
    }
    else if (val >= node->keys[BPSIZE-1])
    { // cheking if it fits at end
        i = BPSIZE-1;
        node->keys[i] = val;
    }
    else
    { // cheking if it fits between some number
        for (; i < BPSIZE; i++)
        {
            if (val >= node->keys[i] && val <= node->keys[i+1])
            {
                ++i;
                arr_shift_right(node->keys, i, BPSIZE);
                node->keys[i] = val;
                break;
            }
        }
    }

    return i; // returns the index in which the item was added
}

void bpnode_split(bpnode** root)
{
    bpnode* node = *root;

    int split = ceil(((float)BPSIZE-1) / 2);
    
    bpnode* right = bpnode_create(0);

    int i = 0;
    node->used -= BPSIZE - split; // updating the used variable
    right->used += BPSIZE - split - 1;
    for (int idx = split + 1; idx < BPSIZE; i++, idx++)
    { // getting keys and childs ptrs to right node
        right->keys[i] = node->keys[idx];
        right->childs[i] = node->childs[idx];
        node->keys[idx] = EMPTY;
        node->childs[idx] = nullptr;
    }
    right->childs[i] = node->childs[BPSIZE];
    node->childs[BPSIZE] = nullptr;

    if (no_parent(node))
    {
        bpnode* new_node = bpnode_create();
        bpnode_insert_here(new_node, node->keys[split]);
        node->keys[split] = EMPTY;
        new_node->childs[0] = node;
        new_node->childs[1] = right;

        right->parent = new_node;
        node->parent = new_node;

        *root = new_node;
    }
    else
    {
        int split_key = node->keys[split];
        int idx = bpnode_insert_here(node->parent, split_key) + 1;
        arr_shift_right_childs(node->parent->childs, idx, BPSIZE);
        node->parent->childs[idx] = right;
        node->keys[split] = EMPTY;
    }
}

void bpnode_add_val(bpnode** root, int val)
{
    bpnode* node = *root;
    if (is_leaf(node))
    {
        bpnode_insert_here(node, val);
    }
    else
    {
        int size = node->used;
        if (val <= node->keys[0])
        {
            bpnode_add_val(&(*root)->childs[0], val);
        }
        else if (val >= node->keys[size-1])
        {
            bpnode_add_val(&(*root)->childs[size], val);
        }
        else
        {
            for (int i = 0; i < size; i++)
            {
                if ((val >= node->keys[i] && val <= node->keys[i+1]))
                {
                    bpnode_add_val(&(*root)->childs[i+1], val);
                    break;
                }
            }
        }
    }

    if (bpnode_full(node))
    {
        bpnode_split(root);
    }
}

void bpnode_print_current(bpnode* node)
{
    for (int i = 0; i < BPSIZE; i++)
    {
        if (node->keys[i] != EMPTY)
            printf("%i ", node->keys[i]);
    }

    printf("used: %i", node->used);
}

void bpnode_print_tree(bpnode* node)
{
    for (int i = 0; i < BPSIZE; i++)
    {
        if (node->childs[i] != nullptr)
        {
            bpnode_print_tree(node->childs[i]);
        }
        int key = node->keys[i];
        if (key != EMPTY)
        {
            printf("%i ", key);
        }
    }
}

void bpnode_childs_current(bpnode* node)
{
    int size = BPSIZE-1;
    for (int i = 0; i < size; i++)
    {
        printf("%p ", node->childs[i]);
    }
    printf("%p\n", node->childs[size]);
}

void free_bptree(bpnode* root)
{
    for (int i = 0; i < BPSIZE; i++)
    {
        if (root->childs[i] == nullptr)
        {
            break;
        }
        free_bptree(root->childs[i]);
        // free(root);
    }
    free(root);
    root = nullptr;
}