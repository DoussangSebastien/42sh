/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** add_str.c
*/

#include <stdlib.h>

static int my_strlen(char *str)
{
    int i = 0;

    if (!str)
        return 0;
    while (str[i]) {
        i += 1;
    }
    return i;
}

char *add_str(char *input_2, char *input)
{
    int len = my_strlen(input);
    int len_2 = my_strlen(input_2);
    char *new = malloc(sizeof(char) * (len + len_2) + 1);

    if (!new)
        return NULL;
    for (int i = 0; i < len_2; i++) {
        new[i] = input_2[i];
    }
    for (int i = 0; i < len; i++) {
        new[len_2 + i] = input[i];
    }
    new[len + len_2] = '\0';
    return new;
}
