/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** build_arg.c
*/

#include "shell_protos.h"

static int is_alphanum(char c)
{
    if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
            || (c >= 'a' && c <= 'z') || c == '_' || c == '%' ||
            c == ':' || c == '.' || c == '/' || c == ' ')
        return YES;
    return NO;
}

static void var_error(char const *argument)
{
    if (!argument)
        return;
    for (size_t i = 0; argument[i] && is_alphanum(argument[i]); i++)
        write(2, &argument[i], 1);
    fprintf(stderr, ": Undefined variable.\n");
}

char *build_command(char *argument, data_t *data)
{
    char *temp = NULL;

    if (!argument || !data)
        return NULL;
    if (argument[0] == '$') {
        temp = get_variable(data->args, &argument[1]);
        if (!temp)
            var_error(&argument[1]);
        free(argument);
        return temp;
    }
    temp = produce_glob(argument);
    if (temp) {
        free(argument);
        return temp;
    }
    return get_inhibitor_content(argument, data);
}
