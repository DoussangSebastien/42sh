/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** shell.c
*/

#include "../bonus/ascii_art.h"
#include "../include/shell_protos.h"
#include "shell_protos_2.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int shell(char const *envp[])
{
    data_t *data = malloc(sizeof(data_t));
    int ret_value = 0;

    if (!envp || !data || init_data(data, envp) == FAILURE)
        return FAILURE;
    create_env(data);
    execute_42shrc("bonus/42shrc.txt", data);
    print_colored_ascii_art();
    ret_value = check_stdin(data);
    return free_functions(data, ret_value);
}
