/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:08:36 by aoussama          #+#    #+#             */
/*   Updated: 2025/07/31 22:18:08 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*set_get_data(void *p)
{
	static t_data	*ptr;

	if (p)
		ptr = p;
	return (ptr);
}
int check_empty_str(char *str)
{
    int i;
    if (ft_strlen(str) == 0)
        return (1);
    while (str[i])
	{
		if (str[i] != ' ')
			return(0);
	}
    return (1);
}
int	main(void)
{
	char	*cmd;
	t_data	data;

	data.lst_gc_env = NULL;
	while (1)
	{
		data.lst_gc_g = NULL;
		set_get_data(&data);
		cmd = readline("<minishell> ");
		if (!cmd)
		{
			printf("exit\n");
			break ;
		}
		if (*cmd)
		{
			add_history(cmd);
			paring_cmd(cmd);
		}
		free_garbage(&data.lst_gc_g);
	}
	free_garbage(&data.lst_gc_g);
	free_garbage(&data.lst_gc_env);
	return (0);
}
