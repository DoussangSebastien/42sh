/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** is_alphanumeric.c
*/

#include <stdlib.h>

static int is_alphanum(char c)
{
    if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
            || (c >= 'a' && c <= 'z') || c == '_' || c == '%' ||
            c == ':' || c == '.' || c == '/' || c == ' ')
        return 1;
    else
        return 0;
}

int is_alphanumeric(const char *str)
{
    if (str == NULL || str[0] == '\0')
        return 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!is_alphanum(str[i]))
            return 0;
    }
    return 1;
}
