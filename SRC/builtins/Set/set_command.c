/*
** EPITECH PROJECT, 2024
** salah-eddine
** File description:
** set_command.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "set_struct.h"
#include "set_protos.h"

char *trim_spaces(char *str)
{
    char *end = NULL;
    char *result = NULL;

    if (!str)
        return NULL;
    while (isspace((unsigned char)*str))
        str++;
    if (*str == 0)
        return strdup("");
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;
    end[1] = '\0';
    result = strdup(str);
    return result;
}

int is_valid_identifier(const char *str)
{
    if (!str || !*str || !isalpha((unsigned char)str[0]))
        return 0;
    for (int i = 1; str[i]; i++) {
        if (str[i] == '=')
            break;
        if (!isalnum((unsigned char)str[i]) && str[i] != '_')
            return 0;
    }
    return 1;
}

static char *create_combined_assignment(char *var, char *value)
{
    size_t len = strlen(var) + (value ? strlen(value) : 0) + 2;
    char *combined = malloc(len);

    if (!combined)
        return NULL;
    if (value)
        snprintf(combined, len, "%s=%s", var, value);
    else
        snprintf(combined, len, "%s=", var);
    return combined;
}

static int handle_spaced_assignment(args_t *args, char **tab, int i)
{
    char *combined = NULL;

    if (!tab[i + 2]) {
        fprintf(stderr, "set: Missing value after '='.\n");
        return 1;
    }
    combined = create_combined_assignment(tab[i], tab[i + 2]);
    if (!combined)
        return 1;
    process_set_argument(args, combined);
    free(combined);
    return 0;
}

static int handle_inline_assignment(args_t *args, char **tab, int *i)
{
    if (strchr(tab[*i], '=') && tab[*i][0] != '=') {
        process_set_argument(args, tab[*i]);
        (*i)++;
        return 1;
    }
    return 0;
}

static int handle_spaced_syntax(args_t *args, char **tab, int *i)
{
    if (tab[*i + 1] && strcmp(tab[*i + 1], "=") == 0) {
        if (!is_valid_identifier(tab[*i])) {
            *i += tab[*i + 2] ? 3 : 2;
            return -1;
        }
        if (handle_spaced_assignment(args, tab, *i))
            return -1;
        *i += tab[*i + 2] ? 3 : 2;
        return 1;
    }
    return 0;
}

int handle_simple_assignment(args_t *args, char **tab, int *i)
{
    if (!is_valid_identifier(tab[*i])) {
        (*i)++;
        return 1;
    }
    args->shell_vars = add_or_update_var(args->shell_vars, tab[*i], "");
    (*i)++;
    return 0;
}

static int handle_argument_case(args_t *args, char **tab, int *i)
{
    int result = handle_spaced_syntax(args, tab, i);

    if (result == 1)
        return 0;
    if (result == -1)
        return 1;
    if (handle_inline_assignment(args, tab, i))
        return 0;
    if (handle_simple_assignment(args, tab, i))
        return 1;
    return 0;
}

int my_set(args_t *args)
{
    static int initialized = 0;
    int i = 1;
    int has_error = 0;

    if (!initialized && args)
        args->shell_vars = NULL;
    if (!initialized) {
        init_minimal_vars(args);
        initialized = 1;
    }
    if (!args->tab[1])
        return handle_set_print(args);
    while (args->tab[i] && !has_error) {
        has_error = handle_argument_case(args, args->tab, &i);
    }
    if (has_error)
        fprintf(stderr, "set: Variable name must begin with a letter.\n");
    return has_error;
}
