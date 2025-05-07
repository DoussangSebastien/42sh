/*
** EPITECH PROJECT, 2024
** my_strcat
** File description:
** my_strcat
*/

#include <string.h>
#include <stdio.h>

static int str_len(char const *str)
{
    int i = 0;

    while (str[i]) {
        i++;
    }
    return i;
}

char *my_strcat(char *dest, char const *src)
{
    int length1 = str_len(dest);
    int length2 = str_len(src);

    for (int i = 0; i <= length2; i++) {
        dest[i + length1] = src[i];
    }
    return dest;
}
