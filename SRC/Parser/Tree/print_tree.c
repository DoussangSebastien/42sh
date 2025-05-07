/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** print_tree.c
*/

#include "shell_protos.h"
#include <stdio.h>

const char *arg_type_to_str(int type)
{
    char const *operations_names[] = {
        [PIPE] = "PIPE", [PIPE2] = "PIPE2",
        [REDIR_R] = "REDIR_R", [REDIR_RR] = "REDIR_RR",
        [REDIR_L] = "REDIR_L", [REDIR_LL] = "REDIR_LL",
        [SEMI_COLON] = "SEMI_COLON", [OPEN_P] = "OPEN_P",
        [CLOSE_P] = "CLOSE_P", [AND] = "AND", [AND2] = "AND2",
        [ARG] = "ARG", [SUBSHELL] = "SUBSHELL", [INVALID] = "INVALID"
    };

    return operations_names[type] ? operations_names[type] : "UNKNOWN";
}

void print_tree_rec(tree_t *node, int depth)
{
    if (!node) {
        printf("%*sNULL\n", depth * 4, "");
        return;
    }
    printf("%*s[%s]\n", depth * 4, "", arg_type_to_str(node->argument_type));
    if (node->file_name)
        printf("%*sFile: %s\n", (depth + 1) * 4, "", node->file_name);
    if (node->command) {
        printf("%*sCommand: ", (depth + 1) * 4, "");
        for (char **cmd = node->command; *cmd; cmd++)
            printf("%s ", *cmd);
        printf("\n");
    }
    printf("%*sLeft:\n", (depth + 1) * 4, "");
    print_tree_rec(node->left, depth + 2);
    printf("%*sRight:\n", (depth + 1) * 4, "");
    print_tree_rec(node->right, depth + 2);
}

void print_tree(tree_t *root)
{
    printf("Parse Tree Structure:\n");
    print_tree_rec(root, 0);
    printf("\n");
}
