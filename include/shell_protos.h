/*
** EPITECH PROJECT, 2024
** Edgar Duquesne
** File description:
** shel_protos.h
*/

#ifndef PROTOS
    #define PROTOS
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <stdio.h>
    #include "my.h"
    #include "shell_protos_2.h"
    #include "macros.h"
    #include "struct.h"
    #include "parsing_struct.h"
    #include "inhibitor.h"
    #include "globbings.h"
    #include "which.h"
int shell(char const *envp[]);
int executable_condition(pid_t pid, data_t *data,
    char const *input, int index);
int check_stdin(data_t *data);
char *create_path(args_t *args);
int execute_builtins(args_t *args, functions_t **functions, int *check);
int my_unalias(args_t *args);
int del_alias(alias_t **alias, alias_t *prev, alias_t **head);
int my_where(args_t *args);
int init_aliases(data_t *data);
int my_setenv(args_t *args);
int my_exit(args_t *args);
int my_cd(args_t *args);
int my_env(args_t *args);
int my_unsetenv(args_t *args);
int my_alias(args_t *args);
int shrimp_command(args_t *args);
int my_history(args_t *args);
void rev_list(environ_t **environ);
functions_t **init_function_list(functions_t **functions);
int init_data(data_t *data, char const *envp[]);
int init_environment(args_t *args, char const *envp[]);
char **build_envp(environ_t *environ);
void change_env_dir(environ_t *environ);
int old_pwd(args_t *args);
int analyze_input(data_t *data);
int display_cd_error(char *new_dir);
int free_functions(data_t *data, int return_val);
void create_env(data_t *data);
#endif
