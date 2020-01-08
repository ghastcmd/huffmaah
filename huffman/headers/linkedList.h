#pragma once
#include <pch.h>
#include "structs.h"

// struct group of functions
// ..groups of interfaces
typedef struct intes
{
    int(*get_value)(const void*);
    void*(*get_values)(const void*);
    int(*compare)(const void*, const void*);
    void*(*create)(const void*);
} intes;

// @param head: the start of the list
// @param ine: funcitons that access list values
void insert_sorted(void* head, intes* ine);