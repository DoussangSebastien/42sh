/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** double_quote_case.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "shell_protos.h"

static char *write_var(char *argument, data_t *data)
{
    char var_name[256] = {0};
    char *new = NULL;
    size_t i = 0;

    if (!argument || !data)
        return NULL;
    for (; is_alpha(argument[i]) && argument[i]; i += 1)
        var_name[i] = argument[i];
    var_name[i] = '\0';
    new = get_variable(data->args, var_name);
    return new;
}

static char *free_all(quote_t *quote)
{
    if (quote->new)
        free(quote->new);
    if (quote->arg)
        free(quote->arg);
    free(quote);
    return NULL;
}

static void add_string(quote_t *quotes, char *added)
{
    char *temp = NULL;
    int new_len = 0;

    if (!added)
        return;
    if (quotes->new) {
        new_len = strlen(added) + (quotes->index);
        temp = add_str(quotes->new, added);
        free(quotes->new);
    } else
        temp = strdup(added);
    if (!temp)
        return;
    free(added);
    quotes->new = temp;
    quotes->index = new_len;
    quotes->size = new_len + 1;
}

static int check_char(quote_t *quotes, int i, char *argument, data_t *data)
{
    char *temp = NULL;

    switch (argument[i]) {
        case ('`'):
            temp = back_tick_case(&argument[i], data);
            break;
        case ('$'):
            temp = write_var(&argument[i + 1], data);
            break;
        default:
            return 1;
    }
    if (!temp)
        return FAILURE;
    add_string(quotes, temp);
    return SUCCESS;
}

static int check_arg(quote_t *quotes, int i, data_t *data)
{
    int result = 0;

    if (quotes->index == quotes->size - 1) {
        quotes->size *= 2;
        quotes->new = realloc(quotes->new, (sizeof(char) * quotes->size));
        if (!quotes->new)
            return FAILURE;
    }
    result = check_char(quotes, i, quotes->arg, data);
    if (result == FAILURE)
        return FAILURE;
    if (result == 1 && quotes->arg[i] >= ' ') {
        quotes->new[quotes->index] = quotes->arg[i];
        quotes->index += 1;
        quotes->new[quotes->index + 1] = '\0';
    }
    return SUCCESS;
}

static int init_quote(quote_t *quotes, char *argument)
{
    quotes->arg = dup_in_quotes(argument, '\"');
    if (!quotes->arg)
        return FAILURE;
    quotes->new = malloc(sizeof(char) * 32);
    if (!quotes->new)
        return FAILURE;
    quotes->new[0] = '\0';
    quotes->size = 32;
    quotes->index = 0;
    return SUCCESS;
}

static int skip_over(int i, quote_t *quotes)
{
    if (!quotes->arg[i])
        return i;
    if (quotes->arg[i] == '$') {
        i += 1;
        for (; is_alpha(quotes->arg[i]) && quotes->arg[i]; i += 1);
    }
    if (quotes->arg[i] == '`') {
        i += 1;
        for (; quotes->arg[i] != '`' && quotes->arg[i]; i += 1);
    }
    if (quotes->arg[i] == '\0')
        return i - 1;
    return i;
}

char *double_quote_case(char *argument, data_t *data)
{
    quote_t *quotes = NULL;
    char *result = 0;

    if (!argument || !data)
        return NULL;
    quotes = malloc(sizeof(quote_t));
    if (!quotes || init_quote(quotes, argument) == FAILURE)
        return free_all(quotes);
    for (int i = 0; quotes->arg[i]; i++) {
        if (check_arg(quotes, i, data) == FAILURE)
            return free_all(quotes);
        i = skip_over(i, quotes);
    }
    quotes->new[quotes->index] = '\0';
    result = strdup(quotes->new);
    free_all(quotes);
    return result;
}
