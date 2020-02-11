#pragma once
#include "pch.h"

struct node_heap {
    int item;
    int priority;
};

struct heap {
    struct node_heap *data;
    int size;
};

//if heap is null
int is_empty_heap (struct heap *heap);

//create struct heap with n numbers of nodes
struct heap *create_heap(int n);

//add node on heap
void enqueue_heap (struct heap *heap, int item, int priority, int n);

// swap two nodes
void swap (struct node_heap *node1, struct node_heap *node2);

//get the father node
int get_parent_index (int i);

//get the node left (child left)
int get_left_index (int i);

//get the node right (child right)
int get_right_index (int i);

// count number of verifications
void search_with_heap (struct heap *heap, int item, int priority, int index, int* count);