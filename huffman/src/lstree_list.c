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
 */

/**
 * @param sts: first lstre node
 * @param ste: first lstree node
 * @param st1: second lstree node
 * @ret: relation between freq of st0 and st1
 * negative, zero and positive for 
 * lesser, equals and greater than respectively
 */
int64_t compare(const void* sts, const void* ste)
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
int64_t equcmp(const void* sts, const void* ste)
{
    lstree* st0v = (lstree*)sts;
    lstree* st1v = (lstree*)ste;

    int* st0vp = (int*)st0v->val;
    int* st1vp = (int*)st1v->val;

    return *st0vp - *st1vp;
}

/**
 * @param head: node pointer
 * @ret: current freq of node pointer 
 */
int64_t get_freq(const void* stn)
{
    lstree* cur = (lstree*)stn;
    return cur->freq;
}

/**
 * @param head: node pointer
 * @ret: current val of node pointer 
 */
int64_t get_val(const void* stn)
{
    lstree* cur = (lstree*)stn;
    int64_t* value = (int64_t*)cur->val;
    return *value;
}

/**
 * @param vals: tuple of val and freq to new lstree
 * @ret: heap allocated lstree node pointer
 * @ret: returns nullptr if fails
 */
// ! ######################## !
// ! #####    UNUSED    ##### !
// ! ######################## !
// void* create_list(const void* vals)
// {
//     tuple* values = (tuple*)vals;
//     lstree* new_lstree = (lstree*)calloc(1, sizeof(lstree));
//     if (!new_lstree) // error checikng
//     {
//         logerr("calloc");
//         return nullptr;
//     }
//     int* value = (int*)malloc(sizeof(int));
//     if (!value)
//     {
//         logerr("malloc");
//         exit(-1)
//     }
//     *value = values->st0;
//     *new_lstree = (lstree)
//     {
//         .val  = value,
//         .freq = values->st1
//     };
//     return (void*)new_lstree;
// }

/**
 * @param stn: lstree node pointer
 * @ret: the integer values of lstree
 * @ret: retuns nullptr if fails
 */
// ! ######################## !
// ! #####    UNUSED    ##### !
// ! ######################## !
// void* get_values(const void* stn)
// {
//     tuple* retvals = (tuple*)stn;
//     lstree* stv = (lstree*)stn;
//     int* malloc(sizeof)
//     *retvals = (tuple)
//     {
//         .st0 = stv->val,
//         .st1 = stv->freq
//     };
//     return (void*)retvals;
// }

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
 * @ret: the next pointer by reference of stn
 */
void** nextptr(const void* stn)
{
    lstree* stv = (lstree*)stn;
    return (void**)&(stv->next);
}

/**
 * @brief: frees the internals of lstree node
 * @param stn: lstree node pointer
 */
void freest(const void* stn)
{
    lstree* stnr = (lstree*)stn;
    free(stnr->val);
}

/**
 * * ****************************************** *
 * * Declaring local-global interface structure *
 * * ****************************************** *
 */

inters ine =
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
    ListFPrint((void*)head, get_val, nextp, "%c");
    puts("");
}

void lstree_add_val(lstree** headr, int val, int freq)
{
    // printf("\x1b[92mInserting:\x1b[94m %i %i\x1b[0m\n", val, freq);
    lstree* stin = (lstree*)calloc(1, sizeof(lstree));
    if (!stin)
    {
        logerr("calloc");
        exit(-1);
    }

    int* value = (int*)malloc(sizeof(int));
    if (!value)
    {
        logerr("malloc");
        exit(-1);
    }
    *value = val;
    *stin = (lstree)
    {
        .val   = value,
        .freq  = freq
    };
    ine.compar = compare;
    ListInsertSorted((void**)headr, stin, &ine);
}

void lstree_add_node(lstree** headr, lstree* node)
{
    ListInsertSorted((void**)headr, (void*)node, &ine);
}

void* lstree_pop(lstree** headr)
{
    return ListPop((void**)headr, nextp, nextptr);
}

void lstree_clean_list(lstree* head)
{
    ListFree(head, nextp, freest);
}
