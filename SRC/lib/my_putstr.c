/*
** EPITECH PROJECT, 2024
** my_putstr
** File description:
** my_putstr.c
*/

#include <unistd.h>

static void my_putchar_2(char c)
{
    write(1, &c, 1);
}

int my_putstr(char const *str)
{
    int i = 0;

    if (!str)
        return 0;
    while (str[i]) {
        my_putchar_2(str[i]);
        i++;
    }
    return i;
}
