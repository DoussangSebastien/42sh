/*
** EPITECH PROJECT, 2024
** Edgar Duquesne
** File description:
** shel_protos.h
*/

#ifndef PARSER
    #define PARSER
/**
 * @enum arg_type
 * @brief Enumeration of token types used in command parsing.
 *
 * Represents different kinds of shell syntax elements, such as redirections,
 * pipes, logical operators, and parentheses.
 */
enum arg_type {
    PIPE,       /**< Single pipe '|' */
    PIPE2,      /**< Double pipe '||' */
    REDIR_R,    /**< Output redirection '>' */
    REDIR_RR,   /**< Output append redirection '>>' */
    REDIR_L,    /**< Input redirection '<' */
    REDIR_LL,   /**< Here-document input '<<' */
    SEMI_COLON, /**< Command separator ';' */
    OPEN_P,     /**< Open parenthesis '(' */
    CLOSE_P,    /**< Close parenthesis ')' */
    AND,        /**< Logical AND '&' */
    AND2,       /**< Logical double AND '&&' */
    ARG,        /**< Regular argument or command word */
    SUBSHELL,   /**< Subshell command block */
    INVALID     /**< Invalid or unrecognized token */
};

/**
 * @struct tree_s
 * @brief A binary tree node representing part of a parsed command line.
 *
 * Each node can represent a command, operator, or grouping.
 * Nodes may contain child nodes representing sub-commands or operands.
 */
typedef struct tree_s {
    char **command;              /**< Command and its arguments */
    char *file_name;             /**< Associated file for redirections (if any) */
    enum arg_type argument_type; /**< Type of argument or operator */
    struct tree_s *left;         /**< Left child node */
    struct tree_s *right;        /**< Right child node */
} tree_t;
#endif
