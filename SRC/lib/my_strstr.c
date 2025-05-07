/*
** EPITECH PROJECT, 2024
** my_strstr
** File description:
** my_strstr
*/

#include <stddef.h>

static int str_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        i++;
    }
    return i;
}

char *my_strstr(char *str, char const *to_find)
{
    int i = 0;
    int size = 0;
    int length = str_strlen(to_find);

    if (length == 0)
        return str;
    while (str[i + size] != '\0') {
        if (str[i + size] != to_find[size]) {
            size = 0;
            i++;
        }
        if (str[i + size] == to_find[size])
            size++;
        if (size == length)
            return &str[i];
    }
    return NULL;
}
