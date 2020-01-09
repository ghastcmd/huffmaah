#pragma once
#include <pch.h>
#include "structs.h"

/**
 * * ********************************************************** *
 * * This have interfaces to interact with linkedList functions *
 * * ********************************************************** *
 */

/**
 * @brief: prints lstree values in form of list
 * @param stn: the head of lstree list
 */
void lstree_print_vals(lstree* head);

/**
 * @brief: prints lstree freqs in form of list
 * @param stn: the head of lstree list
 */
void lstree_print_freq(lstree* head);

void lstree_print_char(lstree* head);

/**
 * @brief: adds a node to lstree with said values
 * @param val: value of char
 * @param freq: frequency of char in file
 */
void lstree_add(lstree** head, int val, int freq);

void lstree_add_node(void** head, void* node);

void* lstree_pop(void** head);

/**
 * @brief: frees memory from list
 * @param head: pointer to start of list
 */
void clean_list(lstree* head);