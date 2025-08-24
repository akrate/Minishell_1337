/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 22:22:23 by aoussama          #+#    #+#             */
/*   Updated: 2025/07/30 14:41:45 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	lens;
	size_t	i;
	char	*res;

	if (!s)
		return (NULL);
	lens = ft_strlen(s);
	i = 0;
	res = (char *)ft_malloc((lens + 1) * sizeof(char),
			&(set_get_data(NULL)->lst_gc_g));
	if (res == NULL)
		return (NULL);
	while (s[i])
	{
		res[i] = (*f)(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
