/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** display_error.c
*/

#include <unistd.h>
#include "my.h"
#include "shell_protos.h"

int display_error(char const *error_message)
{
    int len = 0;

    if (!error_message)
        return FAILURE;
    len = my_strlen(error_message);
    write(2, error_message, len);
    return FAILURE;
}
