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
    puts("opened file");

    lstree* head = nullptr;
    uint8_t al;

    while (fscanf(file, "%c", &al) != EOF)
    {
        num[(unsigned int)al] += 1;
    }
    puts("closing file");
    fclose(file);

    puts("creating tree...");
    for (int i = 0; i < 256; i++)
    {
        if (num[i] > 0)
        {
            lstree_add_val(&head, i, num[i]);
        }
    }

    lstree_bst_treeify(&head);  
    puts("created successfully");

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

    puts("writing len of file");
    fprintf(file, "%c%c", (char)lens[256] & 0xf0, (char)lens[256] & 0x0f);

    puts("writing data to file");
    uint8_t i = 0;
    uint64_t idx = 0;
    int8_t chr = 0;
    int8_t byte = 0;
    bool already = false;

    fseek(filein, 0, SEEK_END);
    size_t fsize = ftell(filein); // getting the size of the file
    rewind(filein);

    uint64_t factor = fsize / 20;
    while(fsize--)
    {
        fscanf(filein, "%c", &chr);
        if (ferror(filein))
        {
            logerr("fscanf");
            puts("pau nas quebrada");
        }
        // printf("%02X ", chr);
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

        if (idx % factor == 0)
        {
            printf("#");
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

    fclose(filein);
    fclose(file);
}

void rw_dir_lstree(const char* infile, const char* outfile)
{
    int64_t* num = (int64_t*)calloc(257, sizeof(int64_t));
    puts("opening file");
    lstree* head = read_dir_lstree(infile, num);
    
    puts("made tree successfully");
    int64_t* bins = (int64_t*)calloc(257, sizeof(int64_t));
    parse_tree_toarr(head, num, bins);


    puts("transfered values from tree to arrays");
    lstree_clean_tree(head);
    puts("successfully free'd memory from tree");

    write_dir_lstree(bins, num, infile, outfile);
    puts("\nsuccessfully writen values to file");
    puts("freeing memory...");
    free(num);
    free(bins);
    puts("free'd memory");
}

void print_lstree(lstree* head)
{
    lstree_bst_foreach_preorder(head, print_huffman);
    puts("");
}