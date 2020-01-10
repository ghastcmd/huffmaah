#include "bsTree.h"

/**
 * @sts: standard token start
 * @ste: standard token end
 * @ine: interface equivalent
 */

void* TreeUnion(void* sts, void* ste, const inters_bst* ine)
{
    void* new_data = ine->merge (sts, ste);
    void* stnew    = ine->create(new_data);

    void** newleftptr  = ine->leftptr (stnew);
    void** newrightptr = ine->rightptr(stnew);
    
    *newleftptr  = sts;
    *newrightptr = ste;

    return stnew;
}

void TreePrintPreorder(void* sth, const inters_bst* ine, int(*get_val)(const void*) )
{
    printf("%i ", get_val(sth));
    TreePrintPreorder(ine->leftp(sth) , ine, get_val);
    TreePrintPreorder(ine->rightp(sth), ine, get_val);
}