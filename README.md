# 🐚 42sh

42sh is a custom shell program developed in C that emulates and extends the functionality of the traditional tcsh shell. Designed as a complete UNIX command-line interpreter, 42sh supports robust command execution, advanced input parsing, and custom shell-specific behaviors. This project is a deep dive into system-level programming, offering insight into how real-world shells manage user interaction, processes, environment variables, and input/output redirection.

Key features include:

Command Execution: Fully supports execution of system binaries via execve, along with built-in shell commands. The shell handles PATH resolution, argument parsing, and process forking using standard UNIX system calls like fork, wait, and execve.
---

## Code documentation

For more information about our **42sh** code, click here : https://doussangsebastien.github.io/42sh/

---

## Features

### Core Functionality
- Execute system commands from terminal or standard input
- Built-in command handling (`cd`, `env`, `setenv`, `unsetenv`, `exit`)
- Environment variables management (custom implementation using linked lists)
- Function pointer system for built-in command dispatch
- Fully interactive shell prompt
- Handles return values and errors gracefully

### Advanced Parsing Support
This shell supports most of the major parsing and syntax features found in common UNIX shells:
- **Semicolons (`;`)** – Run multiple commands in sequence 
  *how to use*
            echo "Start"; ls; echo "End"
- **Pipes (`|`)** – Pipe output of one command to another  
  *how to use*
            ls -l | grep "\.c"
- **Redirections** – Handle all four:
  - `>`: Redirect output to file  
    echo "Hello World" > hello.txt
  - `<`: Redirect input from file  
    echo "Another line" >> hello.txt
  - `>>`: Append output to file  
    cat < hello.txt
  - `<<`: Heredoc input  
    cat << EOF
    Line 1
    Line 2
    EOF

### Additional Shell Features
- **Globbing** – Wildcard pattern matching (`*.c`, `file?.txt`, `file[a-z]`)
    ls *.c
- **Inhibitors** – Proper quoting to strings like we want (`"strings"`)
    echo "Hello * World"
- **Parentheses** – Subshell management (`(command)`)
    echo "Hello * World"
    echo 'This is $HOME'   # Outputs literally
    echo "This is $HOME"   # Expands to home path
- **Backticks** – Command substitution using (`´`)
    echo "Today is `date` What It Does":
        Today is Wed May 1 17:42:03 CEST 2025
- **Aliases** – Define command aliases (from `bonus/aliases.txt`)
    alias ll 'ls -l'
       ll   #will execute 'ls -l' command
- **Arrows** – History navigation with arrow keys (if readline is used or replicated)
    how to navigate:
        press "up arrow" to see the previous command (stored in the 42history.txt)
        press "down arrow" to see the next command (also stored in the 42history.txt), if you press down but you are in the last command , you keep staying in the last command.
        press "left arrow" to move to the left of your command (one caracter before)
        press "right arrow" to move to the right of your command (one caracter after)
- **History** – See all previous commands pass in the shell (`!`)
        the history is stored in the 42history.txt, however if you press history , you will find all the commands you executed during the program execution

---

## 🛠️ Getting Started

### 📋 Prerequisites

- Linux or UNIX system
- `make` and `gcc` installed

### 🚀 Installation

1. **Clone the repository**:
    ```bash
    git clone git@github.com:EpitechPGEPromo2029/B-PSU-200-BDX-2-1-42sh-edgar.duquesne.git
    ```

2. **Navigate to the project directory**:
    ```bash
    cd SRC/
    cd SRC/builtins
    cd SRC/Parser
    cd SRC/user_interface
    ```

3. **Compile the program**:
    ```bash
    make
    ```

4. **Test the program**:
    ```bash
    make tests_run
    ```

5. **Execute the shell**:
    ```bash
    ./42sh
    ```

---

## Usage Examples

### Interactive Mode
```bash
./42sh
42sh> ls -l
42sh> cd src/
42sh> env > file
42sh> ls * | grep he
```

### Via pipe Mode
```bash
echo "ls -l" | ./42sh
echo "cd src/" | ./42sh
echo "env > file" | ./42sh
echo "ls * | grep he" | ./42sh
```

---

## Project Structure
```bash
├── Makefile
├── README.md
├── SRC                                      #Source directory where the main project is stored
│   ├── Inits                                #Directory for the initialisation of datas
│   │   ├── init_aliases.c
│   │   ├── init_data.c
│   │   ├── init_environment.c
│   │   └── init_function_list.c
│   ├── Parser                               #Directory for the project parsing
│   │   ├── Globbings                        #Directory for the globbings of the 42sh
│   │   │   ├── produce_glob.c
│   │   │   └── tokenize_glob.c
│   │   ├── Inhibitors                       #Directory for the Inhibitors of the 42sh
│   │   │   ├── back_tick_case.c
│   │   │   ├── double_quote_case.c
│   │   │   ├── dup_in_quotes.c
│   │   │   ├── get_inhibitor.c
│   │   │   ├── get_inhibitor_content.c
│   │   │   ├── get_variable.c
│   │   │   ├── is_inhibitor.c
│   │   │   └── read_captured_output.c
│   │   ├── Line_Errors                      #Directory for the errors that we handle
│   │   │   ├── binary_error_parser.c
│   │   │   ├── check_inhibitor_error.c
│   │   │   ├── check_left_redir.c
│   │   │   ├── check_parenthesis.c
│   │   │   ├── check_pipe.c
│   │   │   ├── check_right_redir.c
│   │   │   └── display_error.c
│   │   ├── Tree                             #Directory for the Tree we use to store our builtins in the project 42sh
│   │   │   ├── check_linear_args.c
│   │   │   ├── create_node.c
│   │   │   ├── free_tree.c
│   │   │   ├── generate_tree.c
│   │   │   ├── load_command.c
│   │   │   ├── load_redirection.c
│   │   │   ├── print_tree.c
│   │   │   └── spliting.c
│   │   ├── build_arg.c
│   │   ├── count_word.c
│   │   ├── exec_command.c
│   │   ├── exec_subshell.c
│   │   ├── exec_tree.c
│   │   ├── execute_pipe.c
│   │   ├── get_arg_type.c
│   │   ├── handle_redirect.c
│   │   ├── interpret_command.c
│   │   └── line_parser.c
│   ├── UI                                   #Directory for the UI of the 42sh and the 42shrc (not done yet) that will execute commands from a file and display the oh my saladier kun sh
│   │   ├── 42shrc
│   │   ├── git_branch.c
│   │   ├── git_commits.c
│   │   ├── prompt.c
│   │   └── utils.c
│   ├── analyze_input.c
│   ├── build_envp.c
│   ├── builtins                             #Directory for the builtins of the 42sh
│   │   ├── Alias                            #Alias builtin (allow us to create aliases)
│   │   │   ├── alias_function.c
│   │   │   └── compare_aliases.c
│   │   ├── CD                               #Builtin CD (Change Directory)
│   │   │   ├── cd_function.c
│   │   │   ├── change_env_dir.c
│   │   │   ├── display_cd_error.c
│   │   │   └── old_pwd.c
│   │   ├── Env                              #Builtin Env (display the environment variables of the shell terminal, the env is stored in a linked list)
│   │   │   └── env_function.c
│   │   ├── Exit                             #Builtin Exit (will just exit the program forked)
│   │   │   └── exit_function.c
│   │   ├── Set                              #Builtin Set (will display the local variables and add new local variables stored in a linked list)
│   │   │   ├── free_vars.c
│   │   │   ├── open_and_store.c
│   │   │   ├── set_command.c
│   │   │   ├── set_handling.c
│   │   │   ├── set_parser.c
│   │   │   └── set_variables.c
│   │   ├── Setenv                           #Builtin Setenv (will add a new environment variable in the env)
│   │   │   └── setenv_function.c
│   │   ├── Unalias                          #Builtin Unalias (allow us to remove an alias)
│   │   │   ├── del_alias.c
│   │   │   └── unalias_function.c
│   │   ├── Unset                            #Builtin Unset (allow us to remove a local variable from the linked list)
│   │   │   └── unset_command.c
│   │   ├── Unsetenv                         #Builtin Unsetenv (allow us to remove the environment variable from the linked list)
│   │   │   └── unsetenv_function.c
│   │   ├── Where                            #Builtin Where (is used to find the location of source/binary file of a command and manuals sections for a specified file in Linux system.)
│   │   │   └── where_function.c
│   │   ├── Which                            #Builtin Which (allows users to search the list of paths in the $PATH environment variable and outputs the full path of the command)
│   │   │   ├── init_which.c
│   │   │   └── which_function.c
│   │   ├── history                          #Builtin History (display the history of the commands you executed in the shell)
│   │   │   └── history.c
│   │   └── rev_list.c
│   ├── check_stdin.c
│   ├── create_env.c
│   ├── create_path.c
│   ├── executable_condition.c
│   ├── execute_builtins.c
│   ├── free_functions.c
│   ├── lib                                  #Library we coded for our project 42sh
│   │   ├── Makefile
│   │   ├── add_str.c
│   │   ├── include
│   │   │   └── my.h
│   │   ├── is_alpha.c
│   │   ├── is_alphanumeric.c
│   │   ├── my_duptab.c
│   │   ├── my_free_word_array.c
│   │   ├── my_getnbr.c
│   │   ├── my_put_nbr.c
│   │   ├── my_putstr.c
│   │   ├── my_str_to_word_array_n.c
│   │   ├── my_strcat.c
│   │   ├── my_strcmp.c
│   │   ├── my_strdup.c
│   │   ├── my_strlen.c
│   │   └── my_strstr.c
│   ├── line_editing                         #Directory for the line editing part
│   │   ├── autocomplete                     #Directory for the auto completion of the shell
│   │   │   ├── auto.c
│   │   │   ├── find_matches.c
│   │   │   ├── get_dir.c
│   │   │   ├── get_word.c
│   │   │   ├── multiple_matches.c
│   │   │   └── strncmp_case_i.c
│   │   ├── free_line.c
│   │   ├── get_history_path.c
│   │   ├── handle_line.c
│   │   ├── init_action.c
│   │   ├── init_line.c
│   │   ├── keyboard                         #Directory for the keyboard actions such as arrows, controls, tabs etc...
│   │   │   ├── arrows.c
│   │   │   ├── basic_char.c
│   │   │   ├── ctrl.c
│   │   │   ├── directions.c
│   │   │   ├── get_n_cmd.c
│   │   │   ├── handle_keyboard.c
│   │   │   ├── insert_char.c
│   │   │   └── remove_char.c
│   │   └── line.h
│   ├── main.c
│   └── shell.c
├── aliases.txt
├── bonus                                    #Bonus directory where the history is stored, aliases and 42shrc
│   ├── 42history.txt
│   ├── 42shcr.txt
│   └── aliases.txt
├── include                                  #Include directory where protos files are stored , you will find structures for each part of the program, macros and prototypes of functions
│   ├── ansi_colors.h
│   ├── git_branch.h
│   ├── git_commits.h
│   ├── globbings.h
│   ├── inhibitor.h
│   ├── macros.h
│   ├── my.h
│   ├── parsing_struct.h
│   ├── set_protos.h
│   ├── set_struct.h
│   ├── shell_protos.h
│   ├── shell_protos_2.h
│   ├── struct.h
│   └── which.h
└── tests                                    #test directory for the project where you will find unit-tests
    ├── aliases.txt
    ├── my_divzero
    ├── seg_fault
    ├── test_sh.c
    ├── tester.sh
    ├── tests
    └── toto.txt
```
  
---

## Architecture Highlights

- **Builtins Dispatcher**: Managed via a linked list of function pointers for quick identification and execution of built-in commands.
- **Environment Handling**: Custom implementation using linked lists, allowing dynamic creation, update, and deletion of variables.
- **Parser Tree**: Commands are parsed into an abstract syntax tree (AST) to handle nested expressions, pipes, and redirections properly.
- **Custom Lib**: Reimplements standard C utilities to match project standards and ensure tight control over memory and behavior.

### Built-in Commands
```bash
| Command        | Description |
|----------------|-------------|
| `cd <dir>`      | Changes the current working directory to `<dir>`. Handles `CDPATH`, `OLDPWD`, and `~`. |
| `setenv <var> <val>` | Adds or updates an environment variable. Stored in the custom env linked list. |
| `unsetenv <var>` | Removes an environment variable from the custom environment. |
| `env`           | Displays all current environment variables stored in the shell. |
| `exit [code]`   | Exits the shell with optional exit code. Cleans up resources and ends execution. |
| `set`           | Displays local variables or sets a new one (`set var=value`). Uses a linked list for storage. |
| `unset <var>`   | Removes a local variable defined via `set`. |
| `alias <name>=<value>` | Creates a new alias or updates an existing one. Aliases are used to shorten commands. |
| `unalias <name>`| Removes a defined alias. |
| `history`       | Prints the command history from the session or from the `42history.txt` file. |
| `which <command>` | Searches the `$PATH` for the command and shows its full path. If it's a builtin, indicates so. |
| `where <command>` | Similar to `which`, but lists **all** instances found in `$PATH` and indicates if it's a builtin. |
```

### Advanced Shell Features

As part of the enrichment of the 42sh project, the following features were added to enhance command execution, allowing for more powerful and flexible shell operations:

- **Semicolon (;) Management**:
    Semicolons allow you to execute multiple commands sequentially within the same line. Each command will run one after another, regardless of the success or failure of the previous command. Example:

    ```bash
    42sh> echo "First command"; echo "Second command"; ls
    ```

- **Pipe (|) Management**:
    Pipes allow you to chain commands together, where the output of one command is passed as the input to the next command. This allows for powerful command compositions. Example:

    ```bash
    42sh> ls | grep "test"
    ```

- **Redirection Management**:
    42sh supports all four types of redirections to control the flow of input and output between commands and files:
    - Output Redirection (> and >>): Redirects the standard output of a command to a file by overwriting  it if it exists for simple redirection. And add at the follow of the file for double redirection. Example:

    ``` bash
    42sh> echo "Hello, World!" > output.txt
    42sh> echo "Hello, World!" >> output.txt
    ```

    - Simple Input Redirection (<): Redirects the standard input of a command from a file. Example:

    ```bash
    42sh> sort < input.txt
    ```

    - Double Input Redirection (<<): Create a microshell and write all the line in a file till end terminator put. Then it do like in the simple input redirection from this new file. Example:

    ```bash
    42sh> cat << EOF
    > This is a multi-line input
    > that will be passed to the command
    > until the delimiter EOF
    ```

