#include "huffman.h"
#include "lstree_list.h"
#include "lstree_bst.h"
#include "structs.h"

void print_huffman(const int val)
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

lstree* read_dir_lstree(const char* pathname)
{
    FILE* file = fopen(pathname, "rb");
    if (!file)
    {
        logerr("fopen");
        exit(-1);
    }

    lstree* head = nullptr;
    int8_t al;
    int64_t num[256] = { 0 };

    while ((al = fgetc(file)) != EOF)
    {
        num[(int)al] += 1;
    }

    for (int i = 0; i < 256; i++)
    {
        if (num[i] > 0)
        {
            lstree_add_val(&head, i, num[i]);
        }
    }

    lstree_bst_treeify(&head);

    fclose(file);

    return head;
}

void print_lstree(lstree* head)
{
    lstree_bst_foreach_preorder(head, print_huffman);
    puts("");
}

void clean_lstree(lstree* head)
{
    if (head->next)
    {
        lstree_clean_list(head);
    }
    else
    {
        lstree_clean_tree(head);
    }
}