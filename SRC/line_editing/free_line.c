/*
** EPITECH PROJECT, 2025
** test
** File description:
** free_line.c
*/

#include "line.h"
#include <stdlib.h>

void free_line(line_t *line)
{
    if (!line)
        return;
    free(line->line);
    free(line);
}
