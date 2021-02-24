#pragma once
#include "pch.h"
#include "structs.h"
#include "linkedList.h"

/**
 * * ********************************************************** *
 * * This have interfaces to interact with linkedList functions *
 * * ********************************************************** *
 */

/**
 * Prints all .val of lstree list
 * @param head pointer to start of lstree list
 */
void lstree_print_vals(lstree* head);

/**
 * Prints all .freq of lstree list
 * @param head pointer to start of lstre list
 */
void lstree_print_freq(lstree* head);

/**
 * Prints all .val of lstree list formated in char
 * @param head pointer to start of lstree list
 */
void lstree_print_char(lstree* head);

/**
 * Insert sorted into a lstree list by taking input by value
 * @param head pointer by reference to start of lstree list
 * @param val desired .val of new lstree node
 * @param freq desired .freq of new lstree node
 */
void lstree_add_val(lstree** heade, int64_t val, int64_t freq);

/**
 * Insert sorted a lsree node into a lstree list
 * @param head pointer by reference to start of lstree list
 * @param node lstreenode to be added
 */
void lstree_add_node(lstree** headr, lstree* node);

/**
 * Pops lstree node from start of lstree list
 * @param headr: pointer by reference to start of lstree list
 * @return pointer of popped lstree node
 */
void* lstree_pop(lstree** headr);

/**
 * Frees memory of lstree list
 * @param head pointer to start of lstree list
 */
void lstree_clean_list(lstree** head);

/**
 * @return the struct interface used with lstree list
 */
interface* lstree_lst_get_inters();