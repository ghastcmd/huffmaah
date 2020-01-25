#include "huffman.h"
#include "lstree_list.h"
#include "lstree_bst.h"
#include "structs.h"

// Used by prin_lstree
void _print_huffman(const int64_t val)
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

// Prints lstree as preorder to stdout
void print_lstree(lstree* head)
{
    lstree_bst_foreach_preorder(head, _print_huffman);
    puts("");
}

// Used by print_lstree_dir
void _print_huffman_dir(const int64_t val, void* param)
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
    fprintf((FILE*)param, "%s", chr);
}

// Prints tree in preorder to a given file
void print_lstree_dir(lstree* head, FILE* fileout)
{
    lstree_bst_foreach_wparam_preorder(head, _print_huffman_dir, (void*)fileout);
}

// Used by bytelen_lstree
void _len_tree(const int64_t val, void* param)
{
    *(int*)param += 1;
    if (val == '*' || val == '\\')
    {
        *(int*)param += 1;
    }
}

/**
 * @param head: root pointer to lstree tree
 * @ret: the lenght of given tree in preorder
 */
int bytelen_lstree(lstree* head)
{
    int len = 0;
    lstree_bst_foreach_wparam_preorder(head, _len_tree, (void*)&len);
    return len;
}

/**
 * @brief: given an element, it translates to path inside tree
 * @param head: root pointer to lstree tree
 * @param al: the element to find
 * @param found: required to work (set it to false)
 * @param len: required to work (set it to 0)
 * @param ret: required to work (set it to 0)
 */
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

/**
 * @brief: gets the frequency of individual vaues inside file
 * and creates tree with it
 * @param pathname: the name of input file
 * @param num: array of 256 slots to store the frequency of bytes
 * @ret: pointer to root of the parsed tree
 */
lstree* read_dir_lstree(const char* pathname, int64_t* num)
{
    FILE* file = fopen(pathname, "rb");
    logerr_fopen(file, pathname, free(num));

    lstree* head = nullptr;
    uint8_t al = 0;

    fseek(file, 0, SEEK_END);
    uint64_t fsize = ftell(file); // getting lenght of file
    rewind(file);

    /* Those are only used for progress bar */
    int step = fsize / 50;
    step = step == 0 ? 1 : step;
    int len = 0, size = fsize / step;
    /* ------------------------------------ */

    puts(YC"/Getting frequency of bytes\\"WC);
    while (fsize--)
    {
        if (fsize % step == 0)
        {
            upbar(len++, size, WC);
        }
        al = fgetc(file);
        num[al] += 1;
    }
    upbar(len-1, size, GC);
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
    puts(GC"Created successfully"ZC);

    return head;
}


/**
 * @brief: translates the lstree tree into paths of values and lenghts of
 * bits of values
 * @param head: lstree root tree pointer
 * @param num: array to hold lenghts of bytes in bits
 * @param vals: array to hold paths in bits of bytes
 */
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

/**
 * @brief: converts the input file to huffman coding and puts to output file
 * @param bins: the paths of byte values into lstree
 * @param lens: the lenghts of bins
 * @param infile: filename of input file
 * @param outfile: filename of output file
 * @param head: pointer to root of lstree tree
 */
void write_dir_lstree(int64_t* bins, int64_t* lens, const char* infile, const char* outfile, lstree* head)
{
    FILE* filein = fopen(infile, "rb");
    logerr_fopen(filein, infile, free(bins); free(lens); lstree_clean_tree(head)); // error checking
    
    FILE* file = fopen(outfile, "wb+");
    logerr_fopen(file, outfile, free(bins); free(lens); fclose(filein); lstree_clean_tree(head)); // error checking

    printf(BBC"Writing len of tree to file: "BMC"%"PRIu16" bytes\n"BBC, (uint16_t)lens[256]);
    fprintf(file, "%c%c", (char)((lens[256] & 0xff00) >> 8), (char)lens[256] & 0xff);
    
    puts("Writing tree to file"ZC);
    print_lstree_dir(head, file);

    uint8_t i = 0;
    uint64_t idx = 0;
    int8_t chr = 0, byte = 0;
    bool already = false;

    fseek(filein, 0, SEEK_END);
    uint64_t fsize = ftell(filein); // getting the size of the file
    rewind(filein);

    printf(BMC"File size: "BGC"%"PRIu64""BMC" bytes\n"ZC, fsize);

    puts(YC"/Writing data to output file\\"BC);
    int64_t step = (int64_t)fsize / (int64_t)50;
    step = step == 0 ? 1 : step;
    int barlen = 0, size = fsize / step;
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
            upbar(barlen++, size, WC);
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
    upbar(barlen-1, size, GC);

    puts(BMC"\nWriting trash bytes"ZC);
    int8_t trash = 0;
    // Writes the resting bits to file
    if (idx % 8 != 0)
    {
        trash = 8 - idx % 8;
        fprintf(file, "%c", byte << trash);
    }
    puts("Closing files...");

    rewind(file);
    uint8_t tmp = fgetc(file); // getting first byte of file
    rewind(file);
    // Writes the trash into the first byte of file
    fprintf(file, "%c", tmp | (trash << 5));

    fseek(file, 0, SEEK_END);
    printf(BMC"Output file size: "BGC"%"PRId64""BMC" bytes\n"ZC, (int64_t)ftell(file));
    fclose(filein);
    fclose(file);
}

/**
 * @brief: compress an archive using the huffman algorithm
 * @param infile: the pathname of input file
 * @param outfile: the pathname of output file
 */
void rw_dir_lstree(const char* infile, const char* outfile)
{
    int64_t* num = (int64_t*)calloc(256, sizeof(int64_t));
    logerr_calloc(num,);

    printf("Compressing %s to output %s", infile, outfile);
    puts("Opening file");
    lstree* head = read_dir_lstree(infile, num);

    int64_t* bins = (int64_t*)calloc(256, sizeof(int64_t));
    logerr_calloc(bins, free(num));

    parse_tree_toarr(head, num, bins);
    puts(BBC"Transfered values from tree to arrays"ZC);

    write_dir_lstree(bins, num, infile, outfile, head);
    puts(GC"Successfully writen values to file"ZC);

    lstree_clean_tree(head);
    puts(GC"Successfully free'd memory from tree"ZC);

    puts(BMC"Freeing memory local heap arrays..."ZC);
    free(num);
    free(bins);

    puts(BGC"* Compression was successfully executed *"ZC);
}