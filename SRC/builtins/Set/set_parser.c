/*
** EPITECH PROJECT, 2024
** salah-eddine
** File description:
** set_parser.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set_struct.h"
#include "set_protos.h"

static int assign_trimmed_name_and_value(char *name_part,
    const char *value_part, char **name, char **value)
{
    *name = trim_spaces(name_part);
    if (!*name)
        return -1;
    *value = strdup(value_part);
    if (!*value) {
        free(*name);
        *name = NULL;
        return -1;
    }
    return 0;
}

static int extract_assignment_parts(const char *input,
    char **name, char **value)
{
    char *copy = strdup(input);
    char *equal = NULL;
    int result = -1;

    if (!copy)
        return -1;
    equal = strchr(copy, '=');
    if (!equal) {
        free(copy);
        return -1;
    }
    *equal = '\0';
    result = assign_trimmed_name_and_value(copy, equal + 1, name, value);
    free(copy);
    return result;
}

int parse_assignment(const char *input, char **name, char **value)
{
    if (!input || !name || !value)
        return -1;
    *name = NULL;
    *value = NULL;
    if (extract_assignment_parts(input, name, value) != 0)
        return -1;
    if (!is_valid_identifier(*name)) {
        free(*name);
        free(*value);
        *name = NULL;
        *value = NULL;
        return -1;
    }
    return 0;
}

static void copy_var_data(var_t *new_var,
    const char *name, const char *value)
{
    new_var->name = name ? strdup(name) : strdup("");
    new_var->value = value ? strdup(value) : strdup("");
    new_var->next = NULL;
}

var_t *add_var(var_t *head, const char *name, const char *value)
{
    var_t *new = calloc(1, sizeof(var_t));
    var_t *tmp = NULL;

    if (!new)
        return head;
    copy_var_data(new, name, value);
    if (!new->name || !new->value) {
        free_vars(new);
        return head;
    }
    if (!head)
        return new;
    tmp = head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return head;
}

var_t *update_existing_var(var_t *head, var_t *target, const char *value)
{
    char *new_value = NULL;

    if (!target)
        return head;
    new_value = strdup(value ? value : "");
    if (!new_value)
        return head;
    free(target->value);
    target->value = new_value;
    return head;
}

var_t *add_or_update_var(var_t *head, const char *name, const char *value)
{
    var_t *tmp = NULL;
    var_t *new = NULL;

    if (!name || !*name || !is_valid_identifier(name))
        return head;
    if (!head) {
        new = create_new_var(name, value);
        return new ? new : head;
    }
    tmp = head;
    while (tmp) {
        if (tmp->name && strcmp(tmp->name, name) == 0)
            return update_existing_var(head, tmp, value);
        tmp = tmp->next;
    }
    new = create_new_var(name, value);
    if (!new)
        return head;
    new->next = head;
    return new;
}

void read_and_store_vars(FILE *fp, args_t *args)
{
    char line[4096] = {0};
    char *name = NULL;
    char *value = NULL;
    char *name_copy = NULL;

    if (!fp || !args)
        return;
    while (fgets(line, sizeof(line), fp)) {
        name = strtok(line, "\t\n ");
        value = strtok(NULL, "\n");
        if (!name || !*name || !is_valid_identifier(name))
            continue;
        name_copy = strdup(name);
        if (!name_copy)
            continue;
        args->shell_vars = add_or_update_var(
            args->shell_vars, name_copy, value ? value : "");
        free(name_copy);
    }
}
