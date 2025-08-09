/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exuction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:27:51 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/09 11:13:57 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_spcmd_nodes(t_spcmd *head)
{
	int count = 0;

	while (head)
	{
		count++;
		head = head->next;
	}
	return count;
}
int is_built_in(char *str)
{
    if (ft_strcmp(str,"echo") == 0)
        return (1);
    else if (ft_strcmp(str,"cd") == 0)
        return (1);
    else if (ft_strcmp(str,"pwd") == 0)
        return (1);
    else if (ft_strcmp(str,"export") == 0)
        return (1);
    else if (ft_strcmp(str,"unset") == 0)
        return (1);
    else if (ft_strcmp(str,"env") == 0)
        return (1);
    else if (ft_strcmp(str,"exit") == 0)
        return (1);
    return (0);
}
void print_env(t_env *env)
{
    while (env)
    {
        if (env->val[0] != '\0' || ft_strchr(env->var,'=') != NULL)
            printf("%s%s\n",env->var,env->val);
        env = env->next;
    }
}
void printf_pwd(void)
{
    char *str;

    str = getcwd(NULL,0);
    printf("%s\n",str);
    free (str);
}

void ex_echo(t_spcmd *lst)
{
    int i;
    int option = 0;
    
    i = 1;
    if (lst->cmd[1] == NULL)
    {
        printf("\n");
        return;
    }
    if(ft_strcmp(lst->cmd[1], "-n") == 0)
    {
        option = 1;
        i++;   
    }
    while (lst->cmd[i])
    {
        printf("%s",lst->cmd[i]);
        if (lst->cmd[i + 1] != NULL)
            printf(" ");
        i++;
    }
    if(option == 0)
        printf("\n");
}
int ex_built_in(t_spcmd *lst,t_env **env)
{
    if (ft_strcmp(lst->cmd[0],"echo") == 0)
        ex_echo(lst);
    else if (ft_strcmp(lst->cmd[0],"cd") == 0)
        ft_cd(lst,env);
    else if (ft_strcmp(lst->cmd[0],"pwd") == 0)
        printf_pwd();
    else if (ft_strcmp(lst->cmd[0],"export") == 0)
        ft_export_hp(lst,env);
    else if (ft_strcmp(lst->cmd[0],"unset") == 0)
        ft_unset(lst,env);
    else if (ft_strcmp(lst->cmd[0],"env") == 0)
        print_env(*env);
    else if (ft_strcmp(lst->cmd[0],"exit") == 0)
        exit(0);
    return (0);
}
void ft_exuction(t_spcmd *list,t_env **env)
{
    if (count_spcmd_nodes(list) == 1 && list->redir == NULL)
    {
        if (is_built_in(list->cmd[0]) == 1)
        {
            ex_built_in(list,env);
        }
    }
}