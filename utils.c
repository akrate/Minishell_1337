/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:23:13 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/24 20:23:06 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!lst || !new)
		return (1);
	new->next = NULL;
	if (*lst == NULL)
		*lst = new;
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

t_list	*fill_node(char *content, t_token_type t_type, int rm_qu)
{
	t_list	*node;
	t_data	*data;

	data = set_get_data(NULL);
	node = (t_list *)ft_malloc(sizeof(t_list), &(data->lst_gc_g));
	node->content = content;
	node->type = t_type;
	node->remove_qoute = rm_qu;
	node->next = NULL;
	return (node);
}

static void	init_close(int *i, int *d)
{
	*i = 0;
	*d = 0;
}

int	checking_close_qoutes(char *str)
{
	int		i;
	int		d;
	char	c;

	init_close(&i, &d);
	while (str[i])
	{
		if (d == 0 && (str[i] == '\'' || str[i] == '"'))
		{
			c = str[i++];
			d = 1;
		}
		while (str[i] && d != 0)
		{
			if (str[i] == c)
			{
				d = 0;
				break ;
			}
			i++;
		}
		if (str[i])
			i++;
	}
	return (d);
}
