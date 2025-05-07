/*
** EPITECH PROJECT, 2025
** shrimp_command
** File description:
** draw a colorful rainbow shrimp
*/

#include "ansi_colors.h"
#include "shell_protos.h"
#include <fcntl.h>

#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define PURPLE "\033[35m"

static int shrimp_command_part4(args_t *args)
{
    printf(ANSI_BLUE "                          ....................\n" ANSI_RESET);
    printf(ANSI_PURPLE "                              ..........\n" ANSI_RESET);
    return SUCCESS;
}

int shrimp_command_part3(args_t *args)
{
    printf(ANSI_RED " .............  ....    ...\n" ANSI_RESET);
    printf(ANSI_ORANGE "  ............   ....    ..\n" ANSI_RESET);
    printf(ANSI_YELLOW "    ..........     ...\n" ANSI_RESET);
    printf(ANSI_GREEN "                    ...\n" ANSI_RESET);
    printf(ANSI_BLUE "  ..                 .\n" ANSI_RESET);
    printf(ANSI_PURPLE "  ......   ...\n" ANSI_RESET);
    printf(ANSI_PINK "   ............\n" ANSI_RESET);
    printf(ANSI_RED "    ...........\n" ANSI_RESET);
    printf(ANSI_ORANGE "    ............\n" ANSI_RESET);
    printf(ANSI_YELLOW "      ...........\n" ANSI_RESET);
    printf(ANSI_GREEN "       ..........\n" ANSI_RESET);
    printf(ANSI_BLUE "        .........\n" ANSI_RESET);
    printf(ANSI_PURPLE "          ......   ..                   .......\n" ANSI_RESET);
    printf(ANSI_PINK "           ....   ....             ............\n" ANSI_RESET);
    printf(ANSI_RED "                 ........              ........\n" ANSI_RESET);
    printf(ANSI_ORANGE "                 .........\n" ANSI_RESET);
    printf(ANSI_YELLOW "                   ......     .......\n" ANSI_RESET);
    printf(ANSI_GREEN "                       .   ................\n" ANSI_RESET);
    return shrimp_command_part4(args);
}

int shrimp_command_part2(args_t *args)
{
    printf(ANSI_RED "    ...........   ...................\n" ANSI_RESET);
    printf(ANSI_RED "   .............   ................\n" ANSI_RESET);
    printf(ANSI_ORANGE "   ..............   .............\n" ANSI_RESET);
    printf(ANSI_ORANGE "   ...............  ..........\n" ANSI_RESET);
    printf(ANSI_ORANGE "   ................  .......\n" ANSI_RESET);
    printf(ANSI_YELLOW "   ................   ...\n" ANSI_RESET);
    printf(ANSI_YELLOW "    ................\n" ANSI_RESET);
    printf(ANSI_YELLOW "  .  ................\n" ANSI_RESET);
    printf(ANSI_GREEN " .   ..............\n" ANSI_RESET);
    printf(ANSI_GREEN " ..    ...........   ..\n" ANSI_RESET);
    printf(ANSI_GREEN "....    ..........  ....\n" ANSI_RESET);
    printf(ANSI_BLUE "......    .......     ....\n" ANSI_RESET);
    printf(ANSI_BLUE ".......     ....       ....\n" ANSI_RESET);
    printf(ANSI_BLUE ".........     .   ..     ...\n" ANSI_RESET);
    printf(ANSI_PURPLE "...........       ...     ...\n" ANSI_RESET);
    printf(ANSI_PURPLE ".............      ....    ...\n" ANSI_RESET);
    printf(ANSI_PINK "..............       ...    ...\n" ANSI_RESET);
    printf(ANSI_PINK "..............   .     ..    ..\n" ANSI_RESET);
    return shrimp_command_part3(args);
}

int shrimp_command(args_t *args)
{
    printf(ANSI_PINK "                                     ....\n" ANSI_RESET);
    printf(ANSI_PINK "       ..                      ............\n" ANSI_RESET);
    printf(ANSI_PINK "       ....               ..................\n" ANSI_RESET);
    printf(ANSI_PINK "        ........  ..............          ..\n" ANSI_RESET);
    printf(ANSI_PINK "          .................\n" ANSI_RESET);
    printf(ANSI_PINK "    ....    .............\n" ANSI_RESET);
    printf(ANSI_RED "     .................          ...........\n" ANSI_RESET);
    printf(ANSI_RED "          ......      .   ...............      ..\n" ANSI_RESET);
    printf(ANSI_RED "                       ................   ......\n" ANSI_RESET);
    printf(ANSI_ORANGE "                       ......................\n" ANSI_RESET);
    printf(ANSI_ORANGE "                .       ....................\n" ANSI_RESET);
    printf(ANSI_ORANGE "              ....  ..   .................\n" ANSI_RESET);
    printf(ANSI_ORANGE "            .....  ....  ..............\n" ANSI_RESET);
    printf(ANSI_ORANGE "            .....  ....  ............    ..\n" ANSI_RESET);
    printf(ANSI_YELLOW "      ...    .....  ..   .................\n" ANSI_RESET);
    printf(ANSI_YELLOW "      .....    ...      .................\n" ANSI_RESET);
    printf(ANSI_YELLOW "     .......    ....   ................\n" ANSI_RESET);
    printf(ANSI_YELLOW "    ..........   .....................\n" ANSI_RESET);
    return shrimp_command_part2(args);
}
