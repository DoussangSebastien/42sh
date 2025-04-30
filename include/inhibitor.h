/*
** EPITECH PROJECT, 2024
** Edgar Duquesne
** File description:
** inhibitor_protos.h
*/

#ifndef INHIBITOR_PROTOS
    #define INHIBITOR_PROTOS
    #include "struct.h"

/**
 * @struct quotes_s
 * @brief Structure representing a quoted argument for processing.
 *
 * Contains information for managing the content and position of quotes
 * in an argument string during parsing.
 */
typedef struct quotes_s {
    int size;     /**< Size of the quoted string. */
    int index;    /**< Index of the start of the quoted string. */
    char *new;    /**< The new string after processing. */
    char *arg;    /**< The original argument containing quotes. */
} quote_t;

/**
 * @brief Retrieves the value of a shell variable.
 *
 * Searches for a variable by its name and returns its value.
 * 
 * @param args Argument context for the shell.
 * @param var_name Name of the variable to retrieve.
 * @return The value of the variable as a string, or NULL if not found.
 */
char *get_variable(args_t *args, char const *var_name);

/**
 * @brief Duplicates a string and removes a specific delimiter.
 *
 * Creates a copy of the input string while handling the removal of a given
 * delimiter (e.g., quote character) from the string.
 *
 * @param src The source string to duplicate.
 * @param delim The delimiter (e.g., quote character) to remove.
 * @return The duplicated string with the delimiter removed.
 */
char *dup_in_quotes(char *src, char delim);

/**
 * @brief Gets the inhibitor character for a given character.
 *
 * Checks if a character corresponds to a special inhibitor (e.g., backtick, 
 * quote) and returns the appropriate character or null if not an inhibitor.
 *
 * @param c The character to check.
 * @return The inhibitor character, or null if none exists.
 */
char get_inhibitor(char c);

/**
 * @brief Checks for errors in inhibitor handling within a string.
 *
 * Validates that a string containing special characters or inhibitors
 * (quotes, backticks, etc.) is correctly formed.
 *
 * @param line The line to check for errors.
 * @return 1 if there is an error, 0 otherwise.
 */
int check_inhibitor_error(char *line);

/**
 * @brief Retrieves the content within inhibitors in a string.
 *
 * Extracts the content from a string that is enclosed in quotes or backticks
 * for further processing.
 *
 * @param argument The argument string to extract content from.
 * @param data Shell data context for additional processing.
 * @return The extracted content within the inhibitors (quotes, backticks).
 */
char *get_inhibitor_content(char *argument, data_t *data);

/**
 * @brief Handles the case of double quotes within an argument.
 *
 * Processes and extracts content from arguments enclosed in double quotes.
 *
 * @param argument The argument string enclosed in double quotes.
 * @param data Shell data context for additional processing.
 * @return The processed argument string with the quotes handled.
 */
char *double_quote_case(char *argument, data_t *data);

/**
 * @brief Handles the case of backticks within an argument.
 *
 * Processes and extracts content from arguments enclosed in backticks for
 * command substitution.
 *
 * @param argument The argument string enclosed in backticks.
 * @param data Shell data context for additional processing.
 * @return The processed argument string with the backticks handled.
 */
char *back_tick_case(char *argument, data_t *data);

/**
 * @brief Reads the output captured by a pipe.
 *
 * Reads and returns the captured output from a pipe, which may include
 * command substitution or background process output.
 *
 * @param pipefd The pipe file descriptor from which to read.
 * @return The captured output as a string.
 */
char *read_captured_output(int pipefd);

/**
 * @brief Checks if a character is an inhibitor.
 *
 * Determines if a given character is one of the special characters that act as
 * inhibitors (e.g., quotes, backticks).
 *
 * @param c The character to check.
 * @return 1 if the character is an inhibitor, 0 otherwise.
 */
int is_inhibitor(char c);
#endif
