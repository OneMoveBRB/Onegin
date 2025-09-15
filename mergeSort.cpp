#include "mergeSort.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "string.h"


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
        if ( strcmp_(text[i], text[j]) < 0 ) {
            temp[temp_size++] = text[i++];

        } else if ( strcmp_(text[i], text[j]) == 0 ) {
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
