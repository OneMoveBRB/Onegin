#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


char** inputText(FILE* fp, size_t* arr_len);
void merge_sort(char** text, size_t l, size_t r);
void printText(char** text, FILE* stream);
void freeText(char** text, size_t text_len);
int fputs_(const char* str, FILE* stream);

const char* file_name = "onegin.txt";

struct dynamic_set {
    size_t size;
    size_t capacity;
};

int main() {
    FILE* fp = fopen(file_name, "r");
    if (fp == NULL) {
        fprintf(stderr, "NULL file_ptr\n");
        return EXIT_FAILURE;
    }
    
    size_t text_size = 0;
    char** text = inputText(fp, &text_size);

    merge_sort(text, 0, text_size-1);

    printText(text, stdout);
    
    if (text != NULL) freeText(text, text_size);    

    return EXIT_SUCCESS;
}

char** inputText(FILE* fp, size_t* text_size) {
    assert( fp != NULL );
    assert( text_size != NULL );


    const size_t first_size = 10;
    const int exp_multiplier = 2;

    dynamic_set textSet = {0, first_size};
    char** text = (char**)calloc(sizeof(char*), textSet.capacity);

    dynamic_set lineSet = {0, 0};
    char* line = NULL;

    while( getline(&line, &lineSet.size, fp) != EOF ) {
        if (textSet.size + 1 == textSet.capacity) {
            textSet.capacity *= exp_multiplier;
            text = (char**)realloc(text, sizeof(char*)*textSet.capacity);
        }

        text[textSet.size++] = line;
        lineSet.size = 0;
    }
    free(line);
    
    *text_size = textSet.size;
    
    if (textSet.size == 0) {
        free(text);
        return NULL;
    }
    
    return text;
}

void merge_sort(char** text, size_t l, size_t r) {
    assert( text != NULL );
    
    
    if (l == r) return;

    size_t k = (l+r)/2;

    merge_sort(text, l, k);
    merge_sort(text, k+1, r);

    char** temp = (char**)calloc(r-l+1, sizeof(char*));
    size_t temp_size = 0;

    size_t i = l, j = k+1;

    for (; (i <= k) && (j <= r); ) {
        if ( strcmp(text[i], text[j]) < 0 ) {
            temp[temp_size++] = text[i++];

        } else if ( strcmp(text[i], text[j]) == 0 ) {
            temp[temp_size++] = text[i++];
            temp[temp_size++] = text[j++];
            
        } else {
            temp[temp_size++] = text[j++];
        }
    }

    while ( i <= k ) {
        temp[temp_size++] = text[i++];
    }
    while ( j <= r ) {
        temp[temp_size++] = text[j++];
    }

    for (size_t x = l; x <= r; x++) {
        text[x] = temp[x-l];
    }
    
    free(temp);
    temp = NULL;
}

void printText(char** text, FILE* stream) {
    while ( fputs_(*text, stream) != EOF ) {
        ++text;
    }
}

void freeText(char** text, size_t text_len) {    
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
