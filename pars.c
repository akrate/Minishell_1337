/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:55:00 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/10 14:46:40 by aoussama         ###   ########.fr       */
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

t_list	*chr_meta(char *str, int *i)
{
	if (str[*i] == '<')
	{
		if (str[(*i) + 1] == '<')
		{
			if (str[(*i) + 2] == '<')
				return (write(1, "parse error\n", 12), NULL);
			return ((*i) += 2, fill_node(ft_strdup("<<"), T_HEREDOC, 1));
		}
		else
			return ((*i)++, fill_node(ft_strdup("<"), T_LESS, 1));
	}
	else if (str[*i] == '>')
	{
		if (str[(*i) + 1] == '>')
		{
			if (str[(*i) + 2] == '>')
				return (write(1, "parse error\n", 12), NULL);
			return ((*i) += 2, fill_node(ft_strdup(">>"), T_DGREAT, 1));
		}
		else
			return ((*i)++, fill_node(ft_strdup(">"), T_GREAT, 1));
	}
	else if (str[*i] == '|')
	{
		if (str[(*i) + 1] == '|')
			return (write(1, "parse error\n", 12), NULL);
		return ((*i)++, fill_node(ft_strdup("|"), T_PIPE, 1));
	}
	return (NULL);
}

t_list	*split_cmd(char *str, int flag)
{
	int		i;
	int		start;
	t_list	*head;

	i = 0;
	head = NULL;
	if (!str)
		return (NULL);
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			break ;
		if (is_meta(str[i]))
		{
			if (ft_lstadd_back(&head, chr_meta(str, &i)) == 1)
				return (NULL);
		}
		else
		{
			start = i;
			while (str[i] && !is_meta(str[i]) && str[i] != ' ')
				get_pos(str, &i);
			if (i > start)
			{
				if (ft_lstadd_back(&head, fill_node(ft_substr(str, start, i
								- start), T_WORD, flag)) == 1)
					return (NULL);
			}
		}
	}
	return (head);
}
void here(t_list *list)
{
	t_list *tmp = list;
	while (tmp)
	{
		if (tmp->type == T_HEREDOC)
		{
			heredoc(tmp->next->content);
		}
		tmp = tmp->next;
	}
}
void	paring_cmd(char *cmd,t_env **env)
{
	t_list	*args;
	t_list	*tmp;
	t_list	*hd;
	int		flag;

	args = split_cmd(cmd, 0);
	if (args == NULL)
		return ;
	flag = 0;
	if (checking_cmd(&args,env) == 1)
		return ;
	tmp = convert_dolar2(&args,*env);
	hd = tmp;
	while (tmp)
	{
		if (tmp->type == T_HEREDOC)
			flag = 2;
		if (flag == 0)
			tmp->content = checking_dolar(tmp->content,*env);
		tmp->content = skip_qouts(tmp->content, tmp->remove_qoute);
		if (flag != 0)
			flag--;
		tmp = tmp->next;
	}
	parc_token(hd,env);
}
