/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:08:36 by aoussama          #+#    #+#             */
/*   Updated: 2025/04/29 18:15:48 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/////getenv 9ad li founction nhandli $ ??????????

int main()
{
    char *cmd;
    t_list *cmd_list = NULL;

    while (1)
    {
        cmd = readline("<minishell> ");
        if (!cmd)
        {
            printf("exit\n");
            break;
        }

        cmd_list = paring_cmd(cmd);
        
        if (cmd_list)
        {
            t_cmd_exec *cmd_exec = create_cmd_exec(cmd_list);
            
            if (cmd_exec)
            {
                signal_exec(cmd_exec);
            }
        }
        if (*cmd)
            add_history(cmd);
    }

    return 0;
}

