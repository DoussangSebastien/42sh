/*
** EPITECH PROJECT, 2025
** test
** File description:
** term.c
*/

#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "line.h"
#include "macros.h"

static int init_term(struct termios *orig, struct termios *new)
{
    if (tcgetattr(STDIN_FILENO, orig) == -1)
        return FAILURE;
    *new = *orig;
    new->c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, new) == -1)
        return FAILURE;
    return SUCCESS;
}

static int update_line(line_t *line, char **new_line)
{
    int len = 0;

    if (!line || !line->line)
        return -1;
    free(*new_line);
    line->line[line->len] = '\0';
    *new_line = strdup(line->line);
    len = line->len;
    free_line(line);
    return len;
}

static int ret_func(action_t *action, char **new_line, struct termios *orig)
{
    FILE *history = get_history_path(0, 0);
    int len = update_line(action->line, new_line);
    char *history_cmd = get_n_cmd(1);

    if (history && *new_line && (*new_line)[0] != '\0') {
        if (!history_cmd || strcmp(history_cmd, *new_line) != 0)
            fprintf(history, "%s\n", *new_line);
    }
    if (history)
        fclose(history);
    if (history_cmd)
        free(history_cmd);
    free_action(action);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, orig);
    return len;
}

action_t *init_actions(data_t *data)
{
    action_t *action = NULL;

    if (!data)
        return NULL;
    action = malloc(sizeof(action_t));
    if (!action)
        return NULL;
    action->line = init_line();
    if (!action->line) {
        free(action);
        return NULL;
    }
    action->c = '\0';
    action->pos = 0;
    action->history_index = 0;
    action->last_c = '\0';
    action->auto_complete = 0;
    return action;
}

static int echo_case(char **new_line)
{
    size_t len = 0;
    size_t read_len;

    read_len = getline(new_line, &len, stdin);
    if (read_len == -1) {
        return -1;
    }
    if ((*new_line)[read_len - 1] == '\n') {
        (*new_line)[read_len - 1] = '\0';
        read_len--;
    }
    return read_len;
}

int handle_line(char **new_line, data_t *data)
{
    struct termios orig;
    struct termios new;
    action_t *action = init_action(data);

    if (!isatty(STDIN_FILENO))
        return echo_case(new_line);
    if (!action || init_term(&orig, &new))
        return -1;
    while (1) {
        if (read(STDIN_FILENO, &action->c, 1) != 1) {
            tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig);
            return -1;
        }
        if (handle_keyboard(action))
            return -1;
        action->last_c = action->c;
        if (action->c == '\r' || action->c == '\n')
            break;
    }
    return ret_func(action, new_line, &orig);
}
