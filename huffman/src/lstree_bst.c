#include "linkedList.h"
#include "lstree_list.h"
#include "bsTree.h"
#include "structs.h"

/**
 * * ******************************** *
 * * ######### LOOKUP TABLE ######### *
 * * ******************************** *
 * @std:    standard token data
 * @stt:    standard token tuple

 * @stn:    standard token node
 * @sts:    standard token start
 * @ste:    standard token end

 * @stsr:   standard token start resolved
 * @ster:   standard token end resolved
 
 * @val:    value
 * @vals:   values
 */

/**
 * * ************************************* *
 * * ########## LOCAL FUNCTIONS ########## *
 * * ************************************* *
 */

/**
 * @brief: gets two inputs and merge it's integers values and returns is
 * @param sts: first lstree node input
 * @param ste: second lstree node input
 * @ret: the merge of integers of inputs
 */
void* merge(const void* sts, const void* ste)
{
    lstree* stsr = (lstree*)sts;
    lstree* ster = (lstree*)ste;
    
    tuple* retdata = (tuple*)calloc(1, sizeof(tuple));

    *retdata = (tuple)
    {
        .st0 = '*',
        .st1 = stsr->freq + ster->freq
    };

    return (void*)retdata;
}

/**
 * @param std: data used to create new lstree node
 * @ret: pointer to new lstree node
 */
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

/**
 * @param stn: pointer to lstree node
 * @ret: pointe to stn left pointer
 */
void* leftp(const void* stn)
{
    lstree* stnp = (lstree*)stn;
    return stnp->left;
}

/**
 * @param stn: pointer to lstree node
 * @ret: pointe to stn right pointer
 */
void* rightp(const void* stn)
{
    lstree* stnp = (lstree*)stn;
    return stnp->right;
}

/**
 * @param stn: pointer to lstree node
 * @ret: pointe to stn left pointer by reference
 */
void** leftptr(const void* stn)
{
    lstree* stnptr = (lstree*)stn;
    return (void**)&(stnptr->left);
}

/**
 * @param stn: pointer to lstree node
 * @ret: pointe to stn right pointer by reference
 */
void** rightptr(const void* stn)
{
    lstree* stnptr = (lstree*)stn;
    return (void**)&(stnptr->right);
}

/**
 * @param stn: pointer to lstree node
 * @ret: .val value of input node
 */
int get_val_bst(const void* stn)
{
    lstree* stnp = (lstree*)stn;
    return stnp->val;
}

/**
 * * ****************************************** *
 * * Declaring local global interface structure *
 * * ****************************************** *
 */

inters_bst ine_bst = (inters_bst)
{
    .get_val  = get_val_bst,
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
    void* leftchild  = lstree_pop(head);
    void* rightchild = lstree_pop(head);

    void* inputnew = TreeUnion(leftchild, rightchild, &ine_bst);

    lstree_add_node(head, inputnew);
}

void lstree_bst_treeify(lstree** head)
{
    while((*head)->next)
    {
        lstree_bst_union(head);
    }
}

void lstree_bst_foreach_preorder(lstree* head, void(*foo)(const int))
{
    TreeForEachPreorder((void*)head, &ine_bst, foo);
}

void lstree_bst_printf_preorder(lstree* head)
{
    const char* fmt = "%c";
    TreeFPrintPreorder((void*)head, &ine_bst, get_val_bst, fmt);
    puts("");
}

void lstree_bst_print_preorder(lstree* head)
{
    TreePrintPreorder((void*)head, &ine_bst, get_val_bst);
    puts("");
}
