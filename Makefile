##
## EPITECH PROJECT, 2022
## edgar
## File description:
## MAKEFILE
##

SRC		=	SRC/main.c \
			SRC/shell.c \
			SRC/create_path.c \
			SRC/create_env.c \
			SRC/Inits/init_function_list.c \
			SRC/Inits/init_data.c \
			SRC/Inits/init_environment.c \
			SRC/Inits/init_aliases.c \
			SRC/free_functions.c \
			SRC/execute_builtins.c \
			SRC/analyze_input.c \
			SRC/check_stdin.c \
			SRC/build_envp.c \
			SRC/executable_condition.c \
			SRC/UI/utils.c \
			SRC/UI/git_branch.c \
			SRC/UI/git_commits.c \
			SRC/UI/prompt.c \
			SRC/UI/42shrc/zshrc.c	\
			SRC/line_editing/free_line.c \
			SRC/line_editing/handle_line.c \
			SRC/line_editing/init_line.c \
			SRC/line_editing/init_action.c \
			SRC/line_editing/get_history_path.c \
			SRC/line_editing/keyboard/basic_char.c \
			SRC/line_editing/keyboard/ctrl.c \
			SRC/line_editing/keyboard/directions.c \
			SRC/line_editing/keyboard/handle_keyboard.c \
			SRC/line_editing/keyboard/insert_char.c \
			SRC/line_editing/keyboard/remove_char.c \
			SRC/line_editing/keyboard/get_n_cmd.c \
			SRC/line_editing/keyboard/arrows.c \
			SRC/line_editing/autocomplete/auto.c \
			SRC/line_editing/autocomplete/strncmp_case_i.c \
			SRC/line_editing/autocomplete/get_word.c \
			SRC/line_editing/autocomplete/get_dir.c \
			SRC/line_editing/autocomplete/find_matches.c \
			SRC/builtins/Where/where_function.c \
			SRC/line_editing/autocomplete/multiple_matches.c \
			SRC/builtins/Which/init_which.c \
			SRC/builtins/Which/which_function.c \
			SRC/builtins/Unalias/unalias_function.c \
			SRC/builtins/Unalias/del_alias.c \
			SRC/builtins/CD/cd_function.c \
			SRC/builtins/CD/old_pwd.c \
			SRC/builtins/CD/change_env_dir.c \
			SRC/builtins/CD/display_cd_error.c \
			SRC/builtins/Exit/exit_function.c \
			SRC/builtins/Alias/alias_function.c \
			SRC/builtins/Alias/compare_aliases.c \
			SRC/builtins/Setenv/setenv_function.c \
			SRC/builtins/Env/env_function.c \
			SRC/builtins/Unsetenv/unsetenv_function.c \
			SRC/builtins/history/history.c \
			SRC/builtins/rev_list.c \
			SRC/builtins/Set/open_and_store.c \
			SRC/builtins/Set/set_command.c \
			SRC/builtins/Set/set_handling.c \
			SRC/builtins/Set/set_parser.c \
			SRC/builtins/Set/set_variables.c \
			SRC/builtins/Set/free_vars.c \
			SRC/builtins/Unset/unset_command.c \
			SRC/Parser/line_parser.c \
			SRC/Parser/build_arg.c \
			SRC/Parser/interpret_command.c \
			SRC/Parser/count_word.c \
			SRC/Parser/get_arg_type.c \
			SRC/Parser/exec_tree.c \
			SRC/Parser/exec_command.c \
			SRC/Parser/execute_pipe.c \
			SRC/Parser/exec_subshell.c \
			SRC/Parser/handle_redirect.c \
			SRC/Parser/Tree/create_node.c \
			SRC/Parser/Tree/generate_tree.c \
			SRC/Parser/Tree/spliting.c \
			SRC/Parser/Tree/load_command.c \
			SRC/Parser/Tree/load_redirection.c \
			SRC/Parser/Tree/free_tree.c \
			SRC/Parser/Tree/print_tree.c \
			SRC/Parser/Tree/check_linear_args.c \
			SRC/Parser/Inhibitors/is_inhibitor.c \
			SRC/Parser/Inhibitors/get_variable.c \
			SRC/Parser/Inhibitors/get_inhibitor.c \
			SRC/Parser/Inhibitors/dup_in_quotes.c \
			SRC/Parser/Inhibitors/get_inhibitor_content.c \
			SRC/Parser/Inhibitors/back_tick_case.c \
			SRC/Parser/Inhibitors/double_quote_case.c \
			SRC/Parser/Inhibitors/read_captured_output.c \
			SRC/Parser/Globbings/tokenize_glob.c \
			SRC/Parser/Globbings/produce_glob.c \
			SRC/Parser/Line_Errors/check_inhibitor_error.c \
			SRC/Parser/Line_Errors/binary_error_parser.c \
			SRC/Parser/Line_Errors/display_error.c \
			SRC/Parser/Line_Errors/check_right_redir.c \
			SRC/Parser/Line_Errors/check_left_redir.c \
			SRC/Parser/Line_Errors/check_parenthesis.c \
			SRC/Parser/Line_Errors/check_pipe.c \
			bonus/shrimp_command.c

SRC_TEST =	SRC/create_path.c \
			SRC/Inits/init_function_list.c \
			SRC/Inits/init_data.c \
			SRC/Inits/init_environment.c \
			SRC/Inits/init_aliases.c \
			SRC/free_functions.c \
			SRC/execute_builtins.c \
			SRC/analyze_input.c \
			SRC/build_envp.c \
			SRC/executable_condition.c \
			SRC/UI/utils.c \
			SRC/UI/git_branch.c \
			SRC/UI/git_commits.c \
			SRC/UI/prompt.c \
			SRC/line_editing/free_line.c \
			SRC/line_editing/handle_line.c \
			SRC/line_editing/init_line.c \
			SRC/line_editing/init_action.c \
			SRC/line_editing/get_history_path.c \
			SRC/line_editing/keyboard/basic_char.c \
			SRC/line_editing/keyboard/ctrl.c \
			SRC/line_editing/keyboard/directions.c \
			SRC/line_editing/keyboard/handle_keyboard.c \
			SRC/line_editing/keyboard/insert_char.c \
			SRC/line_editing/keyboard/remove_char.c \
			SRC/line_editing/keyboard/get_n_cmd.c \
			SRC/line_editing/keyboard/arrows.c \
			SRC/line_editing/autocomplete/auto.c \
			SRC/line_editing/autocomplete/strncmp_case_i.c \
			SRC/line_editing/autocomplete/get_word.c \
			SRC/line_editing/autocomplete/get_dir.c \
			SRC/line_editing/autocomplete/find_matches.c \
			SRC/builtins/Where/where_function.c \
			SRC/builtins/Which/init_which.c \
			SRC/builtins/Which/which_function.c \
			SRC/builtins/Unalias/unalias_function.c \
			SRC/builtins/Unalias/del_alias.c \
			SRC/line_editing/autocomplete/multiple_matches.c \
			SRC/builtins/CD/cd_function.c \
			SRC/builtins/CD/old_pwd.c \
			SRC/builtins/CD/change_env_dir.c \
			SRC/builtins/CD/display_cd_error.c \
			SRC/builtins/Exit/exit_function.c \
			SRC/builtins/Alias/alias_function.c \
			SRC/builtins/Alias/compare_aliases.c \
			SRC/builtins/Setenv/setenv_function.c \
			SRC/builtins/Env/env_function.c \
			SRC/builtins/Unsetenv/unsetenv_function.c \
			SRC/builtins/history/history.c \
			SRC/builtins/rev_list.c \
			SRC/builtins/Set/open_and_store.c \
			SRC/builtins/Set/set_command.c \
			SRC/builtins/Set/set_handling.c \
			SRC/builtins/Set/set_parser.c \
			SRC/builtins/Set/set_variables.c \
			SRC/builtins/Set/free_vars.c \
			SRC/builtins/Unset/unset_command.c \
			SRC/Parser/line_parser.c \
			SRC/Parser/interpret_command.c \
			SRC/Parser/build_arg.c \
			SRC/Parser/count_word.c \
			SRC/Parser/get_arg_type.c \
			SRC/Parser/exec_tree.c \
			SRC/Parser/exec_command.c \
			SRC/Parser/execute_pipe.c \
			SRC/Parser/exec_subshell.c \
			SRC/Parser/handle_redirect.c \
			SRC/Parser/Tree/create_node.c \
			SRC/Parser/Tree/generate_tree.c \
			SRC/Parser/Tree/spliting.c \
			SRC/Parser/Tree/load_command.c \
			SRC/Parser/Tree/load_redirection.c \
			SRC/Parser/Tree/free_tree.c \
			SRC/Parser/Tree/print_tree.c \
			SRC/Parser/Tree/check_linear_args.c \
			SRC/Parser/Inhibitors/is_inhibitor.c \
			SRC/Parser/Inhibitors/get_variable.c \
			SRC/Parser/Inhibitors/get_inhibitor.c \
			SRC/Parser/Inhibitors/dup_in_quotes.c \
			SRC/Parser/Inhibitors/get_inhibitor_content.c \
			SRC/Parser/Inhibitors/back_tick_case.c \
			SRC/Parser/Inhibitors/double_quote_case.c \
			SRC/Parser/Inhibitors/read_captured_output.c \
			SRC/Parser/Globbings/tokenize_glob.c \
			SRC/Parser/Globbings/produce_glob.c \
			SRC/Parser/Line_Errors/check_inhibitor_error.c \
			SRC/Parser/Line_Errors/binary_error_parser.c \
			SRC/Parser/Line_Errors/display_error.c \
			SRC/Parser/Line_Errors/check_right_redir.c \
			SRC/Parser/Line_Errors/check_left_redir.c \
			SRC/Parser/Line_Errors/check_parenthesis.c \
			SRC/Parser/Line_Errors/check_pipe.c \
			bonus/shrimp_command.c

OBJ		=	$(SRC:.c=.o)

OBJ_TEST = $(SRC_TEST:.c=.o)

NAME 	= 	42sh

TEST_NAME = unit_tests

CFLAGS  =   -Iinclude

TEST_FLAGS = -lcriterion --coverage

TEST_FILE = tests/test_sh.c

LIB = -LSRC/lib -lmy

all: $(NAME)


$(NAME): $(OBJ)
	$(MAKE) -C SRC/lib
	gcc -o $(NAME) $(OBJ) $(LIB) -Wall -Wextra

clean:
	rm -f $(OBJ) $(OBJ_TEST)

fclean: clean
	rm -f $(NAME)
	rm -f *.gcno
	rm -f *.gcda
	rm -f $(TEST_NAME)
	$(MAKE) -C SRC/lib fclean

tests_run:
	$(MAKE) -C SRC/lib
	gcc -o $(TEST_NAME) $(SRC_TEST) $(TEST_FILE) $(LIB) $(CFLAGS) $(TEST_FLAGS)
	./$(TEST_NAME)

coverage: tests_run
	gcovr --exclude ./tests
	gcovr --exclude ./tests --txt-metric=branch

clean_tests: fclean
	rm -f *.gcno
	rm -f *.gcda
	rm -f $(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re tests_run coverage
