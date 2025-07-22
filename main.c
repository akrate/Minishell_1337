/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:08:36 by aoussama          #+#    #+#             */
/*   Updated: 2025/07/22 12:12:46 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int check_empty_str(char *str)
// {
//     // int i;
//     if (ft_strlen(str) == 0)
//         return (1);
//     // while (str)
//     return (0);
// }
int main()
{
    char *cmd;

    while (1)
    {
        cmd = readline("<minishell> ");
		if (!cmd)
        {
            printf("exit\n");
            break;
        }
        if (*cmd)
        {
            
            add_history(cmd);
            paring_cmd(cmd);
        }
    }

    return 0;
}
