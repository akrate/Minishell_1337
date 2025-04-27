/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:23:13 by aoussama          #+#    #+#             */
/*   Updated: 2025/04/27 17:52:36 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstadd_back(t_list **lst, t_list *new)
{
    t_list *tmp;
	if (!lst || !new)
		return (1);
	new->next = NULL;

	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		tmp = *lst;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}
int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
void ft_lstclear(t_list **lst)
{
    t_list *current;
    t_list *next;

    if (!lst)
        return;
    current = *lst;

    while (current)
    {
        next = current->next;
        free(current->content);
        free(current);
        current = next;
    }

    *lst = NULL;
}