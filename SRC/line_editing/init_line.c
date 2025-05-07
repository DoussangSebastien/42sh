/*
** EPITECH PROJECT, 2025
** test
** File description:
** init_line.c
*/

#include "line.h"
#include <stdlib.h>

line_t *init_line(void)
{
    line_t *line = malloc(sizeof(line_t));

    if (!line)
        return NULL;
    line->len = 0;
    line->size = DEFAULT_SIZE;
    line->line = malloc(sizeof(char) * line->size);
    if (!line->line)
        return NULL;
    return line;
}
