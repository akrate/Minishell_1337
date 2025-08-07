/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:44:39 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/07 16:51:09 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup_env(const char *s)
{
	size_t	len;
	size_t	i;
	char	*copy;

	len = ft_strlen(s);
	i = 0;
	copy = (char *)ft_malloc(len + 1, &(set_get_data(NULL)->lst_gc_env));
	while (s[i] != '\0')
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

t_env *ft_env_new(char *var,char *val)
{
    t_env *new;

    new = ft_malloc(sizeof(t_env),&(set_get_data(NULL)->lst_gc_env));
    new->var = ft_strdup_env(var);
    new->val = ft_strdup_env(val);
    new->next = NULL;
    return (new);
}
void ft_env_add_back(t_env **head, t_env *new_node)
{
    t_env *temp;

    if (!head || !new_node)
        return;

    if (*head == NULL)
    {
        *head = new_node;
        return;
    }

    temp = *head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = new_node;
}

void srch(char *str, int *i)
{
    while (str[*i])
    {
        if (str[*i] == '=')
            break;
        (*i)++;
    }
}

t_env *copy_env(char **str)
{
    int i;
    int j;
    char *val;
    char *var;
    t_env *lst;

    lst = NULL;
    j = 0;
    while (str[j])
    {
        i = 0;
        var = NULL;
        val = NULL;
        srch(str[j], &i);
        var = ft_substr(str[j], 0, i);
        if (str[j][i] == '=')
            val = ft_substr(str[j], i + 1, ft_strlen(str[j]) - i - 1);
        else
            val = ft_strdup("");
        ft_env_add_back(&lst, ft_env_new(var, val));
        j++;
    }
    return lst;
}
