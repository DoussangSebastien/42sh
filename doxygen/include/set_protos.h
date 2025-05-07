/*
** EPITECH PROJECT, 2024
** Edgar Duquesne
** File description:
** shel_protos.h
*/

#ifndef PROTOS_2
    #define PROTOS_2
    #include "struct.h"
    #include <stdlib.h>
    #include "set_struct.h"
/**
 * @brief Frees a linked list of shell variables.
 *
 * @param head Pointer to the first var_t node.
 */
void free_vars(var_t *head);

/**
 * @brief Updates the shell variable holding the last executed command.
 *
 * @param args Pointer to argument context.
 * @param cmd Command string to store.
 */
void update_last_cmd(args_t *args, const char *cmd);

/**
 * @brief Adds a new variable to the list.
 *
 * @param head Head of the variable list.
 * @param name Name of the variable.
 * @param value Value to assign.
 * @return New head of the variable list.
 */
var_t *add_var(var_t *head, const char *name, const char *value);

/**
 * @brief Handles a variable assignment with a value.
 *
 * @param args Shell argument context.
 * @param input Full assignment string (e.g., NAME=VALUE).
 * @return 0 on success, -1 on failure.
 */
int handle_set_assignment(args_t *args, const char *input);

/**
 * @brief Handles a variable assignment without a value.
 *
 * @param args Shell argument context.
 * @param name Variable name to set with empty value.
 * @return 0 on success, -1 on failure.
 */
int handle_set_no_value(args_t *args, const char *name);

/**
 * @brief Prints all local shell variables.
 *
 * @param args Shell argument context.
 * @return 0 always.
 */
int handle_set_print(args_t *args);

/**
 * @brief Processes an individual `set` argument.
 *
 * @param args Shell argument context.
 * @param arg Raw argument string.
 */
void process_set_argument(args_t *args, const char *arg);

/**
 * @brief Initializes local variables from tcsh-style configuration.
 *
 * @param args Shell argument context.
 */
void init_local_vars_from_tcsh(args_t *args);

/**
 * @brief Prints all shell variables in the list.
 *
 * @param head Head of the var_t list.
 */
void print_vars(var_t *head);

/**
 * @brief Creates a new var_t node.
 *
 * @param name Variable name.
 * @param value Variable value.
 * @return Pointer to new node.
 */
var_t *create_new_var(const char *name, const char *value);

/**
 * @brief Reads variables from file and stores them in shell context.
 *
 * @param fp Open file pointer.
 * @param args Shell argument context.
 */
void read_and_store_vars(FILE *fp, args_t *args);

/**
 * @brief Sorts the variable list alphabetically by name.
 *
 * @param head Head of the list.
 * @return New sorted head.
 */
var_t *sort_vars(var_t *head);

/**
 * @brief Clones a list of shell variables.
 *
 * @param head Original list.
 * @return New cloned list.
 */
var_t *clone_vars(var_t *head);

/**
 * @brief Parses an assignment into name and value.
 *
 * @param input Full assignment string.
 * @param name Output: pointer to name (malloc’d).
 * @param value Output: pointer to value (malloc’d).
 * @return 0 on success, -1 on format error.
 */
int parse_assignment(const char *input, char **name, char **value);

/**
 * @brief Validates a shell variable name.
 *
 * @param str Variable name to validate.
 * @return 1 if valid, 0 otherwise.
 */
int is_valid_identifier(const char *str);

/**
 * @brief Trims leading and trailing spaces from a string.
 *
 * @param str String to trim.
 * @return Pointer to trimmed string (same or modified).
 */
char *trim_spaces(char *str);

/**
 * @brief Updates an existing variable with a new value.
 *
 * @param head List head.
 * @param target Node to update.
 * @param value New value string.
 * @return Head of the list.
 */
var_t *update_existing_var(var_t *head, var_t *target, const char *value);

/**
 * @brief Adds a variable or updates it if it already exists.
 *
 * @param head List head.
 * @param name Variable name.
 * @param value Value to set.
 * @return Updated list head.
 */
var_t *add_or_update_var(var_t *head, const char *name, const char *value);

/**
 * @brief Initializes a minimal set of shell variables if none exist.
 *
 * @param args Shell argument context.
 */
void init_minimal_vars(args_t *args);
#endif
