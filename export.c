/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:57:39 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/07 20:47:59 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strcmp(const char *s1, const char *s2)
{
    int i = 0;
    while (s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return ((unsigned char)s1[i] - (unsigned char)s2[i]);
        i++;
    }
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int check_env(char *var,char *val,t_env *lst)
{
    while (lst)
    {
        if (ft_strcmp(var,lst->var) == 0)
        {
            lst->val = ft_strdup_env(val);
            return (1);
        }
        lst = lst->next;
    }
    return (0);
}

void ft_export(char *str,t_env **env)
{
    int i;
    char *var;
    char *val;
    if (str == NULL)
    {
        print_env(*env);
        return ;
    }
    i = 0;
    srch(str,&i);
    var = ft_substr(str,0,i);
    if (str[i] == '=')
        val = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
    else
        val = ft_strdup("");
    if (check_env(var,val,*env) == 1)
    {
        return;
    }
    else 
    {  
        ft_env_add_back(env, ft_env_new(var, val));
    } 
}