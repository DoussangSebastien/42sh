/*
** EPITECH PROJECT, 2024
** Edgar Duquesne
** File description:
** inhibitor_protos.h
*/

#ifndef GLOB_PROTOS
    #define GLOB_PROTOS
    #include "struct.h"
/**
 * @format globs.
 * @param pattern Input glob
 * @return a usable glog pattern for libs.
 */
char *tokenize_glob(const char *pattern);
/**
 * @create the glob.
 * @param input_glob Formatted pattern writen by USER
 * @return all matches based on the input glob.
 */
char *produce_glob(const char *input_glob);
#endif
