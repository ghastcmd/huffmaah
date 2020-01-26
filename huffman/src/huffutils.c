#include "huffman.h"
#include "lstree_bst.h"

// Used by prin_lstree
void _print_huffman(const int64_t val)
{
    char chr = (char)val;
    switch(val)
    {
    case FLAG:
        chr = '*';
        break;
    case (int64_t)'*' || (int64_t)'\\':
        putchar('\\');
    }
    putchar(chr);
}

// Prints lstree as preorder to stdout
void print_lstree(lstree* head)
{
    lstree_bst_foreach_preorder(head, _print_huffman);
    puts("");
}

void print_tree(lstree* head)
{
    if (!head) return;
    const int64_t al = *(int64_t*)(head->val);
    if ((char)al == '*' || (char)al == '\\') putchar('\\');
    printf("%c<", al == FLAG ? '*' : (char)al);
    print_tree(head->left);
    print_tree(head->right);
    putchar('>');
}

/**
 * @brief: creates a progress bar given color, size and leght
 * @param len: the current lenght of bar
 * @param size: the total lenght of bar
 * @param color: color of the bar
 */
void upbar(const int len, const int size, const char* color)
{
    char buffer[512];
    int i = 0;
    for (i = 0; i < size; i++)
    {
        buffer[i] = '\b';
    }
    {
        size_t clen = strlen(color);
        memcpy(buffer + i, color, clen);
        i += clen;
    }
    for (int j = 0; j < len; j++, i++)
    {
        buffer[i] = 219;
    }
    {
        size_t clen = strlen(WC); 
        memcpy(buffer + i, WC, clen);
        i += clen;
    }
    for (int j = size - 1; j > len; j--, i++)
    {
        buffer[i] = 221;
    }
    buffer[i] = 0;
    printf(buffer);
}