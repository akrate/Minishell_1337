/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:38:20 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/16 20:48:47 by aoussama         ###   ########.fr       */
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
static char *join_in_dqout(char *str)
{
	char *result;

	result = ft_strjoin("\"",str);
	result = ft_strjoin(result,"\"");
	return (result);
}

static void handle_quoted_string(char *str, t_pd *pd)
{
    pd->helper = extract_quoted_substring(str, &pd->i, str[pd->i]);
    pd->result = ft_strjoin(pd->result, pd->helper);
}

static void handle_assignment(char *str, t_pd *pd)
{
    pd->start = pd->i;
    while (str[pd->i] && str[pd->i] != ' ')
        pd->i++;
    pd->helper = ft_substr(str, pd->start, pd->i - pd->start);
    pd->helper = join_in_dqout(pd->helper);
    pd->result = ft_strjoin(pd->result, pd->helper);
}

static void handle_env_with_spaces(t_pd *pd)
{
    pd->sp = 0;
    while (pd->env_val[pd->sp] && pd->env_val[pd->sp] != ' ')
        pd->sp++;
    if (pd->sp > 0)
    {
        pd->first = ft_substr(pd->env_val, 0, pd->sp);
        pd->result = ft_strjoin(pd->result, pd->first);
        ft_lstadd_back(&pd->tmp, fill_node(ft_strdup(pd->result), T_WORD, 1));
        pd->result = ft_strdup("\0");
    }
    if (pd->env_val[pd->sp] != '\0')
    {
        if (pd->result[0] != '\0')
            ft_lstadd_back(&pd->tmp, fill_node(pd->result, T_WORD, 0));
        join_lists(&pd->tmp, split_cmd(pd->env_val + pd->sp, 1));
        pd->result = ft_strdup("");
    }
}

static void handle_env_variable(char *str, t_pd *pd, t_env *lst)
{
    pd->start = ++pd->i;
    while (ft_isalnum(str[pd->i]) || (str[pd->i] == '_' || str[pd->i] == '?'))
        pd->i++;
    pd->env_name = ft_substr(str, pd->start, pd->i - pd->start);
    pd->env_val = ft_getenv(pd->env_name, lst);
    if (pd->env_val)
    {
        if (check_space(pd->env_val))
            handle_env_with_spaces(pd);
        else
            pd->result = ft_strjoin(pd->result, ft_strdup(pd->env_val));
    }
}

static void handle_dollar_quote(char *str, t_pd *pd)
{
    pd->i++;
    pd->helper = extract_quoted_substring(str, &pd->i, str[pd->i]);
    pd->result = ft_strjoin(pd->result, pd->helper);
}
int get_last_node_content(t_list *head)
{
    if (head == NULL)
        return 1;

    t_list *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    return ft_strcmp(current->content,"export");
}

t_list *process_node_content2(char *str, t_env *lst,int flag)
{
    t_pd pd;

    init_pd(&pd);
    while (str[pd.i])
    {
        if (str[pd.i] == '"' || str[pd.i] == '\'')
            handle_quoted_string(str, &pd);
        else if (str[pd.i] == '=' && str[pd.i + 1] != ' ' && flag == 0)
            handle_assignment(str, &pd);
        else if (str[pd.i] == '$' && (ft_isalpha(str[pd.i + 1]) || 
                (str[pd.i + 1] == '_' || str[pd.i + 1] == '?')))
            handle_env_variable(str, &pd, lst);
        else if (str[pd.i] == '$' && str[pd.i + 1] == '\'')
            handle_dollar_quote(str, &pd);
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
			st.processed = process_node_content2(st.current->content,env,get_last_node_content(st.tmp));
			join_lists(&st.tmp, st.processed);
		}
		st.current = st.current->next;
	}
	return (st.tmp);
}
