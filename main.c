/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:08:36 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/10 16:42:13 by aoussama         ###   ########.fr       */
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
// int check_empty_str(char *str)
// {
//     int i;
//     if (ft_strlen(str) == 0)
//         return (1);
// 	i = 0;
//     while (str[i])
// 	{
// 		if (str[i] != ' ')
// 			return(0);
// 		i++;
// 	}
//     return (1);
// }
int	main(int ac,char **av,char **env)
{
	char	*cmd;
	t_data	data;
	t_env *lst;
	(void)ac;
	(void)av;
	
	lst = NULL;
	data.lst_gc_env = NULL;
	data.lst_gc_g = NULL;
	set_get_data(&data);
	lst = copy_env(env);
	free_garbage(&data.lst_gc_g);
	while (1)
	{
		data.lst_gc_g = NULL;
		set_get_data(&data);
		cmd = readline("<minishell> ");
		if (!cmd)
			break ;
		if (*cmd)
		{
			add_history(cmd);
			paring_cmd(cmd,&lst);
		}
		free_garbage(&data.lst_gc_g);
	}
	ft_exit(lst);
}
