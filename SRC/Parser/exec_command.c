/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** execute_command.c
*/

#include "shell_protos.h"
#include <sys/types.h>
#include <sys/wait.h>

static int handle_status(const int status, data_t *data)
{
    char *sig = NULL;

    if (WTERMSIG(status)) {
        sig = strsignal(WTERMSIG(status));
        if (WTERMSIG(status) == SIGFPE) {
            fprintf(stderr, "Floating exception (core dumped)\n");
            return status;
        }
        fprintf(stderr, "%s", sig);
        if (WCOREDUMP(status))
            fprintf(stderr, " (core dumped)");
        fprintf(stderr, "\n");
        return status;
    }
    return WEXITSTATUS(status);
}

static int process_id(pid_t pid, args_t *args, char **envp, char const *path)
{
    int status = 0;

    if (pid == -1)
        return -1;
    if (pid == 0) {
        dup2(args->fd_in, STDIN_FILENO);
        dup2(args->fd_out, STDOUT_FILENO);
        if (execve(path, args->tab, envp) == -1)
            exit(-1);
    } else {
        if (waitpid(pid, &status, 0) == -1) {
            return -1;
        }
        if (WIFEXITED(status) && WEXITSTATUS(status) == 255) {
            status = -1;
        }
    }
    return status;
}

int exec_command(pid_t pid, args_t *args, char *path, data_t *data)
{
    char **envp = NULL;
    int status = 0;

    if (!args->tab || !args->tab[0])
        return SUCCESS;
    if (!path || pid == -1)
        return ERROR;
    envp = build_envp(args->environ);
    if (!envp) {
        my_free_word_array(envp);
        return ERROR;
    }
    status = process_id(pid, args, envp, path);
    free(path);
    my_free_word_array(envp);
    if (WTERMSIG(status) == 127)
        return ERROR;
    data->check = 1;
    return handle_status(status, data);
}
