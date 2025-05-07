/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** setenv_function.c
*/

#include "shell_protos.h"

static int add_node(environ_t **environ, char *value)
{
    environ_t *new_node = malloc(sizeof(environ_t));

    if (!new_node)
        return FAILURE;
    new_node->variable = value;
    if (!new_node->variable) {
        free(new_node);
        return FAILURE;
    }
    new_node->next = *environ;
    *environ = new_node;
    return SUCCESS;
}

static int str_var_str(char const *var, char const *ref)
{
    int i = 0;

    while (var[i] && ref[i] != '=') {
        if (var[i] != ref[i])
            break;
        if (var[i + 1] == '\0')
            return ERROR;
        i += 1;
    }
    return SUCCESS;
}

static int process_result(char *name, char const *input, environ_t *temp)
{
    char *temp_var = NULL;

    if (str_var_str(name, temp->variable) == 1) {
        free(temp->variable);
        temp_var = add_str(name, "=");
        if (!input) {
            temp->variable = temp_var;
            return SUCCESS;
        }
        temp->variable = add_str(temp_var, (char *)input);
        free(temp_var);
        return SUCCESS;
    }
    return ERROR;
}

static char *make_var(char *name, char *var)
{
    char *temp_name = NULL;
    char *temp_name_2 = NULL;

    temp_name = add_str(name, "=");
    if (!var)
        return temp_name;
    temp_name_2 = add_str(temp_name, var);
    free(temp_name);
    return temp_name_2;
}

static int is_input_valid(char **tab)
{
    if (!tab || !tab[0] || !tab[1])
        return NO;
    if (tab[2] && tab[3]) {
        write(2, "setenv: Too many arguments.\n", 28);
        return NO;
    }
    if (!is_alpha(tab[1][0])) {
        write(2, "setenv: Variable name must begin with a letter.\n", 48);
        return NO;
    }
    if (!is_alphanumeric(tab[1])) {
        write(2,
        "setenv: Variable name must contain alphanumeric characters.\n", 60);
        return NO;
    }
    return YES;
}

int my_setenv(args_t *args)
{
    environ_t *temp = NULL;
    int result = 1;

    if (!args || !args->tab)
        return ERROR;
    if (!args->tab[1])
        return my_env(args);
    if (is_input_valid(args->tab) == NO)
        return ERROR;
    temp = args->environ;
    while (temp && result) {
        result = process_result(args->tab[1], args->tab[2], temp);
        temp = temp->next;
    }
    if (result)
        add_node(&args->environ, make_var(args->tab[1], args->tab[2]));
    return SUCCESS;
}
