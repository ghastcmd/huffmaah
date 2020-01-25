#include "huffman.h"
#include "structs.h"
#include "lstree_bst.h"

void rw_dir_huff(const char* filein, const char* fileout)
{
    FILE* infile = fopen(filein, "rb");
    logerr_fopen(infile, filein,);

    uint16_t tree_len = fgetc(infile);
    uint8_t thrash = tree_len >> 5;

    tree_len = ((tree_len << 8) & 0x1fff) | fgetc(infile);

    printf("%i %i %i\n", thrash, tree_len, 0x1fff);

    char* tree_fmt = (char*)calloc(tree_len, sizeof(char));
    logerr_calloc(tree_fmt, fclose(infile));

    puts("starting shites");

    for (uint64_t i = 0, len = tree_len; len--; i++)
    {
        tree_fmt[i] = fgetc(infile);
    }

    puts("doind the shiz");

    lstree* head = lstree_bst_make_tree(tree_fmt, (uint64_t)tree_len);

    print_lstree(head);

    puts("did the shit");

    free(tree_fmt);
    fclose(infile);
}