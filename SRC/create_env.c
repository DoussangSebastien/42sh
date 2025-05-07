/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** create_env.c
*/

#include "shell_protos.h"

static char *get_concat(const char *builtins[], data_t *data)
{
    size_t total_length = 0;
    char *concatenated = NULL;

    for (int i = 0; builtins[i] != NULL; i++)
        total_length += strlen(builtins[i]);
    concatenated = malloc(sizeof(char) * total_length + 1);
    if (!concatenated)
        return NULL;
    concatenated[0] = '\0';
    for (int i = 0; builtins[i] != NULL; i++)
        strcat(concatenated, builtins[i]);
    concatenated[total_length] = '\0';
    return concatenated;
}

static void load_builtins(data_t *data)
{
    char **tab = (char **)malloc(4 * sizeof(char *));
    const char *builtins[] = {"alias/", "bg/", "bindkey/", "break/",
        "case/", "cd/", "chdir/", "complete/", "continue/", "default/",
        "dirs/", "echo/", "else/", "end/", "endif/", "eval/", "exec/",
        "exit/", "fg/", "foreach/", "glob/", "goto/", "history/", "hup/",
        "if/", "jobs/", "kill/", "limit/", "login/", "logout/", "rehash/",
        "repeat/", "set/", "setenv/", "shift/", "source/", "stop/", "unalias/",
        "unset/", "unsetenv/", "wait/", "where/", "which/", "while/", NULL};

    if (!tab)
        return;
    tab[0] = my_strdup("setenv");
    tab[1] = my_strdup("BUILTINS");
    tab[2] = get_concat(builtins, data);
    tab[3] = NULL;
    data->args->tab = tab;
    my_setenv(data->args);
    my_free_word_array(tab);
}

static void load_path(data_t *data)
{
    char **tab = (char **)malloc(4 * sizeof(char *));

    if (!tab)
        return;
    tab[0] = my_strdup("setenv");
    tab[1] = my_strdup("NLSPATH");
    tab[2] = add_str(NP, PATH);
    tab[3] = NULL;
    data->args->tab = tab;
    my_setenv(data->args);
    my_free_word_array(tab);
}

static void load_alias_file(data_t *data)
{
    char **tab = (char **)malloc(4 * sizeof(char *));
    char cwd[256] = {0};

    if (!tab)
        return;
    getcwd(cwd, 256);
    strcat(cwd, "/");
    tab[0] = my_strdup("setenv");
    tab[1] = my_strdup("ALIAS_FILE");
    tab[2] = add_str(cwd, ALIAS_FILE);
    tab[3] = NULL;
    data->args->tab = tab;
    my_setenv(data->args);
    my_free_word_array(tab);
}

void create_env(data_t *data)
{
    if (!data)
        return;
    load_path(data);
    load_builtins(data);
    load_alias_file(data);
}
