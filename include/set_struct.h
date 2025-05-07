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

typedef struct var_s {
    char *name;
    char *value;
    struct var_s *next;
} var_t;

#endif
