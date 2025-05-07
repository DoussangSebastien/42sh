/*
** EPITECH PROJECT, 2025
** autocomplete
** File description:
** get_word.c
*/

#include "../line.h"
#include "ctype.h"

char *get_word(action_t *action)
{
    int start = 0;
    char *word = NULL;

    if (!action || !action->line || action->pos == 0)
        return NULL;
    start = action->pos - 1;
    while (start >= 0 && !isspace(action->line->line[start]) &&
        action->line->line[start] != '/')
        start--;
    start++;
    if (start >= action->pos) {
        word = strdup("");
        return word;
    }
    word = strndup(&action->line->line[start], action->pos - start);
    return word;
}
