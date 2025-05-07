/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** buil_envp.c
*/

#include "../include/shell_protos.h"

static int get_env_count(environ_t *environ)
{
    int i = 0;

    while (environ) {
        i += 1;
        environ = environ->next;
    }
    return i;
}

char **build_envp(environ_t *environ)
{
    char **envp = NULL;
    int len = 0;
    int i = 0;
    environ_t *temp = environ;

    if (!environ)
        return NULL;
    len = get_env_count(environ);
    envp = malloc(sizeof(char *) * (len + 1));
    if (!envp)
        return NULL;
    while (temp) {
        i += 1;
        envp[len - i] = my_strdup(temp->variable);
        temp = temp->next;
    }
    envp[len] = NULL;
    return envp;
}
