/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** init_which.c
*/

#include "shell_protos.h"
#include "which.h"

static int update_which(char const *str, which_t *which)
{
    char c = '\0';

    if (!str[0] || !str[1] || strlen(str) != 2)
        return FAILURE;
    c = str[1];
    switch (c) {
        case 'a':
            which->flag_a = 1;
            return SUCCESS;
        default:
            return FAILURE;
    }
    return SUCCESS;
}

static char *get_path(environ_t *environ)
{
    environ_t *temp = environ;

    while (temp) {
        if (my_strstr(temp->variable, "PATH=") == temp->variable) {
            return &temp->variable[5];
        }
        temp = temp->next;
    }
    return NULL;
}

int init_which(args_t *args, which_t *which)
{
    char *temp = NULL;

    for (int i = 1; args->tab[i]; i++) {
        if (args->tab[i][0] != '-')
            break;
        if (update_which(args->tab[i], which) == FAILURE)
            return FAILURE;
    }
    temp = get_path(args->environ);
    if (!temp)
        return FAILURE;
    which->directories = my_str_to_word_array_n(temp, ":\n");
    which->saved_result = SUCCESS;
    if (which->directories == NULL)
        return FAILURE;
    return SUCCESS;
}
