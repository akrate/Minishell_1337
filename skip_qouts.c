/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:26:11 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/24 20:23:50 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_qouts(t_qout *strc)
{
	strc->i = 0;
	strc->in_quote = 0;
	strc->quote_char = 0;
	strc->result = ft_strdup("");
	strc->tmp = NULL;
}

static int	handle_opening_quote(char *str, t_qout *qout)
{
	if ((str[qout->i] == '"' || str[qout->i] == '\'') && qout->in_quote == 0)
	{
		qout->in_quote = 1;
		qout->quote_char = str[qout->i];
		qout->i++;
		return (1);
	}
	return (0);
}

static int	handle_closing_quote(char *str, t_qout *qout)
{
	if (str[qout->i] == qout->quote_char && qout->in_quote == 1)
	{
		qout->in_quote = 0;
		qout->quote_char = 0;
		qout->i++;
		return (1);
	}
	return (0);
}

static int	handle_dollar_quote(char *str, t_qout *qout)
{
	if (str[qout->i] == '$' && str[qout->i + 1] == '"')
	{
		qout->i++;
		return (1);
	}
	return (0);
}

char	*skip_qouts(char *str, int rm_qu)
{
	t_qout	qout;

	if (rm_qu == 1)
		return (str);
	init_qouts(&qout);
	while (str[qout.i])
	{
		if (handle_opening_quote(str, &qout) == 1)
			continue ;
		if (handle_closing_quote(str, &qout) == 1)
			continue ;
		if (handle_dollar_quote(str, &qout) == 1)
			continue ;
		qout.result = ft_strjoin(qout.result, ft_substr(str, qout.i, 1));
		qout.i++;
	}
	return (qout.result);
}
