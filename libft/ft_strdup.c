/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:41:38 by aoussama          #+#    #+#             */
/*   Updated: 2025/07/30 15:02:33 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*copy;

	len = ft_strlen(s);
	i = 0;
	copy = (char *)ft_malloc(len + 1, &(set_get_data(NULL)->lst_gc_g));
	while (s[i] != '\0')
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
// int main()
// {
//  char o[] = "sallm";
//  char *p = ft_strdup(o);
//  if(p == NULL)
//   return (0);
//  printf("%s",p);
// }