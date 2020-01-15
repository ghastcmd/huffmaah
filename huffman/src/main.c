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

    printf("%c %c\n\n", 217, 218);

    rw_dir_lstree("test.txt", "test.huff");
    // rw_dir_lstree("Brackets.msi", "test.huff");
    // rw_dir_lstree("movie.mkv", "test.huff");

    return 0;
}