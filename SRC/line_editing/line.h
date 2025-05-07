/*
** EPITECH PROJECT, 2025
** line.h
** File description:
** Epitech line.h
*/

#ifndef LINE_h
    #define LINE_h
    #define DEFAULT_SIZE 1
    #define UP 'A'
    #define DOWN 'B'
    #define RIGHT 'C'
    #define LEFT 'D'
    #define CTRL_A 0x01
    #define CTRL_K 0x0B
    #define CTRL_H 0x08
    #define BACKSPACE 127
    #define TAB '\t'
    #define ARROW 27
    #define NEWLINE '\n'
    #include "../../include/macros.h"
    #include "../../include/shell_protos.h"
    #include <stdio.h>

typedef struct {
    size_t len;
    size_t size;
    char *line;
} line_t;

typedef struct {
    line_t *line;
    char c;
    int pos;
    int history_index;
    char last_c;
    int auto_complete;
    char **builtins;
} action_t;

typedef struct {
    char key;
    int (*func)(action_t *action);
} keyboard_t;

typedef struct match_list_s {
    char **match;
    int count;
} match_list_t;

int handle_line(char **line, data_t *data);
line_t *init_line(void);
void free_line(line_t *line);
action_t *init_action(data_t *data);
void free_action(action_t *action);
char *get_n_cmd(int nb);

int handle_keyboard(action_t *action);

int insert_char(action_t *action);
int remove_char(action_t *action);

int right(int *pos);
int left(int *pos);

int newline(action_t *action);
int start_of_header(action_t *action);
int cut_end(action_t *action);
int backspace(action_t *action);
int arrows(action_t *action);
int printable_char(action_t *action);

int autocomplete(action_t *action);
int strncmp_case_i(char *s1, char *s2, int n);
char *get_word(action_t *action);
void get_dir(action_t *action, char **dir, char *word);
void free_match_list(match_list_t *list);
match_list_t *find_matches(char *word, char *dir_str, action_t *action);
void single_match(action_t *action, char *word, char *match, char *dir);
void multiple_matches(action_t *action, match_list_t *matches,
    char *dir, char *word);

FILE *get_history_path(int read, int write);

#endif /* LINE_h */
