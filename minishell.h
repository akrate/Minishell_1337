#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum e_token_type
{
    T_IDENTIFIER,   // identifier
    T_PIPE,     // pipe
    T_AND,              // logical AND
    T_OR,           // logical OR
    T_O_PARENT, // open parenthesis
    T_C_PARENT, // close parenthesis
    T_DGREAT,   // double greater than
    T_GREAT,    // greater than
    T_DLESS,    // double less than
    T_LESS,    // less than
} t_token_type;

typedef struct s_quote_state
{
    int i;          // index in the input string
    int in_quote;   // flag for quote state
    char quote_char;    // type of quote (single or double)
    char *result;   // result string
    char *tmp;      // temporary string
} t_quote_state;

typedef struct s_env_expander
{
    int i; // index in the input string
    char *result;   // result string
    char *tmp;  // temporary string
    char *var_name;     // name of the variable to expand
    char *var_value;        // value of the variable
    int in_single_quote;        // flag for single quotes
    int in_double_quote;        // flag for double quotes
    int start;          // start index of the variable name
} t_env_expander;

typedef struct s_lexer_token
{
    char *content;
    t_token_type type; // type of token
    struct s_lexer_token *next;   // pointer to the next token
} t_lexer_token;

typedef struct s_command
{
    char **cmd;          // array of arguments
    char *path;          // path to the command binary
    int input_fd;              // file descriptor for input redirection
    int output_fd;        // file descriptor for output redirection
    int redirin;        // file descriptor for input redirection
    int redirout;     // file descriptor for output redirection
    int builtin;           // 0 if not a builtin command, 1 if it is
    int index;          // index of the command in the array    
    int sts;                    // status of the command execution
} t_command;

typedef struct s_shell
{
    char **ap;          // parsed input strings
    int pipes;          // number of pipes
    int **fds;          // file descriptors for pipes
    pid_t *pid;     // array of process IDs
    t_command *cmd;           // array of command structures
} t_shell;

typedef struct s_list
{
    void            *content;       // content of the node
    struct s_list   *next;  // pointer to the next node
} t_list;
void paring_cmd(char *cmd);
char	**ft_split(char const *s, char c);

char *fill_node(char *str, int start, int finish);
char	*ft_substr(char const *s, unsigned int start, size_t len);
// char *lexe_token(char *str,int len,int start);
//////////list////
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
void ft_lstclear(t_list **lst, void (*del)(void *));

/// excution ///
void execute_cmd(t_shell *sh); // function to execute commands
void fork_process(t_shell *sh, int proc); // function to fork processes
int check_cmd(char *cmd); // function to check if a command is a builtin
char **get_cmd(char *str); // function to get command and arguments 
void init_cmd(t_shell *shell, int proc); // function to initialize command structures
char **exec_dir(t_shell *shell, int i); // function to get the execution directory
int *create_pid(int pid); // function to create an array of process IDs
int nbr_of_pid(t_shell *shell, int proc); // function to count the number of processes
void init_cmd2(t_shell *shell, int i); // function to initialize command structures
void init_shell(t_shell *sh); // function to initialize the shell structure

#endif