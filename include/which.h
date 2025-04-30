/*
** EPITECH PROJECT, 2024
** Edgar Duquesne
** File description:
** inhibitor_protos.h
*/

#ifndef WHICH_PROTOS
    #define WHICH_PROTOS
    #include "struct.h"
/**
 * @struct which_s
 * @brief Structure for tracking `which` command state and search results.
 *
 * Used to store options, directories searched, and results of path resolution.
 */
typedef struct which_s {
    int flag_a;            /**< If set, show all matching paths (`-a` flag) */
    char **directories;    /**< List of directories to search in PATH */
    int valid_count;       /**< Number of valid paths found */
    int saved_result;      /**< Return status code (0 = found, 1 = not found) */
} which_t;

/**
 * @brief Initializes a `which_t` structure from parsed arguments.
 *
 * Parses environment and flags, prepares directory list for search.
 *
 * @param args Pointer to current argument context.
 * @param which Pointer to the `which_t` structure to initialize.
 * @return 0 on success, non-zero on error.
 */
int init_which(args_t *args, which_t *which);

/**
 * @brief Main function for executing the `which` command logic.
 *
 * Uses parsed args to determine executable locations.
 *
 * @param args Pointer to the current shell argument context.
 * @return Exit status (0 = found, 1 = not found, other = error).
 */
int my_which(args_t *args);
#endif
