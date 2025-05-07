/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** check_linear_args.c
*/

#include "shell_protos_2.h"
#include "shell_protos.h"

static int start_redir(char const *term, int i)
{
    if (i != 0)
        return NO;
    if (!my_strcmp(term, ">>") || !my_strcmp(term, ">") ||
        !my_strcmp(term, "<<") || !my_strcmp(term, "<"))
        return YES;
    return NO;
}

int check_linear_args(char **command)
{
    int check = 0;
    int type = ARG;

    for (int i = 0; command[i]; i++) {
        type = get_arg_type(command[i]);
        if (type == OPEN_P || type == CLOSE_P || start_redir(command[i], i))
            continue;
        if (i == 0 && type != ARG)
            return display_error("Invalid null command.\n");
        if (check > 1)
            return display_error("Invalid null command.\n");
        if (type != ARG)
            check += 1;
        else
            check = 0;
    }
    if (check >= 1)
        return display_error("Invalid null command.\n");
    return SUCCESS;
}
