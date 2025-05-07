/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** display_cd_error.c
*/

#include "shell_protos.h"

int display_cd_error(char *new_dir)
{
    if (!new_dir)
        return 1;
    if (!access(new_dir, F_OK) && access(new_dir, R_OK) == -1) {
        write(2, new_dir, my_strlen(new_dir));
        write(2, ": Permission denied.\n", 21);
        return 1;
    }
    if (!access(new_dir, F_OK)) {
        write(2, new_dir, my_strlen(new_dir));
        write(2, ": Not a directory.\n", 19);
        return 1;
    }
    write(2, new_dir, my_strlen(new_dir));
    write(2, ": No such file or directory.\n", 29);
    return 1;
}
