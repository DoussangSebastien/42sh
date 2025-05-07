/*
** EPITECH PROJECT, 2025
** autocomplete
** File description:
** get_dir.c
*/

#include "../line.h"
#include <dirent.h>
#include <ctype.h>

static int get_start(action_t *action, char **dir, char *word)
{
    int start = 0;

    if (!action || !action->line || !dir || !word)
        return -1;
    start = action->pos - 1;
    while (start >= 0 && !isspace(action->line->line[start]))
        start--;
    start++;
    if (action->pos - start <= 0)
        return -1;
    return start;
}

void get_dir(action_t *action, char **dir, char *word)
{
    int start = get_start(action, dir, word);
    char *temp = NULL;
    char *last_slash = NULL;

    if (start == -1)
        return;
    if (!start) {
        *dir = strdup("/bin/");
        return;
    }
    temp = strndup(&action->line->line[start], action->pos - start);
    if (!temp)
        return;
    last_slash = strrchr(temp, '/');
    if (last_slash)
        *dir = strndup(temp, last_slash - temp + 1);
    else
        *dir = strdup(".");
    free(temp);
}
