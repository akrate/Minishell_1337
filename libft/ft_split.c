/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:13:24 by aoussama          #+#    #+#             */
/*   Updated: 2025/07/30 14:46:07 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(const char *s, char c)
{
	int	i;
	int	count;
	int	word;

	i = 0;
	count = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			count = 0;
		}
		else if (count == 0)
		{
			word++;
			count = 1;
		}
		i++;
	}
	return (word);
}

static char	*str_d(const char *s, int start, int finish)
{
	char	*result;
	int		i;

	result = (char *)ft_malloc((finish - start + 1) * sizeof(char), &(set_get_data(NULL)->lst_gc_g));
	if (result == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (start < finish)
	{
		result[i] = s[start];
		i++;
		start++;
	}
	result[i] = '\0';
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		j;
	int		start;

	if (s == NULL)
		return (NULL);
	result = (char **)ft_malloc((count_word(s, c) + 1) * sizeof(char *), &(set_get_data(NULL)->lst_gc_g));
	if (result == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (start < i)
			result[j++] = str_d(s, start, i);
		if (result[j - 1] == NULL)
			return (NULL);
	}
	return (result[j] = NULL, result);
}
// int main()
// {
// 	char p[] = ",h";
// 	char **o = ft_split(p,',');
// 	int i = 0;
// 	if (o == NULL){
// 		printf("bbbb\n");
// 		return (0);
// 	}
// 	while (o[i])
// 	{
// 		printf("%s$\n",o[i]);
// 		i++;
// 	}
// }