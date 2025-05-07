/*
** EPITECH PROJECT, 2024
** my_getnbr
** File description:
** my_getnbr
*/
#include <stdlib.h>

static int checking_number(int c)
{
    for (int i = 0; i < 10; i++) {
        if (c == i) {
            return i;
        }
    }
    return -1;
}

static int is_it_negative(char const *str, int result, int index)
{
    if (str == NULL)
        return 0;
    if (result != -1 && (str[index]) == '-') {
        return 1;
    }
    return 0;
}

static int increment_number(int number, int result)
{
    result *= 10;
    result += number;
    return result;
}

int my_getnbr(char const *str)
{
    int i = 0;
    int number = 0;
    int result = 0;
    int is_negative = 0;

    while (str[i]) {
        number = checking_number(str[i] - '0');
        if (number != -1)
            result = increment_number(number, result);
        if (number == -1 && result > 0)
            break;
        if (!is_negative)
            is_negative = is_it_negative(str, result, i);
        i++;
    }
    if (is_negative)
        return result * -1;
    return result;
}
