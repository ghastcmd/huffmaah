#include "lstree_list.h"
#include "linkedList.h"
#include "structs.h"

/**
 * * ******************************** *
 * * ######### LOOKUP TABLE ######### *
 * * ******************************** *
 * @stt:    status token table
 * @sts:    status token start
 * @ste:    status token end
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
int get_freq(const void* stt)
{
    lstree* cur = (lstree*)stt;
    return cur->freq;
}

/**
 * @param head: node pointer
 * @ret: current val of node pointer 
 */
int get_val(const void* stt)
{
    lstree* cur = (lstree*)stt;
    return cur->val;
}

/**
 * @param head: node pointer
 * @ret: current pointer of node 
 */
int get_ptr(const void* stt)
{
    long long ptr = (long long)stt;
    return (int)ptr;
}

/**
 * @param vals: tuple of val and freq to new lstree
 * @ret: heap allocated lstree node pointer
 * @ret: returns nullptr if fails
 */
void* create(const void* vals)
{
    tuple* values = (tuple*)vals;
    lstree* new_lstree = (lstree*)calloc(1, sizeof(lstree));
    if (!new_lstree) // error checikng
    {
        logerr("calloc");
        return nullptr;
    }
    *new_lstree = (lstree)
    {
        .val  = values->st0,
        .freq = values->st1
    };

    return (void*)new_lstree;
}

/**
 * @param head: lstree node pointer
 * @ret: the integer values of lstree
 * @ret: retuns nullptr if fails
 */
void* get_values(const void* stt)
{
    tuple* retvals = (tuple*)malloc(sizeof(tuple));
    if (!retvals) // error checking
    {
        logerr("malloc");
        return nullptr;
    }
    lstree* stv = (lstree*)stt;
    *retvals = (tuple)
    {
        .st0 = stv->val,
        .st1 = stv->freq
    };
    return (void*)retvals;
}

/**
 * @param stt: lstree node pointer
 * @ret: next pointer in stt lstree
 */
void* nextp(const void* stt)
{
    lstree* stv = (lstree*)stt;
    return (void*)stv->next;
}

/**
 * @param stt: lstree node pointer
 * @ret: next pointer by reference in stt lstree
 */
void** nextptr(const void* stt)
{
    lstree* stv = (lstree*)stt;
    return (void**)&(stv->next);
}

/**
 * * ****************************************** *
 * * Declaring local global interface structure *
 * * ****************************************** *
 */

inters ine = (interface)
{
    .get_vals = get_values,
    .compar   = compare,
    .equcmp   = equcmp,
    .nextp    = nextp,
    .nextptr  = nextptr,
};

/**
 * * *************************************** *
 * * Global functions linked at lstreeList.h *
 * * *************************************** *
 */

void lstree_print_vals(lstree* head)
{
    print_list((void*)head, get_val, nextp);
}

void lstree_print_freq(lstree* head)
{
    print_list((void*)head, get_freq, nextp);
}

void lstree_add(lstree** head, int val, int freq)
{
    printf("\x1b[92mInserting:\x1b[94m %i %i\x1b[0m\n", val, freq);
    tuple* stin = (tuple*)calloc(1, sizeof(tuple));
    *stin = (tuple)
    {
        .st0 = val,
        .st1 = freq
    };
    ine.compar = compare;
    insert_sorted((void**)head, stin, &ine);
}

void clean_list(lstree* head)
{
    free_list(head, nextp);
}

void tst(lstree** head)
{
    printf("%p\n", *head);
    printf("%p\n", head);

}