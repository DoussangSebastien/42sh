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
/**
 * @brief Frees the list of shell variables.
 * 
 * Iterates through the linked list and frees all the memory associated with the variables.
 * 
 * @param head Pointer to the first variable in the list.
 */
void free_vars(var_t *head);

/**
 * @brief Implements the `set` built-in command.
 * 
 * Sets or prints environment variables or shell variables.
 * 
 * @param args Argument context for the command.
 * @return 0 on success, -1 on error.
 */
int my_set(args_t *args);

/**
 * @brief Implements the `unset` built-in command.
 * 
 * Unsets a specified environment or shell variable.
 * 
 * @param args Argument context for the command.
 * @return 0 on success, -1 on error.
 */
int my_unset(args_t *args);

/**
 * @brief Parses a command line into individual arguments.
 * 
 * Splits a command line string into its components, handling quotes and special characters.
 * 
 * @param line The input command line string.
 * @param data Pointer to shell data context.
 * @return An array of argument strings.
 */
char **line_parser(char *line, data_t *data);

/**
 * @brief Checks if a character is excluded from processing.
 * 
 * @param c Character to check.
 * @param n String of excluded characters.
 * @return 1 if the character is excluded, 0 otherwise.
 */
int excluded(char c, char const *n);

/**
 * @brief Counts the number of words in a string.
 * 
 * @param str The input string.
 * @return The number of words in the string.
 */
int count_words(char *str);

/**
 * @brief Creates a new node for a syntax tree.
 * 
 * @param type Type of the node (e.g., command, redirection).
 * @param fname Name of the file (if any) associated with the node.
 * @param command List of command arguments for the node.
 * @return Pointer to the newly created tree node.
 */
tree_t *create_node(int type, char *fname, char **command);

/**
 * @brief Determines the type of an argument (e.g., argument, operator).
 * 
 * @param argument The argument string.
 * @return The argument type as an integer.
 */
int get_arg_type(char const *argument);

/**
 * @brief Splits a command line into parts based on redirection symbols.
 * 
 * @param command_line The command line to split.
 * @param start Start index of the line.
 * @param end End index of the line.
 * @return A tree node representing the command and its redirections.
 */
tree_t *split_redir(char **command_line, int start, int end);

/**
 * @brief Loads a command into a syntax tree.
 * 
 * @param command Command arguments to be added to the tree.
 * @param start Start index of the command.
 * @param end End index of the command.
 * @return Pointer to the tree node representing the command.
 */
tree_t *load_command(char **command, int start, int end);

/**
 * @brief Generates a syntax tree from a line of input.
 * 
 * Parses the input and creates a tree structure representing the syntax.
 * 
 * @param line The input command line.
 * @param data Pointer to shell data context.
 * @return Pointer to the root of the syntax tree.
 */
tree_t *generate_tree(char *line, data_t *data);

/**
 * @brief Executes commands in the syntax tree.
 * 
 * Traverses the tree and executes each command based on its node type.
 * 
 * @param root Root node of the syntax tree.
 * @param data Pointer to shell data context.
 * @return Execution result (0 for success, non-zero for error).
 */
int execute_tree(tree_t *root, data_t *data);

/**
 * @brief Executes a single command.
 * 
 * Executes a command in a child process, waiting for it to complete.
 * 
 * @param pid Process ID of the command to execute.
 * @param args Argument context for the command.
 * @param path Path to the command binary.
 * @param data Pointer to shell data context.
 * @return Execution result (0 for success, non-zero for error).
 */
int exec_command(pid_t pid, args_t *args, char *path, data_t *data);

/**
 * @brief Handles input/output redirection for commands.
 * 
 * Sets up file descriptors for redirection operations.
 * 
 * @param tree The tree node representing the command.
 * @param data Pointer to shell data context.
 * @return 0 on success, non-zero on failure.
 */
int handle_redirect(tree_t *tree, data_t *data);

/**
 * @brief Frees a syntax tree structure.
 * 
 * Recursively frees all nodes of the tree.
 * 
 * @param tree Root of the tree to free.
 */
void free_tree(tree_t *tree);

/**
 * @brief Parses and displays errors related to binary execution.
 * 
 * Provides error messages when binary commands fail to execute.
 * 
 * @param tree The tree node where the error occurred.
 * @return 0 on success, non-zero on failure.
 */
int binary_error_parser(tree_t *tree);

/**
 * @brief Displays an error message.
 * 
 * Prints an error message to the standard error.
 * 
 * @param error_message The error message to display.
 * @return Always returns 0.
 */
int display_error(char const *error_message);

/**
 * @brief Checks the right side of a redirection for validity.
 * 
 * Validates the syntax and conditions for right redirection.
 * 
 * @param tree The tree node representing the redirection.
 * @return 1 if valid, 0 otherwise.
 */
int check_right_redir(tree_t *tree);

/**
 * @brief Checks the left side of a redirection for validity.
 * 
 * Validates the syntax and conditions for left redirection.
 * 
 * @param tree The tree node representing the redirection.
 * @return 1 if valid, 0 otherwise.
 */
int check_left_redir(tree_t *tree);

/**
 * @brief Checks if a pipe exists in the command line.
 * 
 * Validates the use of pipes in the command.
 * 
 * @param tree The tree node representing the command.
 * @return 1 if pipe is present, 0 otherwise.
 */
int check_pipe(tree_t *tree);

/**
 * @brief Validates linear arguments in a command.
 * 
 * Ensures that arguments are in a valid format and syntax.
 * 
 * @param command The command arguments.
 * @return 1 if valid, 0 otherwise.
 */
int check_linear_args(char **command);

/**
 * @brief Compares aliases in the shell's context.
 * 
 * Resolves and compares alias definitions.
 * 
 * @param data Pointer to shell data context.
 * @return 1 if an alias is found, 0 otherwise.
 */
int compare_aliases(data_t *data);

/**
 * @brief Checks for matching parentheses in the command.
 * 
 * Ensures proper syntax of parentheses for subshells.
 * 
 * @param cmd_line The command line to check.
 * @return 1 if parentheses are valid, 0 otherwise.
 */
int check_parenthesis(char **cmd_line);

/**
 * @brief Executes a command within a pipe.
 * 
 * Handles the creation and execution of processes within a pipe.
 * 
 * @param tree The tree node representing the command to execute.
 * @param data Pointer to shell data context.
 */
void execute_pipe(tree_t *tree, data_t *data);

/**
 * @brief Splits a command line into parts at pipe symbols.
 * 
 * Divides the command line at pipe symbols (`|`), creating subcommands.
 * 
 * @param command_line The command line to split.
 * @param start Starting index of the command line.
 * @param end Ending index of the command line.
 * @return Pointer to the root of the new syntax tree.
 */
tree_t *split_pipe(char **command_line, int start, int end);

/**
 * @brief Splits a command line into parts at semicolons.
 * 
 * Divides the command line at semicolons (`;`), creating subcommands.
 * 
 * @param command_line The command line to split.
 * @param start Starting index of the command line.
 * @param end Ending index of the command line.
 * @return Pointer to the root of the new syntax tree.
 */
tree_t *split_semicolon(char **command_line, int start, int end);

/**
 * @brief Splits a command line into parts at open parentheses.
 * 
 * Divides the command line at open parentheses (`(`), creating subcommands.
 * 
 * @param command_line The command line to split.
 * @param start Starting index of the command line.
 * @param end Ending index of the command line.
 * @return Pointer to the root of the new syntax tree.
 */
tree_t *split_open_p(char **command_line, int start, int end);

/**
 * @brief Executes a command in a subshell.
 * 
 * Creates a child process to execute a command in a subshell.
 * 
 * @param root Root of the tree node representing the command.
 * @param data Pointer to shell data context.
 * @return Execution result (0 for success, non-zero for error).
 */
int execute_subshell(tree_t *root, data_t *data);

/**
 * @brief Prints the structure of a syntax tree.
 * 
 * Displays the tree structure of parsed commands for debugging purposes.
 * 
 * @param root Root node of the syntax tree.
 */
void print_tree(tree_t *root);

/**
 * @brief Interprets and executes the parsed command.
 * 
 * Executes the necessary action based on the command parsed in the tree.
 * 
 * @param data Pointer to shell data context.
 */
void interpret_command(data_t *data);

/**
 * @brief Displays the shell prompt.
 * 
 * Displays a prompt and waits for user input.
 */
void prompt(void);

/**
 * @brief Builds a command from an argument.
 * 
 * Combines an argument into a valid command for execution.
 * 
 * @param argument The argument to build.
 * @param data Pointer to shell data context.
 * @return A newly constructed command string.
 */
char *build_command(char *argument, data_t *data);
#endif
