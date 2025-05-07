/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** change_env_dir.c
*/

#include "shell_protos.h"

static void change_old_pwd(char *old_dir, environ_t *temp)
{
    while (temp) {
        if (my_strstr(temp->variable, "OLDPWD=")) {
            free(temp->variable);
            temp->variable = add_str("OLDPWD=", old_dir);
            break;
        }
        temp = temp->next;
    }
    free(old_dir);
}

static char *update_pwd(environ_t *temp)
{
    char temp_dir[256];
    char *prev_dir = NULL;

    if (my_strstr(temp->variable, "PWD=")) {
        getcwd(temp_dir, 256);
        prev_dir = my_strdup(&temp->variable[4]);
        free(temp->variable);
        temp->variable = add_str("PWD=", temp_dir);
        return prev_dir;
    }
    return 0;
}

void change_env_dir(environ_t *environ)
{
    environ_t *temp = NULL;
    char *prev_dir = NULL;

    if (!environ)
        return;
    temp = environ;
    while (temp && !prev_dir) {
        if (temp->variable[0] == 'O')
            temp = temp->next;
        prev_dir = update_pwd(temp);
        temp = temp->next;
    }
    if (prev_dir)
        change_old_pwd(prev_dir, environ);
    return;
}
