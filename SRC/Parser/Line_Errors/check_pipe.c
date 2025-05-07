/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** check_pipe.c
*/

#include "shell_protos.h"

static int check_right(tree_t *tree)
{
    if (!tree)
        return SUCCESS;
    if (tree->argument_type == REDIR_L || tree->argument_type == REDIR_LL)
        return display_error("Ambiguous input redirect.\n");
    return SUCCESS;
}

static int check_left(tree_t *tree)
{
    if (!tree)
        return SUCCESS;
    if (tree->argument_type == REDIR_L || tree->argument_type == REDIR_LL)
        return display_error("Ambiguous input\n");
    return SUCCESS;
}

int check_pipe(tree_t *tree)
{
    if (!tree || tree->argument_type != PIPE)
        return SUCCESS;
    if (check_right(tree->right) == FAILURE)
        return FAILURE;
    if (check_left(tree->left) == FAILURE)
        return FAILURE;
    return SUCCESS;
}
