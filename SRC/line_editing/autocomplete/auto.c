/*
** EPITECH PROJECT, 2025
** line_editing
** File description:
** auto.c
*/

#include "../line.h"
#include <dirent.h>
#include <ctype.h>
#include <sys/stat.h>

static void replace_word(action_t *action, char *replace)
{
    if (!action || !replace)
        return;
    while (action->pos > 0 && !isspace(action->line->line[action->pos - 1]) &&
        action->line->line[action->pos - 1] != '/')
        backspace(action);
    cut_end(action);
    for (int i = 0; replace[i] != '\0'; i++) {
        action->c = replace[i];
        printable_char(action);
    }
}

static void build_new_word(char *word, char *match, int is_dir, char **result)
{
    size_t len = strlen(word) + strlen(match) + 3;
    int prefix_len = 0;
    char *slash = strrchr(word, '/');

    *result = malloc(len);
    if (!*result)
        return;
    slash = strrchr(word, '/');
    if (slash) {
        prefix_len = slash - word + 1;
        snprintf(*result, len, "%.*s%s%s", prefix_len, word,
            match, is_dir ? "/" : "");
    } else
        snprintf(*result, len, "%s%s", match, is_dir ? "/" : "");
}

static char *get_full_path(char *dir, char *match)
{
    char *full_path = NULL;
    int len = 0;

    if (!strcmp(dir, "."))
        full_path = strdup(match);
    else {
        len = strlen(dir) + strlen(match) + 2;
        full_path = malloc(len);
        if (!full_path)
            return NULL;
        snprintf(full_path, len, "%s%s", dir, match);
    }
    return full_path;
}

void single_match(action_t *action, char *word, char *match, char *dir)
{
    char *full_path = NULL;
    int is_dir = 0;
    char *new_word = NULL;
    struct stat st;

    full_path = get_full_path(dir, match);
    if (!full_path)
        return;
    if (stat(full_path, &st) == 0 && S_ISDIR(st.st_mode))
        is_dir = 1;
    free(full_path);
    build_new_word(word, match, is_dir, &new_word);
    if (new_word) {
        replace_word(action, new_word);
        free(new_word);
    }
}

static int end_auto(match_list_t *matches, char *dir, char *word)
{
    free_match_list(matches);
    free(dir);
    free(word);
    return SUCCESS;
}

int autocomplete(action_t *action)
{
    char *word = NULL;
    char *dir = NULL;
    match_list_t *matches = NULL;

    if (!action || !action->line)
        return FAILURE;
    word = get_word(action);
    get_dir(action, &dir, word);
    if (!dir || !word)
        return SUCCESS;
    matches = find_matches(word, dir, action);
    if (!matches || matches->count == 0)
        return end_auto(matches, dir, word);
    if (matches->count == 1)
        single_match(action, word, matches->match[0], dir);
    else if (strcmp(dir, "/bin/"))
        multiple_matches(action, matches, dir, word);
    return end_auto(matches, dir, word);
}
