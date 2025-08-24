/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exuction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:27:51 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/22 16:00:36 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_spcmd_nodes(t_spcmd *head)
{
	int	count;

	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	if (count == 0)
		check_env("?=", "0", set_get_env(NULL));
	return (count);
}
int	is_built_in(char *str)
{
	if (!str)
		return (0);
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	else if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(str, "export") == 0)
		return (1);
	else if (ft_strcmp(str, "unset") == 0)
		return (1);
	else if (ft_strcmp(str, "env") == 0)
		return (1);
	else if (ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

void	print_env(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->var, "?=") != 0)
		{
			if (env->val[0] != '\0' || ft_strchr(env->var, '=') != NULL)
				printf("%s%s\n", env->var, env->val);
		}
		env = env->next;
	}
	check_env("?=", "0", env);
}
char	*get_env_value(const char *key, t_env *env)
{
	size_t	len;

	len = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(env->var, key, len) == 0 && env->var[len] == '=')
			return (env->val);
		env = env->next;
	}
	return (NULL);
}
void	update_env(const char *key, const char *value, t_env *env)
{
	t_env	*new;

	while (env)
	{
		if (ft_strcmp(env->var, key) == 0)
		{
			free(env->val);
			env->val = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
	new = ft_malloc(sizeof(t_env), &set_get_data(NULL)->lst_gc_g);
	new->var = ft_strdup(key);
	new->val = ft_strdup(value);
	new->next = NULL;
}

void	printf_pwd(t_env *env)
{
	char	*str;
	char	*pwd_env;

	str = getcwd(NULL, 0);
	if (str)
	{
		printf("%s\n", str);
		update_env("PWD", str, env);
		free(str);
	}
	else
	{
		pwd_env = get_env_value("PWD", env);
		if (pwd_env)
			printf("%s\n", pwd_env);
		else
			printf("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
	}
	check_env("?=", "0", env);
}

void	ex_echo(t_spcmd *lst, t_env *env)
{
	int	i;
	int	option;

	option = 0;
	i = 1;
	if (lst->cmd[1] == NULL)
	{
		printf("\n");
		check_env("?=", "0", env);
		return ;
	}
	if (ft_strcmp(lst->cmd[1], "-n") == 0)
	{
		option = 1;
		i++;
	}
	while (lst->cmd[i])
	{
		printf("%s", lst->cmd[i]);
		if (lst->cmd[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (option == 0)
		printf("\n");
	check_env("?=", "0", env);
}
int	check_nber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
int	is_numeric(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	for (; str[i]; i++)
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}

void	ft_exit(char **cmd, t_env *env)
{
	char		*str;
	long long	exit_val;
	char		*endptr;
	int			exit_code;

	printf("exit\n");
	if (cmd == NULL || cmd[1] == NULL)
	{
		str = ft_getenv("?", env);
		if (!str)
			exit_val = 0;
		else
			exit_val = ft_atoi(str);
	}
	else if (cmd[2] != NULL)
	{
		printf("exit: too many arguments\n");
		exit_val = 1;
	}
	else
	{
		errno = 0;
		exit_val = strtoll(cmd[1], &endptr, 10);
		if (!is_numeric(cmd[1]) || *endptr != '\0' || errno == ERANGE)
		{
			printf("exit: %s: numeric argument required\n", cmd[1]);
			exit_val = 2;
		}
	}
	exit_code = (int)(exit_val % 256);
	if (exit_code < 0)
		exit_code += 256;
	free_garbage(&(set_get_data(NULL)->lst_gc_env));
	free_garbage(&(set_get_data(NULL)->lst_gc_g));
	exit(exit_code);
}
int	ex_built_in(t_spcmd *lst, t_env **env)
{
	if (ft_strcmp(lst->cmd[0], "echo") == 0)
		ex_echo(lst, *env);
	else if (ft_strcmp(lst->cmd[0], "cd") == 0)
		ft_cd(lst, env);
	else if (ft_strcmp(lst->cmd[0], "pwd") == 0)
		printf_pwd(*env);
	else if (ft_strcmp(lst->cmd[0], "export") == 0)
		ft_export_hp(lst, env);
	else if (ft_strcmp(lst->cmd[0], "unset") == 0)
		ft_unset(lst, env);
	else if (ft_strcmp(lst->cmd[0], "env") == 0)
		print_env(*env);
	else if (ft_strcmp(lst->cmd[0], "exit") == 0)
		ft_exit(lst->cmd, *env);
	return (0);
}

int	env_len(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	*str_join_var_val(t_env *env)
{
	char	*tmp;

	tmp = ft_strjoin(env->var, env->val);
	return (tmp);
}

char	**env_to_array(t_env *env)
{
	int		len;
	char	**envp;
	int		i;

	len = env_len(env);
	envp = ft_malloc(sizeof(char *) * (len + 1), &set_get_data(NULL)->lst_gc_g);
	i = 0;
	while (env)
	{
		envp[i] = str_join_var_val(env);
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, s3);
	return (res);
}
void	update_exit_status(t_env *env, int status)
{
	char	*exit_code;

	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else
		status = 1;
	exit_code = ft_itoa(status);
	check_env("?=", exit_code, env);
}

char	*get_cmd_path(char *cmd, t_env *env)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	if (!cmd)
		return (NULL);
	path_env = ft_getenv("PATH", env);
	i = 0;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		full_path = ft_strjoin3(paths[i], "/", cmd);
		if (access(full_path, X_OK) == 0)
		{
			return (full_path);
		}
		i++;
	}
	return (NULL);
}
void	execute_external(t_spcmd *lst, t_env *env)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;
	char	**envp;
	char	*path_env;

	path_env = ft_getenv("PATH", env);
	if (!lst || !lst->cmd || !lst->cmd[0])
	{
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		cmd_path = get_cmd_path(lst->cmd[0], env);
		if (ft_strcmp(lst->cmd[0], "sudo") == 0)
		{
			printf("minishell: sudo: Permission denied\n");
			free(cmd_path);
			exit(126);
		}
		if (!cmd_path)
		{
			if (ft_strchr(lst->cmd[0], '/'))
			{
				if (access(lst->cmd[0], F_OK) == 0)
					printf("minishell: %s: Permission denied\n", lst->cmd[0]);
				else
					printf("minishell: %s: No such file or directory\n",
						lst->cmd[0]);
			}
			else if (!path_env || path_env[0] == '\0')
			{
				printf("minishell: %s: No such file or directory\n",
					lst->cmd[0]);
			}
			else
			{
				printf("minishell: %s: command not found\n", lst->cmd[0]);
			}
			free_garbage(&set_get_data(NULL)->lst_gc_env);
			free_garbage(&set_get_data(NULL)->lst_gc_g);
			exit(127);
		}
		if (access(cmd_path, X_OK) != 0)
		{
			printf("minishell: %s: Permission denied\n", lst->cmd[0]);
			exit(126);
		}
		envp = env_to_array(env);
		execve(cmd_path, lst->cmd, envp);
		perror("execve");
		free_garbage(&set_get_data(NULL)->lst_gc_env);
		free_garbage(&set_get_data(NULL)->lst_gc_g);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		waitpid(pid, &status, 0);
		update_exit_status(env, status);
	}
}

void	handle_redirections(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == T_GREAT)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror(redir->file);
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == T_DGREAT)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				perror(redir->file);
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == T_LESS || redir->type == T_HEREDOC)
		{
			fd = open(redir->file, O_RDONLY);
			if (fd < 0)
			{
				perror(redir->file);
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
}

void	execute_pipeline(t_spcmd *list, t_env *env)
{
	int		pipefd[2];
	pid_t	pid;
	int		fd_in;
	t_spcmd	*curr;
	int		cmd_count;
	int		i;
	pid_t	*pids;
	int		j;

	fd_in = 0;
	curr = list;
	cmd_count = count_spcmd_nodes(list);
	i = 0;
	pids = ft_malloc(sizeof(pid_t) * cmd_count, &set_get_data(NULL)->lst_gc_g);
	while (curr)
	{
		if (curr->next)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			pipefd[0] = -1;
			pipefd[1] = -1;
		}
		pid = fork();
		if (pid == 0)
		{
			if (fd_in != 0)
			{
				dup2(fd_in, STDIN_FILENO);
				close(fd_in);
			}
			if (curr->next)
			{
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[0]);
				close(pipefd[1]);
			}
			handle_redirections(curr->redir);
			if (is_built_in(curr->cmd[0]))
			{
				ex_built_in(curr, &env);
			}
			else
			{
				execute_external(curr, env);
			}
			free_garbage(&set_get_data(NULL)->lst_gc_g);
			free_garbage(&set_get_data(NULL)->lst_gc_env);
			exit(EXIT_SUCCESS);
		}
		else if (pid < 0)
		{
			perror("fork");
			free(pids);
			exit(EXIT_FAILURE);
		}
		if (fd_in != 0)
			close(fd_in);
		if (curr->next)
			close(pipefd[1]);
		fd_in = (curr->next) ? pipefd[0] : 0;
		pids[i++] = pid;
		curr = curr->next;
	}
	j = 0;
	while (j < cmd_count)
	{
		waitpid(pids[j], NULL, 0);
		j++;
	}
}
// int count_word(char **str)
// {
// int i;
// i = 0;
//
// printf("tesssssssst\n");
// while (*str)
// {
// i++;
// }
// return (str);
// }
//
void	ft_exuction(t_spcmd *list, t_env **env)
{
	// if (count_spcmd_nodes(list) == 0 && list->redir == NULL)
	// {
	//     printf("testttttttttt\n");
	//     // check_env("?=","0",*env);
	//     // return ;
	// }
	if (count_spcmd_nodes(list) == 1 && list->redir == NULL)
	{
		if (is_built_in(list->cmd[0]))
			ex_built_in(list, env);
		else
			execute_external(list, *env);
	}
	else
	{
		execute_pipeline(list, *env);
	}
}
