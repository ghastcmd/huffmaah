#pragma once

// a list of tree nodes
typedef struct lstree
{
    int val;
    int freq;
    struct lstree* next;
    struct lstree* left;
    struct lstree* right;
} lstree;

typedef struct tuple
{
    int st0, st1;
} tuple;