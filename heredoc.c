/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:33:22 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/24 20:03:04 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*checking_dolar_doc(char *str, t_env *env)
{
	t_dolar	dolar;

	init_dolar(&dolar);
	while (str[dolar.i])
	{
		if (str[dolar.i] == '$')
			handle_dolar(&dolar, str, env);
		else
		{
			dolar.result = ft_strjoin(dolar.result, ft_substr(str, dolar.i, 1));
			dolar.i++;
		}
	}
	return (dolar.result);
}

static int	is_delimiter(const char *line, const char *delimiter)
{
	int	len_delim;
	int	len_line;

	len_delim = strlen(delimiter);
	len_line = strlen(line);
	if (len_line != len_delim)
		return (0);
	return (strncmp(line, delimiter, len_delim) == 0);
}

static char	*open_rd_file(void)
{
	char	*str;
	int		i;
	int		fd;
	char	*file;

	str = "heredoc";
	i = 0;
	while (1)
	{
		file = ft_strjoin(ft_itoa(i), str);
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			if (errno == ENOENT)
				break ;
			else
			{
				i++;
				continue ;
			}
		}
		close(fd);
		i++;
	}
	return (file);
}

void	handle_sigint_heredoc(int sig)
{
	int	fd;

	(void)sig;
	free_garbage(&set_get_data(NULL)->lst_gc_env);
	free_garbage(&set_get_data(NULL)->lst_gc_g);
	write(1, "\n", 1);
	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
	exit(130);
}

int	in_qout(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

char	*heredoc(char *str)
{
	pid_t	pid;
	char	*file;
	char	*line;
	char	*delimiter;
	char	*helper;
	int		flag;
	int		fd;
	int		wstatus;
	int		status;

	file = open_rd_file();
	delimiter = skip_qouts(str, 0);
	flag = in_qout(str);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (NULL);
	}
	if (pid == 0)
	{
		signal(SIGINT, handle_sigint_heredoc);
		signal(SIGQUIT, SIG_IGN);
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("open");
			exit(1);
		}
		while (1)
		{
			line = readline("> ");
			if (!line)
				break ;
			if (is_delimiter(line, delimiter))
				break ;
			if (flag == 0)
			{
				helper = checking_dolar_doc(line, set_get_env(NULL));
				write(fd, helper, ft_strlen(helper));
			}
			else
				write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
		close(fd);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &wstatus, 0);
		status = WEXITSTATUS(wstatus);
		if (status == 130 || status == 1)
		{
			check_env("?=", "130", set_get_env(NULL));
			unlink(file);
			return (NULL);
		}
		return (file);
	}
}
