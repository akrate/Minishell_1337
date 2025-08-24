/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:08:36 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/24 16:34:06 by aoussama         ###   ########.fr       */
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

t_env	*set_get_env(t_env *p)
{
	static t_env	*ptr;

	if (p)
		ptr = p;
	return (ptr);
}

void	sigint_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	check_env("?=", "130", set_get_env(NULL));
}

int	main(int ac, char **av, char **env)
{
	char	*cmd;
	t_data	data;
	t_env	*lst;

	(void)ac;
	(void)av;
	lst = NULL;
	data.lst_gc_env = NULL;
	data.lst_gc_g = NULL;
	set_get_data(&data);
	lst = copy_env(env);
	set_get_env(lst);
	free_garbage(&data.lst_gc_g);
	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		data.lst_gc_g = NULL;
		set_get_data(&data);
		cmd = readline("<minishell> ");
		if (!cmd)
			break ;
		if (*cmd)
		{
			add_history(cmd);
			paring_cmd(cmd, &lst);
		}
		free_garbage(&data.lst_gc_g);
	}
	ft_exit(NULL, lst);
}
