/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** del_node.c
*/

#include "shell_protos.h"

int del_alias(alias_t **alias, alias_t *prev, alias_t **head)
{
    alias_t *temp = NULL;

    if (!*alias)
        return ERROR;
    temp = *alias;
    if (!prev)
        *head = temp->next;
    else
        prev->next = temp->next;
    free(temp->name);
    free(temp->command);
    free(temp);
    return SUCCESS;
}
