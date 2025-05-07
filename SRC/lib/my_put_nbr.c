/*
** EPITECH PROJECT, 2024
** my_putnbr
** File description:
** my_putnbr
*/

#include <unistd.h>

static int my_putchar(char c, int port)
{
    if (write(1, &c, 1))
        return 1;
    return 0;
}

static int power(int num, int power)
{
    for (int i = 0; i < power; i++) {
        if (num >= 0) {
            num *= 10;
            continue;
        }
        return -1;
    }
    return num;
}

static int get_result(int num, int pow, int port, int divider)
{
    int new_number = num;
    int return_val = 0;

    for (int i = 0; i <= pow; i++) {
        new_number /= divider;
        if (i > 0)
            new_number %= 10;
        divider /= 10;
        return_val += my_putchar(new_number + '0', port);
        new_number = num;
    }
    return return_val;
}

int get_power(int num)
{
    int power = 0;

    while (num >= 10) {
        num /= 10;
        power += 1;
    }
    return power;
}

int my_put_nbr(int num, int port)
{
    int new_number = 0;
    int pow = 0;
    int divider = 1;

    if (num < 0) {
        my_putchar('-', 2);
        num = num * (-1);
    }
    new_number = num;
    if (num < 10) {
        my_putchar(num + '0', 2);
        return 1;
    }
    pow = get_power(new_number);
    divider = power(divider, pow);
    if (divider < 0)
        return -1;
    return get_result(num, pow, port, divider);
}
