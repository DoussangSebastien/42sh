/*
** EPITECH PROJECT, 2024
** salah-eddine
** File description:
** unset_command.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "set_struct.h"
#include "set_protos.h"

static void free_var_node(var_t *node)
{
    free(node->name);
    free(node->value);
    free(node);
}

static var_t *handle_match_node(var_t *head, var_t *curr, var_t *prev)
{
    if (prev)
        prev->next = curr->next;
    else
        head = curr->next;
    free_var_node(curr);
    return head;
}

var_t *remove_var(var_t *head, const char *name)
{
    var_t *curr = head;
    var_t *prev = NULL;

    if (!name || !*name)
        return head;
    while (curr && curr->name) {
        if (strcmp(curr->name, name) == 0)
            return handle_match_node(head, curr, prev);
        prev = curr;
        curr = curr->next;
    }
    return head;
}

static void print_unset_error(const char *var)
{
    if (!var || !*var) {
        fprintf(stderr, "unset: Missing variable name.\n");
        return;
    }
    if (!isalpha(var[0])) {
        fprintf(stderr, "unset: Variable name must begin with a letter.\n");
        return;
    }
    for (int i = 1; var[i]; i++) {
        if (!isalnum(var[i]) && var[i] != '_') {
            fprintf(stderr,
            "unset: Variable name contains invalid character.\n");
            return;
        }
    }
}

static int process_var(args_t *args, const char *var)
{
    if (!is_valid_identifier(var)) {
        print_unset_error(var);
        return 1;
    }
    args->shell_vars = remove_var(args->shell_vars, var);
    return 0;
}

int my_unset(args_t *args)
{
    int status = 0;

    if (!args || !args->tab) {
        fprintf(stderr, "unset: Internal error: null args.\n");
        return 1;
    }
    if (!args->tab[1]) {
        fprintf(stderr, "unset: Too few arguments.\n");
        return 1;
    }
    for (int i = 1; args->tab[i]; i++)
        status |= process_var(args, args->tab[i]);
    return status;
}
