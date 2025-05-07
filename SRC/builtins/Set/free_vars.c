/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** free_vars.c
*/

#include "set_protos.h"

void free_vars(var_t *head)
{
    var_t *tmp = NULL;

    while (head) {
        tmp = head;
        head = head->next;
        free(tmp->name);
        free(tmp->value);
        free(tmp);
    }
}
