/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** get_arg_type.c
*/

#include "shell_protos.h"

int get_arg_type(char const *argument)
{
    int result_arg = ARG;
    char const *possible_arguments[] = {"|\0", "||\0", ">\0", ">>\0", "<\0",
        "<<\0", ";\0", "(\0", ")\0", "&\0", "&&\0", NULL};

    for (int i = 0; possible_arguments[i] != NULL; i++) {
        if (!my_strcmp(argument, possible_arguments[i])) {
            result_arg = i;
            break;
        }
    }
    return result_arg;
}
