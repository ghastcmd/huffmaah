#include <pch.h>
#include "structs.h"
#include "lstree_list.h"
#include "lstree_bst.h"

void print_tree(const int val)
{
    char chr[3] = { 0 };
    chr[0] = val;
    switch(val)
    {
    case FLAG:
        chr[0] = '*';
        break;
    case '*':
        strcpy(chr, "\\*");
        break;
    case '\\':
        strcpy(chr, "\\\\");
    }
    printf("%s", chr);
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

    lstree* head = nullptr;

    lstree_add_val(&head, 'C', 4);
    lstree_add_val(&head, 'B', 5);
    lstree_add_val(&head, 'F', 1);
    lstree_add_val(&head, 'E', 2);
    lstree_add_val(&head, 'D', 3);
    lstree_add_val(&head, 'A', 6);

    lstree_print_char(head);
    lstree_print_freq(head);
    lstree_print_vals(head);

    lstree_bst_treeify(&head);

    lstree_bst_foreach_preorder(head, print_tree);
    puts("");

    lstree_clean_tree(head);

    return 0;
}