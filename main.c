/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:08:36 by aoussama          #+#    #+#             */
/*   Updated: 2025/07/16 11:41:40 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/////getenv 9ad li founction nhandli $ ??????????

int main()
{
    char *cmd;
	// char *pwd = getcwd(NULL,0); ktjib path li kyn fiha;
    // paring_cmd("l shello \"jksgdfkjd\" ");
	// printf("%s\n",pwd);
    // printf("HOME=%s\n", getenv("HOME"));

    while (1)
    {
        cmd = readline("<minishell> ");
		if (!cmd)
        {
            printf("exit\n");
            break;
        }
        paring_cmd(cmd);
        // printf("%s\n",skip_qouts(cmd));
        if (*cmd)
            add_history(cmd);
    }

    return 0;
}
