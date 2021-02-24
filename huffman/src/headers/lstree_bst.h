#pragma once
#include "pch.h"
#include "bsTree.h"

/**
 * Gets the first 2 nodes of list and makes them childs
 * of another node that have it's values as char '*', and it's frequency
 * as the sum of the childs frequency, and inputs the new node into the list
 * in a sorted order
 * @param head pointer to start of a lstree list
 */
void lstree_bst_union(lstree** head);

/**
 * Makes a tree of lstree list
 * the tree follow the rules of lstree_bst_union
 * @param head pointer to start of lstree list
 */
void lstree_bst_treeify(lstree** head);

/**
 * Construct a tree following preorder print of vals
 * @param tree_fmt string containing preorder of previous tree
 * @param len lenght of tree_fmt string
 * @return pointer to root of made lstree
 */
lstree* lstree_bst_make_tree(char* tree_fmt, const uint64_t len);

/**
 * Executes a function in every lstree node in tree
 * @param head pointer to root of tree (a lstree root node)
 * @param foo user specified function to run for each value
 */
void lstree_bst_foreach_preorder(lstree* head, void(*foo)(const int64_t));

/**
 * Executes a function in every lstree node in tree with void* param
 * @param head pointer to root of tree (a lstree root node)
 * @param foo user specified function to run for each value
 * @param stp void pointer to param
 */
void lstree_bst_foreach_wparam_preorder(lstree* head, void(*foo)(const int64_t, void*), void* stp);

/**
 * Prints lstree tree in preorder with char format
 * @param head pointer to root of tree (a lstree root node)
 * @param fmt format to be used in every print call
 */
void lstree_bst_printf_preorder(lstree* head, const char* fmt);

/**
 * Prints lstree tree in preorder
 * @param head pointer to root of tree (a lstree root node)
 * @param fmt format to be used in every print call
 */
void lstree_bst_print_preorder(lstree* head);


/**
 * Frees the memory of tree of lstree nodes
 * @param head lstree tree root pointer
 */
void lstree_clean_tree(lstree** head);

/**
 * @return Interface struct to lstree
 */
inters_bst* lstree_bst_get_inters();