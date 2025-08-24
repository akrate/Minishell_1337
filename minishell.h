/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:43:28 by melkhatr          #+#    #+#             */
/*   Updated: 2025/08/24 20:28:37 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define MAX_LINE 1024

typedef enum s_token_type
{
	T_WORD,
	T_PIPE,
	T_DGREAT,
	T_GREAT,
	T_HEREDOC,
	T_LESS,
}							t_token_type;

typedef struct s_redriction
{
	t_token_type			type;
	char					*file;
	struct s_redriction		*next;
}							t_redir;

typedef struct s_spcmd
{
	char					**cmd;
	t_redir					*redir;
	struct s_spcmd			*next;
}							t_spcmd;

typedef struct s_qout
{
	int						i;
	int						in_quote;
	char					quote_char;
	char					*result;
	char					*tmp;
}							t_qout;

typedef struct s_cmd
{
	char					*cmd;
	char					*token;

}							t_cmd;

typedef struct s_dolar
{
	int						i;
	char					*result;
	char					*tmp;
	char					*var_name;
	char					*var_value;
	int						in_single_quote;
	int						in_double_quote;
	int						start;
	int						retu;
}							t_dolar;

typedef struct s_list
{
	char					*content;
	int						remove_qoute;
	t_token_type			type;
	struct s_list			*next;
}							t_list;

typedef struct s_sqout
{
	int						i;
	int						in_quote;
	char					quote_char;
	int						in_double_quote;
	char					*result;
	char					*tmp;
	char					*new_res;
}							t_sqout;

typedef struct s_dolar2
{
	t_list					*tmp;
	t_list					*current;
	t_list					*processed;
}							t_dolar2;

typedef struct s_processnode
{
	int						i;
	int						start;
	int						sp;
	char					*result;
	char					*helper;
	char					*first;
	char					*env_name;
	char					*env_val;
	t_list					*tmp;
}							t_pd;

typedef struct s_sig
{
	int						sigint;
	int						sigquit;
	int						exit_status;
	pid_t					pid;
}							t_sig;

extern t_sig				g_sig;

typedef struct s_lst_garbage
{
	void					*ptr;
	struct s_lst_garbage	*next;
}							t_lst_garbage;

typedef struct data
{
	t_lst_garbage			*lst_gc_g;
	t_lst_garbage			*lst_gc_env;
}							t_data;

typedef struct s_split
{
	int						i;
	int						start;
	t_list					*head;
}							t_split;

typedef struct s_env
{
	char					*var;
	char					*val;
	struct s_env			*next;
}							t_env;

void						paring_cmd(char *cmd, t_env **env);
t_data						*set_get_data(void *p);
void						free_garbage(t_lst_garbage **head);
t_list						*split_cmd(char *str, int flag);
void						*ft_malloc(size_t size, t_lst_garbage **head);
t_list						*fill_node(char *content, t_token_type t_type,
								int rm_qu);
int							ft_lstadd_back(t_list **lst, t_list *new);
int							checking_close_qoutes(char *str);
int							is_meta(char str);
int							checking_cmd(t_list **list, t_env **env);
t_list						*convert_dolar2(t_list **list, t_env *env);
char						*checking_dolar(char *str, t_env *env);
char						*skip_qouts(char *str, int rm_qu);
void						sig_quit(int code);
void						sig_int(int code);
char						*extract_quoted_substring(char *str, int *index,
								char quote_char);
int							check_space(char *str);
void						handle_sigint(int sig);
int							present_dolar(char *str);
int							is_redirection(t_token_type type);

void						parc_token(t_list *list, t_env **env);
void						ft_exuction(t_spcmd *list, t_env **env);
//////////////////////////////////////////////////////////
void						print_env(t_env *env);
void						ft_unset(t_spcmd *lst, t_env **env);
void						ft_cd(t_spcmd *lst, t_env **env);
int							check_env(char *var, char *val, t_env *lst);
void						ft_exit(char **cmd, t_env *env);
int							check_nber(char *str);
////////////////////////////////////////
int							get_last_node_content(t_list *head);
char						*ft_getenv(char *str, t_env *lst);

t_env						*copy_env(char **str);
char						*ft_strdup_env(const char *s);
t_env						*ft_env_new(char *var, char *val);
void						ft_env_add_back(t_env **head, t_env *new_node);
void						ft_export(char *str, t_env **env);
void						ft_export_hp(t_spcmd *lst, t_env **env);
void						srch(char *str, int *i);
int							ft_strcmp(const char *s1, const char *s2);
char						*heredoc(char *delimiter);

t_env						*set_get_env(t_env *p);
// void update_exit_status(t_env *env, int status);
void						handle_dolar(t_dolar *dolar, char *str, t_env *env);
void						init_dolar(t_dolar *dolar);
t_list						*chr_meta(char *str, int *i);

#endif