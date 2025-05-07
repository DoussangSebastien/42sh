/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** spliting.c
*/

#include "shell_protos.h"

tree_t *split_pipe(char **command_line, int start, int end)
{
    tree_t *tree = NULL;

    if (!command_line)
        return NULL;
    for (int i = end; i >= start; i--) {
        if (!my_strcmp("|", command_line[i])) {
            tree = create_node(PIPE, NULL, NULL);
            tree->left = split_pipe(command_line, start, i - 1);
            tree->right = split_pipe(command_line, i + 1, end);
            return tree;
        }
    }
    return split_redir(command_line, start, end);
}

tree_t *split_or(char **command_line, int start, int end)
{
    tree_t *tree = NULL;

    if (!command_line)
        return NULL;
    for (int i = end; i >= start; i--) {
        if (!my_strcmp("||", command_line[i])) {
            tree = create_node(PIPE2, NULL, NULL);
            tree->left = split_or(command_line, start, i - 1);
            tree->right = split_or(command_line, i + 1, end);
            return tree;
        }
    }
    return split_pipe(command_line, start, end);
}

tree_t *split_and_and(char **command_line, int start, int end)
{
    tree_t *tree = NULL;

    if (!command_line)
        return NULL;
    for (int i = end; i >= start; i--) {
        if (!my_strcmp("&&", command_line[i])) {
            tree = create_node(AND2, NULL, NULL);
            tree->left = split_and_and(command_line, start, i - 1);
            tree->right = split_and_and(command_line, i + 1, end);
            return tree;
        }
    }
    return split_or(command_line, start, end);
}

tree_t *split_semicolon(char **command_line, int start, int end)
{
    tree_t *tree = NULL;

    if (!command_line)
        return NULL;
    for (int i = end; i >= start; i--) {
        if (!my_strcmp(";", command_line[i])) {
            tree = create_node(SEMI_COLON, NULL, NULL);
            tree->left = split_semicolon(command_line, start, i - 1);
            tree->right = split_semicolon(command_line, i + 1, end);
            return tree;
        }
    }
    return split_and_and(command_line, start, end);
}
