/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** tokenize_glob.c
*/

#include "shell_protos.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static int append_char(char **str, size_t *index, size_t *size, char c)
{
    char *new_ptr = NULL;

    if (*index >= *size - 1) {
        *size *= 2;
        new_ptr = realloc(*str, *size);
        if (!new_ptr)
            return FAILURE;
        *str = new_ptr;
    }
    (*str)[(*index)] = c;
    *index += 1;
    (*str)[*index] = '\0';
    return SUCCESS;
}

static int append_string(char **str, size_t *index,
    size_t *size, const char *s)
{
    for (size_t i = 0; s[i]; i++) {
        if (append_char(str, index, size, s[i]) == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}

static int process_glob_char(char c, char **buffer,
    size_t *index, size_t *size)
{
    switch (c) {
        case '*':
            return append_string(buffer, index, size, ".*");
        case '?':
            return append_char(buffer, index, size, '.');
        case '.':
            return append_string(buffer, index, size, "\\.");
        default:
            return append_char(buffer, index, size, c);
    }
}

static char *ouput(char *buffer)
{
    free(buffer);
    return NULL;
}

char *tokenize_glob(const char *pattern)
{
    size_t index = 0;
    size_t size = 32;
    char *result = NULL;

    if (!pattern)
        return NULL;
    result = malloc(sizeof(char) * size);
    if (!result)
        return NULL;
    result[0] = '^';
    index += 1;
    for (size_t i = 0; pattern[i]; i++) {
        if (process_glob_char(pattern[i], &result,
            &index, &size) == FAILURE) {
            return ouput(result);
        }
    }
    if (append_char(&result, &index, &size, '$') == FAILURE)
        return ouput(result);
    return result;
}
