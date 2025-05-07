/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** check_right_redir.c
*/

#include "shell_protos.h"

static int check_left(tree_t *tree)
{
    if (!tree)
        return SUCCESS;
    if (tree->argument_type == REDIR_R || tree->argument_type == REDIR_RR)
        return display_error("Ambiguous output redirect.\n");
    return SUCCESS;
}

static int check_right(tree_t *tree)
{
    if (!tree)
        return SUCCESS;
    if (tree->argument_type == REDIR_R || tree->argument_type == REDIR_RR)
        return display_error("Ambiguous output redirect.\n");
    return SUCCESS;
}

int check_right_redir(tree_t *tree)
{
    if (!tree)
        return SUCCESS;
    if (tree->argument_type != REDIR_R && tree->argument_type != REDIR_RR)
        return SUCCESS;
    if (!tree->left)
        return FAILURE;
    if (check_left(tree->left) == FAILURE)
        return FAILURE;
    if (check_right(tree->left) == FAILURE)
        return FAILURE;
    return SUCCESS;
}
