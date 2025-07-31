/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:23:13 by aoussama          #+#    #+#             */
/*   Updated: 2025/07/30 22:43:38 by aoussama         ###   ########.fr       */
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
        // free(current->content);
        // free(current);
        current = next;
    }
    *lst = NULL;
}
// void ft_lstclear_dolar(t_list **lst,char **tmp)
// {
//     t_list *current;
//     t_list *next;

//     if (!lst)
//         return;
//     current = *lst;

//     while (current)
//     {
//         next = current->next;
//         // free(current->content);
//         // free(current);
//         current = next;
//     }
//     // free_split(tmp);
//     *lst = NULL;
// }
t_list *fill_node(char *content,t_token_type t_type,int rm_qu)
{
    t_list	*node;
    t_data *data;

    data = set_get_data(NULL);
	node = (t_list *)ft_malloc(sizeof(t_list), &(data->lst_gc_g));
	node->content = content;
    node->type = t_type;
    node->remove_qoute = rm_qu;
	node->next = NULL;
	return (node);
}

int checking_close_qoutes(char *str)
{
    int i = 0;
    int d = 0;
    char c;

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
                break;
            }
            i++;
        }
        if (str[i])
            i++;
    }
    return d;
}

t_list *ft_lastlist(t_list *lst)
{
    if (!lst)
        return NULL;

    while (lst->next)
        lst = lst->next;

    return lst;
}