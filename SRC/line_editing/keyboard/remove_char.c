/*
** EPITECH PROJECT, 2025
** test
** File description:
** remove_char.c
*/

#include "../line.h"
#include <string.h>

int remove_char(action_t *action)
{
    if (!action || !action->line || action->pos >= action->line->len)
        return FAILURE;
    memmove(&action->line->line[action->pos],
            &action->line->line[action->pos + 1],
            action->line->len - action->pos);
    action->line->len--;
    action->line->line[action->line->len] = '\0';
    return SUCCESS;
}
