#include <pch.h>
#include "structs.h"
#include "lstree_list.h"

int main()
{
    #ifdef _WIN32
    system("color 0");
    #endif
    #ifdef _U16M
    _setmode(_fileno(stdout), _O_U16TEXT);
    #endif
    
    // int num[256] = { 0 };

    lstree* head = nullptr;

    printf("%p\n", head);

    lstree_add(&head, 1, 10);
    lstree_add(&head, 10, 1);
    lstree_add(&head, 0, 10);
    lstree_add(&head, 4, 20);
    lstree_add(&head, 2, 10);

    puts("\x1b[94mprint freqs\x1b[0m");
    lstree_print_freq(head);
    puts("\x1b[94mprint vals\x1b[0m");
    lstree_print_vals(head);

    return 0;
}