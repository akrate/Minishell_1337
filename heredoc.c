/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:33:22 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/16 15:01:05 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_delimiter(const char *line, const char *delimiter)
{
	int len_delim = ft_strlen(delimiter);
	int len_line = ft_strlen(line);

	if (len_line != len_delim)
		return (0);
	return (ft_strncmp(line, delimiter, len_delim) == 0);
}
// char *create_rn(char *str)
// {
// 	int i;
// 	char *file;
// 	i = 0;
// 	while (1)
// 	{
// 		file = ft_strjoin(str,ft_itoa(i));
// 		if (access(file,F_OK) != 0)
// 			break;
// 		i++;
// 	}
// 	return (file);
// }

static char *open_rd_file()
{
    char *str = "heredoc";
    int i = 0;
    int fd;
    char *file;

    while (1)
    {
        file = ft_strjoin(ft_itoa(i), str);
        fd = open(file, O_RDONLY);
        if (fd == -1)
        {
            if (errno == ENOENT)
                break;
            else
            {
                i++;
                continue;
            }
        }
        close(fd);
        i++;
    }
    return file;
}
char *heredoc(const char *delimiter)
{
	int		i;
	char	buf[MAX_LINE + 1];
	int		fd;
	char	*file;
	int		nbred;

	file = open_rd_file();
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (write(2, "ERROR : Failed to open file\n", 28),NULL);
	while (1)
	{
		write(1, "> ", 2);
		i = 0;
		while ((nbred = read(0, &buf[i], 1)) > 0 && buf[i] != '\n' && i < MAX_LINE)
			i++;
		if (nbred <= 0)
			break;
		buf[i] = 0;
		if (is_delimiter(buf, delimiter))
			break;
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
	}
	close(fd);
	return (file);
}
