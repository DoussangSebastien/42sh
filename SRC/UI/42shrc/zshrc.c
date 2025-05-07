/*
** EPITECH PROJECT, 2024
** salah-eddine
** File description:
** 42shcr.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../../../bonus/ascii_art.h"
#include "shell_protos_2.h"

static int process_42shrc(char *line, data_t *data)
{
    tree_t *tree = generate_tree(line, data);
    int ret = 0;

    if (!tree)
        return -1;
    printf("\n");
    ret = execute_tree(tree, data);
    free_tree(tree);
    return ret;
}

void execute_42shrc(const char *filename, data_t *data)
{
    FILE *file = fopen(filename, "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if (!file)
        return;
    read = getline(&line, &len, file);
    while (read != -1) {
        if (read > 0 && line[read - 1] == '\n')
            line[read - 1] = '\0';
        if (line[0] == '#' || line[0] == '\0')
            continue;
        process_42shrc(line, data);
        read = getline(&line, &len, file);
    }
    free(line);
    fclose(file);
}

void print_colored_ascii_art(void)
{
    const char *colors[] = {
        "\033[31m", "\033[32m", "\033[33m",
        "\033[34m", "\033[35m", "\033[36m"
    };
    int color_count = 6;
    char *art = strdup(ASCII_ART);
    char *line = strtok(art, "\n");
    int i = 0;

    printf("\n");
    while (line) {
        printf("%s%s\033[0m\n", colors[i % color_count], line);
        line = strtok(NULL, "\n");
        i++;
    }
    free(art);
}
