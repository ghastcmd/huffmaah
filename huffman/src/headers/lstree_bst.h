#pragma once
#include <pch.h>

/**
 * @brief: gets the first 2 nodes of list and makes them childs
 * of another node that have it's values as char '*', and it's frequency
 * as the sum of the childs frequency, and inputs the new node into the list
 * in a sorted order
 * @param head: pointer to start of a lstree list
 */
void lstree_bst_union(lstree** head);

/**
 * @brief: makes a tree of lstree list
 * the tree follow the rules of lstree_bst_union
 * @param head: pointer to start of lstree list
 */
void lstree_bst_treeify(lstree** head);

/**
 * @brief: prints tree lstree tree in preorder
 * @param head: pointer to start of lstree list
 */
void lstree_bst_print_preorder(lstree* head);