/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** executable_condition.c
*/

#include "../include/shell_protos.h"
#include "shell_protos_2.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

int static put_str_2(char const *str)
{
    int i = 0;

    while (str[i]) {
        write(2, &str[i], 1);
        i += 1;
    }
    return i;
}

static int ret_function(char *message, char *name, int pid)
{
    if (pid == 0)
        return FAILURE;
    put_str_2(name);
    write(2, message, my_strlen(message));
    return ERROR;
}

int is_directory(const char *path)
{
    struct stat path_stat = {0};

    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

int executable_condition(pid_t pid, data_t *data, char const *input, int index)
{
    char const *temp_tab[2] = {input, NULL};
    char *path = my_strdup((char *)&input[index]);

    if (!path)
        return ERROR;
    if (access(&input[index], F_OK) || is_directory(&input[index]) == 1) {
        if (access(&input[index], X_OK) != 0 || is_directory(&input[index])) {
            free(path);
            return ret_function(": Permission denied.\n",
                data->args->tab[0], pid);
        }
    }
    if (access(&input[index], F_OK) != 0) {
        free(path);
        return ret_function(": Command not found.\n",
                data->args->tab[0], pid);
    }
    data->args->tab = (char **)temp_tab;
    return exec_command(pid, data->args, path, data);
}
