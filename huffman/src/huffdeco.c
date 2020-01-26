#include "huffman.h"
#include "structs.h"
#include "lstree_bst.h"

void make_decomp(lstree* head, const int8_t trash, FILE* infile, FILE* outfile)
{
    int64_t fsize;
    {
        uint64_t pos = ftell(infile);
        fseek(infile, 0, SEEK_END);
        fsize = ftell(infile) - pos; // getting lenght of input file
        fseek(infile, pos, SEEK_SET);
    }

    int64_t step = (int64_t)fsize / (int64_t)50;
    step = step == 0 ? 1 : step;
    int barlen = 0, size = fsize / step;

    lstree* current = head;
    uint8_t right, byte, ini = 0;
    while (fsize--)
    {
        if (fsize == 0)
        {
            ini = trash;
        }

        if (fsize % step == 0)
        {
            upbar(barlen++, size, WC);
        }

        byte = fgetc(infile);
        for (int8_t i = 7; i >= ini; i--)
        {
            right = (byte >> i) & 1u;
            if ((right && !current->right) || (!right && !current->left))
            {
                puts("The archive is incompatible with the program");
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
    upbar(barlen-1, size, GC);
}

void rw_dir_huff(const char* filein, const char* fileout)
{
    printf(BBC"Decompressing "GC"%s"BBC" to output "GC"%s\n"ZC, filein, fileout);
    puts("Opening input file");
    FILE* infile = fopen(filein, "rb");
    logerr_fopen(infile, filein,);

    puts(BBC"Getting lenght of tree"ZC);
    uint16_t tree_len = fgetc(infile);
    uint8_t trash = tree_len >> 5;

    tree_len = ((tree_len << 8) & 0x1fff) | fgetc(infile);

    puts(BMC"Mounting tree..."ZC);
    char* tree_fmt = (char*)calloc(tree_len, sizeof(char));
    logerr_calloc(tree_fmt, fclose(infile));

    for (int64_t i = 0, len = tree_len; len--; i++)
    {
        tree_fmt[i] = fgetc(infile);
    }

    lstree* head = lstree_bst_make_tree(tree_fmt, (uint64_t)tree_len);
    free(tree_fmt);
    puts(GC"Mounted successfully"ZC);

    puts("Opening file output");
    FILE* outfile = fopen(fileout, "wb+");
    logerr_fopen(outfile, fileout, fclose(infile));

    puts(YC"/Decompressing archive\\"ZC);
    make_decomp(head, trash, infile, outfile);
    
    puts(BMC"\nFreeing heap..."ZC);
    lstree_clean_tree(head);
    puts("Closing files");
    fclose(outfile);
    fclose(infile);

    puts(BGC"* Decompression was successfully executed *\n"ZC);
}