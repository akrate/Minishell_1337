/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:28:39 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/07 20:53:43 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int check_env(char *var,char *val,t_env *lst)
// {
//     while (lst)
//     {
//         if (ft_strcmp(var,lst->var) == 0)
//         {
//             lst->val = ft_strdup_env(val);
//             return (1);
//         }
//         lst = lst->next;
//     }
//     return (0);
// }
char *ft_getenv(char *str,t_env *lst)
{
    char *result;
    
    while (lst)
    {
        if (ft_strcmp(str,lst->var) == 0)
        {
            result = ft_strdup(lst->val);
            return (result);
        }
        lst = lst->next;
    }
    result = ft_strdup("");
    return (result);
}