/*
** EPITECH PROJECT, 2024
** salah-eddine
** File description:
** git_branch.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include "ansi_colors.h"
#include "git_branch.h"
#include "git_commits.h"

static void get_git_head_path(char *path, char *git_path, size_t size)
{
    snprintf(git_path, size, "%s/.git/HEAD", path);
}

static void print_branch_name(char *buffer)
{
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strncmp(buffer, "ref: refs/heads/", 16) == 0) {
        write_colored(STDOUT_FILENO, ANSI_BOLD ANSI_PURPLE, "  ", 0);
        write_colored(STDOUT_FILENO, ANSI_BOLD ANSI_PURPLE, buffer + 16, 1);
    }
}

static void print_commit_count(int commit_count)
{
    char count_str[32];

    if (commit_count >= 0) {
        snprintf(count_str, sizeof(count_str), " ↙±%d", commit_count);
        write_colored(STDOUT_FILENO, ANSI_BOLD ANSI_YELLOW, count_str, 1);
    }
}

void display_current_branch(char *path)
{
    FILE *file = NULL;
    char git_path[256];
    char buffer[256];
    int commit_count = count_commits(path);

    get_git_head_path(path, git_path, sizeof(git_path));
    file = fopen(git_path, "r");
    if (file == NULL)
        return;
    if (fgets(buffer, sizeof(buffer), file) != NULL) {
        print_branch_name(buffer);
        print_commit_count(commit_count);
    }
    fclose(file);
}

int is_git_repo(const char *path, int end)
{
    struct stat st;
    char git_path[512] = {0};
    char new_path[256] = {0};

    strncpy(new_path, path, end);
    snprintf(git_path, sizeof(git_path), "%s/.git", new_path);
    if (stat(git_path, &st) == 0 && (S_ISDIR(st.st_mode)
    || S_ISREG(st.st_mode))) {
        display_current_branch(new_path);
        return 1;
    }
    return 0;
}

int get_path_index(char *path, int stop)
{
    int last_index = 0;

    for (int i = 0; path[i] && i < stop; i++) {
        if (path[i] == '/')
            last_index = i;
    }
    return last_index;
}

void find_repo_root(char *path)
{
    int last_index = 0;

    if (!path)
        return;
    last_index = strlen(path);
    while (1) {
        if (is_git_repo(path, last_index))
            return;
        if (!last_index)
            break;
        last_index = get_path_index(path, last_index);
    }
}
