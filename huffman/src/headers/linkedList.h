#pragma once
#include "pch.h"
#include "structs.h"

/**
 * * *********************************************************** *
 * * This object contains interfaces for utilizing a linked list *
 * * *********************************************************** *
 * 
 * @param ine  interface equivalent
 * @param stn  standard token node
 * @param stnr stantard token node reference
 * @param stin standard token input
 * @param fmt  char pointer to format
*/

/**
 * Group of functions used for interfacing
 */
typedef struct inters
{
    int64_t(*compar)(const void*, const void*);
    void*(*nextp   )(const void*);
    void**(*nextptr)(const void*);
} inters, interface;

/**
 * @param stn  the start of the list
 * @param stin node to be added
 * @param ine  funcitons that access list values
 */
void ListInsertSorted(void** stn, void* stin, inters* ine);

/**
 * Prints the list;
 * it have line break at the end of string
 * @param stn: head of list
 * @param get_value: the get_value interface for stn structure
 * @param netp: gets the next pointer for stn structure
 */
void ListPrint(void* stn, int64_t(*get_value)(const void*), void*(*nextp)(const void*));

/**
 * Similar to ListPrint but with format param;
 * it doesn't have line break at the end of string
 * @param stn head pointer of list
 * @param get_value the get_value interface for stn structure
 * @param netp gets the next pointer for stn structure
 */
void ListFPrint(void* stn, int64_t(*get_value)(const void*), void*(*nextp)(const void*), const char* fmt);

/**
 * Frees the memory of the list
 * @param stn pointer to the list start
 * @param nextp function that returs next pointer
 * @param freest frees the insides of node
 */
void ListFree(void* stn, void*(*nextp)(const void*), void(*freest)(const void*));

/**
 * Remove first element of list and returns it
 * @param stnr pointer of pointer of head of list
 * @param nextp function that returns next pointer
 * @param nexptr function that returns the next pointer by reference
 * @return pointer to start of list
 */
void* ListPop(void** stnr, void*(*nextp)(const void*), void**(*nextptr)(const void*));