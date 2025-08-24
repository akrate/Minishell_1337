/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:28:25 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/24 19:57:36 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var_name(char *var)
{
	int	j;

	j = 0;
	srch(var, &j);
	return (ft_substr(var, 0, j));
}

static void	remove_env_var(t_env **env, t_env *curr, t_env *prev)
{
	if (prev)
		prev->next = curr->next;
	else
		*env = curr->next;
}

static void	find_and_remove_var(char *var_name, t_env **env)
{
	t_env	*curr;
	t_env	*prev;
	char	*str;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		str = get_var_name(curr->var);
		if (ft_strcmp(str, var_name) == 0)
		{
			remove_env_var(env, curr, prev);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	ft_unset(t_spcmd *lst, t_env **env)
{
	int	i;

	if (!lst->cmd[1])
		return ;
	i = 1;
	while (lst->cmd[i])
	{
		if (ft_strcmp(lst->cmd[i], "?") == 0)
		{
			i++;
			continue ;
		}
		find_and_remove_var(lst->cmd[i], env);
		i++;
	}
	check_env("?=", "0", *env);
}

static int	validate_cd_args(t_spcmd *lst, t_env **env)
{
	if (lst->cmd[2] != NULL)
	{
		printf("cd: too many arguments\n");
		check_env("?=", "1", *env);
		return (1);
	}
	return (0);
}

static int	change_directory(char *path, t_env **env)
{
	if (chdir(path) == -1)
	{
		perror("chdir");
		check_env("?=", "2", *env);
		return (1);
	}
	return (0);
}

static void	update_oldpwd(char *old_path, t_env **env)
{
	char	*tmp;

	if (old_path)
	{
		tmp = ft_strjoin("OLDPWD=", old_path);
		if (tmp)
			ft_export(tmp, env);
	}
}

static int	handle_getcwd_error(char *old_path, t_env **env)
{
	printf("cd: error retrieving current directory: getcwd: cannot ");
	printf("access parent directories: No such file or directory\n");
	check_env("?=", "1", *env);
	update_oldpwd(old_path, env);
	return (1);
}

static void	update_pwd_vars(char *new_path, char *old_path, t_env **env)
{
	char	*tmp;

	update_oldpwd(old_path, env);
	tmp = ft_strjoin("PWD=", new_path);
	if (tmp)
		ft_export(tmp, env);
}

void	ft_cd(t_spcmd *lst, t_env **env)
{
	char	*path_nw;
	char	*path_old;

	path_nw = NULL;
	path_old = NULL;
	path_old = getcwd(NULL, 0);
	if (validate_cd_args(lst, env) == 1)
		return ;
	if (change_directory(lst->cmd[1], env) == 1)
		return ;
	path_nw = getcwd(NULL, 0);
	if (!path_nw)
	{
		if (handle_getcwd_error(path_old, env) == 1)
			return ;
	}
	update_pwd_vars(path_nw, path_old, env);
	check_env("?=", "0", *env);
}
