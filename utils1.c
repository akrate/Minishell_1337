/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:22:46 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/24 20:23:55 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lastlist(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	is_redirection(t_token_type type)
{
	if (type == T_DGREAT || type == T_GREAT || type == T_HEREDOC
		|| type == T_LESS)
		return (1);
	return (0);
}

int	checking_cmd(t_list **list, t_env **env)
{
	t_list	*lst;

	lst = *list;
	while (lst)
	{
		if (checking_close_qoutes(lst->content) == 1)
		{
			write(2, "Error: unclosed quotes found\n", 29);
			return (check_env("?=", "2", *env), 1);
		}
		if (is_redirection(lst->type) && (!lst->next
				|| lst->next->type != T_WORD))
		{
			write(2, "Error: command must end with identifier\n", 41);
			return (check_env("?=", "2", *env), 1);
		}
		if ((*list)->type == T_PIPE || (lst->type == T_PIPE && (!lst->next
					|| lst->next->type == T_PIPE)))
		{
			write(2, "Error: command must end with identifier\n", 41);
			return (check_env("?=", "2", *env), 1);
		}
		lst = lst->next;
	}
	return (0);
}
