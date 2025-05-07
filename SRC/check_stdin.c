/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** check_stdin.c
*/

#include "../include/shell_protos.h"
#include "line_editing/line.h"

void display_cursor(void)
{
    if (isatty(STDIN_FILENO))
        prompt();
}

static void prep_command(data_t *data)
{
    if (data->args->interpreted == YES) {
        my_free_word_array(data->args->tab);
        data->args->interpreted = NO;
    }
}

static void load_local_status(int ret_value, data_t *data)
{
    char str[40] = {0};
    char *temp_tab[5] = {"set", "status", "=", str, NULL};

    prep_command(data);
    sprintf(str, "%d", ret_value);
    data->args->tab = temp_tab;
    my_set(data->args);
}

static int exec_stdin(data_t *data, char *line, int len)
{
    int ret_value = 0;
    tree_t *tree = NULL;

    if (!line || !len)
        return ERROR;
    if (line[0] == '\0')
        return SUCCESS;
    tree = generate_tree(line, data);
    if (!tree)
        return ERROR;
    if (binary_error_parser(tree) == FAILURE) {
        free_tree(tree);
        return ERROR;
    }
    ret_value = execute_tree(tree, data);
    free_tree(tree);
    return ret_value;
}

static int split_line(char *line, int read, data_t *data)
{
    int i = 0;
    char **tab = NULL;
    int ret_value = 0;

    prep_command(data);
    tab = my_str_to_word_array_n(line, "\r\n\0");
    if (!tab)
        return SUCCESS;
    while (tab[i] && !data->args->exit) {
        ret_value = exec_stdin(data, tab[i], read);
        i += 1;
        load_local_status(ret_value, data);
    }
    my_free_word_array(tab);
    if (!data->args->exit)
        display_cursor();
    return ret_value;
}

int check_stdin(data_t *data)
{
    char *line = NULL;
    int ret_value = 0;
    int len = 0;

    if (!data->args->environ)
        return FAILURE;
    display_cursor();
    len = handle_line(&line, data);
    data->args->input = line;
    while (len >= 0 && !data->args->exit) {
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';
        ret_value = split_line(line, len, data);
        if (data->args->exit)
            break;
        data->args->input = line;
        len = handle_line(&line, data);
    }
    free(line);
    return ret_value;
}
