#include "dynamicSettings.h"

#include <stdio.h>
#include <stdlib.h>


void freeText(char** text, size_t text_len) {    
    for (size_t i = 0; i < text_len; ++i) {
        free(text[i]);
    }

    free(text);
}
