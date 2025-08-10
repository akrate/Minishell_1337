/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:26:11 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/10 15:30:41 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static void init_qouts(t_qout *strc)
{
    strc->i = 0;
    strc->in_quote = 0;
    strc->quote_char = 0;
    strc->result = ft_strdup("");
    strc->tmp = NULL;
}

char *skip_qouts(char *str, int rm_qu)
{
    t_qout qout;

    if (rm_qu == 1)
        return (str);
    init_qouts(&qout);
    while (str[qout.i])
    {
        if ((str[qout.i] == '"' || str[qout.i] == '\'') && qout.in_quote == 0)
        {
            qout.in_quote = 1;
            qout.quote_char = str[qout.i];
            qout.i++;
            continue;
        }
        if (str[qout.i] == qout.quote_char && qout.in_quote == 1)
        {
            qout.in_quote = 0;
            qout.quote_char = 0;
            qout.i++;
            continue;
        }
        if (str[qout.i] == '$' && str[qout.i + 1] == '"')
        {
            qout.i++;
            continue;
        }
        qout.result = ft_strjoin(qout.result, ft_substr(str, qout.i, 1));
        qout.i++;
    }
    return (qout.result);
}

int	is_redirection(t_token_type type)
{
	if (type == T_DGREAT || type == T_GREAT || type == T_HEREDOC
		|| type == T_LESS)
		return (1);
	return (0);
}

int	checking_cmd(t_list **list,t_env **env)
{
	t_list	*lst;
	lst = *list;
	while (lst)
	{
		if (checking_close_qoutes(lst->content) == 1)
		{
			write(2, "Error: unclosed quotes found\n", 29);
            check_env("?=","2",*env);
			return (1);
		}
		if (is_redirection(lst->type) && (!lst->next
				|| lst->next->type != T_WORD))
		{
			write(2, "Error: command must end with identifier\n", 41);
            check_env("?=","2",*env);
            return (1);
		}
		if ((*list)->type == T_PIPE || (lst->type == T_PIPE && (!lst->next
					|| lst->next->type == T_PIPE)))
		{
			write(2, "Error: command must end with identifier\n", 41);
            check_env("?=","2",*env);
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}
