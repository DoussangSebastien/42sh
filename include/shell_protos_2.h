/*
** EPITECH PROJECT, 2024
** Edgar Duquesne
** File description:
** shel_protos.h
*/

#ifndef PROTOS_2
    #define PROTOS_2
    #include "struct.h"
    #include "set_protos.h"
    #include <stdlib.h>
void free_vars(var_t *head);
int my_set(args_t *args);
int my_unset(args_t *args);
char **line_parser(char *line, data_t *data);
int excluded(char c, char const *n);
int count_words(char *str);
tree_t *create_node(int type, char *fname, char **command);
int get_arg_type(char const *argument);
tree_t *split_redir(char **command_line, int start, int end);
tree_t *load_command(char **command, int start, int end);
tree_t *generate_tree(char *line, data_t *data);
int execute_tree(tree_t *root, data_t *data);
int exec_command(pid_t pid, args_t *args, char *path, data_t *data);
int handle_redirect(tree_t *tree, data_t *data);
void free_tree(tree_t *tree);
int binary_error_parser(tree_t *tree);
int display_error(char const *error_message);
int check_right_redir(tree_t *tree);
int check_left_redir(tree_t *tree);
int check_pipe(tree_t *tree);
int check_linear_args(char **command);
int compare_aliases(data_t *data);
int check_parenthesis(char **cmd_line);
void execute_pipe(tree_t *tree, data_t *data);
tree_t *split_pipe(char **command_line, int start, int end);
tree_t *split_semicolon(char **command_line, int start, int end);
tree_t *split_open_p(char **command_line, int start, int end);
int execute_subshell(tree_t *root, data_t *data);
void print_tree(tree_t *root);
void interpret_command(data_t *data);
void prompt(void);
char *build_command(char *argument, data_t *data);
#endif
