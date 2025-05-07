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
void free_vars(var_t *head);
void update_last_cmd(args_t *args, const char *cmd);
var_t *add_var(var_t *head, const char *name, const char *value);
int handle_set_assignment(args_t *args, const char *input);
int handle_set_no_value(args_t *args, const char *name);
int handle_set_print(args_t *args);
void process_set_argument(args_t *args, const char *arg);
void init_local_vars_from_tcsh(args_t *args);
void print_vars(var_t *head);
var_t *create_new_var(const char *name, const char *value);
void read_and_store_vars(FILE *fp, args_t *args);
var_t *sort_vars(var_t *head);
var_t *clone_vars(var_t *head);
int parse_assignment(const char *input, char **name, char **value);
int is_valid_identifier(const char *str);
char *trim_spaces(char *str);
var_t *update_existing_var(var_t *head, var_t *target, const char *value);
var_t *add_or_update_var(var_t *head, const char *name, const char *value);
void init_minimal_vars(args_t *args);
#endif
