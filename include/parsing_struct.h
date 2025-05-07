/*
** EPITECH PROJECT, 2024
** Edgar Duquesne
** File description:
** shel_protos.h
*/

#ifndef PARSER
    #define PARSER
enum arg_type {
    PIPE,
    PIPE2,
    REDIR_R,
    REDIR_RR,
    REDIR_L,
    REDIR_LL,
    SEMI_COLON,
    OPEN_P,
    CLOSE_P,
    AND,
    AND2,
    ARG,
    SUBSHELL,
    INVALID
};

typedef struct tree_s {
    char **command;
    char *file_name;
    enum arg_type argument_type;
    struct tree_s *left;
    struct tree_s *right;
} tree_t;
#endif
