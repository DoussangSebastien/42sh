/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** get_history_path.c
*/

#include "line.h"
#include <unistd.h>
#include <libgen.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>

char *get_repo_history_path(void)
{
    static char history_path[PATH_MAX];
    char exe_path[PATH_MAX];
    ssize_t len;
    char *dir = NULL;

    len = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);
    if (len == -1)
        return NULL;
    exe_path[len] = '\0';
    dir = dirname(exe_path);
    snprintf(history_path, sizeof(history_path), "%s/bonus/42history.txt",
        dir);
    return history_path;
}

FILE *get_history_path(int read, int write)
{
    char *path = get_repo_history_path();

    if (!path)
        return NULL;
    if (write)
        return fopen(path, "w");
    return (read) ? fopen(path, "r") : fopen(path, "a");
}
