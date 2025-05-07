/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** which_function.c
*/

#include "shell_protos.h"
#include "which.h"
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

static int check_which(char const *str, which_t *which)
{
    int result = 0;

    which->valid_count = 0;
    for (int i = 0; which->directories[i]; i++) {
        result = check_dir(str, which->directories[i]);
        if (result == 1 && !which->flag_a) {
            printf("%s/%s\n", which->directories[i], str);
            which->valid_count += 1;
            break;
        }
        if (result == 1) {
            which->valid_count += 1;
            printf("%s/%s\n", which->directories[i], str);
        }
        if (which->valid_count != 0)
            return 1;
    }
    if (which->valid_count != 0)
        return 1;
    return SUCCESS;
}

static void check_builtin(args_t *args, which_t *which, char *builtin_name)
{
    char *temp = get_variable(args, "BUILTINS");

    if (strstr(temp, builtin_name) != NULL) {
        printf("%s: shell built-in command\n", builtin_name);
        free(temp);
        return;
    }
    if (which->valid_count == 0) {
        printf("%s: Command not found.\n", builtin_name);
        which->saved_result = ERROR;
    }
    free(temp);
}

static int freeing(which_t which, int result)
{
    my_free_word_array(which.directories);
    return result;
}

int my_which(args_t *args)
{
    which_t which = {0};
    int checker = 0;

    which.flag_a = 0;
    which.directories = NULL;
    if (!args || !args->tab || !args->tab[0] || !args->tab[1])
        return fprintf(stderr, "which: Too few arguments.\n"), ERROR;
    if (init_which(args, &which) == FAILURE)
        return ERROR;
    for (int i = 1; args->tab[i]; i++) {
        checker = check_which(args->tab[i], &which);
        if (checker == FAILURE)
            return freeing(which, ERROR);
        if (checker == 1)
            continue;
        check_builtin(args, &which, args->tab[i]);
    }
    return freeing(which, which.saved_result);
}
