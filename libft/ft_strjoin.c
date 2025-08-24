/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:45:44 by aoussama          #+#    #+#             */
/*   Updated: 2025/07/30 14:41:31 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*reslt;
	size_t	j;

	if (!s1)
		return (NULL);
	j = ft_strlen(s1) + ft_strlen(s2);
	reslt = (char *)ft_malloc((j + 1) * sizeof(char),
			&(set_get_data(NULL)->lst_gc_g));
	if (reslt == NULL)
		return (NULL);
	ft_strlcpy(reslt, s1, ft_strlen(s1) + 1);
	ft_strlcat(reslt, s2, j + 1);
	return (reslt);
}
