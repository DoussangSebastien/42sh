/*
** EPITECH PROJECT, 2024
** Edgar Duquesne
** File description:
** shel_protos.h
*/

#ifndef LIB
    #define LIB
/**
 * @display of str.
 * @param str String to write
 * @return if the str was succesfully writen
 */
int my_putstr(char const *str);
/**
 * @lenght of str.
 * @param str String to count
 * @return the number of char in str.
 */
int my_strlen(char const *str);
/**
 * @look for pattern in str.
 * @param str String where we look for pattern
 * @param to_find String we are looking for in pattern
 * @return str from the begining of to_find.
 */
char *my_strstr(char *str, char const *to_find);
/**
 * @display of int.
 * @param num Int to write
 * @param port Output where num is displayed
 * @return if the int was succesfully writen.
 */
int my_put_nbr(int num, int port);
/**
 * @duplicate str.
 * @param str String to duplicate
 * @return the duplicate if it exist else NULL.
 */
char *my_strdup(char *str);
/**
 * @duplicate of str array.
 * @param tab String array to duplicate
 * @return the duplicate if it exist else NULL.
 */
char **my_duptab(char **tab);
/**
 * @get int from str.
 * @param str String where int is extracted from
 * @return int extracted from str.
 */
int my_getnbr(char const *str);
/**
 * @create word array from str.
 * @param str String where words will be extracted from
 * @param spec Separator between words
 * @return the word array if it exist else NULL.
 */
char **my_str_to_word_array_n(char const *str, char const *spec);
/**
 * @concatenate two str.
 * @param dest First part of new word
 * @param src Second part of new word
 * @return concatenation of dest and src if it exist else NULL.
 */
char *my_strcat(char *dest, char const *src);
/**
 * @free String array.
 * @param tab String array to free
 * @return nothing
 */
void my_free_word_array(char **tab);
/**
 * @check for letter.
 * @param c Char to check
 * @return 1/0 if it's a letter or not.
 */
int is_alpha(char c);
/**
 * @compare two str.
 * @param str_1 First string
 * @param str_2 Second string
 * @return the number of differences between the two str
 */
int my_strcmp(char const *str_1, char const *str_2);
/**
 * @concatenate two str.
 * @param dest First part of new word
 * @param src Second part of new word
 * @return concatenation of dest and src if it exist else NULL.
 */
char *add_str(char *input_2, char *input);
/**
 * @check for letter and number.
 * @param str String to check
 * @return 1/0 if str only countain letters and numbers.
 */
int is_alphanumeric(const char *str);
#endif
