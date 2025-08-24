/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_meta_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 16:58:48 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/24 20:22:05 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*handle_less_than(char *str, int *i)
{
	if (str[(*i) + 1] == '<')
	{
		if (str[(*i) + 2] == '<')
			return (write(2, "parse error\n", 12), NULL);
		return ((*i) += 2, fill_node(ft_strdup("<<"), T_HEREDOC, 1));
	}
	else
		return ((*i)++, fill_node(ft_strdup("<"), T_LESS, 1));
}

static t_list	*handle_greater_than(char *str, int *i)
{
	if (str[(*i) + 1] == '>')
	{
		if (str[(*i) + 2] == '>')
			return (write(2, "parse error\n", 12), NULL);
		return ((*i) += 2, fill_node(ft_strdup(">>"), T_DGREAT, 1));
	}
	else
		return ((*i)++, fill_node(ft_strdup(">"), T_GREAT, 1));
}

static t_list	*handle_pipe(char *str, int *i)
{
	if (str[(*i) + 1] == '|')
		return (write(2, "parse error\n", 12), NULL);
	return ((*i)++, fill_node(ft_strdup("|"), T_PIPE, 1));
}

t_list	*chr_meta(char *str, int *i)
{
	if (str[*i] == '<')
		return (handle_less_than(str, i));
	else if (str[*i] == '>')
		return (handle_greater_than(str, i));
	else if (str[*i] == '|')
		return (handle_pipe(str, i));
	return (NULL);
}
