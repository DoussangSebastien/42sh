/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** analyze_input.c
*/

#include "../include/shell_protos.h"
#include <errno.h>
#include <wait.h>
#include <errno.h>

static void exit_exe(char const *path)
{
    if (my_strstr((char *)path, ".exe") != NULL) {
        if (errno == ENOEXEC) {
            write(2, path, my_strlen(path) + 1);
            write(2,
            ": Exec format error. Binary file not executable.\n", 50);
            exit(126);
        }
    }
}

static int check_exec(pid_t pid, args_t *args, data_t *data)
{
    char *path = NULL;

    if (pid == -1 || !args->tab || !args->tab[0])
        return ERROR;
    exit_exe(args->tab[0]);
    if ((args->tab[0][0] == '.' && args->tab[0][1] == '/')) {
        data->check = 1;
        return executable_condition(pid, data, args->tab[0], 2);
    }
    path = create_path(args);
    if (!path)
        return ERROR;
    interpret_command(data);
    return exec_command(pid, args, path, data);
}

static int output(data_t *data, int result)
{
    if (!data->check) {
        fprintf(stderr, "%s", data->args->tab[0]);
        fprintf(stderr, ": Command not found.\n");
        return ERROR;
    }
    return result;
}

int analyze_input(data_t *data)
{
    int result = 0;
    int pid = 0;

    if (!data->args->tab || !data->args->tab[0])
        return SUCCESS;
    if (!data || !data->args)
        return FAILURE;
    data->check = 0;
    result = execute_builtins(data->args, data->functions, &data->check);
    if (data->check)
        return result;
    result = compare_aliases(data);
    if (!data->check) {
        pid = fork();
        result = check_exec(pid, data->args, data);
    }
    return output(data, result);
}
