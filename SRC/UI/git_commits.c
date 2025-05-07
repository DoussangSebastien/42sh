/*
** EPITECH PROJECT, 2024
** salah-eddine
** File description:
** git_commits.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "git_commits.h"
#include "macros.h"

static void handle_child_process(int *pipefd, char *path)
{
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[0]);
    close(pipefd[1]);
    chdir(path);
    execlp("git", "git", "rev-list", "--count", "HEAD", NULL);
    _exit(1);
}

static int handle_parent_process(int *pipefd, pid_t pid)
{
    char buffer[64] = {0};
    int count = 0;

    close(pipefd[1]);
    waitpid(pid, NULL, 0);
    read(pipefd[0], buffer, sizeof(buffer) - 1);
    close(pipefd[0]);
    count = atoi(buffer);
    return count;
}

int count_commits(char *path)
{
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1)
        return FAILURE;
    pid = fork();
    if (pid == 0) {
        handle_child_process(pipefd, path);
    } else
        return handle_parent_process(pipefd, pid);
    return FAILURE;
}
