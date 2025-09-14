#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


char** inputText(FILE* fp, size_t* arr_len);
inline void printText(char** text, FILE* stream);
inline void freeText(char** text, size_t text_len);
int fputs_(const char* str, FILE* stream);

int main() {
    FILE* fp = fopen("onegin.txt", "r");
    
    size_t text_len = 0;
    char** text = inputText(fp, &text_len);

    printText(text, stdout);
    
    if (text != NULL) freeText(text, text_len);    

    return 0;
}

char** inputText(FILE* fp, size_t* arr_len) {
    assert( fp!= NULL );
    assert( arr_len!= NULL );


    const size_t first_size = 10;

    size_t strings_cur_len = 0;
    size_t strings_len = first_size;
    char** strings = (char**)calloc(sizeof(NULL), first_size);

    size_t line_len = 0;
    char* line = NULL;

    while( getline(&line, &line_len, fp) != EOF ) {
        if (strings_cur_len + 1 == strings_len) {
            strings_len *= 2;
            strings = (char**)realloc(strings, sizeof(NULL)*strings_len);
        }

        strings[strings_cur_len] = (char*)calloc(sizeof(char), line_len);
        strcpy(strings[strings_cur_len], line);
        ++strings_cur_len;

        free(line);
        line = NULL;
    }
    if (line != NULL) free(line);
    
    *arr_len = strings_cur_len;
    
    if (strings_cur_len == 0) {
        free(strings);
        return NULL;
    }
    
    return strings;
}

inline void printText(char** text, FILE* stream) {
    while ( fputs_(*text, stream) != EOF ) {
        ++text;
    }
}

inline void freeText(char** text, size_t text_len) {    
    for (size_t i = 0; i < text_len; ++i) {
        free(text[i]);
    }

    free(text);
}

int fputs_(const char* str, FILE* stream) {
    if (str == NULL) return EOF;

    while (*str != '\0') {
        if (fputc(*str, stream) == EOF) return EOF;
        ++str;
    }

    return *(str-1);
}
