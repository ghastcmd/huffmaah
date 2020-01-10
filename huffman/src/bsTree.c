#include "bsTree.h"
#include "structs.h"

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

void TreeAdd_holder(void** sth, void* stin, const inters_bst* ine, bool* found)
{
    if (!*sth)
    {
        *found = true;
        *sth = stin;
        return;
    }

    void* lptr = ine->leftp (*sth);   
    if ((!lptr || ine->get_val(lptr) == FLAG) && !*found)
    {
        TreeAdd_holder(ine->leftptr(*sth), stin, ine, found);
    }

    void* rptr = ine->rightp(*sth);
    if ((!rptr || ine->get_val(rptr) == FLAG) && !*found)
    {
        TreeAdd_holder(ine->rightptr(*sth), stin, ine, found);
    }
}

void TreeAdd(void** sth, void* stin, const inters_bst* ine)
{
    bool found = false;
    TreeAdd_holder(sth, stin, ine, &found);
}

void TreeForEachPreorder(void* sth, const inters_bst* ine, void(*foo)(const int))
{
    if (!sth) return;
    foo(ine->get_val(sth));
    TreeForEachPreorder(ine->leftp(sth) , ine, foo);
    TreeForEachPreorder(ine->rightp(sth), ine, foo);
}

void TreePrintPreorder(void* sth, const inters_bst* ine, int(*get_val)(const void*))
{
    if (!sth) return;
    printf("%i ", get_val(sth));
    TreePrintPreorder(ine->leftp(sth) , ine, get_val);
    TreePrintPreorder(ine->rightp(sth), ine, get_val);
}

void TreeFPrintPreorder(void* sth, const inters_bst* ine, int(*get_val)(const void*), const char* fmt)
{
    if (!sth) return;
    printf(fmt, get_val(sth));
    TreeFPrintPreorder(ine->leftp(sth) , ine, get_val, fmt);
    TreeFPrintPreorder(ine->rightp(sth), ine, get_val, fmt);
}

