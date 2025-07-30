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
    // T_O_PARENT, /*this is open Parenthesis --> ' ( ' */
    // T_C_PARENT, /*this is close Parenthesis --> ' ) '*/
    T_DGREAT, /*this is  double greater than --> ' >> '*/
    T_GREAT, /*this is greater than --> ' > '*/
    T_DLESS, /*this is double less than --> ' << ' */
    T_LESS, /*this is less than-->  ' < ' */
    
} t_token_type;

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

void paring_cmd(char *cmd);

int is_meta(char str);

int ft_lstadd_back(t_list **lst, t_list *new);

void ft_lstclear(t_list **lst);

int					ft_lstsize(t_list *lst);

char *checking_dolar(char *str);

char *ft_strjoin_free(char *s1, char *s2);

char *skip_qouts(char *str,int rm_qu);

t_list *fill_node(char *content,t_token_type t_type,int rm_qu);

int checking_close_qoutes(char *str);

int checking_cmd(t_list **list);
t_list *ft_lastlist(t_list *lst);
/////////////////////////////////////////////////////
t_list *split_cmd(char *str ,int flag);
t_list *convert_dolar2(t_list **list);
char *extract_quoted_substring(char *str, int *index, char quote_char);
int check_space(char *str);
void join_lists(t_list **a, t_list *b);
//////////////////////////////////////////////////////===>test
const char *token_type_to_string(t_token_type type);
char *remove_space_in_dqout(char *str);
void convert_dolar(t_list **list);
void ft_lstclear_dolar(t_list **lst,char **tmp);
void free_split(char **tmp);
int present_dolar(char *str);
// char* add_single_quotes(const char* str);
void remove_pattern(char *input);
char *wrap_with_pattern(const char *input);
///////////////////////////////////////////////////////
int has_pattern(const char *input);
// char *extract_string(const char *input);
void remove_pattern(char *input);
char *wrap_with_pattern(const char *input);
char *extract_string(const char *input);
//////////////////////////////////////////////////////////=====>tool
t_list *chr_meta(char *str,int *i);

#endif