/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** test_sh.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/shell_protos.h"
#include <stdio.h>

void redirect_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stdin();
    cr_redirect_stderr();
}

//testing the lib
Test(add_str, regular_str_add)
{
    char *str_1 = "toto\0";
    char *str_2 = "titi\0";

    cr_assert_str_eq(add_str(str_1, str_2), "tototiti\0");
}

Test(str_to_word_array_n, working_str_to_words)
{
    char **tab = my_str_to_word_array_n("ls -la ", " \0");
    char *expect_tab[] = {"ls", "-la", NULL};

    for (int i = 0; tab[i] != NULL && expect_tab[i] != NULL; i++) {
        cr_assert(strcmp(tab[i], expect_tab[i]) == 0);
    }

    cr_assert(tab[2] == NULL && expect_tab[2] == NULL);
}

Test(str_to_word_array_n, str_to_word_array_NULL_words)
{
    char **tab = my_str_to_word_array_n(NULL, " \0");
    cr_assert(tab == NULL);
}

Test(my_strcat, normal_strcat)
{
    char dest[30] = "./";
    char src[30] = "a.out";

    char *str = my_strcat(dest, src);
    cr_assert_str_eq(str, "./a.out");
}

Test(my_strlen, normal_strlen)
{
    char *str = "toto\0";

    int result = my_strlen(str);
    cr_assert(result == 4);
}

Test(my_strlen, NULL_strlen)
{
    char *str = NULL;

    int result = my_strlen(str);
    cr_assert(result == 0);
}

Test(my_strcmp, normal_cmp)
{
    int result = my_strcmp("toto", "toto");

    cr_assert(result == 0);
}

Test(my_strcmp, normal_cmp_minus_one)
{
    int result = my_strcmp("tot", "toto");

    cr_assert(result == -1);
}

Test(my_strcmp, normal_cmp_one)
{
    int result = my_strcmp("toto", "tot");

    cr_assert(result == 1);
}

Test(my_getnbr, normal_getnbr)
{
    int result = my_getnbr("500\0");

    cr_assert(result == 500);
}

Test(my_getnbr, error_getnbr)
{
    int result = my_getnbr("toto\0");

    cr_assert(result == 0);
}

Test(my_getnbr, error_getnbr_with_letters)
{
    int result = my_getnbr("toto60\0");

    cr_assert(result == 60);
}

Test(my_putstr, normal_and_null_putstr)
{
    int result = my_putstr("toto\0");
    int result_2 = my_putstr(NULL);
    cr_expect(result == 4);
    cr_assert(result_2 == 0);
}

Test(my_str_to_word_array_n, test_path_var)
{
    char **tab = my_str_to_word_array_n("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Program Files (x86)/VMware/VMware Workstation/bin/:/mnt/c/Windows/system32:/mnt/c/Windows:/mnt/c/Windows/System32/Wbem:/mnt/c/Windows/System32/WindowsPowerShell/v1.0/:/mnt/c/Windows/System32/OpenSSH/:/mnt/c/Program Files/dotnet/:/mnt/c/Program Files/Microsoft SQL Server/150/Tools/Binn/:/mnt/c/Program Files/Microsoft SQL Server/Client SDK/ODBC/170/Tools/Binn/:/mnt/c/Users/edgar/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/edgar/AppData/Local/Programs/Microsoft VS Code/bin:/mnt/c/Users/edgar/.dotnet/tools", ":=\0");
    cr_assert(tab);
}

//testing SRC/functions
Test(executable_condition, executable_binary)
{
    char *tab[2] = {"/bin/ls", NULL};
    const char *envp[4] = { "titi",
                    "toto",
                    "tutu", NULL};

    data_t *data = malloc(sizeof(data_t));
    init_data(data, envp);
    int result = executable_condition(0, data, "/bin/ls", 0);
    cr_assert(result == SUCCESS);
}

Test(init_data, execute_regular_init_of_struct)
{
    char *tab[2] = {"cd", NULL};
    char *envp[4] = { "titi",
                    "toto",
                    "tutu", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);
    cr_expect(data->args != NULL);
    cr_expect(data->functions != NULL);
    data->args->tab = tab;
    cr_assert_str_eq(data->args->tab[0], "cd");
}

Test(init_data, init_NULL_data_null_envp)
{
    char *tab[2] = {"cd", NULL};
    char *envp[4] = { "titi",
                    "toto",
                    "tutu", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(NULL, (const char **)envp) == FAILURE);
    cr_expect(init_data(data, NULL) == FAILURE);
}

Test(change_env, regular_pwd_switch)
{
    char *tab[2] = {"/bin/ls", NULL};
    char *envp[4] = {"PWD=toto",
                    "OLDPWD=tutu",
                    "tutu", NULL};
    char old[256];
    char new[256];
    args_t *args = malloc(sizeof(args_t));

    cr_expect(init_environment(args, (const char **)envp) == SUCCESS);
    getcwd(old, 256);
    change_env_dir(args->environ);
    getcwd(new, 256);
    while (args->environ) {
        if (args->environ->variable[0] != 'O') {
            if (strstr(args->environ->variable, "PWD="))
                cr_expect_str_eq(&args->environ->variable[4], new);
        } if (strstr(args->environ->variable, "OLDPWD=")) {
            cr_expect_str_eq(&args->environ->variable[7], "toto");
        }
        args->environ = args->environ->next;
    }
}

Test(create_path, creating_regular_path_not_found)
{
    char *tab[2] = {"ls", NULL};
    char *envp[4] = { "PATH=:toto:titi:tata",
                    "WEB=tutu",
                    "PWD=tutu", NULL};
    args_t *args = malloc(sizeof(args_t));

    cr_expect(init_environment(args, (const char **)envp) == SUCCESS);
    args->tab = tab;
    cr_expect_str_eq(create_path(args), "/bin/ls");
    free(args);
}

Test(create_path, creating_NULL_path)
{
    cr_expect(create_path(NULL) == NULL);
}


//builtins
Test(exit_function, normal_exit)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);
    tree_t *tree = generate_tree("exit 45", data);
    cr_assert(execute_tree(tree, data) == 45);
}

Test(setenv, setenv_normal)
{
    char *tab[4] = {"setenv", "WEB", "toto", NULL};
    char *envp[4] = { "PATH=:toto:titi:tata",
                    "WIWI=tutu",
                    "PWD=tutu", NULL};
    args_t *args = malloc(sizeof(args_t));

    cr_expect(init_environment(args, (const char **)envp) == SUCCESS);
    args->tab = tab;
    cr_expect(my_setenv(args) == SUCCESS);

    while (args->environ) {
        if (strstr(args->environ->variable, "WEB=")) {
            cr_assert_str_eq(args->environ->variable, "WEB=toto");
        }
        args->environ = args->environ->next;
    }
}

Test(setenv, setenv_replace)
{
    char *tab[4] = {"setenv", "WEB", "toto", NULL};
    char *envp[4] = { "PATH=:toto:titi:tata",
                    "WEB=tutu",
                    "PWD=tutu", NULL};
    args_t *args = malloc(sizeof(args_t));

    cr_expect(init_environment(args, (const char **)envp) == SUCCESS);
    args->tab = tab;
    cr_expect(my_setenv(args) == 0);
    while (args->environ) {
        if (strstr(args->environ->variable, "WEB=")) {
            cr_assert_str_eq(args->environ->variable, "WEB=toto");
        }
        args->environ = args->environ->next;
    }
}

Test(setenv, setenv_error_too_many_args, .init = redirect_stdout)
{
    char *tab[5] = {"setenv", "iIWI", "toto", "toot", NULL};
    char *envp[4] = { "PATH=:toto:titi:tata",
                    "WEB=tutu",
                    "PWD=tutu", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);
    data->args->tab = tab;
    cr_expect(my_setenv(data->args) == 1);
    cr_assert_stderr_eq_str("setenv: Too many arguments.\n");
}

Test(setenv, setenv_replacing_no_content)
{
    char *tab[3] = {"setenv", "WEB", NULL};
    char *envp[4] = { "PATH=:toto:titi:tata",
                    "WEB=tutu",
                    "PWD=tutu", NULL};
    args_t *args = malloc(sizeof(args_t));
    int i = 0;
    int j = 0;
    environ_t *temp = NULL;
    environ_t *temp_2 = NULL;

    cr_expect(init_environment(args, (const char **)envp) == SUCCESS);
    args->tab = tab;

    temp = args->environ;
    while (temp) {
        j += 1;
        temp = temp->next;
    }
    
    cr_expect(j == 3);
    cr_expect(my_setenv(args) == 0);

    temp_2 = args->environ;
    while (temp_2) {
        i += 1;
        temp_2 = temp_2->next;
    }
    cr_assert(i == 3);
}

Test(setenv, setenv_add)
{
    char *tab[4] = {"setenv", "WIWI", "toto", NULL};
    char *envp[4] = { "PATH=:toto:titi:tata",
                    "WEB=tutu",
                    "PWD=tutu", NULL};
    args_t *args = malloc(sizeof(args_t));
    int i = 0;
    int j = 0;
    environ_t *temp = NULL;
    environ_t *temp_2 = NULL;

    cr_expect(init_environment(args, (const char **)envp) == SUCCESS);
    args->tab = tab;

    temp = args->environ;
    while (temp) {
        j += 1;
        temp = temp->next;
    }
    
    cr_expect(j == 3);
    cr_expect(my_setenv(args) == 0);

    temp_2 = args->environ;
    while (temp_2) {
        i += 1;
        temp_2 = temp_2->next;
    }
    cr_assert(i == 4);
}


Test(unsetenv, unsetenv_head_node)
{
    char *tab[3] = {"unsetenv", "PWD", NULL};
    char *envp[4] = { "PATH=:toto:titi:tata",
                    "MIMI=tutu",
                    "PWD=tutu", NULL};
    args_t *args = malloc(sizeof(args_t));
    int i = 0;
    int j = 0;
    environ_t *temp = NULL;
    environ_t *temp_2 = NULL;

    cr_expect(init_environment(args, (const char **)envp) == SUCCESS);
    args->tab = tab;

    temp = args->environ;
    while (temp) {
        j += 1;
        temp = temp->next;
    }
    cr_expect(j == 3);
    cr_expect(my_unsetenv(args) == 0);

    temp_2 = args->environ;
    while (temp_2) {
        i += 1;
        temp_2 = temp_2->next;
    }
    cr_assert(i == 2);
}

Test(unsetenv, unsetenv_normal)
{
    char *tab[3] = {"unsetenv", "MIMI", NULL};
    char *envp[4] = { "PATH=:toto:titi:tata",
                    "MIMI=tutu",
                    "PWD=tutu", NULL};
    args_t *args = malloc(sizeof(args_t));
    int i = 0;
    int j = 0;
    environ_t *temp = NULL;
    environ_t *temp_2 = NULL;

    cr_expect(init_environment(args, (const char **)envp) == SUCCESS);
    args->tab = tab;

    temp = args->environ;
    while (temp) {
        j += 1;
        temp = temp->next;
    }
    cr_expect(j == 3);
    cr_expect(my_unsetenv(args) == 0);

    temp_2 = args->environ;
    while (temp_2) {
        i += 1;
        temp_2 = temp_2->next;
    }
    cr_assert(i == 1);
}

Test(unsetenv, unsetenv_unknown_name)
{
    char *tab[3] = {"unsetenv", "Mumu\0", NULL};
    char *envp[4] = { "PATH=:toto:titi:tata",
                    "MIMI=tutu",
                    "PWD=tutu", NULL};
    args_t *args = malloc(sizeof(args_t));
    environ_t *temp = NULL;
    environ_t *temp_2 = NULL;

    cr_expect(init_environment(args, (const char **)envp) == SUCCESS);
    args->tab = tab;
    cr_expect(my_unsetenv(args) == 0);
}

Test(unsetenv, setenv_invalid_name_2, .init = redirect_stdout)
{
    char *tab[4] = {"setenv", "1eori", "toto", NULL};
    char *envp[4] = { "PATH=:toto:titi:tata",
                    "MIMI=tutu",
                    "PWD=tutu", NULL};
    args_t *args = malloc(sizeof(args_t));
    environ_t *temp = NULL;
    environ_t *temp_2 = NULL;

    cr_expect(init_environment(args, (const char **)envp) == SUCCESS);
    args->tab = tab;
    cr_expect(my_setenv(args) == 1);
    fflush(stderr);
    cr_assert_stderr_eq_str("setenv: Variable name must begin with a letter.\n");
}

Test(env, normal_env, .init = redirect_stdout)
{
    char *tab[2] = {"env", NULL};
    char *envp[4] = { "PATH=toto:",
                    "WEB=tutu",
                    "PWD=tutu", NULL};
    args_t *args = malloc(sizeof(args_t));

    cr_expect(init_environment(args, (const char **)envp) == SUCCESS);
    args->tab = tab;
    cr_expect(my_env(args) == 0);
    cr_assert_stdout_eq_str("PATH=toto:\nWEB=tutu\nPWD=tutu\n");
}

Test(env, normal_env_rev, .init = redirect_stdout)
{
    char *tab[2] = {"env", NULL};
    char *envp[4] = { "PATH=toto:",
                    "WEB=tutu",
                    "PWD=tutu", NULL};
    args_t *args = malloc(sizeof(args_t));

    cr_expect(init_environment(args, (const char **)envp) == SUCCESS);
    args->tab = tab;
    rev_list(&args->environ);
    cr_expect(!my_env(args));
    cr_assert_stdout_eq_str("PWD=tutu\nWEB=tutu\nPATH=toto:\n");
}

Test(cd, normal_dash_cd)
{
    char *tab[3] = {"cd", "-", NULL};
    char *envp[4] = { "PATH=toto:",
                    "OLDPWD=~",
                    "PWD=tutu", NULL};
    args_t *args = malloc(sizeof(args_t));

    cr_expect(init_environment(args, (const char **)envp) == SUCCESS);
    args->tab = tab;
    old_pwd(args);
}

Test(cd, normal_cd)
{
    char *tab[3] = {"cd", "..", NULL};
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=tutu", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);
    data->args->tab = tab;
    cr_assert(my_cd(data->args) == 0);
}

Test(cd, normal_cd_home)
{
    char *tab[3] = {"cd", "~/", NULL};
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=tutu", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);
    data->args->tab = tab;
    cr_assert(my_cd(data->args) == 0);
}

Test(analyze_input, normal_analyze_input_cd)
{
    char *tab[2] = {"cd", NULL};
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);
    data->args->tab = tab;
    cr_assert(analyze_input(data) == 0);
}

Test(analyze_input, cd_into_file, .init = redirect_stdout)
{
    char *tab[3] = {"cd", "tests/test_sh.c", NULL};
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);
    data->args->tab = tab;
    cr_assert(analyze_input(data) == 1);
    fflush(stderr);
    cr_assert_stderr_eq_str("tests/test_sh.c: Not a directory.\n");
}

Test(analyze_input, cd_unknown, .init = redirect_stdout)
{
    char *tab[3] = {"cd", "toto", NULL};
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);
    data->args->tab = tab;
    cr_expect(analyze_input(data) == 1);
    cr_assert_stderr_eq_str("toto: No such file or directory.\n");
}

Test(analyze_input, cd_no_home)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);
    tree_t *tree = generate_tree("unsetenv HOME ; cd", data);
    cr_assert(execute_tree(tree, data) == SUCCESS);
}

Test(analyze_input, exec_seg_fault, .init = redirect_stdout)
{
    char *tab[2] = {"./tests/seg_fault", NULL};
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);
    data->args->tab = tab;
    cr_expect(analyze_input(data) == 139);
}

Test(analyze_input, exec_bin_ls)
{
    char *tab[2] = {"/bin/ls", NULL};
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);
    data->args->tab = tab;
    cr_assert(analyze_input(data) == 0);
}

Test(analyze_input, exec_div_zero, .init = redirect_stdout)
{
    char *tab[2] = {"./tests/my_divzero", NULL};
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);
    data->args->tab = tab;
    cr_expect(analyze_input(data) == 136);
}

Test(my_env, exec_env)
{
    char *tab[3] = {"env", "toto", NULL};
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);
    data->args->tab = tab;
    cr_assert(analyze_input(data) == 127);
}

// ALIASES
Test(analyze_input, check_aliases, .init = redirect_stdout)
{
    char *tab[4] = {"alias", "toto", "ls", NULL};
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);
    data->args->tab = tab;
    cr_expect(analyze_input(data) == SUCCESS);
    cr_assert_str_eq(data->args->alias->command, "ls");
}

Test(analyze_input, check_bad_aliases, .init = redirect_stdout)
{
    char *tab[5] = {"alias", "toto", "\'ls | grep a\'", "ls", NULL};
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);
    data->args->tab = tab;
    cr_expect(analyze_input(data) == ERROR);
}

Test(count_words, parsing_line_normally)
{
    int count = count_words("ls | >> << <|cd>||&;ld");

    cr_assert(count == 12);
}

Test(parser, parsing_line_normally)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);
    char **tab = line_parser("ls -la | grep a >> cat.toto", data);
    cr_assert(tab != NULL);
}

Test(detecting_line_errors, empty_command)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);
    tree_t *tree = generate_tree("ls -la | |", data);
    
    cr_assert(tree == NULL);
}

Test(detecting_line_errors, ambiguous_redir_output)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);
    tree_t *tree = generate_tree("ls -la >>", data);
    
    cr_assert(tree == NULL);
}

Test(detecting_line_errors, ambiguous_redir_input)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);
    tree_t *tree = generate_tree("ls -la <<", data);
    
    cr_assert(tree == NULL);
}

Test(detecting_line_errors, ambiguous_redir_not_a_file)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);
    tree_t *tree = generate_tree("ls -la | ls << toto", data);
    int result = binary_error_parser(tree); 
    cr_assert(result == SUCCESS);
}

Test(detecting_line_errors, correct_tree_generation)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);
    tree_t *tree = generate_tree("ls -la | grep a", data);
    
    cr_assert(tree != NULL);
}

Test(check_parenthesis, semi_in_parenthesis)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);
    char *line = "(ls ; ls -la) | toto";
    char **tab = line_parser(line, data);
    cr_assert(check_parenthesis(tab) == SUCCESS);
}

Test(check_parenthesis, 2_close)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);
    char *line = "(ls | grep toto )) | toto";
    char **tab = line_parser(line, data);
    cr_assert(check_parenthesis(tab) == FAILURE);
}

Test(check_parenthesis, 2_open)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);
    char *line = "((ls | grep toto ) | toto";
    char **tab = line_parser(line, data);
    cr_assert(check_parenthesis(tab) == FAILURE);
}

Test(check_parenthesis, empty_close)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);
    char *line = ")ls | grep toto  | toto";
    char **tab = line_parser(line, data);
    cr_assert(check_parenthesis(tab) == FAILURE);
}

Test(check_parenthesis, empty_open)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);
    char *line = "ls | grep toto  | toto(";
    char **tab = line_parser(line, data);
    cr_assert(check_parenthesis(tab) == FAILURE);
}

Test(check_parenthesis, arg_after_closed_p)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);

    char *line = "(ls | grep a) ls";
    char **tab = line_parser(line, data);
    cr_assert(check_parenthesis(tab) == FAILURE);
}

Test(check_parenthesis, correct_parenthesis_redir)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);

    char *line = "(ls | grep a) > toto";
    char **tab = line_parser(line, data);
    cr_assert(check_parenthesis(tab) == SUCCESS);
}

Test(check_parenthesis, correct_parenthesis_rr_redir)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);

    char *line = "(ls | grep a) >> toto";
    char **tab = line_parser(line, data);
    cr_assert(check_parenthesis(tab) == SUCCESS);
}

Test(exec_line, special_r_redir)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);

    char *line = "> toto ls";
    char **tab = line_parser(line, data);
    cr_assert(tab != NULL);
}

Test(exec_line, special_rr_redir)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);

    char *line = ">> toto ls -la";
    char **tab = line_parser(line, data);
    cr_assert(tab != NULL);
}

Test(exec_line, special_l_redir_error)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);

    char *line = "< toto ls -la";
    char **tab = line_parser(line, data);
    cr_assert(tab != NULL);
}

Test(exec_line, inhibitors_single_quote)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);

    char *line = "\'toto\'";
    char **tab = line_parser(line, data);
    cr_assert(tab != NULL);
}

Test(exec_line, inhibitors_double_quote)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);

    char *line = "\"toto\"";
    char **tab = line_parser(line, data);
    cr_assert(tab != NULL);
}

Test(exec_line, inhibitors_back_tick_quote)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);

    char *line = "`toto`";
    char **tab = line_parser(line, data);
    cr_assert(tab != NULL);
}

Test(exec_line, inhibitor_interpreting_with_env_var)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);

    char *line = "setenv toto $HOME";
    tree_t *tree = generate_tree(line, data);
    cr_expect(tree);
    cr_expect(execute_tree(tree, data) == SUCCESS);
}

Test(exec_line, glob_interpreting)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);

    char *line = "setenv tutu *.a";
    tree_t *tree = generate_tree(line, data);
    cr_expect(tree);
    cr_expect(execute_tree(tree, data) == SUCCESS);
}

Test(exec_line, complex_glob_interpreting)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);

    char *line = "setenv tata *.??[a-z]n";
    tree_t *tree = generate_tree(line, data);
    cr_expect(tree);
    cr_expect(execute_tree(tree, data) == SUCCESS);
}

Test(exec_line, normal_parenthesis)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);

    char *line = "(toto | toto)";
    tree_t *tree = generate_tree(line, data);
    cr_expect(tree);
    cr_expect(execute_tree(tree, data) == SUCCESS);
}

Test(exec_line, normal_prompt, .init = cr_redirect_stdout)
{
    char output[256] = {0};
    fflush(stdout);
    prompt();
    FILE *file = cr_get_redirected_stdout();
    fread(output, sizeof(char), 2560, file);
    cr_assert(strlen(output) >= 2, "Prompt output is too short");
}

Test(exec_line, right_redir_success)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);

    char *line = "(ls) > tests/toto.txt";
    tree_t *tree = generate_tree(line, data);
    cr_expect(tree);
    cr_expect(execute_tree(tree, data) == SUCCESS);
    FILE *fp = fopen("tests/toto.txt","r" );
    cr_expect(fp);
    fseek (fp, 0, SEEK_END);
    size_t size = ftell(fp);
    cr_assert(size != 0);
}

Test(exec_line, rr_redir_success)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);

    char *line = "(ls) >> tests/toto.txt";
    tree_t *tree = generate_tree(line, data);
    cr_expect(tree);
    cr_expect(execute_tree(tree, data) == SUCCESS);
    FILE *fp = fopen("tests/toto.txt","r" );
    cr_expect(fp);
    fseek (fp, 0, SEEK_END);
    size_t size = ftell(fp);
    cr_assert(size != 0);
}

Test(exec_line, history)
{
    char *envp[4] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home", NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);

    char *line = "history -c";
    tree_t *tree = generate_tree(line, data);
    cr_expect(tree);
    cr_expect(execute_tree(tree, data) == SUCCESS);
    line = "history -s";
    tree = generate_tree(line, data);
    cr_expect(execute_tree(tree, data) == SUCCESS);
    line = "history -s 67";
    tree = generate_tree(line, data);
    cr_expect(execute_tree(tree, data) == SUCCESS);
    line = "history";
    tree = generate_tree(line, data);
    cr_expect(execute_tree(tree, data) == SUCCESS);
}

Test(exec_line, where_which_noenv)
{
    char *envp[5] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home",
                    NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);

    char *line = "where ls";
    tree_t *tree = generate_tree(line, data);
    cr_expect(execute_tree(tree, data) == ERROR);
    line = "which ls";
    tree = generate_tree(line, data);
    cr_expect(execute_tree(tree, data) == ERROR);
    line = "which -a ls";
    tree = generate_tree(line, data);
    cr_expect(execute_tree(tree, data) == ERROR);
}

Test(set, normal_sets, .init = redirect_stdout)
{
    char *envp[5] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home",
                    NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);

    char *line = "set toto = titi";
    tree_t *tree = generate_tree(line, data);
    cr_expect(execute_tree(tree, data) == SUCCESS);
    line = "set toto";
    tree = generate_tree(line, data);
    cr_expect(execute_tree(tree, data) == SUCCESS);
    line = "set";
    tree = generate_tree(line, data);
    cr_expect(execute_tree(tree, data) == SUCCESS);
    line = "echo $toto";
    tree = generate_tree(line, data);
    cr_expect(execute_tree(tree, data) == SUCCESS);
    fflush(stderr);
    line = "set \%\%";
    tree = generate_tree(line, data);
    cr_expect(execute_tree(tree, data) == ERROR);
    cr_assert_stderr_eq_str("set: Variable name must begin with a letter.\n");
}

Test(unset, normal_unsets, .init = redirect_stdout)
{
    char *envp[5] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home",
                    NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);

    char *line = "set toto = titi";
    tree_t *tree = generate_tree(line, data);
    cr_expect(execute_tree(tree, data) == SUCCESS);
    line = "unset toto";
    tree = generate_tree(line, data);
    cr_expect(execute_tree(tree, data) == SUCCESS);
    line = "unset toto";
    tree = generate_tree(line, data);
    cr_expect(execute_tree(tree, data) == SUCCESS);
    fflush(stderr);
    line = "unset";
    tree = generate_tree(line, data);
    cr_expect(execute_tree(tree, data) == ERROR);
    cr_assert_stderr_eq_str("unset: Too few arguments.\n");
}

Test(exec_line, unalias)
{
    char *envp[5] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home",
                    NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);

    char *line = "unalias fsdofhdsof";
    tree_t *tree = generate_tree(line, data);
    cr_expect(execute_tree(tree, data) == SUCCESS);
    line = "alias tototo ls; unalias tototo";
    tree = generate_tree(line, data);
    cr_expect(execute_tree(tree, data) == SUCCESS);
    line = "alias toto ls; unalias toto ; toto";
    tree = generate_tree(line, data);
    cr_expect(execute_tree(tree, data) == ERROR);
}

Test(exec_line, andand_oror)
{
    char *envp[5] = { "OLDPWD=titi",
                    "PWD=toto",
                    "HOME=/home",
                    NULL};
    data_t *data = malloc(sizeof(data_t));
    cr_expect(init_data(data, (const char **)envp) == SUCCESS);

    char *line = "fail || ls";
    tree_t *tree = generate_tree(line, data);
    cr_expect(execute_tree(tree, data) == SUCCESS);
    line = "ls || ls";
    tree = generate_tree(line, data);
    cr_expect(execute_tree(tree, data) == SUCCESS);
    line = "ls && toto";
    tree = generate_tree(line, data);
    cr_expect(execute_tree(tree, data) == ERROR);
    line = "ls && ls";
    tree = generate_tree(line, data);
    cr_expect(execute_tree(tree, data) == SUCCESS);
    line = "toto && ls";
    tree = generate_tree(line, data);
    cr_expect(execute_tree(tree, data) == ERROR);
}
