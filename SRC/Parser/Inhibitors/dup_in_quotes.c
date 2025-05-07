/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** dup_in_quotes.c
*/

#include "shell_protos.h"

static char *display_condition(char c)
{
    if (c == '\"')
        write(2, "Unmatched \'\"\'.\n", 15);
    if (c == '\'')
        write(2, "Unmatched \'\'\'.\n", 15);
    if (c == '`')
        write(2, "Unmatched \'`\'.\n", 15);
    return NULL;
}

static int get_len(char *src, char delim)
{
    int i = 1;

    for (; src[i] != delim && src[i]; i++);
    if (src[i] != delim)
        return -1;
    return i;
}

char *dup_in_quotes(char *src, char delim)
{
    int size = 0;
    int i = 0;
    char *memo = NULL;

    if (!src)
        return NULL;
    size = get_len(src, delim);
    if (size == -1)
        return display_condition(delim);
    memo = malloc(sizeof(char) * (size + 1));
    if (memo == NULL)
        return NULL;
    for (; i < (size - 1); i++)
        memo[i] = src[i + 1];
    memo[i] = '\0';
    return memo;
}
