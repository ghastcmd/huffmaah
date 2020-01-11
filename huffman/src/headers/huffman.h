#pragma once
#include <pch.h>
#include "structs.h"

lstree* read_dir(const char* pathname);

void print_lstree(lstree* head);
void clean_lstree(lstree* head);