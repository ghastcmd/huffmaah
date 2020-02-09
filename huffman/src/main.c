#include "pch.h"
#include "huffman.h"

enum options
{
    none,
    comp,
    decomp,
    out
};

char* prog_path;
int argcount;

void do_opt(char* buffer, char* output, enum options opt);
enum options get_opt(const char* argument);
void usage();
void low_args();

int main(int argc, char** argv)
{
#ifdef _WIN32
    system("color 0");
#endif
#ifdef _U16M
    _setmode(_fileno(stdout), _O_U16TEXT);
#endif
    prog_path = argv[0];
    argcount = argc;

    if (argc == 1)
    {
        puts("Invalid option");
        usage();
        return 0;
    }

    char buffer[512] = { 0 };
    char output[512] = { 0 };
    for (int i = 1; i < argc; i++)
    {
        enum options opt = get_opt(argv[i]);

        i++; // getting input file path
        if (i >= argc) low_args();
        strncpy(buffer, argv[i++], 512);

        if (i < argc && get_opt(argv[i]) == out)
        {
            i++;
            if (i >= argc) low_args();
            strncpy(output, argv[i], 512);
        }
        else
        {
            i--;
            strncpy(output, opt == comp ? "out.huff" : "out.e", 9);
        }
        if (i == argc-2) low_args();
        do_opt(buffer, output, opt);
    }

    return 0;
}

void low_args()
{
    puts("Insuficient arguments");
    usage();
    exit(0);
}

void usage()
{
    puts("Usage: ");
    printf("\t%s -[c|d] <input> [-o <output> (optional)]\n", prog_path);
    puts("\t[-c] compress an input to output");
    puts("\t[-d] decompress an input to output");
    puts("\tDefault compression output is 'out.huff' and decompression output is 'out.e'");
}

enum options get_opt(const char* argument)
{
    if (!strncmp(argument, "-c", 3))
    {
        return comp;
    }
    else if (!strncmp(argument, "-d", 3))
    {
        return decomp;    
    }
    else if (!strncmp(argument, "-o", 3))
    {
        return out;
    }
    else
    {
        return none;
    }
}

void do_opt(char* input, char* output, enum options opt)
{
    switch(opt)
    {
    case comp:
        rw_dir_lstree(input, output);
    break;
    case decomp:
        rw_dir_huff(input, output);
    break;
    default:
        puts("Invalid option");
        usage();
        exit(0);
    }
}