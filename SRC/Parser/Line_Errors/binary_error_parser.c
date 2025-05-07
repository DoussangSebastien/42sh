/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** binary_error_parser.c
*/

#include "shell_protos.h"
#include "shell_protos_2.h"

static int check_errors(tree_t *tree)
{
    if (check_pipe(tree) == FAILURE)
        return FAILURE;
    if (check_right_redir(tree) == FAILURE)
        return FAILURE;
    if (check_left_redir(tree) == FAILURE)
        return FAILURE;
    return SUCCESS;
}

int binary_error_parser(tree_t *tree)
{
    if (!tree)
        return SUCCESS;
    if (tree->argument_type == -1)
        return display_error("Invalid null command.\n");
    if (check_errors(tree) == FAILURE)
        return check_right_redir(tree);
    if (tree->argument_type == PIPE) {
        binary_error_parser(tree->right);
        binary_error_parser(tree->left);
    }
    binary_error_parser(tree->right);
    binary_error_parser(tree->left);
    return SUCCESS;
}
