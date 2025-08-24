/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:28:39 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/24 20:01:44 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *str, t_env *lst)
{
	char	*result;
	char	*var;
	int		i;

	while (lst)
	{
		i = 0;
		srch(lst->var, &i);
		if (lst->var[i] == '=')
			var = ft_substr(lst->var, 0, i);
		else
			var = lst->var;
		if (ft_strcmp(str, var) == 0)
		{
			result = ft_strdup(lst->val);
			return (result);
		}
		lst = lst->next;
	}
	result = ft_strdup("");
	return (result);
}
