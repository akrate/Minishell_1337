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


int main()
{
    char *cmd;
	// char *pwd = getcwd(NULL,0); ktjib path li kyn fiha;
	// printf("%s\n",pwd);
    while (1)
    {
        cmd = readline("<minishell> ");
		if (!cmd)
        {
            printf("exit\n");
            break;
        }
        paring_cmd(cmd);
		// if (cheking_doubleqoutes(cmd) == 1)
		// {
		// 	printf("sd qoutes asahbi\n");
		// }
        if (*cmd)
            add_history(cmd);
    }

    return 0;
}
