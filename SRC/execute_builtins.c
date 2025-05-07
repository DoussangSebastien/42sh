/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** execute_builtins.c
*/

#include "../include/shell_protos.h"

static void display_builtins(functions_t **functions)
{
    fflush(stdout);
    for (int i = 0; i < FUNCTION_COUNT; i++)
        printf(" %s", functions[i]->function_name);
    printf("\n");
}

int execute_builtins(args_t *args, functions_t **functions, int *check)
{
    if (!functions || !args->tab || !args->tab[0] || !args)
        return ERROR;
    if (!strcmp(args->tab[0], "builtins")) {
        display_builtins(functions);
        *check = 1;
        return SUCCESS;
    }
    for (int i = 0; i < FUNCTION_COUNT; i++) {
        if (!my_strcmp(functions[i]->function_name, args->tab[0])) {
            *check = 1;
            return functions[i]->exec(args);
        }
    }
    return SUCCESS;
}
