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
 * @brief: prints lstree tree in preorder with char format
 * @param head: pointer to root of tree (a lstree root node)
 * @param fmt: format to be used in every print call
 */
void lstree_bst_printf_preorder(lstree* head, const char* fmt);

/**
 * @brief: prints lstree tree in preorder
 * @param head: pointer to root of tree (a lstree root node)
 * @param fmt: format to be used in every print call
 */
void lstree_bst_print_preorder(lstree* head);

/**
 * @brief: executes a function in every lstree node in tree
 * @param head: pointer to root of tree (a lstree root node)
 * @param foo: user specified function to run for each value
 */
void lstree_bst_foreach_preorder(lstree* head, void(*foo)(const int));