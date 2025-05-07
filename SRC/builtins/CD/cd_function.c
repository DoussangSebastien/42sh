/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** cd_function.c
*/

#include "shell_protos.h"
#include <sys/stat.h>

static int get_args_count(char **tab)
{
    int i = 0;

    for (; tab[i]; i++);
    return i;
}

static char *get_home_path(environ_t *environ)
{
    char *home_path = NULL;
    environ_t *temp = environ;

    while (temp) {
        if (my_strstr(temp->variable, "HOME=") == temp->variable) {
            home_path = my_strdup(&temp->variable[5]);
            break;
        }
        temp = temp->next;
    }
    return home_path;
}

static int get_index(char const *input)
{
    int result = 0;

    if (input[0] == '~')
        result = 1;
    if (input[0] == '/')
        result = 2;
    return result;
}

static int free_condition(char *new_dir, char *path, int res,
    environ_t *environ)
{
    if (new_dir && my_strcmp(new_dir, path))
        free(new_dir);
    if (path) {
        if (path[0] == '~' || path[0] == '-')
            return SUCCESS;
    }
    return res;
}

static int change_specified_dir(char *path, environ_t *env)
{
    char *home_dir = NULL;
    char *new_dir = path;
    int index = 0;
    char *temp = NULL;

    if (path[0] == '~') {
        home_dir = get_home_path(env);
        index = get_index(path);
        temp = add_str(home_dir, "/");
        new_dir = add_str(temp, (char *)&path[index]);
        free(temp);
    }
    if (new_dir == NULL)
        new_dir = home_dir;
    if (home_dir)
        free(home_dir);
    if (chdir(new_dir) == -1)
        return free_condition(new_dir, path, display_cd_error(new_dir), env);
    return free_condition(new_dir, path, 0, env);
}

static int process_count(const int count, char *home_path, args_t *args)
{
    if (!args || !args->tab || !args->environ || count > 2)
        return ERROR;
    if (!my_strcmp(args->tab[1], "-\0")) {
        free(home_path);
        return old_pwd(args);
    }
    if (count == 2) {
        free(home_path);
        return change_specified_dir(args->tab[1], args->environ);
    }
    if (count == 1 && home_path) {
        if (chdir(home_path) == -1) {
            free(home_path);
            return ERROR;
        }
    }
    if (home_path)
        free(home_path);
    return SUCCESS;
}

int my_cd(args_t *args)
{
    int count = 0;
    char *home_path = NULL;
    int result = 1;

    if (!args || !args->tab)
        return FAILURE;
    for (int i = 0; args->tab[i]; i++) {
        if (i >= 2)
            return display_error("cd: Too many arguments.\n");
    }
    home_path = get_home_path(args->environ);
    count = get_args_count(args->tab);
    result = process_count(count, home_path, args);
    change_env_dir(args->environ);
    if (result == 1 || result == 0)
        return result;
    return free_condition(NULL, NULL, result, args->environ);
}
