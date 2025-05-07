/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** load_redirection.c
*/

#include "shell_protos.h"
#include "shell_protos_2.h"

static enum arg_type check_redir_type(char **command_line,
    char *type, int start, int end)
{
    for (int i = end; i >= start; i--) {
        if (!my_strcmp(type, command_line[i]))
            return get_arg_type(command_line[i]);
    }
    return -1;
}

static int is_redir_type(enum arg_type type)
{
    if (type == REDIR_L || type == REDIR_LL ||
        type == REDIR_R || type == REDIR_RR)
        return YES;
    return NO;
}

tree_t *split_condition(char **command_line, int i, int end, int start)
{
    if (i == 0) {
        if ((i + 1) == end)
            return create_node(-1, NULL, NULL);
        return split_redir(command_line, i + 2, end);
    } else {
        return split_redir(command_line, start, i - 1);
    }
    return NULL;
}

tree_t *split_redir(char **command_line, int start, int end)
{
    tree_t *tree = NULL;
    enum arg_type type = ARG;

    for (int i = end; i >= start; i--) {
        type = check_redir_type(command_line, command_line[i], start, end);
        if (is_redir_type(type)) {
            tree = create_node(type, command_line[(i + 1)], NULL);
            tree->left = split_condition(command_line, i, end, start);
            return tree;
        }
    }
    return load_command(command_line, start, end);
}
