/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** init_function_list.c
*/

#include "shell_protos.h"
#include "shell_protos_2.h"
#include "set_protos.h"

static functions_t *add_tab(int (*exec)(args_t *), char *function_name,
    functions_t *function)
{
    function = malloc(sizeof(functions_t));
    function->function_name = function_name;
    function->exec = exec;
    return function;
}

functions_t **init_list(functions_t **functions, char const *names[],
    int (*execs[])(args_t *))
{
    for (int i = 0; i < FUNCTION_COUNT; i++) {
        functions[i] = add_tab(execs[i], (char *)names[i], functions[i]);
    }
    return functions;
}

functions_t **init_function_list(functions_t **functions)
{
    char const *names[FUNCTION_COUNT] = {"cd", "env",
        "setenv", "unsetenv", "exit", "alias", "history", "unalias",
        "which", "set", "unset", "where", "shrimp"};
    int (*execs[FUNCTION_COUNT])(args_t *) = {my_cd, my_env,
        my_setenv, my_unsetenv, my_exit, my_alias, my_history, my_unalias,
        my_which, my_set, my_unset, my_where, shrimp_command};

    functions = malloc(sizeof(functions_t *) * FUNCTION_COUNT);
    if (!functions)
        return NULL;
    return init_list(functions, names, execs);
}
