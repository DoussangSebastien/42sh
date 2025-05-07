/*
** EPITECH PROJECT, 2024
** my_str_to_word_array
** File description:
** my_str_to_word_array
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int my_strlen(char const *str)
{
    int i = 0;

    while (str[i]) {
        i += 1;
    }
    return i;
}

int is_excluded(char c, char const *n)
{
    int len = my_strlen(n);

    for (int i = 0; i < len; i++) {
        if (n[i] == c)
            return 1;
    }
    return 0;
}

static void next_word(char const *str, int *index, char const *n)
{
    while (is_excluded(str[*index], n) && str[*index] != '\0') {
        *index += 1;
    }
}

static char *add_letters(int start, int end, char *ltr_memo, char const *str)
{
    int x = 0;

    for (int j = start; j < end; j++) {
        ltr_memo[x] = str[j];
        x += 1;
    }
    ltr_memo[x] = '\0';
    return ltr_memo;
}

static char *convert_to_word(char const *str, int *index, char const *n)
{
    char *letter_memo = NULL;
    int i = 0;
    int size = 0;
    int start = *index;

    for (i = start; str[i] != '\0'; i++) {
        if (is_excluded(str[i], n))
            break;
        size += 1;
    }
    *index = i;
    next_word(str, index, n);
    letter_memo = malloc((size + 1) * sizeof(char));
    if (!letter_memo)
        return NULL;
    return add_letters(start, (size + start), letter_memo, str);
}

static int word_count2(char const *str, char const *n)
{
    int word_count = 0;
    int i = 0;

    while (str[i] != '\0') {
        if (!is_excluded(str[i], n) &&
            (i == 0 || is_excluded(str[i - 1], n))) {
            word_count += 1;
        }
        i += 1;
    }
    return word_count;
}

char **my_str_to_word_array_n(char const *str, char const *n)
{
    int word_count = 0;
    int index = 0;
    char **word_memo = NULL;

    if (!str)
        return NULL;
    next_word(str, &index, n);
    word_count = word_count2(str, n);
    word_memo = malloc((sizeof(char *)) * (word_count + 1));
    if (!word_memo)
        return NULL;
    for (int j = 0; j < word_count; j++)
        word_memo[j] = convert_to_word(str, &index, n);
    word_memo[word_count] = NULL;
    return word_memo;
}
