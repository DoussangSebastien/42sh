/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** read_captured_output.c
*/

#include "shell_protos.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

static int check_bytes(char *buffer, ssize_t bytes_read,
    int pipefd, size_t *total_bytes)
{
    if (bytes_read < 0) {
        free(buffer);
        close(pipefd);
        return -1;
    }
    if (bytes_read == 0) {
        return 0;
    }
    *total_bytes += bytes_read;
    return 1;
}

static int load_buffer(char **buffer, int pipefd,
    size_t *total_bytes, size_t *buf_size)
{
    ssize_t bytes_read;
    char *new_buf = NULL;

    if (*total_bytes >= *buf_size - 1) {
        *buf_size *= 2;
        new_buf = realloc(*buffer, *buf_size);
        if (!new_buf) {
            free(*buffer);
            close(pipefd);
            return -1;
        }
        (*buffer) = new_buf;
    }
    bytes_read = read(pipefd, (*buffer) + *total_bytes,
                        *buf_size - *total_bytes - 1);
    while (bytes_read == -1 && errno == EINTR)
        bytes_read = read(pipefd, (*buffer) + *total_bytes,
                            *buf_size - *total_bytes - 1);
    return check_bytes(*buffer, bytes_read, pipefd, total_bytes);
}

char *sanitize_string(char *result)
{
    for (int i = 0; result[i]; i++) {
        if (result[i] < ' ')
            result[i] = ' ';
    }
    return result;
}

char *read_captured_output(int pipefd)
{
    size_t buf_size = 4096;
    size_t total_bytes = 0;
    char *buffer = malloc(sizeof(char) * buf_size);
    int ret = 0;

    if (!buffer) {
        close(pipefd);
        return NULL;
    }
    while (1) {
        ret = load_buffer(&buffer, pipefd, &total_bytes, &buf_size);
        if (ret <= 0)
            break;
        if (ret == -1)
            return NULL;
    }
    close(pipefd);
    buffer[total_bytes] = '\0';
    return sanitize_string(buffer);
}
