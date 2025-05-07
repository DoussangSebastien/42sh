/*
** EPITECH PROJECT, 2024
** Salah-Eddine
** File description:
** git_branch.h
*/

#ifndef GIT_BRANCH_H
    #define GIT_BRANCH_H
/**
 * @display current github repo branch.
 * @param path Path to github repo
 * @return display of current branch
 */
void display_current_branch(char *path);
/**
 * @check if current directory is a github repo.
 * @param path Path to github repo
 * @param end Number of char in path
 * @return 1/0 depending is directory is a github repo.
 */
int is_git_repo(const char *path, int end);
int get_path_index(char *path, int stop);
/**
 * @display repo from root.
 * @param path Path to github repo
 * @display the repo from root if it's a repo.
 */
void find_repo_root(char *path);
/**
 * @write with color.
 * @param fd Output of your choice
 * @param color ANSI color code of your choice
 * @param text Text to write
 * @param reset Option to reset color
 * @write text in color in output of choice and possibility to reset color.
 */
void write_colored(int fd, const char *color, const char *text, int reset);
#endif /* GIT_BRANCH_H */
