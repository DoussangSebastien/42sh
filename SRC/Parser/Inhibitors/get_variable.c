/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** get_variable.c
*/

#include "shell_protos.h"
#include <stdio.h>

static int str_var_str(const char *var, const char *ref)
{
    int i = 0;

    while (var[i] && ref[i] != '=') {
        if (var[i] != ref[i])
            return 0;
        i++;
    }
    return (var[i] == '\0' && ref[i] == '=');
}

static char *get_variable_content(char const *var_name, char *variable)
{
    int len = my_strlen(var_name);

    if (!len)
        return NULL;
    return my_strdup(&variable[len + 1]);
}

char *get_status(args_t *args)
{
    for (var_t *tmp = args->shell_vars; tmp; tmp = tmp->next) {
        if (!strcmp(tmp->name, "status"))
            return my_strdup(tmp->value);
    }
    fprintf(stderr, "Exit status yet to be defined.\n");
    return NULL;
}

static int is_valid_name(char const *name)
{
    if ((name[0] < 'A' || name[0] > 'Z') &&
        (name[0] < '1' || name[0] > '9') &&
        (name[0] < 'a' || name[0] > 'z')) {
        fprintf(stderr, "Illegal variable name.\n");
        return NO;
    }
    return YES;
}

char *get_variable(args_t *args, char const *var_name)
{
    if (!args || !var_name)
        return NULL;
    if (!strcmp(var_name, "?"))
        return get_status(args);
    if (is_valid_name(var_name) == NO)
        return NULL;
    for (environ_t *temp = args->environ; temp; temp = temp->next) {
        if (str_var_str(var_name, temp->variable))
            return get_variable_content(var_name, temp->variable);
    }
    for (var_t *tmp = args->shell_vars; tmp; tmp = tmp->next) {
        if (!strcmp(tmp->name, var_name))
            return my_strdup(tmp->value);
    }
    return NULL;
}
