/*
** EPITECH PROJECT, 2025
** test
** File description:
** handle_keyboard.c
*/

#include "../line.h"
#include <termios.h>
#include <unistd.h>
#include <stdbool.h>

int handle_keyboard(action_t *action)
{
    keyboard_t keyboard[] = {
        {NEWLINE, newline}, {CTRL_A, start_of_header},
        {CTRL_K, cut_end}, {BACKSPACE, backspace},
        {CTRL_H, backspace}, {ARROW, arrows},
        {TAB, autocomplete}, {0, NULL}
    };

    if (!action || !action->line)
        return FAILURE;
    for (int i = 0; keyboard[i].func != NULL; i++) {
        if (action->c == keyboard[i].key)
            return keyboard[i].func(action);
    }
    return printable_char(action);
}
