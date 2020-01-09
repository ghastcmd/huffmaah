#include "linkedList.h"

void ListInsertSorted(void** stn, void* stin, inters* ine)
{
    if (!*stn)
    {
        *stn = stin;
        return;
    }
    int cmp  = ine->compar(stin, *stn);
    int cmpe = ine->equcmp(stin, *stn);
    if (cmp < 0 || (cmp == 0 && cmpe < 0))
    {
        // * ************************ *
        // *    put stin before stn   *
        // * ************************ *
        void** innextptr = ine->nextptr(stin);
        *innextptr       = *stn;
        *stn             = stin;
        return;
    }
    else if (cmp == 0)
    {
        ine->compar = ine->equcmp;
    }

    void* current = *stn;
    void* trail   = *stn;

    void* tmp;
    int(*comparo)(const void*, const void*) = ine->compar;
    while ((tmp = ine->nextp(current)))
    {
        current = tmp;

        cmp  = ine->compar(stin, current);
        cmpe = ine->equcmp(stin, current);
        // int tmpval;
        // if ((tmpval = comparo(stin, current)) == 0)
        // {
        //     continue;
        //     ine->compar = ine->equcmp;
        // }
        // else
        // {
        //     cmp = tmpval;
        //     ine->compar = comparo;
        // }

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
        else if (cmp == 0 && cmpe > 0)
        {

        }
        
        comparo(stin, current);
        trail = current;
    }

    void** curnxptr = ine->nextptr(current);
    *curnxptr = stin;
}

void ListPrint(void* stn, int(*get_value)(const void*), void*(*nextp)(const void*))
{
    void* current = stn;
    void* tmp;
    while((tmp = nextp(current)))
    {
        printf("%i ", get_value(current));
        current = tmp;
    }
    printf("%i\n", get_value(current));
}

void ListFPrint(void* stn, int(*get_value)(const void*), void*(*nextp)(const void*), const char* fmt)
{
    void* current = stn;
    while(current)
    {
        printf(fmt, get_value(current));
        current = nextp(current);
    }
}

void ListFree(void* stn, void*(*nextp)(const void*))
{
    if (stn)
    {
        ListFree(nextp(stn), nextp);
        free(stn);
    }
}

void* ListPop(void** stn, void*(*nextp)(const void*))
{
    void* stou = *stn;
    *stn = nextp(*stn);
    return stou;
}