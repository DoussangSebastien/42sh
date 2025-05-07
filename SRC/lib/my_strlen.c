/*
** EPITECH PROJECT, 2024
** my_strlen
** File description:
** my_strlen.c
*/

int my_strlen(char const *str)
{
    int i = 0;

    if (!str)
        return 0;
    while (str[i]) {
        i++;
    }
    return i;
}
