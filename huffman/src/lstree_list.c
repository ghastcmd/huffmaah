#include "lstree_list.h"
#include "linkedList.h"
#include "structs.h"

/**
 * * ******************************** *
 * * ######### LOOKUP TABLE ######### *
 * * ******************************** *
 * @param stn    standard token normal
 * @param sts    standard token start
 * @param ste    standard token end
 * @param vals   values
 * @param vals   values
 * @param inters interfaces
 */

/**
 * @param sts first lstre node
 * @param ste first lstree node
 * @param st1 second lstree node
 * @return  relation between freq of st0 and st1
 * negative, zero and positive for 
 * lesser, equals and greater than respectively
 */
int64_t compare(const void* sts, const void* ste)
{
    lstree* st0v = (lstree*)sts;
    lstree* st1v = (lstree*)ste;

    int64_t val = st0v->freq - st1v->freq;
    if(val == 0)
    {
        int64_t* st0vp = (int64_t*)st0v->val;
        int64_t* st1vp = (int64_t*)st1v->val;
        return (*st0vp - *st1vp);
    }
    else
    {
        return val;
    }
}

/**
 * Similar to compare, but using val element
 * @param sts first lstre node
 * @param ste first lstree node
 * @param st1 second lstree node
 * @return neg, zero, posi, for lesser, equ, greather
 */
// ! ######################## !
// ! #####    UNUSED    ##### !
// ! ######################## !
int64_t equcmp(const void* sts, const void* ste)
{
    lstree* st0v = (lstree*)sts;
    lstree* st1v = (lstree*)ste;

    int64_t* st0vp = (int64_t*)st0v->val;
    int64_t* st1vp = (int64_t*)st1v->val;

    return *st0vp - *st1vp;
}

/**
 * @param head node pointer
 * @return current freq of node pointer 
 */
int64_t get_freq(const void* stn)
{
    lstree* cur = (lstree*)stn;
    return cur->freq;
}

/**
 * @param head node pointer
 * @return current val of node pointer 
 */
int64_t get_val(const void* stn)
{
    lstree* cur = (lstree*)stn;
    int64_t* value = (int64_t*)cur->val;
    return *value;
}

/**
 * @param vals tuple of val and freq to new lstree
 * @return heap allocated lstree node pointer
 * @return returns nullptr if fails
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
 * @param stn lstree node pointer
 * @return the integer values of lstree
 * @return retuns nullptr if fails
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
 * @param stn lstree node pointer
 * @return next pointer in stn lstree
 */
void* nextp(const void* stn)
{
    lstree* stv = (lstree*)stn;
    // printf("\x1b[31m%p\x1b[0m\n", stv->next);
    return (void*)stv->next;
}

/**
 * @param stn lstree node pointer
 * @return the next pointer by reference of stn
 */
void** nextptr(const void* stn)
{
    lstree* stv = (lstree*)stn;
    return (void**)&(stv->next);
}

/**
 * Frees the internals of lstree node
 * @param stn lstree node pointer
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

void lstree_add_val(lstree** headr, int64_t val, int64_t freq)
{
    // printf("\x1b[92mInserting:\x1b[94m %i %i\x1b[0m\n", val, freq);
    lstree* stin = (lstree*)calloc(1, sizeof(lstree));
    logerr_calloc(stin,);

    int64_t* value = (int64_t*)calloc(1, sizeof(int64_t));
    logerr_calloc(value,free(stin));

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

void lstree_clean_list(lstree** head)
{
    ListFree(*head, nextp, freest);
    *head = nullptr;
}

interface* lstree_lst_get_inters()
{
    return &ine;
}