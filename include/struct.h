/*
** EPITECH PROJECT, 2024
** Edgar Duquesne
** File description:
** shel_protos.h
*/

#ifndef STRUCT
    #define STRUCT
    #include "parsing_struct.h"
    #include "set_struct.h"
/**
 * @struct alias_s
 * @brief Represents a user-defined alias in the shell.
 *
 * Stores the alias name and the command it expands to.
 */
typedef struct alias_s {
    char *command;            /**< Command string the alias expands to */
    char *name;               /**< Name of the alias */
    struct alias_s *next;     /**< Next alias in the linked list */
} alias_t;

/**
 * @struct environ_s
 * @brief Represents an environment variable in a linked list.
 *
 * Used to track environment variables internally in the shell.
 */
typedef struct environ_s {
    char *variable;           /**< Full variable string in the form NAME=VALUE */
    struct environ_s *next;   /**< Next variable in the list */
} environ_t;

/**
 * @struct args_s
 * @brief Represents all shell input and context passed to built-in functions.
 *
 * Contains argument data, environment, aliases, file descriptors, and state flags.
 */
typedef struct args_s {
    char **tab;               /**< Parsed input tokens (e.g., argv-style) */
    int interpreted;          /**< Flag indicating if input was interpreted */
    char *input;              /**< Raw input string */
    environ_t *environ;       /**< Linked list of environment variables */
    alias_t *alias;           /**< Linked list of aliases */
    var_t *shell_vars;        /**< Shell internal variables (e.g., custom vars) */
    int fd_out;               /**< File descriptor for stdout redirection */
    int fd_in;                /**< File descriptor for stdin redirection */
    int exit;                 /**< Exit flag or status code */
} args_t;

/**
 * @struct functions_s
 * @brief Maps built-in function names to their implementation.
 *
 * Used to dispatch shell built-ins via function pointers.
 */
typedef struct functions_s {
    int (*exec)(args_t *);    /**< Function pointer to command implementation */
    char *function_name;      /**< Name of the built-in command */
} functions_t;

/**
 * @struct data_s
 * @brief Global shell execution context.
 *
 * Combines args and functions with state flags like status and checks.
 */
typedef struct data_s {
    args_t *args;             /**< Pointer to current shell args context */
    functions_t **functions;  /**< Array of built-in function mappings */
    int check;                /**< Status flag for command chaining or flow control */
    int p_status;             /**< Last process exit status */
} data_t;
#endif
