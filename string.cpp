#include "string.h"

#include <stdio.h>


int strcmp_(const char* str1, const char* str2) {
    while (*str1 == *str2 && *str1 != '\0') {
        ++str1; ++str2;
    }

    if (*str1 == '\0' && *str2 == '\0') return 0;
    if (*str1 < *str2) return -1;
    return 1;
}

int fputs_(const char* str, FILE* stream) {
    if (str == NULL) return EOF;

    while (*str != '\0') {
        if (fputc(*str, stream) == EOF) return EOF;
        ++str;
    }

    return *(str-1);
}
