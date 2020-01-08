#pragma once
#include <pch.h>
#include "structs.h"

/**
 * * *********************************************************** *
 * * This object contains interfaces for utilizing a linked list *
 * * *********************************************************** *
 * 
 * @ine:  interface equivalent
 * @stn:  standard token normal
 * @stin: standard token input
*/

/// @brief Group of functions used for interfacing
typedef struct inters
{
    int  (*compar  )(const void*, const void*);
    int  (*equcmp  )(const void*, const void*);
    void*(*nextp   )(const void*);
    void**(*nextptr)(const void*);
} inters, interface;

/**
 * @param stn : the start of the list
 * @param stin: node to be added
 * @param ine : funcitons that access list values
 */
void ListInsertSorted(void** stn, void* stin, inters* ine);

/**
 * @brief: prints the list
 * @param stn: head of list
 * @param get_value: the get_value interface for stn structure
 * @param netp: gets the next pointer for stn structure
 */
void ListPrint(void* stn, int(*get_value)(const void*),  void*(*nextp)(const void*));

/**
 * @brief: frees the memory of the list
 * @param stn: list head
 * @param nextp: interface to get stn->next pointer
 */
void ListFree(void* stn,  void*(*nextp)(const void*));

/**
 * @brief: remove first element of list and returns it
 * @param stn: pointer of pointer of head of list
 * @ret: pointer to start of list
 */
void* ListPop(void** stn, void*(*nextp)(const void*));