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

void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void arr_shift_right(int arr[], int idx, int size)
{
    for (int j = size-1; j >= idx; j--)
    { // shifiting key values to right
        arr[j] = arr[j-1];
    }
}

void arr_shift_left(int arr[], int idx, int size)
{
    for (int i = idx; i < size-1; i++)
    {
        arr[i] = arr[i+1];
    }
}

void arr_shift_right_childs(bpnode** arr, int idx, int size)
{
    for (int i = size; i >= idx; i--)
    {
        arr[i] = arr[i-1];
    }
}

void arr_shift_left_childs(bpnode** arr, int idx, int size)
{
    for (int i = idx; i <= size; i++)
    {
        arr[i] = arr[i+1];
    }
}

int arr_search_val(int* arr, int val, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == val)
        {
            return i;
        }
    }
    return -1;
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
            printf("%2i ", key);
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

void free_bpnode(bpnode* root)
{
    for (int i = 0; i < BPSIZE; i++)
    {
        if (root->childs[i] == nullptr)
        {
            break;
        }
        free_bpnode(root->childs[i]);
        // free(root);
    }
    free(root);
    root = nullptr;
}

void _bpnode_search(bpnode* node, int val, bool* ret, bpnode** ret_node)
{
    if (*ret) return;
    for (int i = 0; i < BPSIZE; i++)
    {
        if (node->childs[i] != nullptr)
        {
            _bpnode_search(node->childs[i], val, ret, ret_node);
        }
        if (node->keys[i] == val)
        {
            *ret = true;
            *ret_node = node;
        }
    }
}

bool bpnode_search(bpnode* node, int val)
{
    bool ret = false;
    bpnode* al = nullptr;
    _bpnode_search(node, val, &ret, &al);
    return ret;
}

bpnode* bpnode_find_node(bpnode* node, int val)
{
    bool ret = false;
    bpnode* al = nullptr;
    _bpnode_search(node, val, &ret, &al);
    return al;
}

void bpnode_remove_here(bpnode* node, int val)
{
    for (int i = 0; i < BPSIZE; i++)
    {
        if (node->keys[i] == val)
        {
            arr_shift_left(node->keys, i, BPSIZE);
            break;
        }
    }
}

int bpnode_get_interval(bpnode* node, int val, int idx)
{
    if (val >= node->parent->keys[idx])
    {
        idx++;
    }
    return idx;
}

bpnode* bpnode_swap_succ(bpnode* node, int idx)
{
    bpnode* current = node->childs[idx + 1];
    while(!is_leaf(current))
    {
        current = current->childs[0];
    }

    swap(&current->keys[0], &node->keys[idx]);
    return current;
}

bpnode* bpnode_get_neighbour(bpnode* node, int interval)
{
    if (interval == 0)
    {
        return node->parent->childs[1];
    }
    else
    {
        return node->parent->childs[interval - 1];
    }
}

int bpnode_pop_right_key(bpnode* node)
{
    node->used--;
    int key = 0;
    for (int i = BPSIZE; i > 0; i--)
    {
        if ((key = node->keys[i]) != EMPTY)
        {
            node->keys[i] = EMPTY;
            break;
        }
    }
    return key;
}

int bpnode_pop_left_key(bpnode* node)
{
    node->used--;
    int key = node->keys[0];
    arr_shift_left(node->keys, 0, BPSIZE);
    return key;
}

void bpnode_transfer(bpnode* node, bpnode* neighbour, bool left)
{
    int nbhd_key = 0, prnt_key = 0;
    if (left)
    {
        nbhd_key = bpnode_pop_right_key(neighbour);
        prnt_key = bpnode_pop_right_key(node->parent);
    }
    else
    {
        nbhd_key = bpnode_pop_left_key(neighbour);
        prnt_key = bpnode_pop_left_key(node->parent);
    }

    bpnode_insert_here(node->parent, nbhd_key);
    bpnode_insert_here(node, prnt_key);
}

void bpnode_fusion(bpnode* node, bpnode* neighbour, bool left, int itv)
{
    int key = 0;
    if (left)
    {
        key = bpnode_pop_right_key(node->parent);
        bpnode_insert_here(neighbour, key);
        neighbour->childs[neighbour->used] = node->childs[0];

        arr_shift_left_childs(node->parent->childs, itv, BPSIZE);
        free(node);
    }
    else
    {
        key = bpnode_pop_left_key(node->parent);
        arr_shift_right_childs(neighbour->childs, 0, BPSIZE);
        neighbour->childs[0] = node->childs[0];
        bpnode_insert_here(neighbour, key);

        arr_shift_left_childs(node->parent->childs, 0, BPSIZE);
        free(node);
    }
}

void bpnode_remove(bpnode* root, int val)
{
    bpnode* node = bpnode_find_node(root, val);
    if (!node) return;

    int idx = arr_search_val(node->keys, val, BPSIZE);
    if (!is_leaf(node))
    {
        node = bpnode_swap_succ(node, idx);
    }

    if (node->used > 1)
    {
        bpnode_remove_here(node, val);
        return;
    }

    int itv = bpnode_get_interval(node, val, idx);
    bpnode* nbhd = nullptr;
    {
        bpnode* tmp = node->parent;
        nbhd = itv == 0 ? tmp->childs[1] : tmp->childs[itv - 1];
    }

    if (nbhd->used > 1)
    { // if neighbour isn't a 2-node
        bpnode_transfer(node, nbhd, itv == idx);
    }
    else
    {
        bpnode_fusion(node, nbhd, itv == idx, itv);
    }
}