#pragma once
#include <pch.h>
#include "structs.h"

// Compresses a file
void rw_dir_lstree(const char* infile, const char* outfile);

// Decompresses a file
void rw_dir_huff(const char* filein, const char* fileout);

// Prints the lstree tree in preorder
void print_lstree(lstree* head);

// Makes a 'progress bar'
void upbar(const int len, const int size, const char* color);

// Prints tree encapsulated by </>
void print_tree(lstree* head);