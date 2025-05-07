/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** where_function.c
*/

#include "shell_protos.h"
#include <fcntl.h>
#include <dirent.h>

static int check_dir(const char *str, const char *dir_name)
{
    DIR *dir = opendir(dir_name);
    struct dirent *entry = NULL;

    if (!dir)
        return SUCCESS;
    entry = readdir(dir);
    while (entry != NULL) {
        if (strcmp(entry->d_name, str) == 0) {
            closedir(dir);
            return 1;
        }
        entry = readdir(dir);
    }
    closedir(dir);
    return SUCCESS;
}

static char *get_path(environ_t *environ)
{
    environ_t *temp = environ;

    while (temp) {
        if (my_strstr(temp->variable, "PATH=") == temp->variable) {
            return &temp->variable[5];
        }
        temp = temp->next;
    }
    return NULL;
}

static int init_directory_struct(which_t *which, args_t *args)
{
    char *temp = NULL;

    temp = get_path(args->environ);
    if (!temp)
        return FAILURE;
    which->valid_count = 0;
    which->directories = my_str_to_word_array_n(temp, ":\n");
    if (which->directories == NULL)
        return FAILURE;
    return SUCCESS;
}

static void check_where(char const *str, which_t *which)
{
    int result = 0;

    for (int i = 0; which->directories[i]; i++) {
        result = check_dir(str, which->directories[i]);
        if (result == 1) {
            which->valid_count += 1;
            printf("%s/%s\n", which->directories[i], str);
        }
    }
    if (which->valid_count == 0)
        which->saved_result = ERROR;
}

static void check_builtin(args_t *args, which_t *which, char *builtin_name)
{
    char *temp = get_variable(args, "BUILTINS");

    which->valid_count = 0;
    if (strstr(temp, strcat(builtin_name, "/")) != NULL) {
        printf("%s is a shell built-in\n", builtin_name);
        which->valid_count += 1;
    }
    free(temp);
}

int my_where(args_t *args)
{
    which_t which = {0};

    which.flag_a = 0;
    which.saved_result = 0;
    which.directories = NULL;
    if (!args || !args->tab || !args->tab[0] || !args->tab[1])
        return fprintf(stderr, "where: Too few arguments.\n"), ERROR;
    if (init_directory_struct(&which, args) == FAILURE)
        return ERROR;
    for (int i = 1; args->tab[i]; i++) {
        if (args->tab[i][0] == '-')
            continue;
        check_where(args->tab[i], &which);
        check_builtin(args, &which, args->tab[i]);
    }
    my_free_word_array(which.directories);
    return which.saved_result;
}
