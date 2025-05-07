/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** create_node.c
*/

#include "shell_protos.h"
#include "shell_protos_2.h"

tree_t *create_node(int type,
    char *fname, char **command)
{
    tree_t *tree = NULL;

    tree = malloc(sizeof(tree_t));
    if (!tree)
        return NULL;
    tree->left = NULL;
    tree->right = NULL;
    tree->argument_type = type;
    tree->command = NULL;
    tree->file_name = NULL;
    if (command)
        tree->command = command;
    if (fname)
        tree->file_name = my_strdup(fname);
    return tree;
}
