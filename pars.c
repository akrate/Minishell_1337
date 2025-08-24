/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:55:00 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/24 19:01:11 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_pos(char *str, int *i)
{
	char	c;

	if (str[*i] == '\'' || str[*i] == '"')
	{
		c = str[*i];
		(*i)++;
		while (str[*i] && str[*i] != c)
			(*i)++;
		if (str[*i] == c)
			(*i)++;
	}
	else
	{
		while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != ' '
			&& is_meta(str[*i]) == 0)
			(*i)++;
	}
}

static void	skip_whitespace(char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
}

static int	handle_meta_token(char *str, int *i, t_list **head)
{
	if (ft_lstadd_back(head, chr_meta(str, i)) == 1)
		return (1);
	return (0);
}

static int	handle_word_token(char *str, int *i, t_list **head, int flag)
{
	int	start;

	start = *i;
	while (str[*i] && !is_meta(str[*i]) && str[*i] != ' ')
		get_pos(str, i);
	if (*i > start)
	{
		if (ft_lstadd_back(head, fill_node(ft_substr(str, start, *i - start),
					T_WORD, flag)) == 1)
			return (1);
	}
	return (0);
}

t_list	*split_cmd(char *str, int flag)
{
	int		i;
	t_list	*head;

	i = 0;
	head = NULL;
	if (!str)
		return (NULL);
	while (str[i])
	{
		skip_whitespace(str, &i);
		if (str[i] == '\0')
			break ;
		if (is_meta(str[i]))
		{
			if (handle_meta_token(str, &i, &head) == 1)
				return (NULL);
		}
		else
		{
			if (handle_word_token(str, &i, &head, flag) == 1)
				return (NULL);
		}
	}
	return (head);
}

static void	cleanup_heredoc_files(t_list *hd)
{
	t_list	*tmp;

	tmp = hd;
	while (tmp)
	{
		if (tmp->type == T_HEREDOC && tmp->next)
			unlink(tmp->next->content);
		tmp = tmp->next;
	}
}

static int	process_heredoc_token(t_list *tmp, t_list *hd)
{
	char	*heredoc_file;

	if (tmp->next)
	{
		heredoc_file = heredoc(tmp->next->content);
		if (!heredoc_file)
		{
			cleanup_heredoc_files(hd);
			return (1);
		}
		tmp->next->content = heredoc_file;
	}
	return (0);
}

static int	handle_single_token(t_list *tmp, t_list *hd, t_env *env, int *flag)
{
	if (tmp->type == T_HEREDOC)
	{
		if (process_heredoc_token(tmp, hd) == 1)
			return (1);
		*flag = 2;
	}
	if (*flag == 0)
		tmp->content = checking_dolar(tmp->content, env);
	tmp->content = skip_qouts(tmp->content, tmp->remove_qoute);
	if (*flag != 0)
		(*flag)--;
	return (0);
}

static int	process_token_list(t_list *hd, t_env *env)
{
	t_list	*tmp;
	int		flag;

	tmp = hd;
	flag = 0;
	while (tmp)
	{
		if (handle_single_token(tmp, hd, env, &flag) == 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	paring_cmd(char *cmd, t_env **env)
{
	t_list	*args;
	t_list	*hd;

	args = split_cmd(cmd, 0);
	if (args == NULL)
		return ;
	if (checking_cmd(&args, env) == 1)
		return ;
	hd = convert_dolar2(&args, *env);
	if (process_token_list(hd, *env) == 1)
		return ;
	parc_token(hd, env);
	cleanup_heredoc_files(hd);
}
