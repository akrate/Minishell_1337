/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:38:20 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/10 14:07:54 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_lists(t_list **a, t_list *b)
{
	t_list	*last;

	if (!*a)
	{
		*a = b;
		return ;
	}
	last = *a;
	while (last->next)
		last = last->next;
	last->next = b;
}

static void	init_pd(t_pd *pd)
{
	pd->i = 0;
	pd->result = ft_strdup("");
	pd->tmp = NULL;
}

t_list	*process_node_content2(char *str,t_env *lst)
{
	t_pd	pd;

	init_pd(&pd);
	while (str[pd.i])
	{
		if (str[pd.i] == '"' || str[pd.i] == '\'')
		{
			pd.helper = extract_quoted_substring(str, &pd.i, str[pd.i]);
			pd.result = ft_strjoin(pd.result, pd.helper);
		}
		else if (str[pd.i] == '$' && (ft_isalpha(str[pd.i + 1]) || (str[pd.i
					+ 1] == '_' || str[pd.i + 1] == '?')))
		{
			pd.start = ++pd.i;
			while (ft_isalnum(str[pd.i]) || (str[pd.i] == '_' || str[pd.i] == '?'))
				pd.i++;
			pd.env_name = ft_substr(str, pd.start, pd.i - pd.start);
			pd.env_val = ft_getenv(pd.env_name,lst);
			if (pd.env_val)
			{
				if (check_space(pd.env_val))
				{
					pd.sp = 0;
					while (pd.env_val[pd.sp] && pd.env_val[pd.sp] != ' '
						&& is_meta(pd.env_val[pd.sp]) == 0)
						pd.sp++;
					if (pd.sp > 0)
					{
						pd.first = ft_substr(pd.env_val, 0, pd.sp);
						pd.result = ft_strjoin(pd.result, pd.first);
						ft_lstadd_back(&pd.tmp, fill_node(ft_strdup(pd.result),
								T_WORD, 1));
						pd.result = ft_strdup("");
					}
					if (pd.env_val[pd.sp])
					{
						ft_lstadd_back(&pd.tmp, fill_node(pd.result,
								T_WORD, 0));
						join_lists(&pd.tmp, split_cmd(pd.env_val + pd.sp, 1));
						pd.result = ft_strdup("");
					}
				}
				else
					pd.result = ft_strjoin(pd.result, ft_strdup(pd.env_val));
			}
		}
		else if (str[pd.i] == '$' && str[pd.i + 1] == '\'')
		{
			pd.i++;
			pd.helper = extract_quoted_substring(str, &pd.i, str[pd.i]);
			pd.result = ft_strjoin(pd.result, pd.helper);
		}
		else
		{
			pd.result = ft_strjoin(pd.result, ft_substr(str, pd.i, 1));
			pd.i++;
		}
	}
	if (pd.result && *pd.result)
		ft_lstadd_back(&pd.tmp, fill_node(pd.result, T_WORD, 0));
	return (pd.tmp);
}

static void	init_st(t_dolar2 *st, t_list *list)
{
	st->tmp = NULL;
	st->current = list;
}

t_list	*convert_dolar2(t_list **list,t_env *env)
{
	t_dolar2	st;

	init_st(&st, *list);
	while (st.current)
	{
		if (st.current->type == T_HEREDOC)
		{
			if (st.current->next != NULL)
			{
				ft_lstadd_back(&st.tmp,
					fill_node(ft_strdup(st.current->content), st.current->type,
						st.current->remove_qoute));
				st.current = st.current->next;
				ft_lstadd_back(&st.tmp,
					fill_node(ft_strdup(st.current->content), st.current->type,
						st.current->remove_qoute));
				st.current = st.current->next;
				continue ;
			}
		}
		if (present_dolar(st.current->content) == 0)
			ft_lstadd_back(&st.tmp,
				fill_node(ft_strdup(st.current->content),
					st.current->type, st.current->remove_qoute));
		else
		{
			st.processed = process_node_content2(st.current->content,env);
			join_lists(&st.tmp, st.processed);
		}
		st.current = st.current->next;
	}
	return (st.tmp);
}
