/*
** EPITECH PROJECT, 2024
** Salah-Eddine Ghellab
** File description:
** set_struct.h
*/

#ifndef SET_STRUCT_H
    #define SET_STRUCT_H
    #include <stddef.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

/**
 * @struct var_s
 * @brief Represents a single shell variable (name-value pair).
 *
 * This structure stores a variable name and its associated value.
 * The list is singly linked to allow efficient insertion and traversal.
 */
typedef struct var_s {
    char *name;           /**< Name of the variable */
    char *value;          /**< Value associated with the variable */
    struct var_s *next;   /**< Pointer to the next variable in the list */
} var_t;

#endif
