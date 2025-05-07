/*
** EPITECH PROJECT, 2025
** line_editing
** File description:
** init_action.c
*/

#include "line.h"

static int init_builtin(action_t *action, data_t *data)
{
    action->builtins = malloc(sizeof(char *) * FUNCTION_COUNT);
    if (!action->builtins)
        return FAILURE;
    for (int i = 0; i < FUNCTION_COUNT; i++)
        action->builtins[i] = strdup(data->functions[i]->function_name);
    return SUCCESS;
}

action_t *init_action(data_t *data)
{
    action_t *action = NULL;

    if (!data)
        return NULL;
    action = malloc(sizeof(action_t));
    if (!action)
        return NULL;
    action->line = init_line();
    if (!action->line)
        return NULL;
    action->c = '\0';
    action->pos = 0;
    action->history_index = 0;
    action->last_c = '\0';
    action->auto_complete = 0;
    return (init_builtin(action, data)) ? NULL : action;
}

void free_action(action_t *action)
{
    for (int i = 0; i < FUNCTION_COUNT; i++)
        free(action->builtins[i]);
    free(action->builtins);
    free(action);
}
