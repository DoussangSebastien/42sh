/*
** EPITECH PROJECT, 2024
** my_free_word_array
** File description:
** my_free_word_array
*/

#include <stdlib.h>

void my_free_word_array(char **str)
{
    for (int i = 0; str[i]; i++) {
        free(str[i]);
    }
    free(str);
}
