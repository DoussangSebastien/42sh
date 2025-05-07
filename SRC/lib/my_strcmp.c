/*
** EPITECH PROJECT, 2024
** my_strcmp
** File description:
** my_strcmp
*/

#include <stdio.h>

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    if (!s1)
        return -1;
    if (!s2)
        return 1;
    while (s1[i] || s2[i]) {
        if (s1[i] > s2[i])
            return 1;
        if (s1[i] < s2[i])
            return -1;
        i++;
    }
    return 0;
}
