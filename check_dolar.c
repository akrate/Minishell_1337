/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dolar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:37:05 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/07 20:37:20 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_dolar(t_dolar *dolar)
{
	dolar->i = 0;
	dolar->start = 0;
	dolar->result = ft_strdup("");
	dolar->tmp = NULL;
	dolar->var_name = NULL;
	dolar->var_value = NULL;
	dolar->in_single_quote = 0;
	dolar->in_double_quote = 0;
}

static void	handle_single_quote(t_dolar *dolar, char *str)
{
	dolar->in_single_quote = !dolar->in_single_quote;
	dolar->result = ft_strjoin(dolar->result, ft_substr(str, dolar->i, 1));
	dolar->i++;
}

static void	handle_double_quote(t_dolar *dolar, char *str)
{
	dolar->in_double_quote = !dolar->in_double_quote;
	dolar->result = ft_strjoin(dolar->result, ft_substr(str, dolar->i, 1));
	dolar->i++;
}

static void	handle_dolar(t_dolar *dolar, char *str,t_env *env)
{
	if (!ft_isalnum(str[dolar->i + 1]))
	{
		dolar->result = ft_strjoin(dolar->result, ft_substr(str, dolar->i, 1));
		dolar->i++;
		return ;
	}
	dolar->start = ++dolar->i;
	while (str[dolar->i] && (ft_isalnum(str[dolar->i]) || str[dolar->i] == '_'))
		dolar->i++;
	dolar->var_name = ft_substr(str, dolar->start, dolar->i - dolar->start);
	dolar->var_value = ft_getenv(dolar->var_name,env);
	if (dolar->var_value)
		dolar->result = ft_strjoin(dolar->result, ft_strdup(dolar->var_value));
}

char	*checking_dolar(char *str,t_env *env)
{
	t_dolar	dolar;

	init_dolar(&dolar);
	while (str[dolar.i])
	{
		if (str[dolar.i] == '\'' && !dolar.in_double_quote)
			handle_single_quote(&dolar, str);
		else if (str[dolar.i] == '"' && !dolar.in_single_quote)
			handle_double_quote(&dolar, str);
		else if (str[dolar.i] == '$' && !dolar.in_single_quote
			&& dolar.in_double_quote)
			handle_dolar(&dolar, str,env);
		else
		{
			dolar.result = ft_strjoin(dolar.result, ft_substr(str, dolar.i, 1));
			dolar.i++;
		}
	}
	return (dolar.result);
}
