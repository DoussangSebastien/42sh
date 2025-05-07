/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** line_parser.c
*/

#include "shell_protos.h"
#include "shell_protos_2.h"

int excluded(char c, char const *n)
{
    for (int i = 0; n[i] != '\0'; i++) {
        if (n[i] == c)
            return YES;
    }
    return NO;
}

static int inner_loop(char *line, int i)
{
    char c_1 = line[i];
    char c_2 = line[i + 1];

    if ((c_1 == '<' && c_2 == '<') || (c_1 == '>' && c_2 == '>')
        || (c_1 == '&' && c_2 == '&') || (c_1 == '|' && c_2 == '|')) {
        return 2;
    }
    return 1;
}

static int get_len(char *line, int check)
{
    int i = 0;

    if (check == 0)
        return inner_loop(line, i);
    if (check == 1) {
        for (; line[i] && !excluded(line[i], SPLITTERS); i++);
    }
    return i;
}

static void filling(char **dest, int len, int *index, char *line)
{
    int t = 0;
    int i = 0;

    for (; i < len; i++) {
        if (line[*index + i] == ' ' ||
            line[*index + i] == '\t')
            continue;
        (*dest)[t] = line[*index + i];
        t += 1;
    }
    (*dest)[t] = '\0';
    (*index) += t;
}

static int fill_inhibitor(char **dest, char *line, int *index, data_t *data)
{
    char inhibitor = line[*index];
    int len = 1;

    for (; line[len + (*index)] &&
        line[len + (*index)] != inhibitor; len++);
    if (line[len + (*index)] == inhibitor)
        len += 1;
    *dest = build_command(&line[*index], data);
    (*index) += len;
    return SUCCESS;
}

static int fill_word(char **dest, char *line, int *index, data_t *data)
{
    int len = 0;

    while (line[*index] == ' ' || line[*index] == '\t')
        *index += 1;
    if (is_inhibitor(line[*index]) == YES)
        return fill_inhibitor(dest, line, index, data);
    if (excluded(line[*index], SPLITTERS) == YES)
        len = get_len(&line[*index], 0);
    else
        len = get_len(&line[*index], 1);
    *dest = malloc(sizeof(char) * (len + 1));
    if (!*dest)
        return FAILURE;
    filling(dest, len, index, line);
    *dest = build_command(*dest, data);
    if (!*dest)
        return FAILURE;
    return SUCCESS;
}

static int fill_tab(char **tab, int word_counted, char *line, data_t *data)
{
    int index = 0;

    for (int i = 0; i < word_counted; i++) {
        if (fill_word(&tab[i], line, &index, data) == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}

char **line_parser(char *line, data_t *data)
{
    int word_counted = 0;
    char **tab = NULL;

    if (!line || line[0] == '\0')
        return NULL;
    word_counted = count_words(line);
    tab = malloc(sizeof(char *) * (word_counted + 1));
    if (!tab)
        return NULL;
    if (fill_tab(tab, word_counted, line, data) == FAILURE) {
        my_free_word_array(tab);
        return NULL;
    }
    tab[word_counted] = NULL;
    return tab;
}
