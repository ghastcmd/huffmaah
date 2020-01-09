#include "lstree_list.h"
#include "linkedList.h"
#include "structs.h"

/**
 * * ******************************** *
 * * ######### LOOKUP TABLE ######### *
 * * ******************************** *
 * @stn:    standard token normal
 * @sts:    standard token start
 * @ste:    standard token end
 * @vals:   values
 * @vals:   values
 * @inters: interfaces
 * * ******************************** *
 * *        perror string format      *
 * * @[cur func] > .[variable] [func] *
 * * ******************************** *
 */

/**
 * @param sts: first lstre node
 * @param ste: first lstree node
 * @param st1: second lstree node
 * @ret: relation between freq of st0 and st1
 * negative, zero and positive for 
 * lesser, equals and greater than respectively
 */
int compare(const void* sts, const void* ste)
{
    lstree* st0v = (lstree*)sts;
    lstree* st1v = (lstree*)ste;

    return st0v->freq - st1v->freq;
}

/**
 * @brief: similar to compare, but using val element
 * @param sts: first lstre node
 * @param ste: first lstree node
 * @param st1: second lstree node
 * @ret: neg, zero, posi, for lesser, equ, greather
 */
int equcmp(const void* sts, const void* ste)
{
    lstree* st0v = (lstree*)sts;
    lstree* st1v = (lstree*)ste;

    return st0v->val - st1v->val;
}

/**
 * @param head: node pointer
 * @ret: current freq of node pointer 
 */
int get_freq(const void* stn)
{
    lstree* cur = (lstree*)stn;
    return cur->freq;
}

/**
 * @param head: node pointer
 * @ret: current val of node pointer 
 */
int get_val(const void* stn)
{
    lstree* cur = (lstree*)stn;
    return cur->val;
}

/**
 * @param head: node pointer
 * @ret: current pointer of node 
 */
int get_ptr(const void* stn)
{
    long long ptr = (long long)stn;
    return (int)ptr;
}

/**
 * @param vals: tuple of val and freq to new lstree
 * @ret: heap allocated lstree node pointer
 * @ret: returns nullptr if fails
 */
// ! Unused
// void* create_list(const void* vals)
// {
//     tuple* values = (tuple*)vals;
//     lstree* new_lstree = (lstree*)calloc(1, sizeof(lstree));
//     if (!new_lstree) // error checikng
//     {
//         logerr("calloc");
//         return nullptr;
//     }
//     *new_lstree = (lstree)
//     {
//         .val  = values->st0,
//         .freq = values->st1
//     };

//     return (void*)new_lstree;
// }

/**
 * @param stn: lstree node pointer
 * @ret: the integer values of lstree
 * @ret: retuns nullptr if fails
 */
void* get_values(const void* stn)
{
    tuple* retvals = (tuple*)malloc(sizeof(tuple));
    if (!retvals) // error checking
    {
        logerr("malloc");
        return nullptr;
    }
    lstree* stv = (lstree*)stn;
    *retvals = (tuple)
    {
        .st0 = stv->val,
        .st1 = stv->freq
    };
    return (void*)retvals;
}

/**
 * @param stn: lstree node pointer
 * @ret: next pointer in stn lstree
 */
void* nextp(const void* stn)
{
    lstree* stv = (lstree*)stn;
    // printf("\x1b[31m%p\x1b[0m\n", stv->next);
    return (void*)stv->next;
}

/**
 * @param stn: lstree node pointer
 * @ret: next pointer by reference in stn lstree
 */
void** nextptr(const void* stn)
{
    lstree* stv = (lstree*)stn;
    return (void**)&(stv->next);
}

/**
 * * ****************************************** *
 * * Declaring local global interface structure *
 * * ****************************************** *
 */

inters ine = (interface)
{
    .compar   = compare,
    .equcmp   = equcmp,
    .nextp    = nextp,
    .nextptr  = nextptr,
};

/**
 * * **************************************** *
 * * Global functions linked at lstree_list.h *
 * * **************************************** *
 */

void lstree_print_vals(lstree* head)
{
    ListPrint((void*)head, get_val, nextp);
}

void lstree_print_freq(lstree* head)
{
    ListPrint((void*)head, get_freq, nextp);
}

void lstree_print_char(lstree* head)
{
    ListFPrint((void*)head, get_val, nextp, "%c ");
}

void lstree_add(lstree** head, int val, int freq)
{
    printf("\x1b[92mInserting:\x1b[94m %i %i\x1b[0m\n", val, freq);
    lstree* stin = (lstree*)calloc(1, sizeof(lstree));
    *stin = (lstree)
    {
        .val   = val,
        .freq  = freq
    };
    ine.compar = compare;
    ListInsertSorted((void**)head, stin, &ine);
}

void lstree_add_node(void** head, void* node)
{
    ListInsertSorted(head, node, &ine);
}

void* lstree_pop(void** head)
{
    return ListPop(head, nextp);
}

void clean_list(lstree* head)
{
    ListFree(head, nextp);
}
