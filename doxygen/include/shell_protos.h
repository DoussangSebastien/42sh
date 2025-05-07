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
/** 
 * @brief Main shell loop entry point.
 * 
 * Initializes shell data and begins input loop.
 * 
 * @param envp Array of environment variables.
 * @return Exit status code of the shell.
 */
int shell(char const *envp[]);

/**
 * @brief Executes a child process or handles post-fork behavior.
 * 
 * @param pid Process ID returned from fork.
 * @param data Pointer to main shell context.
 * @param input Raw input string.
 * @param index Index of command in command list.
 * @return Exit code of the child process or error.
 */
int executable_condition(pid_t pid, data_t *data,
    char const *input, int index);

/**
 * @brief Checks if standard input is valid or redirected.
 * 
 * @param data Pointer to shell data.
 * @return 1 if stdin is valid, 0 otherwise.
 */
int check_stdin(data_t *data);

/**
 * @brief Constructs the full path to a command.
 * 
 * @param args Pointer to parsed argument context.
 * @return Allocated string containing the full path.
 */
char *create_path(args_t *args);

/**
 * @brief Executes a built-in command if one matches.
 * 
 * @param args Argument context.
 * @param functions Built-in function table.
 * @param check Output: set if a built-in was matched.
 * @return Return value of executed built-in or -1.
 */
int execute_builtins(args_t *args, functions_t **functions, int *check);

/**
 * @brief Executes the `unalias` built-in.
 */
int my_unalias(args_t *args);

/**
 * @brief Deletes an alias from the list.
 * 
 * @param alias Pointer to alias node.
 * @param prev Pointer to previous alias node.
 * @param head Pointer to head of alias list.
 * @return 0 on success, -1 if alias not found.
 */
int del_alias(alias_t **alias, alias_t *prev, alias_t **head);

/**
 * @brief Executes the `where` built-in.
 */
int my_where(args_t *args);

/**
 * @brief Initializes the alias list.
 */
int init_aliases(data_t *data);

/**
 * @brief Built-in implementation of `setenv`.
 */
int my_setenv(args_t *args);

/**
 * @brief Exits the shell with a specified status.
 */
int my_exit(args_t *args);

/**
 * @brief Changes the current working directory.
 */
int my_cd(args_t *args);

/**
 * @brief Displays the environment variables.
 */
int my_env(args_t *args);

/**
 * @brief Removes environment variables.
 */
int my_unsetenv(args_t *args);

/**
 * @brief Defines or displays aliases.
 */
int my_alias(args_t *args);

/**
 * @brief Displays the shell's command history.
 */
int my_history(args_t *args);

/**
 * @brief Reverses the environment variable linked list.
 */
void rev_list(environ_t **environ);

/**
 * @brief Initializes the table of built-in functions.
 * 
 * @param functions Preallocated function table (optional).
 * @return Initialized function table.
 */
functions_t **init_function_list(functions_t **functions);

/**
 * @brief Initializes the global shell data.
 * 
 * @param data Pointer to the data structure.
 * @param envp Array of environment variables.
 * @return 0 on success.
 */
int init_data(data_t *data, char const *envp[]);

/**
 * @brief Initializes the environment variable list.
 */
int init_environment(args_t *args, char const *envp[]);

/**
 * @brief Builds an envp-style array from internal list.
 */
char **build_envp(environ_t *environ);

/**
 * @brief Updates environment after a directory change.
 */
void change_env_dir(environ_t *environ);

/**
 * @brief Retrieves the old working directory.
 */
int old_pwd(args_t *args);

/**
 * @brief Parses and analyzes raw input for execution.
 */
int analyze_input(data_t *data);

/**
 * @brief Displays an error message for a failed `cd`.
 */
int display_cd_error(char *new_dir);

/**
 * @brief Frees all function-related memory in shell data.
 * 
 * @param data Shell state structure.
 * @param return_val Exit status.
 * @return The same return_val for chaining.
 */
int free_functions(data_t *data, int return_val);

/**
 * @brief Creates initial environment list in the shell.
 */
void create_env(data_t *data);
#endif
