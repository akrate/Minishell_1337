/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:28:25 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/09 13:30:37 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_unset(t_spcmd *lst, t_env **env)
{
    t_env *curr;
    t_env *prev;
    char *str;
    int j;
    int i;

    if (!lst->cmd[1])
        return;
    i = 1;
    while (lst->cmd[i])
    {
        curr = *env;
        prev = NULL;
        while (curr)
        {
            j = 0;
            srch(curr->var,&j);
            str = ft_substr(curr->var,0,j);
            if (ft_strcmp(str, lst->cmd[i]) == 0)
            {
                if (prev)
                prev->next = curr->next;
                else
                *env = curr->next;
                break;
            }
            prev = curr;
            curr = curr->next;
        }
        i++;
    }
}

void ft_cd(t_spcmd *lst,t_env **env)
{
    char *path_nw;
    char *path_old;
    
    (void)env;
    path_old = getcwd(NULL,0);
    if (lst->cmd[2] != NULL)
    {
        printf("cd: too many arguments\n");
        return;
    }
    if (chdir(lst->cmd[1]) == -1)
    {
        perror("chdir");
        return ;
    }
    path_nw = getcwd(NULL,0);
    ft_export(ft_strjoin("OLDPWD=",path_old),env);
    ft_export(ft_strjoin("PWD=",path_nw),env);
    free (path_nw);
    free (path_old);
}
