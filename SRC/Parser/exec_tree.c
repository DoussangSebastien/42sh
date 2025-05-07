/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** exec_tree.c
*/

#include "shell_protos.h"
#include <wait.h>

static void execute_redirect(pid_t pid, tree_t *tree, data_t *data)
{
    if (pid == -1) {
        return;
    } else if (pid == 0) {
        handle_redirect(tree, data);
        execute_tree(tree->left, data);
        exit(SUCCESS);
    } else {
        waitpid(pid, NULL, 0);
    }
}

static void redirect(int type, tree_t *tree, data_t *data)
{
    pid_t pid = 0;

    if (type == REDIR_R || type == REDIR_RR
            || type == REDIR_L || type == REDIR_LL) {
        if (!tree->left)
            return;
        pid = fork();
        execute_redirect(pid, tree, data);
    }
}

static int process_main_types(int type, tree_t *root, data_t *data)
{
    int result = 0;

    if (type == SEMI_COLON) {
        execute_tree(root->left, data);
        return execute_tree(root->right, data);
    }
    if (type == AND2) {
        if (execute_tree(root->left, data) != SUCCESS ||
            data->p_status != SUCCESS)
            return ERROR;
        return execute_tree(root->right, data);
    }
    if (type == PIPE2) {
        result = execute_tree(root->left, data);
        if (result != SUCCESS || data->p_status != SUCCESS)
            return execute_tree(root->right, data);
    }
    return result;
}

static void prep_command(data_t *data)
{
    if (data->args->interpreted == YES) {
        my_free_word_array(data->args->tab);
        data->args->interpreted = NO;
    }
}

static int process_sub_types(int type, tree_t *root, data_t *data)
{
    int result = 0;

    if (type == SUBSHELL) {
        data->p_status = execute_subshell(root, data);
        return execute_tree(root->right, data);
    }
    if (type == PIPE) {
        execute_pipe(root, data);
        return SUCCESS;
    }
    result = process_main_types(type, root, data);
    if (type == ARG) {
        prep_command(data);
        data->args->tab = root->command;
        return analyze_input(data);
    }
    redirect(type, root, data);
    return result;
}

int execute_tree(tree_t *root, data_t *data)
{
    int type = 0;

    if (!data)
        return ERROR;
    if (!root)
        return SUCCESS;
    type = root->argument_type;
    return process_sub_types(type, root, data);
}
