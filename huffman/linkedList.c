#include "linkedList.h"

void insert_sorted(void** stt, void* stin, inters* ine)
{
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
        inters tmpine;
        memcpy(&tmpine, ine, sizeof(inters));

        tmpine.compar = ine->equcmp;
        tmpine.equcmp = ine->compar;

        insert_sorted(stt, stin, &tmpine);
        return;
    }

    void* current = *stt;
    void* trail   = *stt;

    void* tmp;
    while ((tmp = ine->nextp(current)))
    {
        current = tmp;
        cmp  = ine->compar(stin, current);
        cmpe = ine->equcmp(stin, current);
        if (cmp < 0)
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
        trail = current;
    }

    void** curnxptr = ine->nextptr(current);
    *curnxptr = stin;
}

void clean_list(void* stt, void*(*nextp)(const void*))
{
    if (stt)
    {
        clean_list(nextp(stt), nextp);
        free(stt);
    }
}