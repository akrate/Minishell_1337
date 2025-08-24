/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 09:56:09 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/20 14:20:18 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	void	*res;

	i = nmemb * size;
	res = (void *)ft_malloc(i, &set_get_data(NULL)->lst_gc_g);
	ft_bzero(res, i);
	return (res);
}
