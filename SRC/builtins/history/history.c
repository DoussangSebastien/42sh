/*
** EPITECH PROJECT, 2025
** history
** File description:
** history.c
*/

#include "shell_protos.h"
#include "../../line_editing/line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

static int my_isdigit(char c)
{
    return (c >= '0' && c <= '9');
}

static int history_clear(void)
{
    FILE *fp = get_history_path(0, 1);

    if (fp)
        fclose(fp);
    return SUCCESS;
}

static int history_search(char *pattern)
{
    char *line = NULL;
    size_t len = 0;
    FILE *fp = get_history_path(1, 0);

    if (!fp)
        return ERROR;
    for (int i = 0; getline(&line, &len, fp) != -1; i++) {
        if (strstr(line, pattern))
            printf("line %d - %s", i, line);
    }
    fclose(fp);
    free(line);
    return SUCCESS;
}

static int history_cmd(char *cmd_index)
{
    char *line = NULL;
    size_t len = 0;
    int index = atoi(cmd_index) - 1;
    FILE *fp = get_history_path(1, 0);

    if (!fp)
        return ERROR;
    for (int i = 0; getline(&line, &len, fp) != -1; i++) {
        if (i == index) {
            printf("%s", line);
            break;
        }
    }
    fclose(fp);
    free(line);
    return SUCCESS;
}

static int basic_history(void)
{
    char *line = NULL;
    size_t len = 0;
    FILE *fp = get_history_path(1, 0);

    if (!fp)
        return ERROR;
    for (int i = 0; getline(&line, &len, fp) != -1; i++)
        printf("%d  %s", i, line);
    fclose(fp);
    free(line);
    return SUCCESS;
}

int my_history(args_t *args)
{
    if (args->tab[1]) {
        if (!strcmp(args->tab[1], "-c"))
            return history_clear();
        if (!strcmp(args->tab[1], "-s") && args->tab[2])
            return history_search(args->tab[2]);
        if (args->tab[1][0] == '!' && my_isdigit(args->tab[1][1]))
            return history_cmd(&args->tab[1][1]);
    }
    return basic_history();
}
