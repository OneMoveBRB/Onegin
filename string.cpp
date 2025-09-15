#include "string.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


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

ssize_t getline_(char** line, size_t* n, FILE* fp) {
    assert( n != NULL );
    assert( fp != NULL );


    const int fst_size = 5;
    const int exp_multiplier = 2;
    if (*n == 0) {
        *n = fst_size;
        *line = (char *)calloc(*n, sizeof(char));
    }

    // FIXME n и line в переменную  // ЧТО это значит? Как?
    int c = 0;
    size_t line_size = 0;
    while ( (c = getc(fp)) != EOF ) {
        if (line_size + 2 > *n) {
            *n *= exp_multiplier;
            *line = (char*)realloc(*line, *n);
        }
        (*line)[line_size++] = (char)c;
        if (c == '\n') break;
    }

    if (line_size == 0) {
        *n = 0;
        free(*line);
        *line = NULL;
        return EOF;
    } else {
        *n = line_size + 1;
        *line = (char*)realloc(*line, *n);
        (*line)[line_size] = '\0';
    }

    return (ssize_t)line_size;
}
