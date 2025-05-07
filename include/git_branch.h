/*
** EPITECH PROJECT, 2024
** Salah-Eddine
** File description:
** git_branch.h
*/

#ifndef GIT_BRANCH_H
    #define GIT_BRANCH_H
void display_current_branch(char *path);
int is_git_repo(const char *path, int end);
int get_path_index(char *path, int stop);
void find_repo_root(char *path);
void write_colored(int fd, const char *color, const char *text, int reset);
#endif /* GIT_BRANCH_H */
