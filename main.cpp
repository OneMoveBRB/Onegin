#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "io.h"
#include "mergeSort.h"
#include "dynamicSettings.h"


const char* file_name = "onegin.txt";

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
