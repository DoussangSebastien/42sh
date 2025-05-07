/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** get_inhibitor.c
*/

#include "shell_protos.h"

char get_inhibitor(char c)
{
    for (int i = 0; INHIBITORS[i]; i++) {
        if (INHIBITORS[i] == c)
            return c;
    }
    return '\0';
}
