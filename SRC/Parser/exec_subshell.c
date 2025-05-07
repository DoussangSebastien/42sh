/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** exec_subshell.c
*/

#include "shell_protos.h"
#include <wait.h>
#include <fcntl.h>

static int is_redir(int type)
{
    if (type == REDIR_R || type == REDIR_RR
            || type == REDIR_L || type == REDIR_LL)
        return YES;
    return NO;
}

static int execute_p_left(int need_pipe, int pipe_fd[2],
    data_t *data, tree_t *root)
{
    if (need_pipe) {
        close(pipe_fd[0]);
        dup2(data->args->fd_in, STDIN_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
    }
    if (root->right && is_redir(root->right->argument_type)) {
        if (handle_redirect(root->right, data) != SUCCESS)
            exit(FAILURE);
    }
    exit(execute_tree(root->left, data));
}

static int init_p(pid_t *pid, int pipe_fd[2], tree_t *root, int *need_pipe)
{
    if (root->right && root->right->argument_type == PIPE)
        *need_pipe = 1;
    if (need_pipe && pipe(pipe_fd) == -1)
        return FAILURE;
    *pid = fork();
    if (*pid == -1) {
        if (*need_pipe) {
            close(pipe_fd[0]);
            close(pipe_fd[1]);
        }
        return FAILURE;
    }
    return SUCCESS;
}

int execute_subshell(tree_t *root, data_t *data)
{
    pid_t pid = 0;
    int status = 0;
    int pipe_fd[2] = {-1, -1};
    int need_pipe = 0;

    if (!data || !root || init_p(&pid, pipe_fd, root, &need_pipe) == FAILURE)
        return FAILURE;
    if (pid == 0) {
        execute_p_left(need_pipe, pipe_fd, data, root);
    } else {
        if (need_pipe) {
            close(pipe_fd[1]);
            data->args->fd_in = pipe_fd[0];
        }
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            return WEXITSTATUS(status);
    }
    return status;
}
