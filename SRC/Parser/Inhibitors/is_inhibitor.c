/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** is_inhibitor.c
*/

#include "shell_protos.h"

int is_inhibitor(char c)
{
    for (int i = 0; INHIBITORS[i]; i++) {
        if (c == INHIBITORS[i])
            return YES;
    }
    return NO;
}
