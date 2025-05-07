/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** create_path.c
*/

#include "../include/shell_protos.h"
#include <stdbool.h>

static char *get_bin_path(char **tab, char *input)
{
    char *path = NULL;

    for (int i = 0; tab[i]; i++) {
        if (!strcmp(tab[i], "/"))
            continue;
        path = add_str(tab[i], input);
        if (!path)
            return NULL;
        if (access(path, X_OK | F_OK) == 0)
            return path;
        free(path);
        path = NULL;
    }
    return NULL;
}

static char *get_bin(char *env, char *input)
{
    char **tab = NULL;
    char *path = NULL;

    if (!input || !env)
        return NULL;
    tab = my_str_to_word_array_n(env, ":=\0");
    if (!tab)
        return NULL;
    path = get_bin_path(tab, input);
    my_free_word_array(tab);
    return path;
}

static char *get_path(char *input, environ_t *environ)
{
    environ_t *temp = environ;
    char *path = NULL;

    while (temp) {
        if (my_strstr(temp->variable, "PATH=") == temp->variable) {
            path = get_bin(temp->variable, input);
            return path;
        }
        temp = temp->next;
    }
    return NULL;
}

char *create_path(args_t *args)
{
    char *path = NULL;
    char *input = NULL;
    char default_prefix[5] = "/bin/";

    if (!args || !args->tab)
        return NULL;
    if (args->tab[0][0] == '/')
        return strdup(args->tab[0]);
    input = add_str("/\0", args->tab[0]);
    path = get_path(input, args->environ);
    free(input);
    if (!path)
        return add_str(default_prefix, args->tab[0]);
    return path;
}
