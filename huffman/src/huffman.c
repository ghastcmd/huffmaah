#include "huffman.h"
#include "lstree_list.h"
#include "lstree_bst.h"
#include "structs.h"

void print_huffman(const int64_t val)
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

void len_tree(const int val, void* param)
{
    int* len = (int*)param;
    *len += 1;
    if (val == '*' || val == '\\')
    {
        *len += 1;
    }
}

int bytelen_lstree(lstree* head)
{
    int len = 0;
    lstree_bst_foreach_wparam_preorder(head, len_tree, (void*)&len);
    return len;
}

void translate_elem(lstree* head, const char al, bool* found, int* len, int64_t* ret)
{
    bool side = false;
    
    const char* value = (char*)head->val;
    if (*value == al)
    {
        *found = true;
        return;
    }

    if (head->left && !*found)
    {
        translate_elem(head->left, al, found, len, ret);
        side = false;
    }
    
    if (head->right && !*found)
    {
        translate_elem(head->right, al, found, len, ret);
        side = true;
    }
    
    if (*found)
    {
        *len += 1;
        *ret = *ret << 1 | side;
    }
}

// ! ##### UNUSED ##### !
int64_t _ret_revbin_len(int64_t bin, uint8_t len)
{
    int64_t ret = 0;
    while(len--)
    {
        ret = ret << 1 | (bin & 1);
        bin = bin >> 1;
    }
    return ret;
}

lstree* read_dir_lstree(const char* pathname, int64_t* num)
{
    FILE* file = fopen(pathname, "r");
    if (!file)
    {
        logerr("fopen");
        exit(-1);
    }

    lstree* head = nullptr;
    uint8_t al;

    fseek(file, 0, SEEK_END);
    size_t fsize = ftell(file);
    rewind(file);

    int64_t step = fsize / 25;
    step = step == 0 ? 1 : step;

    puts(YC"/Getting frequency of bytes\\"ZC);
    puts(BWC" --------------------------"GC);
    putchar(' ');
    while (fsize--)
    {
        if (fsize % step == 0)
        {
            putchar('#');
        }
        al = fgetc(file);
        num[(unsigned int)al] += 1;
    }
    puts(BWC"\nClosing file");
    fclose(file);

    puts(BMC"Creating tree...");
    for (int i = 0; i < 256; i++)
    {
        if (num[i] > 0)
        {
            lstree_add_val(&head, i, num[i]);
        }
    }

    lstree_bst_treeify(&head);  
    puts(BGC"Created successfully"ZC);

    return head;
}

void parse_tree_toarr(lstree* head, int64_t* num, int64_t* vals)
{
    num[256] = bytelen_lstree(head);

    for (int i = 0; i < 256; i++)
    {
        if (num[i] > 0)
        {
            bool flag = false;
            int len = 0;
            int64_t ret = 0;
            translate_elem(head, (char)i, &flag, &len, &ret);
            vals[i] = ret; // the value is bit reversed
            num[i] = len;
        }
    }
}

void write_dir_lstree(int64_t* bins, int64_t* lens, const char* infile, const char* outfile)
{
    FILE* filein = fopen(infile,  "r+");
    FILE* file   = fopen(outfile, "w+");

    puts(BBC"Writing len of file");
    fprintf(file, "%c%c", (char)lens[256] & 0xf0, (char)lens[256] & 0x0f);

    puts("Writing data to file"ZC);
    uint8_t i = 0;
    uint64_t idx = 0;
    int8_t chr = 0;
    int8_t byte = 0;
    bool already = false;

    fseek(filein, 0, SEEK_END);
    uint64_t fsize = ftell(filein); // getting the size of the file
    rewind(filein);

    printf(BMC"File size: "BGC"%"PRIu64""BMC" bytes\n"ZC, fsize);

    puts(YC"/Writing data to output file\\"BC);
    puts(BWC" ---------------------------"GC);
    putchar(' ');
    int64_t step = (int64_t)fsize / (int64_t)26;
    step = step == 0 ? 1 : step;
    while(fsize--)
    {
        chr = fgetc(filein);
        int64_t len = lens[(uint8_t)chr];
        i = 0;
        while(len--)
        {
            byte = byte << 1 | (int8_t)((bins[(uint8_t)chr] >> i) & 1);
            i++;
            idx++;
            if (idx % 8 == 0)
            {
                fprintf(file, "%c", byte);
                already = true;
                byte = 0;
            }
        }

        if (fsize % step == 0)
        {
            putchar('#');
        }

        if (idx % 8 == 0 && !already)
        {
            fprintf(file, "%c", byte);
            byte = 0;
        }
        else
        {
            already = false;
        }
    }

    puts(BMC"\nWriting trash bytes"ZC);
    int8_t trash = 0;
    if (idx % 8 != 0)
    {
        trash = 8 - idx % 8;
        fprintf(file, "%c", byte << trash);
    }

    rewind(file);
    char tmp = fgetc(file);
    rewind(file);
    fprintf(file, "%c", tmp | (trash << 5));

    puts("Closing files...");
    fclose(filein);
    fclose(file);
}

void rw_dir_lstree(const char* infile, const char* outfile)
{
    int64_t* num = (int64_t*)calloc(257, sizeof(int64_t));
    puts("Opening file");
    lstree* head = read_dir_lstree(infile, num);
    
    int64_t* bins = (int64_t*)calloc(257, sizeof(int64_t));
    parse_tree_toarr(head, num, bins);


    puts(BBC"Transfered values from tree to arrays"ZC);
    lstree_clean_tree(head);
    puts(GC"Successfully free'd memory from tree"ZC);

    write_dir_lstree(bins, num, infile, outfile);
    puts(GC"Successfully writen values to file"ZC);
    puts(BMC"Freeing memory..."ZC);
    free(num);
    free(bins);
    puts(BGC"* Compression was successfully executed *"ZC);
}

void print_lstree(lstree* head)
{
    lstree_bst_foreach_preorder(head, print_huffman);
    puts("");
}