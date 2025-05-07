/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** count_word.c
*/

#include "shell_protos_2.h"
#include "shell_protos.h"
#include <stdio.h>

int redir_condition(char *str, int *i, char const *n)
{
    if ((!str) || (!str[*i]))
        return -1;
    if (str[(*i) + 1]) {
        if (str[*i] == '(' || str[*i] == ')')
            return 1;
        if (str[*i] != str[*i + 1])
            return 1;
        if (excluded(str[(*i) + 1], n)) {
            (*i) += 1;
            return 1;
        }
    }
    return 1;
}

static int check_char(char *str, int *i)
{
    int ret = 0;
    char inhibitor = get_inhibitor(str[*i]);

    if (inhibitor && str[*i]) {
        (*i) += 1;
        while (str[*i] && str[*i] != inhibitor)
            (*i) += 1;
        if (str[*i] && str[*i] == inhibitor)
            (*i) += 1;
        return 1;
    }
    if (excluded(str[*i], KEEPERS))
        ret = redir_condition(str, i, KEEPERS);
    return ret;
}

static int should_increment(int i, char *str)
{
    if (!excluded(str[i], SPLITTERS) &&
        (i == 0 || excluded(str[i - 1], SPLITTERS)))
        return YES;
    return NO;
}

int count_words(char *str)
{
    int word_count = 0;
    int i = 0;
    int temp = 0;

    while (str[i] != '\0') {
        temp = check_char(str, &i);
        if (temp == -1)
            return -1;
        if (!str[i])
            i -= 1;
        if (temp) {
            word_count += 1;
            i += 1;
            continue;
        }
        if (should_increment(i, str))
            word_count += 1;
        i++;
    }
    return word_count;
}
