#pragma once

// A list of tree nodes
typedef struct lstree
{
    void* val;
    int64_t freq;
    struct lstree* next;
    struct lstree* left;
    struct lstree* right;
} lstree;

typedef struct tuple
{
    int64_t st0;
    int64_t st1;
} tuple;