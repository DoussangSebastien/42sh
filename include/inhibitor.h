/*
** EPITECH PROJECT, 2024
** Edgar Duquesne
** File description:
** inhibitor_protos.h
*/

#ifndef INHIBITOR_PROTOS
    #define INHIBITOR_PROTOS
    #include "struct.h"

typedef struct quotes_s {
    int size;
    int index;
    char *new;
    char *arg;
} quote_t;

char *get_variable(args_t *args, char const *var_name);
char *dup_in_quotes(char *src, char delim);
char get_inhibitor(char c);
int check_inhibitor_error(char *line);
char *get_inhibitor_content(char *argument, data_t *data);
char *double_quote_case(char *argument, data_t *data);
char *back_tick_case(char *argument, data_t *data);
char *read_captured_output(int pipefd);
int is_inhibitor(char c);
#endif
