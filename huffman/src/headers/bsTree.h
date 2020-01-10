#pragma once
#include <pch.h>

/// @brief Group of functions used for interfacing
typedef struct inters_bst
{
    void*(*merge    )(const void*, const void*);
    void*(*create   )(const void*);
    void*(*leftp    )(const void*);
    void**(*leftptr )(const void*);
    void*(*rightp   )(const void*);
    void**(*rightptr)(const void*);
} inters_bst;

/**
 * @brief: gets two node tree nodes merge them as father
 * than puts the inputs as childs
 * @param sts: left child tree node
 * @param str: right child tree node
 * @param ine: struct of interfaces
 * @ret: pointer to created father
 */
void* TreeUnion(void* sts, void* ste, const inters_bst* ine);

/**
 * @brief: prints Tree in preorder
 * @param sth: pointer to root of tree
 * @param ine: struct of interfaces
 * @param get_val: function that returns the value to be printed
 */
void TreePrintPreorder(void* sth, const inters_bst* ine, int(*get_val)(const void*));

/**
 * @brief: prints Tree in preorder with formated output
 * @param sth: pointer to root of tree
 * @param ine: struct of interfaces
 * @param get_val: function that returns the value to be printed
 * @param fmt: format to be used in every print call
 */
void TreeFPrintPreorder(void* sth, const inters_bst* ine, int(*get_val)(const void*), const char* fmt);