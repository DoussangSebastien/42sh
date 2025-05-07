/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** unsetenv_function.c
*/

#include "shell_protos.h"

static void unset_node(environ_t **environ, environ_t *prev, environ_t **head)
{
    environ_t *temp = NULL;

    if (!(*environ)) {
        if (prev)
            prev->next = NULL;
        return;
    }
    temp = (*environ);
    if (!prev) {
        (*environ) = temp->next;
        *head = (*environ);
    } else
        prev->next = temp->next;
    free(temp->variable);
    free(temp);
}

static int str_var_str(char const *var, char const *ref)
{
    int i = 0;

    while (var[i] && ref[i] != '=') {
        if (var[i] != ref[i])
            return 0;
        i += 1;
    }
    if (ref[i] == '=')
        return 1;
    return 0;
}

static int ret_result(int result, environ_t **temp,
    environ_t *prev, environ_t **head)
{
    if (result)
        unset_node(temp, prev, head);
    return SUCCESS;
}

int my_unsetenv(args_t *args)
{
    environ_t *temp = NULL;
    environ_t *prev = NULL;
    int result = 0;

    if (!args || !args->environ || !args->tab || !args->tab[0])
        return ERROR;
    if (!args->tab[1]) {
        write(2, "unsetenv: Too few arguments.\n", 29);
        return ERROR;
    }
    temp = args->environ;
    for (int i = 0; temp && !result; i++) {
        result = str_var_str(args->tab[1], temp->variable);
        if (i > 0 && !result)
            prev = temp;
        if (!result)
            temp = temp->next;
    }
    return ret_result(result, &temp, prev, &args->environ);
}
