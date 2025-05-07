/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** build_command.c
*/

#include "shell_protos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int build_str(char **result, const char *str)
{
    char *temp = NULL;
    int len = 0;

    if (!result || !str)
        return FAILURE;
    if (!*result) {
        *result = strdup(str);
        return *result ? SUCCESS : FAILURE;
    }
    len = snprintf(NULL, 0, "%s %s", *result, str) + 1;
    if (len <= 0)
        return FAILURE;
    temp = malloc(sizeof(char) * len);
    if (!temp)
        return FAILURE;
    snprintf(temp, len, "%s %s", *result, str);
    free(*result);
    *result = temp;
    return SUCCESS;
}

static char *fill_arr(char **tab)
{
    char *result = NULL;
    size_t i = 0;

    if (!tab || !tab[0])
        return NULL;
    for (; tab[i]; i++) {
        if (build_str(&result, tab[i]) == FAILURE) {
            free(result);
            return NULL;
        }
    }
    return result;
}

void interpret_command(data_t *data)
{
    char *concatenated = NULL;

    if (!data || !data->args || !data->args->tab
        || !data->args->tab[0])
        return;
    concatenated = fill_arr(data->args->tab);
    if (!concatenated)
        return;
    data->args->interpreted = YES;
    data->args->tab = my_str_to_word_array_n(concatenated, "\n ");
    free(concatenated);
}
