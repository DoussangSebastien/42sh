/*
** EPITECH PROJECT, 2024
** salah-eddine
** File description:
** set_handling.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set_struct.h"
#include "set_protos.h"
#include "../../line_editing/line.h"

int handle_set_print(args_t *args)
{
    char *prev_cmd = get_n_cmd(2);

    if (prev_cmd) {
        args->shell_vars = add_or_update_var(args->shell_vars, "_", prev_cmd);
        free(prev_cmd);
    }
    print_vars(args->shell_vars);
    return 0;
}

static int set_assignment_error(const char *msg, char *name, char *value)
{
    fprintf(stderr, "%s", msg);
    free(name);
    free(value);
    return 1;
}

int handle_set_assignment(args_t *args, const char *input)
{
    char *name = NULL;
    char *value = NULL;

    if (parse_assignment(input, &name, &value) == -1 || !name)
        return set_assignment_error
        ("set: Variable name must begin with a letter.\n", name, value);
    if (!is_valid_identifier(name))
        return set_assignment_error(
        "set: Variable name must contain alphanumeric characters.\n",
        name, value);
    args->shell_vars = add_or_update_var(args->shell_vars, name,
    value ? value : "");
    free(name);
    free(value);
    return 0;
}

int handle_set_no_value(args_t *args, const char *name)
{
    if (!name || !*name) {
        fprintf(stderr, "set: Missing variable name.\n");
        return 1;
    }
    if (!is_valid_identifier(name)) {
        if (name[0] == '=')
            fprintf(stderr, "set: Missing variable name.\n");
        else
            fprintf(stderr, "set: Variable name must begin with a letter.\n");
        return 1;
    }
    args->shell_vars = add_or_update_var(args->shell_vars, name, "");
    return 0;
}

void update_last_cmd(args_t *args, const char *cmd)
{
    char *prev_cmd = NULL;

    if (!args || !cmd)
        return;
    if (strcmp(cmd, "set") != 0) {
        prev_cmd = get_n_cmd(2);
        if (prev_cmd) {
            args->shell_vars = add_or_update_var(args->shell_vars, "_",
            prev_cmd);
            free(prev_cmd);
        }
    }
}

static int process_assignment(args_t *args, const char *arg, char *equal)
{
    char *name = strndup(arg, equal - arg);
    char *value = equal + 1;

    if (!name)
        return 1;
    if (!is_valid_identifier(name)) {
        fprintf(stderr, "set: Variable name must begin with a letter.\n");
        free(name);
        return 1;
    }
    args->shell_vars = add_or_update_var(args->shell_vars, name, value);
    free(name);
    return 0;
}

static int process_simple_variable(args_t *args, const char *arg)
{
    if (!is_valid_identifier(arg)) {
        fprintf(stderr, "set: Variable name must begin with a letter.\n");
        return 1;
    }
    args->shell_vars = add_or_update_var(args->shell_vars, arg, "");
    return 0;
}

void process_set_argument(args_t *args, const char *arg)
{
    char *equal = NULL;

    if (!arg || !*arg) {
        fprintf(stderr, "set: Variable name must begin with a letter.\n");
        return;
    }
    equal = strchr(arg, '=');
    if (equal) {
        if (equal == arg) {
            fprintf(stderr, "set: Variable name must begin with a letter.\n");
            return;
        }
        process_assignment(args, arg, equal);
    } else {
        process_simple_variable(args, arg);
    }
}
