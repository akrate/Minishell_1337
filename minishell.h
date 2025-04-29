#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "libft/libft.h"
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
typedef struct s_dolar
{
    int i;
    char *result;
    char *tmp;
    char *var_name;
    char *var_value;
    int in_single_quote;
    int in_double_quote;
    int start;
} t_dolar;
typedef struct s_list
{
    char *content;
    t_token_type type;
    struct s_list *next;
} t_list;

void paring_cmd(char *cmd);
// char	*ft_substr(char const *s, unsigned int start, size_t len);
// char	*ft_strdup(const char *s);
int is_meta(char str);
//////////list////
// t_list	*ft_lstnew(void *content);
int ft_lstadd_back(t_list **lst, t_list *new);
void ft_lstclear(t_list **lst);
int					ft_lstsize(t_list *lst);
char *checking_dolar(const char *str);

//////////////////////////////////////////////////////===>test
const char *token_type_to_string(t_token_type type);
//////////////////////////////////////////////////////////

#endif