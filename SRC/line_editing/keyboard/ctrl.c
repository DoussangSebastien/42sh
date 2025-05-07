/*
** EPITECH PROJECT, 2025
** keyboard
** File description:
** ctrl.c
*/

#include "../line.h"
#include <unistd.h>

int start_of_header(action_t *action)
{
    if (!action)
        return FAILURE;
    while (action->pos > 0) {
        if (left(&action->pos))
            return FAILURE;
    }
    return SUCCESS;
}

int cut_end(action_t *action)
{
    if (!action)
        return FAILURE;
    action->line->line[action->pos] = '\0';
    action->line->len = action->pos;
    write(STDOUT_FILENO, "\033[K", 3);
    return SUCCESS;
}
