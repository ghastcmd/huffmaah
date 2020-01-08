#include <pch.h>
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

void print_list(void* stt, int(*get_value)(const void*), void*(*nextp)(const void*))
{
    void* current = stt;
    void* tmp;
    while((tmp = nextp(current)))
    {
        printf("%i ", get_value(current));
        current = tmp;
    }
    printf("%i\n", get_value(current));
}

int main()
{
#ifdef _WIN32
    system("color 0");
#endif
#ifdef _U16M
    _setmode(_fileno(stdout), _O_U16TEXT);
#endif

    // int num[256] = { 0 };

    lstree* head = calloc(1, sizeof(lstree));
    if (!head)
    {
        logerr("calloc");
        exit(-1);
    }

    *head = (lstree)
    {
        .freq = 10,
        .val  = 1
    };

    inters ine = (inters)
    {
        .get_vals = get_values,
        .compar   = compare,
        .equcmp   = equcmp,
        .nextp    = nextp,
        .nextptr  = nextptr
    };

    lstree* obj;
    {
        tuple stin = (tuple)
        {
            .st0 = 2,
            .st1 = 10,
        };
        obj = (lstree*)create(&stin);
        if (!obj)
        {
            logerr("craete");
            
            free(head);
            exit(-1);
        }
    }

    lstree* obj2;
    {
        tuple stin = (tuple)
        {
            .st0 = 0,
            .st1 = 10
        };
        obj2 = (lstree*)create(&stin);
        if (!obj2)
        {
            logerr("create");
            free(obj);
            free(head);
            exit(-1);
        }
    }

    printf("\x1b[32mInserting:\x1b[34m %i %i\x1b[0m\n", obj2->val, obj2->freq);
    insert_sorted((void**)&head, obj2, &ine);
    printf("\x1b[32mInserting:\x1b[34m %i %i\x1b[0m\n", obj->val, obj->freq);
    insert_sorted((void**)&head, obj , &ine);

    puts("head print");
    print_list(head, get_freq, nextp);
    puts("val print");
    print_list(head, get_val , nextp);

    
    puts("clean list");
    clean_list(head, nextp);

    return 0;
}