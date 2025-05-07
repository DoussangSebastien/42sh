/*
** EPITECH PROJECT, 2025
** line_editing
** File description:
** strlower.c
*/

#include <ctype.h>
#include <unistd.h>

int strncmp_case_i(char *s1, char *s2, int n)
{
    unsigned char c1 = '\0';
    unsigned char c2 = '\0';

    for (int i = 0; i < n; i++) {
        c1 = (unsigned char)tolower((unsigned char)s1[i]);
        c2 = (unsigned char)tolower((unsigned char)s2[i]);
        if (c1 != c2)
            return c1 - c2;
        if (c1 == '\0')
            break;
    }
    return 0;
}
