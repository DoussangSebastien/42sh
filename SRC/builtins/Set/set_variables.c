/*
** EPITECH PROJECT, 2024
** salah-eddine
** File description:
** set_variables.c
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "set_struct.h"

var_t *create_new_var(const char *name, const char *value)
{
    var_t *new = calloc(1, sizeof(var_t));

    if (!new)
        return NULL;
    new->name = name ? strdup(name) : strdup("");
    new->value = value ? strdup(value) : strdup("");
    if (!new->name || !new->value) {
        free(new->name);
        free(new->value);
        free(new);
        return NULL;
    }
    new->next = NULL;
    return new;
}
