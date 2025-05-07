/*
** EPITECH PROJECT, 2024
** salah-eddine
** File description:
** utils.c
*/

#include <unistd.h>
#include <string.h>
#include "ansi_colors.h"

void write_colored(int fd, const char *color, const char *text, int reset)
{
    write(fd, color, strlen(color));
    write(fd, text, strlen(text));
    if (reset)
        write(fd, ANSI_RESET, strlen(ANSI_RESET));
}
