#include "linkedList.h"
#include "lstree_list.h"
#include "bsTree.h"
#include "structs.h"

/**
 * * ******************************** *
 * * ######### LOOKUP TABLE ######### *
 * * ******************************** *
 * @stn:    standard token normal
 * @stt:    standard token tuple
 * @sts:    standard token start
 * @ste:    standard token end
 * @stsrs:  standard token start resolved
 * @sters:  standard token end resolved
 * @val:    value
 * @vals:   values
 * @inters: interfaces
 */

void* merge(const void* sts, const void* ste)
{
    lstree* stsrs = (lstree*)sts;
    lstree* sters = (lstree*)ste;
    
    tuple* retdata = (tuple*)calloc(1, sizeof(tuple));

    *retdata = (tuple)
    {
        .st0 = '*',
        .st1 = stsrs->freq + sters->freq
    };

    return (void*)retdata;
}

void* create(const void* std)
{
    tuple* stt    = (tuple*)std;
    lstree* stnew = (lstree*)calloc(1, sizeof(lstree));
    if (!stnew)
    {
        logerr("calloc");
        exit(-1);
    }
    *stnew = (lstree)
    {
        .val  = stt->st0,
        .freq = stt->st1
    };

    return (void*)stnew;
}

void* leftp(const void* stn)
{
    lstree* stnp = (lstree*)stn;
    return stnp->left;
}

void* rightp(const void* stn)
{
    lstree* stnp = (lstree*)stn;
    return stnp->right;
}

void** leftptr(const void* stn)
{
    lstree* stnptr = (lstree*)stn;
    return (void**)&(stnptr->left);
}

void** rightptr(const void* stn)
{
    lstree* stnptr = (lstree*)stn;
    return (void**)&(stnptr->right);
}

int get_val_bst(const void* stn)
{
    lstree* stnp = (lstree*)stn;
    return stnp->freq;
}

/**
 * * ****************************************** *
 * * Declaring local global interface structure *
 * * ****************************************** *
 */

inters_bst ine_bst = (inters_bst)
{
    .merge    = merge,
    .create   = create,
    .leftp    = leftp,
    .leftptr  = leftptr,
    .rightp   = rightp,
    .rightptr = rightptr
};

/**
 * * *************************************** *
 * * Global functions linked at lstree_bst.h *
 * * *************************************** *
 */

void lstree_bst_union(lstree** head)
{
    void* leftchild  = lstree_pop((void**)head);
    void* rightchild = lstree_pop((void**)head);

    void* inputnew = TreeUnion(leftchild, rightchild, &ine_bst);

    lstree_add_node((void**)head, inputnew);
}

void lstree_bst_treeify(lstree** head)
{
    while((*head)->next)
    {
        lstree_bst_union(head);
    }
}

void lstree_bst_print_preorder(lstree* head)
{
    TreePrintPreorder((void*)head, &ine_bst, get_val_bst);
}