/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** my_duptab.c
*/

#include "../../include/shell_protos.h"

char **my_duptab(char **tab)
{
    int i = 0;
    char **new_tab = NULL;

    for (; tab[i]; i++);
    new_tab = malloc(sizeof(char *) * i + 1);
    if (!new_tab)
        return NULL;
    for (int j = 0; tab[j]; j++) {
        new_tab[j] = my_strdup(tab[j]);
        if (!new_tab[j]) {
            free(new_tab);
            return NULL;
        }
    }
    new_tab[i] = NULL;
    return new_tab;
}
