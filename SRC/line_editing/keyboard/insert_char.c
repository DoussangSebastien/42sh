/*
** EPITECH PROJECT, 2025
** test
** File description:
** insert_char.c
*/

#include "../line.h"
#include <stdlib.h>
#include <string.h>

int insert_char(action_t *action)
{
    if (!action || !action->line || action->pos > action->line->len)
        return FAILURE;
    if (action->line->len + 1 >= action->line->size) {
        action->line->size *= 2;
        action->line->line = realloc(action->line->line, action->line->size);
        if (!action->line->line)
            return FAILURE;
    }
    memmove(&action->line->line[action->pos + 1],
        &action->line->line[action->pos], action->line->len - action->pos);
    action->line->line[action->pos] = action->c;
    action->line->len++;
    return SUCCESS;
}
