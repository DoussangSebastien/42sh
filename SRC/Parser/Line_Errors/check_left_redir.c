/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** check_left_redir.c
*/

#include "shell_protos.h"

int check_left_redir(tree_t *tree)
{
    if (!tree)
        return SUCCESS;
    if (tree->argument_type != REDIR_LL && tree->argument_type != REDIR_L)
        return SUCCESS;
    if (!tree->file_name)
        return display_error("Missing name for redirect.\n");
    if (tree->argument_type == REDIR_L &&
        access(tree->file_name, F_OK) != 0) {
        write(2, tree->file_name, my_strlen(tree->file_name));
        return display_error(": No such file or directory.\n");
    }
    if (tree->left->argument_type != ARG)
        return display_error("Invalid null command.\n");
    return SUCCESS;
}
