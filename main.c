/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:08:36 by aoussama          #+#    #+#             */
/*   Updated: 2025/04/21 18:10:10 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cheking_doubleqoutes(char *str)
{
	int i;
	int count;
	int pos; 
	pos = 0;
	count = 0;
	i = 0;

	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			if (pos == 0)
				pos = i;
			if (str[i - 1] != 92 && str[pos] == str[i])
				count++;
		}
		i++;
	}
	if (count % 2 == 0)
		return (0);
	else
		return (1);
	
}
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
		if (cheking_doubleqoutes(cmd) == 1)
		{
			printf("sd qoutes asahbi\n");
		}
        if (*cmd)
            add_history(cmd);
    }

    return 0;
}
