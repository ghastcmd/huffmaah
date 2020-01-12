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
    FILE* file = fopen(pathname, "rb");
    if (!file)
    {
        logerr("fopen");
        exit(-1);
    }

    lstree* head = nullptr;
    int8_t al;

    while ((al = fgetc(file)) != EOF)
    {
        num[(int)al] += 1;
    }
    fclose(file);

    for (int i = 0; i < 256; i++)
    {
        if (num[i] > 0)
        {
            lstree_add_val(&head, i, num[i]);
        }
    }

    lstree_bst_treeify(&head);  

    return head;
}

void write_dir_lstree(lstree* head, int64_t* num)
{
    const int bytelen = bytelen_lstree(head);
    printf("bytelen %i\n", bytelen);

    for (int i = 0; i < 256; i++)
    {
        if (num[i] > 0)
        {
            bool flag = false;
            int len = 0;
            int64_t ret = 0;
            translate_elem(head, (char)i, &flag, &len, &ret);
            const int64_t _ret = _ret_revbin_len(ret, len);
            printf("%"PRId64"\n", _ret);
        }
    }
}

void rw_dir_lstree(const char* filepath)
{
    int64_t num[256] = { 0 };
    lstree* head = read_dir_lstree(filepath, num);
    write_dir_lstree(head, num);

    lstree_clean_tree(head);
}

void print_lstree(lstree* head)
{
    lstree_bst_foreach_preorder(head, print_huffman);
    puts("");
}