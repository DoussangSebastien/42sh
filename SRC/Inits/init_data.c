/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** init_data.c
*/

#include "../include/shell_protos.h"
#include <signal.h>

static void print_line(int signal)
{
    if (signal == SIGTSTP || signal == SIGINT ||
            signal == SIGQUIT)
        write(1, "\n$> ", 4);
}

static void block_signal(void)
{
    signal(SIGTSTP, print_line);
    signal(SIGINT, print_line);
    signal(SIGQUIT, print_line);
}

static int init_alias(data_t *data)
{
    int result = 0;

    result = init_aliases(data);
    if (result == FAILURE) {
        free(data->args);
        free(data->functions);
        free(data);
        return FAILURE;
    }
    return SUCCESS;
}

int init_args(data_t *data, char const *envp[])
{
    data->args = malloc(sizeof(args_t));
    data->args->alias = NULL;
    if (!data->args || init_environment(data->args, envp) == FAILURE) {
        free(data->functions);
        free(data);
        return FAILURE;
    }
    if (init_alias(data) == FAILURE)
        return FAILURE;
    data->args->exit = 0;
    data->args->interpreted = NO;
    data->args->input = NULL;
    data->args->shell_vars = NULL;
    return SUCCESS;
}

int init_data(data_t *data, char const *envp[])
{
    if (!data || !envp)
        return FAILURE;
    block_signal();
    data->check = 0;
    data->p_status = 0;
    data->args = NULL;
    data->functions = init_function_list(data->functions);
    if (data->functions == NULL) {
        free(data);
        return FAILURE;
    }
    if (init_args(data, envp) == FAILURE)
        return FAILURE;
    return SUCCESS;
}
