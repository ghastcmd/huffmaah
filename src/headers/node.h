#pragma once

typedef struct node
{
    int val;
    int freq;
    struct node* next;
    struct node* left;
    struct node* right;
} node;