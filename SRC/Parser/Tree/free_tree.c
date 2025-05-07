/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** free_tree.c
*/

#include "shell_protos.h"

void free_tree(tree_t *tree)
{
    if (!tree)
        return;
    free_tree(tree->right);
    free_tree(tree->left);
    if (tree->command)
        my_free_word_array(tree->command);
    if (tree->file_name)
        free(tree->file_name);
    free(tree);
}
