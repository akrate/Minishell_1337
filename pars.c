/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:55:00 by aoussama          #+#    #+#             */
/*   Updated: 2025/04/24 20:41:18 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_list *split_cmd(char *str)
{
    int i;
    int b;
    int j;
    char c;
    t_list *head = NULL;
    if (!str)
        return (NULL);
    i = 0;
    b = 0;
    while (str[i])
    {
        if (str[i] == '"' || str[i] == '\'')
        {
            b = 1;
        }
        if (b == 1)
        {
            j = i;
            c = str[i++];
            while (str[i] != c)
                i++;
        }
        else
        {
            
        }
        
    }
}

void paring_cmd(char *cmd)
{
    t_list *args = split_cmd(cmd);
    
    t_list *tmp = args;
    while (tmp)
    {
        printf("arg: %s\n", (char *)tmp->content);
        tmp = tmp->next;
    }
}
