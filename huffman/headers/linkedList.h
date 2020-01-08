#pragma once
#include <pch.h>
#include "structs.h"

/*
 * ine: interface equivalent
 * stt: status token table
 * stin: status token input
*/

/// @brief Group of functions used for interfacing
typedef struct inters
{
    int  (*compar  )(const void*, const void*);
    int  (*equcmp  )(const void*, const void*);
    void*(*get_vals)(const void*);
    void*(*nextp   )(const void*);
    void**(*nextptr)(const void*);
} inters, interface;

/**
 * @param stt : the start of the list
 * @param stin: node to be added
 * @param ine : funcitons that access list values
 */
void insert_sorted(void** stt, void* stin, inters* ine);

void clean_list(void* stt, void*(*nextp)(const void*));