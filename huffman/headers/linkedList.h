#pragma once
#include <pch.h>
#include "structs.h"

/**
 * * *********************************************************** *
 * * This object contains interfaces for utilizing a linked list *
 * * *********************************************************** *
 * 
 * @ine:  interface equivalent
 * @stt:  status token table
 * @stin: status token input
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
 * @param stt : the start of the list
 * @param stin: node to be added
 * @param ine : funcitons that access list values
 */
void ListInsertSorted(void** stt, void* stin, inters* ine);

/**
 * @brief: prints the list
 * @param stt: head of list
 * @param get_value: the get_value interface for stt structure
 * @param netp: gets the next pointer for stt structure
 */
void ListPrint(void* stt, int(*get_value)(const void*), void*(*nextp)(const void*));

/**
 * @brief: frees the memory of the list
 * @param stt: list head
 * @param nextp: interface to get stt->next pointer
 */
void ListFree(void* stt, void*(*nextp)(const void*));

/**
 * @brief: remove first element of list and returns it
 * @param stt: pointer of pointer of head of list
 * @ret: pointer to start of list
 */
void* ListPop(void** stt);