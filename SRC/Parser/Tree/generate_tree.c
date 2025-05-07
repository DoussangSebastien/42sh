/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** generate_tree.c
*/

#include "shell_protos.h"
#include "shell_protos_2.h"

static int check_p(char **command_line, int start, int end)
{
    size_t p_count = 1;
    int i = start;

    for (; i <= end && p_count > 0; i++) {
        if (!my_strcmp("(", command_line[i]))
            p_count += 1;
        if (!my_strcmp(")", command_line[i]))
            p_count -= 1;
    }
    if (p_count != 0)
        return -1;
    return i;
}

static tree_t *init_subshell(int type, tree_t *left, tree_t *right)
{
    tree_t *new = NULL;

    if (type == -1)
        return NULL;
    new = malloc(sizeof(tree_t));
    if (!new)
        return NULL;
    new->argument_type = type;
    new->command = NULL;
    new->file_name = NULL;
    new->right = right;
    new->left = left;
    return new;
}

static tree_t *handle_p(char **command_line, int i, int j, int stops[2])
{
    tree_t *left_tree = NULL;
    tree_t *inside_tree = NULL;
    tree_t *right_tree = NULL;
    int start = stops[0];
    int end = stops[1];
    tree_t *subshell_node = NULL;

    if (i > start)
        left_tree = split_semicolon(command_line, start, i - 1);
    inside_tree = split_open_p(command_line, i + 1, j - 2);
    if (j <= end)
        right_tree = split_open_p(command_line, j, end);
    subshell_node = init_subshell(SUBSHELL, inside_tree, right_tree);
    if (left_tree)
        return init_subshell(get_arg_type(command_line[i - 1]),
            left_tree, subshell_node);
    return subshell_node;
}

tree_t *split_open_p(char **command_line, int start, int end)
{
    int stops[2] = {start, end};
    int j = 0;

    if (!command_line || start < 0 || end < 0)
        return NULL;
    for (int i = start; i <= end; i++) {
        if (!my_strcmp("(", command_line[i])) {
            j = check_p(command_line, i + 1, end);
            return handle_p(command_line, i, j, stops);
        }
    }
    return split_semicolon(command_line, start, end);
}

static int get_len(char **command_line)
{
    int i = 0;

    for (; command_line[i]; i++);
    return i;
}

static tree_t *return_func(char **command, tree_t *tree)
{
    if (*command)
        my_free_word_array(command);
    if (!tree)
        return NULL;
    return tree;
}

tree_t *generate_tree(char *line, data_t *data)
{
    char **command_line = NULL;
    tree_t *tree = NULL;
    int len = 0;

    if (!line || check_inhibitor_error(line) == FAILURE)
        return NULL;
    command_line = line_parser(line, data);
    if (!command_line)
        return NULL;
    if (check_parenthesis(command_line) == FAILURE)
        return return_func(command_line, NULL);
    if (check_linear_args(command_line) == FAILURE)
        return return_func(command_line, NULL);
    len = get_len(command_line) - 1;
    tree = split_open_p(command_line, 0, len);
    if (!tree)
        return return_func(command_line, NULL);
    return return_func(command_line, tree);
}
