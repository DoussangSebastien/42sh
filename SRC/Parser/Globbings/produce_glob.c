/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** matches_glob.c
*/

#include "shell_protos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <regex.h>

static int is_matching(const char *pattern, const char *file_name)
{
    char error_msg[100] = {0};
    int ret = 0;
    regex_t regex;

    if (!pattern || !file_name)
        return NO;
    ret = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (ret) {
        regerror(ret, &regex, error_msg, sizeof(error_msg));
        fprintf(stderr, "No Globs: %s\n", error_msg);
        return NO;
    }
    ret = regexec(&regex, file_name, 0, NULL, 0);
    regfree(&regex);
    return ret == 0 ? YES : NO;
}

static char *output(char *to_free, DIR *dir,
    char *output_str, int glob_matches)
{
    if (glob_matches == 0)
        fprintf(stderr, "No globs matches found.\n");
    if (dir)
        closedir(dir);
    if (to_free)
        free(to_free);
    return output_str;
}

static int build_str(char **result, struct dirent *entry,
    const char *pattern, int *glob_matches)
{
    char *temp = NULL;
    size_t new_len = 0;

    if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
        return SUCCESS;
    if (!is_matching(pattern, entry->d_name))
        return SUCCESS;
    *glob_matches += 1;
    if (!*result) {
        *result = strdup(entry->d_name);
        return *result ? SUCCESS : FAILURE;
    }
    new_len = strlen(*result) + strlen(entry->d_name) + 2;
    temp = malloc(new_len);
    if (!temp)
        return FAILURE;
    snprintf(temp, new_len, "%s %s", *result, entry->d_name);
    free(*result);
    *result = temp;
    return SUCCESS;
}

static int init_elems(char **regex_pattern, DIR **dir,
    const char *input_glob, struct dirent **entry)
{
    *dir = opendir(".");
    if (!*dir) {
        fprintf(stderr, "No Globs: %s\n", input_glob);
        return FAILURE;
    }
    *regex_pattern = tokenize_glob(input_glob);
    if (!*regex_pattern) {
        closedir(*dir);
        return FAILURE;
    }
    *entry = readdir(*dir);
    if (!entry) {
        closedir(*dir);
        return FAILURE;
    }
    return SUCCESS;
}

static int matche_glob(char c)
{
    for (int i = 0; GLOBBINGS[i]; i++) {
        if (c == GLOBBINGS[i])
            return YES;
    }
    return NO;
}

static int contains_glob(const char *input)
{
    for (size_t i = 0; input[i] && input[i] > ' '; i++) {
        if (matche_glob(input[i]) == YES)
            return YES;
    }
    return NO;
}

char *produce_glob(const char *input_glob)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char *regex_pattern = NULL;
    char *result = NULL;
    int glob_matches = 0;

    if (!input_glob || contains_glob(input_glob) == NO ||
        init_elems(&regex_pattern, &dir, input_glob, &entry) == FAILURE)
        return NULL;
    while (entry != NULL) {
        if (build_str(&result, entry,
            regex_pattern, &glob_matches) == FAILURE) {
            free(regex_pattern);
            return output(result, dir, NULL, glob_matches);
        }
        entry = readdir(dir);
    }
    return output(regex_pattern, dir, result, glob_matches);
}
