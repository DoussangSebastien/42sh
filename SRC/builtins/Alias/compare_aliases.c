/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** compare_aliases.c
*/

#include "shell_protos.h"
#include "shell_protos_2.h"
#include <fcntl.h>
#include <sys/stat.h>

static char *get_command_line(alias_t *alias, char *alias_name)
{
    alias_t *temp = alias;

    if (!alias)
        return NULL;
    while (temp) {
        if (!strcmp(alias_name, temp->name))
            return temp->command;
        temp = temp->next;
    }
    return NULL;
}

static int execute_alias(data_t *data, char *command_line)
{
    int result = 0;
    tree_t *tree = generate_tree(command_line, data);

    if (!tree)
        return ERROR;
    result = execute_tree(tree, data);
    free_tree(tree);
    data->check = 1;
    return result;
}

int compare_aliases(data_t *data)
{
    char *alias_name = NULL;
    char *command_line = NULL;

    if (!data || !data->args->tab || !data->args->tab[0])
        return ERROR;
    alias_name = data->args->tab[0];
    command_line = get_command_line(data->args->alias, alias_name);
    if (!command_line)
        return SUCCESS;
    return execute_alias(data, command_line);
}
