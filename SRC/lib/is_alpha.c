/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** is_alpha.c
*/

int is_alpha(char c)
{
    if ((c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        (c == '_'))
        return 1;
    return 0;
}
