/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:23:13 by aoussama          #+#    #+#             */
/*   Updated: 2025/04/26 18:42:54 by aoussama         ###   ########.fr       */
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

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*copy;

	len = ft_strlen(s);
	i = 0;
	copy = (char *)malloc(len + 1);
	if (copy == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}
t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
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
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*copy;

	len = ft_strlen(s);
	i = 0;
	copy = (char *)malloc(len + 1);
	if (copy == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*res;
	size_t			s_len;
	size_t			lend;

	if (!s)
		return (NULL);
	i = 0;
	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	if (len < s_len - start)
		lend = len;
	else
		lend = s_len - start;
	res = (char *)malloc((lend + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (i < lend)
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}