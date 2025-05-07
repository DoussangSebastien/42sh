/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** execute_pipe.c
*/

#include "shell_protos.h"
#include <wait.h>

static void terminate(pid_t left_pid, pid_t right_pid, int pipefd[2])
{
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(left_pid, NULL, 0);
    waitpid(right_pid, NULL, 0);
}

static void pipe_left(int pipefd[2], data_t *data, tree_t *tree)
{
    close(pipefd[0]);
    dup2(data->args->fd_in, STDIN_FILENO);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);
    if (tree->right->argument_type == SUBSHELL)
        execute_subshell(tree->left, data);
    else
        execute_tree(tree->left, data);
    exit(SUCCESS);
}

static void pipe_right(int pipefd[2], data_t *data, tree_t *tree)
{
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    dup2(data->args->fd_out, STDOUT_FILENO);
    close(pipefd[0]);
    if (tree->right->argument_type == SUBSHELL)
        execute_subshell(tree->right, data);
    else
        execute_tree(tree->right, data);
    exit(SUCCESS);
}

void execute_pipe(tree_t *tree, data_t *data)
{
    int pipefd[2] = {0};
    pid_t left_pid = 0;
    pid_t right_pid = 0;

    if (!tree || !data)
        return;
    if (pipe(pipefd) == -1)
        exit(1);
    left_pid = fork();
    if (left_pid == 0)
        pipe_left(pipefd, data, tree);
    right_pid = fork();
    if (right_pid == 0)
        pipe_right(pipefd, data, tree);
    terminate(left_pid, right_pid, pipefd);
}
