/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:08:36 by aoussama          #+#    #+#             */
/*   Updated: 2025/04/22 14:25:31 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

void init_shell(t_shell *sh)
{
    sh->ap = NULL;
    sh->pipes = 0;
    sh->fds = NULL;
    sh->pid = NULL;
    sh->cmd = NULL;
}

int main()
{
    char *cmd;
    t_shell shell;
	// char *pwd = getcwd(NULL,0); ktjib path li kyn fiha;
	// printf("%s\n",pwd);
    while (1)
    {
        init_shell(&shell);
        cmd = readline("<minishell> ");
		if (!cmd)
        {
            printf("exit\n");
            break;
        }
		// if (cheking_doubleqoutes(cmd) == 1)
		// {
            // 	printf("sd qoutes asahbi\n");
            // }
            if (*cmd)
            add_history(cmd);
         //paring_cmd(cmd);
        shell.ap = ft_split(cmd, '|');
        if(shell.ap == NULL || shell.ap[0] == NULL)
        {
            execute_cmd(&shell);
        }
    }
    return 0;
}
