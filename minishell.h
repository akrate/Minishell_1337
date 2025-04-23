#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum s_token_type
{
    T_IDENTIFIER,/*thsi is cmd or file name*/
    T_PIPE, /*this is pipe ->> '|'*/
    T_AND, /*this is and --> ' && '*/
    T_OR, /*this is or --> ' || '*/
    T_O_PARENT, /*this is open Parenthesis --> ' ( ' */
    T_C_PARENT, /*this is close Parenthesis --> ' ) '*/
    T_DGREAT, /*this is  double greater than --> ' >> '*/
    T_GREAT, /*this is greater than --> ' > '*/
    T_DLESS, /*this is double less than --> ' << ' */
    T_LESS, /*this is less than-->  ' < ' */
    
} t_token_type;

typedef struct s_cmd
{
    char *cmd;
    char *token;

} t_cmd;
typedef struct s_list
{
    char *content;
    struct s_list *next;
} t_list;

void paring_cmd(char *cmd);

t_list *fill_node(char *str, int start, int finish);
//////////list////
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
#endif