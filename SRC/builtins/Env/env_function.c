/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** env_function.c
*/

#include "shell_protos.h"

static int put_str_2(char const *str)
{
    int i = 0;

    while (str[i]) {
        write(2, &str[i], 1);
        i += 1;
    }
    return i;
}

int my_env(args_t *args)
{
    char **envp = build_envp(args->environ);

    if (!envp)
        return SUCCESS;
    if (args->tab[1]) {
        write(2, "env: \'", 6);
        put_str_2(args->tab[1]);
        write(2, "\': No such file or directory\n", 29);
        return 127;
    }
    for (int i = 0; envp[i]; i++) {
        if (my_putstr(envp[i]) == -1) {
            my_free_word_array(envp);
            return 127;
        }
        write(1, "\n", 1);
    }
    my_free_word_array(envp);
    return SUCCESS;
}
