/*
** EPITECH PROJECT, 2024
** Edgar Duquesne
** File description:
** inhibitor_protos.h
*/

#ifndef WHICH_PROTOS
    #define WHICH_PROTOS
    #include "struct.h"
typedef struct which_s {
    int flag_a;
    char **directories;
    int valid_count;
    int saved_result;
} which_t;
int init_which(args_t *args, which_t *which);
int my_which(args_t *args);
#endif
