#include <pch.h>
#include "structs.h"
#include "lstree_list.h"
#include "lstree_bst.h"

void print_tree(lstree* head)
{
    if (!head) return;
    printf("%c ", head->val);
    print_tree(head->left);
    print_tree(head->right);
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

    puts("\x1b[94mprint freqs before\x1b[0m");
    lstree_print_freq(head);
    puts("\x1b[94mprint vals before\x1b[0m");
    lstree_print_vals(head);
    puts("\x1b[94mprint chars before\x1b[0m");
    lstree_print_char(head);

    puts("");
    lstree_bst_treeify(&head);
    
    lstree_bst_printf_preorder(head, "%c");

    puts("\x1b[94mprint freqs\x1b[0m");
    lstree_print_freq(head);
    puts("\x1b[94mprint vals\x1b[0m");
    lstree_print_vals(head);
    puts("\x1b[94mprint chars\x1b[0m");
    lstree_print_char(head);

    return 0;
}