/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** alias_function.c
*/

#include "shell_protos.h"
#include <fcntl.h>

static int add_node(alias_t **alias, char *name, char *command)
{
    alias_t *new_node = malloc(sizeof(alias_t));

    if (!new_node)
        return FAILURE;
    new_node->name = strdup(name);
    if (command)
        new_node->command = strdup(command);
    new_node->next = *alias;
    *alias = new_node;
    return SUCCESS;
}

static void print_aliases(alias_t *alias)
{
    alias_t *temp = alias;

    if (!alias)
        return;
    while (temp) {
        printf("%s\t%s\n", temp->name, temp->command);
        temp = temp->next;
    }
}

static int check_error(args_t *args)
{
    if (!args->tab[2]) {
        fprintf(stderr, "alias: No command given.\n");
        return ERROR;
    }
    if (args->tab[3]) {
        fprintf(stderr, "alias: Too many arguments.\n");
        return ERROR;
    }
    return SUCCESS;
}

static void replace(char *replace_name, args_t *args)
{
    alias_t *prev = NULL;
    alias_t *current = NULL;

    if (!args || !replace_name || !args->alias)
        return;
    current = args->alias;
    while (current) {
        if (!strcmp(current->name, replace_name)) {
            del_alias(&current, prev, &args->alias);
            return;
        }
        prev = current;
        current = current->next;
    }
}

int my_alias(args_t *args)
{
    if (!args || !args->tab[0])
        return ERROR;
    if (!args->tab[1]) {
        print_aliases(args->alias);
        return SUCCESS;
    }
    if (check_error(args) == ERROR)
        return ERROR;
    replace(args->tab[1], args);
    if (add_node(&args->alias, args->tab[1], args->tab[2]) == FAILURE)
        return ERROR;
    return SUCCESS;
}
