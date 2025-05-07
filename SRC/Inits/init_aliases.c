/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** init_aliases.c
*/

#include "shell_protos.h"

static int get_len(char const *line)
{
    int i = 0;

    while (line[i] != '=' && line[i] && line[i] != '\n') {
        i += 1;
    }
    return i;
}

static char *get_alias(char const *line, int *start)
{
    int len = 0;
    char *result = 0;
    int i = 0;

    len = get_len(line);
    if (!line[len] || !line[len + 1])
        return NULL;
    result = malloc(sizeof(char) * len + 1);
    if (!result)
        return NULL;
    *start = len + 1;
    for (; i < len; i++)
        result[i] = line[i];
    result[i] = '\0';
    return result;
}

static char *get_alias_command(char const *line)
{
    int len = 0;
    char *result = 0;
    int i = 0;

    len = strlen(line);
    result = malloc(sizeof(char) * len + 1);
    if (!result)
        return NULL;
    for (; i < len && line[i] != '\n'; i++)
        result[i] = line[i];
    result[i] = '\0';
    return result;
}

int add_node(alias_t **alias, char const *line)
{
    alias_t *new_node = malloc(sizeof(alias_t));
    int start = 0;

    if (!new_node || !line)
        return FAILURE;
    new_node->next = NULL;
    new_node->name = get_alias(line, &start);
    if (!new_node->name) {
        free(new_node);
        return FAILURE;
    }
    new_node->command = get_alias_command(&line[start]);
    if (!new_node->command) {
        free(new_node->name);
        free(new_node);
        return FAILURE;
    }
    new_node->next = *alias;
    *alias = new_node;
    return SUCCESS;
}

int add_alias(alias_t **alias, char const *line)
{
    if (!line)
        return FAILURE;
    if (line[0] == '#')
        return SUCCESS;
    return add_node(alias, line);
}

static int ouput(int result, char *line, FILE *file)
{
    if (line)
        free(line);
    if (file)
        fclose(file);
    return result;
}

static int check_file(FILE *file, int result)
{
    file = fopen(ALIAS_FILE, "w");
    if (file)
        fclose(file);
    return result;
}

int init_aliases(data_t *data)
{
    FILE *file = NULL;
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;

    if (!data->args)
        return ERROR;
    file = fopen(ALIAS_FILE, "r");
    if (!file)
        return check_file(file, ERROR);
    read = getline(&line, &len, file);
    while (read != -1) {
        if (add_alias(&data->args->alias, line) == FAILURE)
            return ouput(FAILURE, line, file);
        read = getline(&line, &len, file);
    }
    return ouput(SUCCESS, line, file);
}
