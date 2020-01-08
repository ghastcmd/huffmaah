#include "linkedList.h"

void* nextp_l(void* stt)
{
    lstree* ls = (lstree*)stt;
    return ls->next;
}

void insert_sorted(void** stt, void* stin, inters* ine)
{
    if (!*stt)
    {
        *stt = stin;
        return;
    }
    int cmp  = ine->compar(stin, *stt);
    int cmpe = ine->equcmp(stin, *stt);
    if (cmp < 0 || (cmp == 0 && cmpe < 0))
    {
        // * ************************ *
        // *    put stin before stt   *
        // * ************************ *
        void** innextptr = ine->nextptr(stin);
        *innextptr       = *stt;
        *stt             = stin;
        return;
    }
    else if (cmp == 0)
    {
        ine->compar = ine->equcmp;
    }

    void* current = *stt;
    void* trail   = *stt;

    void* tmp;
    while ((tmp = ine->nextp(current)))
    {
        current = tmp;
        cmp  = ine->compar(stin, current);
        cmpe = ine->equcmp(stin, current);
        if (cmp < 0 || (cmp == 0 && cmpe < 0))
        {
            // * ************************** *
            // *  stick stin where it fits  *
            // * ************************** *
            void** trnextptr = ine->nextptr(trail);
            *trnextptr       = stin;
            void** innextptr = ine->nextptr(stin);
            *innextptr       = current;
            return;
        }
        else if (cmp == 0)
        {
            ine->compar = ine->equcmp;
        }
        trail = current;
    }

    void** curnxptr = ine->nextptr(current);
    *curnxptr = stin;
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

void free_list(void* stt, void*(*nextp)(const void*))
{
    if (stt)
    {
        free_list(nextp(stt), nextp);
        free(stt);
    }
}