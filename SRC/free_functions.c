/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** free_functions.c
*/

#include "../include/shell_protos.h"
#include "shell_protos_2.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

void cleanup_local_variables(args_t *args)
{
    if (!args)
        return;
    if (args->shell_vars) {
        free_vars(args->shell_vars);
        args->shell_vars = NULL;
    }
}

static int write_aliases(alias_t *alias, char *file_name)
{
    FILE *fd = NULL;
    alias_t *temp = NULL;

    if (file_name == NULL)
        return ERROR;
    fd = fopen(file_name, "w");
    if (!fd) {
        free(file_name);
        return ERROR;
    }
    temp = alias;
    while (temp) {
        fprintf(fd, "%s=%s\n", temp->name, temp->command);
        temp = temp->next;
    }
    fclose(fd);
    free(file_name);
    return SUCCESS;
}

static void free_args(args_t *args)
{
    environ_t *temp_env = NULL;
    alias_t *temp_alias = NULL;

    if (!args)
        return;
    write_aliases(args->alias, get_variable(args, "ALIAS_FILE"));
    while (args->environ) {
        temp_env = args->environ;
        args->environ = args->environ->next;
        free(temp_env->variable);
        free(temp_env);
    }
    while (args->alias) {
        temp_alias = args->alias;
        args->alias = args->alias->next;
        free(temp_alias->name);
        free(temp_alias->command);
        free(temp_alias);
    }
    free(args);
}

int free_functions(data_t *data, int return_val)
{
    if (!data)
        return FAILURE;
    cleanup_local_variables(data->args);
    free_args(data->args);
    for (int i = 0; i < FUNCTION_COUNT; i++) {
        if (data->functions[i]) {
            free(data->functions[i]);
        }
    }
    free(data->functions);
    free(data);
    if (!isatty(STDIN_FILENO))
        return return_val;
    if (return_val == 1)
        return SUCCESS;
    return return_val;
}
