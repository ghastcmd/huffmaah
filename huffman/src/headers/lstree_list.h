#pragma once
#include <pch.h>
#include "structs.h"

/**
 * * ********************************************************** *
 * * This have interfaces to interact with linkedList functions *
 * * ********************************************************** *
 */

/**
 * @brief: prints all .val of lstree list
 * @param head: pointer to start of lstree list
 */
void lstree_print_vals(lstree* head);

/**
 * @brief: prints all .freq of lstree list
 * @param head: pointer to start of lstre list
 */
void lstree_print_freq(lstree* head);

/**
 * @brif: prints all .val of lstree list formated in char
 * @param head: pointer to start of lstree list
 */
void lstree_print_char(lstree* head);

/**
 * @brief: insert sorted into a lstree list by taking input by value
 * @param head: pointer by reference to start of lstree list
 * @param val: desired .val of new lstree node
 * @param freq: desired .freq of new lstree node
 */
void lstree_add_val(lstree** heade, int val, int freq);

/**
 * @brief: insert sorted a lsree node into a lstree list
 * @param head: pointer by reference to start of lstree list
 * @param node: lstreenode to be added
 */
void lstree_add_node(lstree** headr, lstree* node);

/**
 * @brief: pops lstree node from start of lstree list
 * @param headr: pointer by reference to start of lstree list
 * @ret: pointer of popped lstree node
 */
void* lstree_pop(void** headr);

/**
 * @brief: frees memory of lstree list
 * @param head: pointer to start of lstree list
 */
void clean_list(lstree* head);