#pragma once

#include <stdio.h>


int strcmp_(const char* str1, const char* str2);
int fputs_(const char* str, FILE* stream);
ssize_t getline_(char** line, size_t* n, FILE* fp);
