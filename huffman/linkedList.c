#include "linkedList.h"

void insert_sorted(void* head, intes* ine)
{
    puts("ewqeqw");
    lstree* current = head;

    printf("(%i)\n", ine->get_value(head));

    printf("-%i-\n", current->val);

    lstree** another_value = (lstree**)&head;
    free(head);
    *another_value = (lstree*)calloc(1, sizeof(lstree));
    (*another_value)->val = 20;
}

// void insert_sorted(lstree* head, int freq, int val)
// {
//     if (val <= head->val)
//     {
//         if (head->freq);
//     }
// }