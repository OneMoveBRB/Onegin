#include "io.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "dynamicSettings.h"
#include "string.h"


char** inputText(FILE* fp, size_t* text_size) {
    assert( fp != NULL );
    assert( text_size != NULL );


    const size_t first_size = 10;
    const int exp_multiplier = 2;

    dynamic_set textSet = {0, first_size};
    char** text = (char**)calloc(sizeof(char*), textSet.capacity);

    dynamic_set lineSet = {0, 0};
    char* line = NULL;

    while( getline_(&line, &lineSet.size, fp) != EOF ) {
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

void printText(char** text, FILE* stream) {
    while ( fputs_(*text, stream) != EOF ) {
        ++text;
    }
}
