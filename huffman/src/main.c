#include <pch.h>
#include "structs.h"
#include "huffman.h"

int main()
{
    #ifdef _WIN32
    system("color 0");
    #endif
    #ifdef _U16M
    _setmode(_fileno(stdout), _O_U16TEXT);
    #endif

    lstree* head = read_dir("test.txt");

    print_lstree(head);

    clean_lstree(head);
    
    return 0;
}