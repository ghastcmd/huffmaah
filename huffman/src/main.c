#include <pch.h>
#include "huffman.h"

#include "CUnit/CUnit.h"

int main(int argc, char** argv)
{
    #ifdef _WIN32
    system("color 0");
    #endif
    #ifdef _U16M
    _setmode(_fileno(stdout), _O_U16TEXT);
    #endif
    
    puts("Initialized...");

    if (argc >= 2)
    {
        if (!strncmp(argv[1], "png", 3))
        {
            rw_dir_lstree("image.png", "test.huff");
            rw_dir_huff("test.huff", "output.png");
        }
        else if (!strncmp(argv[1], "msi", 3))
        {
            rw_dir_lstree("Brackets.msi", "test.huff");
            rw_dir_huff("test.huff", "output.msi");
        }
    }
    else
    {
        rw_dir_lstree("test.txt", "test.huff");
        rw_dir_huff("test.huff", "output.txt");
    }
    
    return 0;
}