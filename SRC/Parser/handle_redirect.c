/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** handle_redirect.c
*/

#include <fcntl.h>
#include "shell_protos.h"
#include <wait.h>

static int case_right_right(tree_t *tree)
{
    int fd = 0;

    fd = open(tree->file_name, O_APPEND | O_CREAT | O_WRONLY, 0644);
    if (fd == -1)
        return FAILURE;
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return SUCCESS;
}

static int case_right(tree_t *tree)
{
    int fd = 0;

    fd = open(tree->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
        return FAILURE;
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return SUCCESS;
}

static int case_left(tree_t *tree)
{
    int fd = 0;

    fd = open(tree->file_name, O_RDONLY);
    if (fd == -1)
        return FAILURE;
    dup2(fd, STDIN_FILENO);
    close(fd);
    return SUCCESS;
}

static int is_the_same(char *stop_word, char *input, size_t size)
{
    if (input[size - 1] == '\n')
        input[size - 1] = '\0';
    if (my_strcmp(stop_word, input) == 0) {
        free(input);
        return NO;
    }
    return YES;
}

static int result_func(int fd[2], int return_val)
{
    close(fd[0]);
    close(fd[1]);
    return return_val;
}

static int write_input(char **input, size_t *len, int fd[2], ssize_t *size)
{
    write(1, "? ", 2);
    *size = getline(input, len, stdin);
    if (*size == -1) {
        free(input);
        return result_func(fd, FAILURE);
    }
    return SUCCESS;
}

static int case_left_left(tree_t *tree, data_t *data)
{
    int fd[2] = {0};
    char *stop_word = NULL;
    char *input = NULL;
    size_t len = 0;
    ssize_t size = 0;

    if (!tree->file_name)
        return FAILURE;
    stop_word = tree->file_name;
    if (pipe(fd) == -1)
        return FAILURE;
    while (1) {
        if (write_input(&input, &len, fd, &size) == FAILURE)
            return FAILURE;
        if (is_the_same(stop_word, input, size) == NO)
            break;
        write(fd[1], my_strcat(input, "\n"), size);
    }
    dup2(fd[0], STDIN_FILENO);
    return result_func(fd, SUCCESS);
}

int handle_redirect(tree_t *tree, data_t *data)
{
    if (!tree)
        return FAILURE;
    switch (tree->argument_type) {
        case REDIR_R:
            return case_right(tree);
        case REDIR_RR:
            return case_right_right(tree);
        case REDIR_L:
            return case_left(tree);
        case REDIR_LL:
            return case_left_left(tree, data);
        default:
            break;
    }
    return SUCCESS;
}
