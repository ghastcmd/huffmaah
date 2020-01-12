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

    rw_dir_lstree("Brackets.msi", "test.huff");

    return 0;
}