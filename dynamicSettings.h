#pragma once

#include <stdio.h>


struct dynamic_set {
    size_t size;
    size_t capacity;
};

void freeText(char** text, size_t text_len);
