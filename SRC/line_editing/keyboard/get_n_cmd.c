/*
** EPITECH PROJECT, 2025
** line_editing
** File description:
** get_n_cmd.c
*/

#include "../line.h"
#include <stdlib.h>
#include <string.h>

static char *my_revstr(char *str)
{
    int len = strlen(str);
    char tmp = '\0';

    for (int i = 0; i < len / 2; i++) {
        tmp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = tmp;
    }
    return str;
}

static char *get_correct_cmd(char *buffer, int nb)
{
    char *token = strtok(buffer, "\n");
    char *copy = NULL;

    for (int i = 1; i < nb && token != NULL; i++)
        token = strtok(NULL, "\n");
    if (token) {
        copy = strdup(token);
        return my_revstr(copy);
    }
    return NULL;
}

static char *return_func(char *buffer, FILE *history, int size, int nb)
{
    char *cmd = NULL;

    buffer[size] = 0;
    fclose(history);
    cmd = get_correct_cmd(buffer, nb);
    free(buffer);
    buffer = NULL;
    return cmd;
}

char *get_n_cmd(int nb)
{
    FILE *history = get_history_path(1, 0);
    int size = 0;
    char *buffer = NULL;

    if (!history) {
        return NULL;
    }
    fseek(history, 0, SEEK_END);
    size = ftell(history);
    buffer = malloc(sizeof(char) * (size + 1));
    if (!buffer) {
        fclose(history);
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        fseek(history, size - 1 - i, SEEK_SET);
        buffer[i] = fgetc(history);
    }
    return return_func(buffer, history, size, nb);
}
