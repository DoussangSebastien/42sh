/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** load_command.c
*/

#include "shell_protos.h"
#include "shell_protos_2.h"

static int get_len(char **commands, int start, int end)
{
    int len = 0;

    for (int i = end; i >= start && get_arg_type(commands[i]) == ARG; i--) {
        len++;
    }
    return len;
}

tree_t *load_command(char **commands, int start, int end)
{
    tree_t *tree = NULL;
    char **tab = NULL;
    int len = 0;

    if (!commands || !commands[0])
        return NULL;
    len = get_len(commands, start, end);
    if (!len)
        return NULL;
    tab = malloc(sizeof(char *) * (len + 1));
    if (!tab)
        return NULL;
    for (int i = 0; i < len; i++) {
        tab[i] = my_strdup(commands[start]);
        start += 1;
    }
    tab[len] = NULL;
    tree = create_node(ARG, NULL, tab);
    return tree;
}
