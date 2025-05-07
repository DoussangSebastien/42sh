/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** prompt.c
*/

#include <unistd.h>
#include "ansi_colors.h"
#include "git_branch.h"
#include "git_commits.h"

static int get_tild_index(char *buffer)
{
    int slash_count = 0;
    int i = 0;

    for (; buffer[i] && slash_count <= 2; i++) {
        if (buffer[i] == '/')
            slash_count += 1;
    }
    return i;
}

void prompt(void)
{
    char buffer[256] = {0};
    int start = 0;

    getcwd(buffer, 256);
    start = get_tild_index(buffer);
    write_colored(STDOUT_FILENO, ANSI_BOLD ANSI_CYAN, "~/", 0);
    write_colored(STDOUT_FILENO, ANSI_BOLD ANSI_CYAN, &buffer[start], 1);
    find_repo_root(buffer);
    write_colored(STDOUT_FILENO, ANSI_BOLD ANSI_GREEN, " > ", 1);
}
