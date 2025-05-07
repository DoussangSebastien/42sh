/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** check_parenthesis.c
*/

#include "shell_protos.h"

static int check_valid(char **cmd_line, size_t i, int p_count, int type)
{
    int next_type = 0;

    if (!cmd_line[i])
        return FAILURE;
    if (!cmd_line[i + 1])
        return SUCCESS;
    next_type = get_arg_type(cmd_line[i + 1]);
    if (type == CLOSE_P && next_type == ARG)
        return display_error("Badly placed ()'s.\n");
    if (type == ARG && next_type == OPEN_P)
        return display_error("Badly placed ()'s.\n");
    if ((type != ARG) && cmd_line[i + 1]) {
        next_type = get_arg_type(cmd_line[i + 1]);
        if (type != CLOSE_P && next_type == CLOSE_P)
            return display_error("Badly placed ()'s.\n");
    }
    return SUCCESS;
}

int check_parenthesis(char **cmd_line)
{
    int p_count = 0;
    int type = 0;
    size_t i = 0;

    for (; cmd_line[i]; i++) {
        type = get_arg_type(cmd_line[i]);
        if (type == CLOSE_P)
            p_count -= 1;
        if (type == OPEN_P)
            p_count += 1;
        if (p_count == -1)
            return display_error("Too many )'s.\n");
        if (check_valid(cmd_line, i, p_count, type) == FAILURE)
            return FAILURE;
    }
    if (p_count)
        return display_error("Too many ('s.\n");
    return SUCCESS;
}
