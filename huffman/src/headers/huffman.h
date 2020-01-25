#pragma once
#include <pch.h>
#include "structs.h"

// Compresses a file
void rw_dir_lstree(const char* infile, const char* outfile);

// Decompresses a file
void rw_dir_huff(const char* filein, const char* fileout);

void print_lstree(lstree* head);