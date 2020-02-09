#pragma once
#include "pch.h"
#include "structs.h"

// Compresses a file
void rw_dir_lstree(const char* infile, const char* outfile);

// Decompresses a file
void rw_dir_huff(const char* filein, const char* fileout);

// Prints lstree in preorder to a given file handler
void print_lstree_dir(lstree* head, FILE* fileout);

// Prints the lstree tree in preorder
void print_lstree(lstree* head);

// Makes a 'progress bar'
void upbar(const int len, const int size, const char* color);

// Prints tree encapsulated by </>
void print_tree(lstree* head);

// Returns the huffman format tree character count
int bytelen_lstree(lstree* head);

// Parses a lstree in preorder to char string
void parse_lstree_string(lstree* head, char* arr, int* i);