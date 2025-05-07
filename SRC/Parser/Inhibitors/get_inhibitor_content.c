/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** get_inhibitor_content.c
*/

#include "shell_protos.h"
#include "shell_protos_2.h"

static char *single_quote_case(char *argument, data_t *data)
{
    return dup_in_quotes(argument, '\'');
}

char *get_inhibitor_content(char *argument, data_t *data)
{
    if (!argument || !data)
        return NULL;
    switch (argument[0]) {
        case '\'':
            return single_quote_case(argument, data);
        case '`':
            return back_tick_case(argument, data);
        case '\"':
            return double_quote_case(argument, data);
        default:
            return argument;
    }
    return argument;
}
