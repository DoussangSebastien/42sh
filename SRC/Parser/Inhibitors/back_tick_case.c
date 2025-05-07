/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** back_tick_case.c
*/

#include "shell_protos.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

static int save_restore_stdout(int *saved_fd)
{
    *saved_fd = dup(STDOUT_FILENO);
    return (*saved_fd == -1) ? FAILURE : SUCCESS;
}

static void restore_stdout(int saved_fd)
{
    if (saved_fd != -1) {
        dup2(saved_fd, STDOUT_FILENO);
        close(saved_fd);
    }
}

static int setup_capture_pipe(int pipefd[2])
{
    if (pipe(pipefd) == -1)
        return FAILURE;
    if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return FAILURE;
    }
    close(pipefd[1]);
    return SUCCESS;
}

static int execute_backtick_command(char *cmd, data_t *data)
{
    tree_t *tree = generate_tree(cmd, data);

    if (!tree || binary_error_parser(tree) == FAILURE) {
        free_tree(tree);
        return FAILURE;
    }
    execute_tree(tree, data);
    free_tree(tree);
    return SUCCESS;
}

static char *execution(char *temp, int pipefd[2],
    data_t *data, int saved_stdout)
{
    if (!temp) {
        restore_stdout(saved_stdout);
        close(pipefd[0]);
        return NULL;
    }
    if (execute_backtick_command(temp, data) == FAILURE) {
        free(temp);
        restore_stdout(saved_stdout);
        close(pipefd[0]);
        return NULL;
    }
    free(temp);
    restore_stdout(saved_stdout);
    return read_captured_output(pipefd[0]);
}

char *back_tick_case(char *argument, data_t *data)
{
    int saved_stdout = 0;
    int pipefd[2] = {0};
    char *temp = NULL;

    if (!argument || !data)
        return NULL;
    if (save_restore_stdout(&saved_stdout) == FAILURE)
        return NULL;
    if (setup_capture_pipe(pipefd) == FAILURE) {
        restore_stdout(saved_stdout);
        return NULL;
    }
    temp = dup_in_quotes(argument, '`');
    fflush(stdout);
    return execution(temp, pipefd, data, saved_stdout);
}
