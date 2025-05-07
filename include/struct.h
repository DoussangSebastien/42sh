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
typedef struct alias_s {
    char *command;
    char *name;
    struct alias_s *next;
} alias_t;
typedef struct environ_s {
    char *variable;
    struct environ_s *next;
} environ_t;
typedef struct args_s {
    char **tab;
    int interpreted;
    char *input;
    environ_t *environ;
    alias_t *alias;
    var_t *shell_vars;
    int fd_out;
    int fd_in;
    int exit;
} args_t;
typedef struct functions_s {
    int (*exec)(args_t *);
    char *function_name;
} functions_t;
typedef struct data_s {
    args_t *args;
    functions_t **functions;
    int check;
    int p_status;
} data_t;
#endif
