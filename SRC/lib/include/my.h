/*
** EPITECH PROJECT, 2024
** Edgar Duquesne
** File description:
** shel_protos.h
*/

#ifndef LIB
    #define LIB
int my_putstr(char const *str);
int my_strlen(char const *str);
char *my_strstr(char *str, char const *to_find);
int my_put_nbr(int num, int port);
char *my_strdup(char *str);
char **my_duptab(char **tab);
int my_getnbr(char const *str);
char **my_str_to_word_array_n(char const *str, char const *spec);
char *my_strcat(char *dest, char const *src);
void my_free_word_array(char **tab);
int is_alpha(char c);
int my_strcmp(char const *str_1, char const *str_2);
char *add_str(char *input_2, char *input);
int is_alphanumeric(const char *str);
#endif
