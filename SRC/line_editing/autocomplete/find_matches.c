/*
** EPITECH PROJECT, 2025
** autocomplete
** File description:
** find_matches.c
*/

#include "../line.h"
#include <dirent.h>
#include "macros.h"

static match_list_t *create_match_list(void)
{
    match_list_t *list = malloc(sizeof(match_list_t));

    if (!list)
        return NULL;
    list->match = NULL;
    list->count = 0;
    return list;
}

static int add_match(match_list_t *list, const char *name)
{
    char **tmp = realloc(list->match, sizeof(char *) * (list->count + 1));

    if (!tmp)
        return FAILURE;
    list->match = tmp;
    list->match[list->count] = strdup(name);
    if (!list->match[list->count])
        return FAILURE;
    list->count++;
    return SUCCESS;
}

void free_match_list(match_list_t *list)
{
    if (!list)
        return;
    for (int i = 0; i < list->count; i++)
        free(list->match[i]);
    free(list->match);
    free(list);
}

static void add_builtins(match_list_t *matches, char *dir_str,
    action_t *action, char *word)
{
    if (strcmp(dir_str, "/bin/"))
        return;
    for (int i = 0; i < FUNCTION_COUNT; i++) {
        if (!word || !strncmp_case_i(word, action->builtins[i],
            strlen(word)))
            add_match(matches, action->builtins[i]);
    }
}

match_list_t *find_matches(char *word, char *dir_str, action_t *action)
{
    DIR *dir = opendir(dir_str);
    struct dirent *entry;
    match_list_t *matches = create_match_list();

    if (!dir || !matches)
        return NULL;
    add_builtins(matches, dir_str, action, word);
    entry = readdir(dir);
    while (entry != NULL) {
        if (entry->d_name[0] == '.') {
            entry = readdir(dir);
            continue;
        }
        if (!word ||
            !strncmp_case_i(entry->d_name, word, strlen(word)))
            add_match(matches, entry->d_name);
        entry = readdir(dir);
    }
    closedir(dir);
    return matches;
}
