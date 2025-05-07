/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** set_arguments.c
*/

#include "../include/shell_protos.h"

static int add_node(environ_t **environ, char *value)
{
    environ_t *new_node = malloc(sizeof(environ_t));

    if (!new_node)
        return FAILURE;
    new_node->variable = my_strdup(value);
    if (!new_node->variable) {
        free(new_node);
        return FAILURE;
    }
    new_node->next = *environ;
    *environ = new_node;
    return SUCCESS;
}

static int create_environment_list(environ_t **environ, char const *envp[])
{
    *environ = NULL;
    for (int i = 0; envp[i]; i++) {
        if (add_node(environ, (char *)envp[i]) == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}

int init_environment(args_t *args, char const *envp[])
{
    if (!envp)
        return FAILURE;
    args->fd_in = STDIN_FILENO;
    args->fd_out = STDOUT_FILENO;
    return create_environment_list(&args->environ, envp);
}
