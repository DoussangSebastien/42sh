/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** main.c
*/

#include "shell_protos.h"
#include <unistd.h>
#include <glob.h>
#include <stdio.h>

static int display_help(void)
{
    printf("42sh:\n");
    printf(" Run the binary with ./42sh and use it like a real terminal.\n");
    printf(" You can also test it using the echo command:\n");
    printf("    - echo \"ls | grep a\" | ./42sh\n");
    return SUCCESS;
}

int main(int const argc, char const *argv[], char const *envp[])
{
    if (argc == 2) {
        if (!strcmp(argv[1], "-h")) {
            return display_help();
        } else {
            fprintf(stderr, "Too many arguments.\n");
            return FAILURE;
        }
    }
    return shell(envp);
}
