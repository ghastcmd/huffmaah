#include "lstree_bst.h"
#include "structs.h"

/**
 * * ******************************** *
 * * ######### LOOKUP TABLE ######### *
 * * ******************************** *
 * @stn:    standard token table
 * @sts:    standard token start
 * @ste:    standard token end
 * @stsrs:  standard token start resolved
 * @sters:  standard token end resolved
 * @val:    value
 * @vals:   values
 * @inters: interfaces
 */

// * void*(*merge    )(const void*, const void*);
// ! void*(*create   )(const void*);
// ! void*(*leftp    )(const void*);
// ! void**(*leftptr )(const void*);
// ! void*(*rightp   )(const void*);
// ! void**(*rightptr)(const void*);


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

// void* create(const void* std)
// {

// }