/*
** EPITECH PROJECT, 2025
** autocomplete
** File description:
** multiple_matches.c
*/

#include "../line.h"
#include <sys/ioctl.h>
#include <stdbool.h>

static int get_terminal_width(void)
{
    struct winsize w;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
        return 80;
    return w.ws_col;
}

static int calculate_lines(match_list_t *matches, int term_width)
{
    int line_count = 1;
    int current_line_len = 0;
    int tab_len = 0;

    for (int i = 0; i < matches->count; i++) {
        tab_len = 8 - (current_line_len % 8);
        if (current_line_len + strlen(matches->match[i]) > term_width) {
            line_count++;
            current_line_len = 0;
        }
        current_line_len += strlen(matches->match[i]);
        if (i == matches->count - 1)
            continue;
        if (current_line_len + tab_len > term_width) {
            line_count++;
            current_line_len = 0;
        } else
            current_line_len += tab_len;
    }
    return line_count;
}

static void clear_previous(int lines)
{
    for (int i = 0; i < lines; i++) {
        write(1, "\033[1A", 4);
        write(1, "\033[2K", 4);
    }
}

static void print_matches(match_list_t *matches, int current)
{
    for (int i = 0; i < matches->count; i++) {
        if (i == current)
            write(1, "\033[7m", 4);
        write(1, matches->match[i], strlen(matches->match[i]));
        if (i == current)
            write(1, "\033[0m", 4);
        write(1, "\t", 1);
    }
    write(1, "\n", 1);
}

static void update_current(int *current, char c[3], match_list_t *matches)
{
    if (c[1] == '[' && c[2] == RIGHT)
        (*current)++;
    if (c[1] == '[' && c[2] == LEFT)
        (*current)--;
    if (*current >= matches->count)
        *current = 0;
    else if (*current < 0)
        *current = matches->count - 1;
}

static void display_newline(action_t *action)
{
    prompt();
    write(1, action->line->line, action->line->len);
}

static void end_multiple(action_t *action, char *word, int nb_lines, char *dir)
{
    clear_previous(nb_lines + 1);
    display_newline(action);
    if (!strcmp(dir, "/bin/"))
        return single_match(action, word, action->line->line, dir);
    single_match(action, word, "", "");
}

static void arrow_case(int *current, match_list_t *matches, int *nb_lines,
    char *dir)
{
    char c[3];
    const int width = get_terminal_width();
    int line = *nb_lines;

    c[0] = '\x1b';
    if (read(STDIN_FILENO, &c[1], 1) != 1 || read(STDIN_FILENO, &c[2], 1) != 1)
        return;
    if (c[2] == DOWN || c[2] == UP)
        return;
    clear_previous(*nb_lines);
    update_current(current, c, matches);
    *nb_lines = calculate_lines(matches, width);
    print_matches(matches, *current);
}

void multiple_matches(action_t *action, match_list_t *matches,
    char *dir, char *word)
{
    const int width = get_terminal_width();
    int current = 0;
    char c[3];
    int nb_lines = write(1, "\n", 1);

    nb_lines = calculate_lines(matches, width);
    print_matches(matches, current);
    while (read(STDIN_FILENO, &c[0], 1) != -1) {
        if (c[0] == NEWLINE) {
            clear_previous(nb_lines + 1);
            display_newline(action);
            return single_match(action, word, matches->match[current], dir);
        }
        if (c[0] == '\x1b') {
            arrow_case(&current, matches, &nb_lines, dir);
        } else
            return end_multiple(action, word, nb_lines, dir);
    }
}
