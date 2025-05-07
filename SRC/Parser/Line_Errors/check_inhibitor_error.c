/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** check_inhibitor_error.c
*/

#include "shell_protos.h"

static int display_condition(char c)
{
    if (c == '\"')
        write(2, "Unmatched \'\"\'.\n", 15);
    if (c == '\'')
        write(2, "Unmatched \'\'\'.\n", 15);
    if (c == '`')
        write(2, "Unmatched \'`\'.\n", 15);
    return FAILURE;
}

static int get_count(char *line, char prev)
{
    int count = 0;

    for (int i = 0; line[i]; i++) {
        if (line[i] == prev)
            count += 1;
    }
    if ((count % 2) != 0)
        return display_condition(prev);
    return SUCCESS;
}

int check_inhibitor_error(char *line)
{
    if (!line)
        return FAILURE;
    for (int i = 0; INHIBITORS[i]; i++) {
        if (get_count(line, INHIBITORS[i]) == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}
