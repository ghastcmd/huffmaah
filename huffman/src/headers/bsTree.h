#pragma once
#include <pch.h>

/// Group of functions used for interfacing
typedef struct inters_bst
{
    void*(*merge    )(const void*, const void*);
    int64_t(*get_val)(const void*);
    void*(*create   )(const void*);
    void*(*leftp    )(const void*);
    void**(*leftptr )(const void*);
    void*(*rightp   )(const void*);
    void**(*rightptr)(const void*);
} inters_bst;

/**
 * Gets two node tree nodes merge them as father
 * than puts the inputs as childs
 * @param sts left child tree node
 * @param str right child tree node
 * @param ine struct of interfaces
 * @return pointer to created father
 */
void* TreeUnion(void* sts, void* ste, const inters_bst* ine);

/**
 * Adds a node to the tree
 * @param sth pointer by reference to tree's root
 * @param stin pointer to node to be added
 * @param ine struct of interfaces
 */
void TreeAdd(void** sth, void* stin, const inters_bst* ine);

/**
 * Executes a user-defined function for every values of tree in preorder
 * @param sth pointer of tree's root
 * @param ine interface struct
 * @param foo user-defined function to be executed
 */
void TreeForEachPreorder(void* sth, const inters_bst* ine, void(*foo)(const int64_t));

/**
 * Executes a user-defined function for every values of tree and void* in preorder
 * @param sth pointer of tree's root
 * @param ine interface struct
 * @param foo user-defined function to be executed
 * @param stp void* param to be used in foo function
 */
void TreeForEachPreorderWParam(void* sth, const inters_bst* ine, void(*foo)(const int64_t, void*), void* stp);

/**
 * Prints Tree in preorder
 * @param sth pointer to root of tree
 * @param ine struct of interfaces
 * @param get_val function that returns the value to be printed
 */
void TreePrintPreorder(void* sth, const inters_bst* ine, int64_t(*get_val)(const void*));

/**
 * Prints Tree in preorder with formated output
 * @param sth pointer to root of tree
 * @param ine struct of interfaces
 * @param get_val function that returns the value to be printed
 * @param fmt format to be used in every print call
 */
void TreeFPrintPreorder(void* sth, const inters_bst* ine, int64_t(*get_val)(const void*), const char* fmt);

/**
 * Frees the memory of entire tree
 * @param sth pointer to root of lstree tree
 * @param ine struct of interfaces to lstree
 * @param freebst clears the internals of lstree node
 */
void TreeFree(void* sth, const inters_bst* ine, void(*freebst)(const void*));