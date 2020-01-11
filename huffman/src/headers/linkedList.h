#pragma once
#include <pch.h>
#include "structs.h"

/**
 * * *********************************************************** *
 * * This object contains interfaces for utilizing a linked list *
 * * *********************************************************** *
 * 
 * @ine:  interface equivalent
 * @stn:  standard token node
 * @stnr: stantard token node reference
 * @stin: standard token input
 * @fmt:  char pointer to format
*/

/**
 * @brief Group of functions used for interfacing
 */
typedef struct inters
{
    int64_t(*compar)(const void*, const void*);
    int64_t(*equcmp)(const void*, const void*);
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
 * OBS: is have break line at the end of string
 * @param stn: head of list
 * @param get_value: the get_value interface for stn structure
 * @param netp: gets the next pointer for stn structure
 */
void ListPrint(void* stn, int64_t(*get_value)(const void*), void*(*nextp)(const void*));

/**
 * @brief: similar to ListPrint but with format param
 * OBS: it doesn't have break line at the end
 * @param stn: head pointer of list
 * @param get_value: the get_value interface for stn structure
 * @param netp: gets the next pointer for stn structure
 */
void ListFPrint(void* stn, int64_t(*get_value)(const void*), void*(*nextp)(const void*), const char* fmt);

/**
 * @brief: frees the memory of the list
 * @param stn: pointer to the list start
 * @param nextp: function that returs next pointer
 * @param freest: frees the insides of node
 */
void ListFree(void* stn, void*(*nextp)(const void*), void(*freest)(const void*));

/**
 * @brief: remove first element of list and returns it
 * @param stnr: pointer of pointer of head of list
 * @param nextp: function that returns next pointer
 * @param nexptr: function that returns the next pointer by reference
 * @ret: pointer to start of list
 */
void* ListPop(void** stnr, void*(*nextp)(const void*), void**(*nextptr)(const void*));