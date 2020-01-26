#include "huffman.h"
#include "structs.h"
#include "lstree_bst.h"

void make_decomp(lstree* head, const int8_t trash, FILE* infile, FILE* outfile)
{
    int64_t size;
    {
        uint64_t pos = ftell(infile);
        fseek(infile, 0, SEEK_END);
        size = ftell(infile) - pos; // getting lenght of input file
        fseek(infile, pos, SEEK_SET);
    }

    printf("trash: %i\n", trash);

    lstree* current = head;
    uint8_t right, byte, ini = 0;
    while (size--)
    {
        if (size == 0)
        {
            ini = trash;
        }

        byte = fgetc(infile);
        for (int8_t i = 7; i >= ini; i--)
        {
            right = (byte >> i) & 1u;
            if ((right && !current->right) || (!right && !current->left))
            {
                puts("none");
                return;
            }
            if (right)
            {
                current = current->right;
            }
            else
            {
                current = current->left;
            }
            
            int64_t chr;
            if ((chr = *(int64_t*)(current->val)) != FLAG)
            {
                fputc((char)chr, outfile);
                current = head;
            }
        }
    }
}

void rw_dir_huff(const char* filein, const char* fileout)
{
    FILE* infile = fopen(filein, "rb");
    logerr_fopen(infile, filein,);

    uint16_t tree_len = fgetc(infile);
    uint8_t trash = tree_len >> 5;

    tree_len = ((tree_len << 8) & 0x1fff) | fgetc(infile);

    char* tree_fmt = (char*)calloc(tree_len, sizeof(char));
    logerr_calloc(tree_fmt, fclose(infile));

    for (int64_t i = 0, len = tree_len; len--; i++)
    {
        tree_fmt[i] = fgetc(infile);
    }

    lstree* head = lstree_bst_make_tree(tree_fmt, (uint64_t)tree_len);
    free(tree_fmt);

    FILE* outfile = fopen(fileout, "wb+");
    logerr_fopen(outfile, fileout, fclose(infile));

    puts("making decomp");
    make_decomp(head, trash, infile, outfile);
    
    lstree_clean_tree(head);
    fclose(outfile);
    fclose(infile);
}