/*
** EPITECH PROJECT, 2024
** salah-eddine
** File description:
** open_and_store.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set_struct.h"
#include "set_protos.h"
#include "../../line_editing/line.h"

static void cleanup_shell_vars(var_t **head)
{
    if (!head || !*head)
        return;
    free_vars(*head);
    *head = NULL;
}

void init_minimal_vars(args_t *args)
{
    if (!args)
        return;
    if (args->shell_vars)
        cleanup_shell_vars(&args->shell_vars);
    else
        args->shell_vars = NULL;
    args->shell_vars = add_or_update_var(args->shell_vars, "_", "");
}

var_t *clone_vars(var_t *head)
{
    var_t *new_head = NULL;
    var_t *current = head;
    var_t *temp = NULL;

    if (!head)
        return NULL;
    while (current) {
        if (!current->name || !current->value) {
            current = current->next;
            continue;
        }
        temp = add_var(new_head, current->name, current->value);
        if (!temp) {
            free_vars(new_head);
            return NULL;
        }
        new_head = temp;
        current = current->next;
    }
    return new_head;
}

static var_t *insert_sorted(var_t *sorted, var_t *node)
{
    var_t *tmp = NULL;

    if (!sorted || strcmp(node->name, sorted->name) < 0) {
        node->next = sorted;
        return node;
    }
    tmp = sorted;
    while (tmp->next && strcmp(tmp->next->name, node->name) < 0)
        tmp = tmp->next;
    node->next = tmp->next;
    tmp->next = node;
    return sorted;
}

var_t *sort_vars(var_t *head)
{
    var_t *sorted = NULL;
    var_t *current = NULL;

    if (!head)
        return NULL;
    while (head) {
        current = head;
        head = head->next;
        current->next = NULL;
        sorted = insert_sorted(sorted, current);
    }
    return sorted;
}

void print_underscore_var(var_t *sorted)
{
    var_t *current = sorted;
    char *last_cmd = get_n_cmd(2);

    while (current) {
        if (current->name && strcmp(current->name, "_") == 0) {
            printf("_\t%s\n", last_cmd ? last_cmd : current->value);
            free(last_cmd);
            return;
        }
        current = current->next;
    }
    printf("_\t%s\n", last_cmd ? last_cmd : "");
    free(last_cmd);
}

static void print_other_vars(var_t *sorted)
{
    var_t *current = sorted;

    while (current) {
        if (current->name && current->value &&
        strcmp(current->name, "_") != 0) {
            printf("%s\t%s\n", current->name, current->value);
        }
        current = current->next;
    }
}

static var_t *prepare_sorted_clone(var_t *head)
{
    var_t *clone = clone_vars(head);
    var_t *sorted = NULL;

    if (!clone)
        return NULL;
    sorted = sort_vars(clone);
    if (!sorted) {
        free_vars(clone);
        return NULL;
    }
    return sorted;
}

void print_vars(var_t *head)
{
    var_t *sorted = NULL;

    if (!head) {
        printf("_\t\n");
        return;
    }
    sorted = prepare_sorted_clone(head);
    if (!sorted) {
        printf("_\t\n");
        return;
    }
    print_underscore_var(sorted);
    print_other_vars(sorted);
    free_vars(sorted);
}
