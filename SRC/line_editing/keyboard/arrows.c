/*
** EPITECH PROJECT, 2025
** line_editing
** File description:
** up_down.c
*/

#include "../line.h"
#include <stdlib.h>
#include <string.h>

static void update_line(action_t *action, char *cmd)
{
    free(action->line->line);
    action->line->line = strdup(cmd);
    for (int i = 0; cmd[i] != '\0'; i++) {
        action->c = cmd[i];
        insert_char(action);
        write(1, &action->line->line[action->pos],
            action->line->len - action->pos);
        action->pos++;
    }
}

static int block_last_cmd(char **cmd, int limit, int *current)
{
    *cmd = get_n_cmd(limit);
    if (!*cmd)
        return FAILURE;
    *current = limit;
    return SUCCESS;
}

static void update_current(int *current, char arrow)
{
    if (arrow == UP)
        *current += 1;
    if (arrow == DOWN && *current > 0)
        *current -= 1;
}

static int return_new_cmd(action_t *action, char **cmd)
{
    if (cut_end(action))
        return FAILURE;
    update_line(action, *cmd);
    free(*cmd);
    return SUCCESS;
}

static int up_down(action_t *action, char arrow, int *current)
{
    char *cmd = NULL;
    int limit = *current;

    update_current(current, arrow);
    while (action->pos != 0) {
        if (backspace(action))
            return FAILURE;
    }
    if (arrow == DOWN && *current == 0)
        return SUCCESS;
    cmd = get_n_cmd(*current);
    if (!cmd) {
        if (block_last_cmd(&cmd, limit, current))
            return SUCCESS;
        update_line(action, cmd);
        free(cmd);
        return SUCCESS;
    }
    return return_new_cmd(action, &cmd);
}

int arrows(action_t *action)
{
    char arrow[2];
    int *current = &action->history_index;

    if (read(STDIN_FILENO, &arrow[0], 1) != 1 ||
        read(STDIN_FILENO, &arrow[1], 1) != 1)
        return FAILURE;
    if (arrow[0] == '[') {
        if (arrow[1] == UP || arrow[1] == DOWN)
            return up_down(action, arrow[1], current);
        if (arrow[1] == RIGHT && action->pos < action->line->len)
            return right(&action->pos);
        if (arrow[1] == LEFT && action->pos > 0)
            return left(&action->pos);
    }
    return SUCCESS;
}
