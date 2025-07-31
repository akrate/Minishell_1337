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
    T_WORD,/*thsi is cmd or file name*/
    T_PIPE, /*this is pipe ->> '|'*/
    T_DGREAT, /*this is  double greater than --> ' >> '*/
    T_GREAT, /*this is greater than --> ' > '*/
    T_DLESS, /*this is double less than --> ' << ' */
    T_LESS, /*this is less than-->  ' < ' */
} t_token_type;
\
typedef struct s_qout
{
    int i;
    int in_quote;
    char quote_char;
    char *result;
    char *tmp;
} t_qout;

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
    int retu;
} t_dolar;

typedef struct s_list
{
    char *content;
    int remove_qoute;
    t_token_type type;
    struct s_list *next;
} t_list;

typedef struct s_sqout
{
    int i;
    int in_quote;
    char quote_char;
    int in_double_quote;
    char *result;
    char *tmp;
    char *new_res;
} t_sqout;

typedef struct s_dolar2
{
    t_list *tmp;
    t_list *current;
    t_list *processed;
} t_dolar2;

typedef struct s_processnode
{
    int i;
    int start;
    int sp;
    char *result;
    char *helper;
    char *first;
    char *env_name;
    char *env_val;
    t_list *tmp; 
} t_pd;

typedef struct convert
{
    int i;
    char *result;
    char *str;
    char *str1;
    t_list *tmp;
    t_list *helper;
    char *var_value;
    int start;
    char *to_add;
    int flag;
}convert_d;

typedef struct s_lst_garbage
{
   void *ptr;
   struct s_lst_garbage *next;
} t_lst_garbage;

typedef struct data
{
    t_list *tokens_lst;
    t_lst_garbage *lst_gc_g;
    t_lst_garbage *lst_gc_env;
}t_data;

typedef struct s_split
{
	int		i;
	int		start;
	t_list	*head;
} t_split;

void	paring_cmd(char *cmd);
t_data	*set_get_data(void *p);
void	free_garbage(t_lst_garbage **head);
t_list	*split_cmd(char *str, int flag);
void	*ft_malloc(size_t size, t_lst_garbage **head);
t_list	*fill_node(char *content, t_token_type t_type, int rm_qu);
int	ft_lstadd_back(t_list **lst, t_list *new);
int	checking_close_qoutes(char *str);
int	is_meta(char str);
int	checking_cmd(t_list **list);
t_list	*convert_dolar2(t_list **list);
char	*checking_dolar(char *str);
char	*skip_qouts(char *str, int rm_qu);
char	*extract_quoted_substring(char *str, int *index, char quote_char);
int	check_space(char *str);
char	*skip_single_qout(char *str);
int	present_dolar(char *str);
int	is_redirection(t_token_type type);

#endif