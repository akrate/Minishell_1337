/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:49:31 by aoussama          #+#    #+#             */
/*   Updated: 2025/07/31 13:52:00 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_qouts(t_sqout *strc)
{
	strc->i = 0;
	strc->in_quote = 0;
	strc->quote_char = 0;
	strc->in_double_quote = 0;
	strc->result = ft_strdup("");
	strc->tmp = NULL;
}

char	*skip_single_qout(char *str)
{
	t_sqout	qout;

	init_qouts(&qout);
	while (str[qout.i])
	{
		if (str[qout.i] == '"')
		{
			qout.in_double_quote = !qout.in_double_quote;
			qout.new_res = ft_strjoin(qout.result, ft_substr(str, qout.i, 1));
			qout.result = qout.new_res;
			qout.i++;
			continue ;
		}
		if (str[qout.i] == '\'')
		{
			if (qout.in_double_quote)
			{
				qout.new_res = ft_strjoin(qout.result, ft_substr(str, qout.i,
							1));
				qout.result = qout.new_res;
			}
			qout.i++;
			continue ;
		}
		qout.new_res = ft_strjoin(qout.result, ft_substr(str, qout.i, 1));
		qout.result = qout.new_res;
		qout.i++;
	}
	return (qout.result);
}

char	*extract_quoted_substring(char *str, int *index, char quote_char)
{
	int	start;

	start = (*index)++;
	while (str[*index] && str[*index] != quote_char)
		(*index)++;
	if (str[*index] == quote_char)
		(*index)++;
	if (quote_char == '\'')
		return (skip_single_qout(ft_substr(str, start, *index - start)));
	return (ft_substr(str, start, *index - start));
}

int	present_dolar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i])
				i++;
		}
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"' && str[i])
				i++;
		}
		if (str[i] == '$')
		{
			if (ft_isalpha(str[i + 1]) == 1 || str[i + 1] == '_')
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			return (1);
		}
		i++;
	}
	return (0);
}
