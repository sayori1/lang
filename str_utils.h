
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef UNTITLED4_STR_UTILS_H
#define UNTITLED4_STR_UTILS_H

char* appendCharDynamic(char *str, char ch) {
    size_t len = strlen(str);

    char *new_str = malloc(strlen(str) * (sizeof(char) + 2));

    if (new_str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return str;
    }

    strcpy(new_str, str);

    new_str[len] = ch;
    new_str[len + 1] = '\0';
    return new_str;
}

#endif //UNTITLED4_STR_UTILS_H
