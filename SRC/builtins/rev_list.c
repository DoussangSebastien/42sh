/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** rev_list.c
*/

#include "shell_protos.h"

void rev_list(environ_t **environ)
{
    environ_t *curr = *environ;
    environ_t *prev = NULL;
    environ_t *next = NULL;

    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *environ = prev;
}
