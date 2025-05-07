/*
** EPITECH PROJECT, 2025
** test
** File description:
** basic_char.c
*/

#include "../line.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int newline(action_t *action)
{
    if (!action || !action->line)
        return FAILURE;
    write(1, "\n", 1);
    action->line->line[action->line->len] = '\0';
    return SUCCESS;
}

int backspace(action_t *action)
{
    if (!action || !action->line)
        return FAILURE;
    if (action->pos <= 0)
        return SUCCESS;
    action->pos--;
    remove_char(action);
    write(1, "\b", 1);
    write(1, &action->line->line[action->pos],
        action->line->len - action->pos);
    write(1, " ", 1);
    for (size_t i = 0; i <= action->line->len - action->pos; i++)
        write(1, "\b", 1);
    return SUCCESS;
}

int printable_char(action_t *action)
{
    if (!action || !action->line)
        return FAILURE;
    if (action->c < 32 || action->c > 126)
        return SUCCESS;
    insert_char(action);
    write(1, &action->line->line[action->pos],
        action->line->len - action->pos);
    action->pos++;
    for (size_t i = 0; i < action->line->len - action->pos; i++)
        write(1, "\b", 1);
    return SUCCESS;
}
