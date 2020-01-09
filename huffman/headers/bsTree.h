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
 * @ret: pointer to created father
 */
void* TreeUnion(void* sts, void* ste, const inters_bst* ine);

void TreePrintPreorder(void* sth, const inters_bst* ine, int(*get_val)(const void*));