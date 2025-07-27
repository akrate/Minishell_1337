/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dolar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:37:05 by aoussama          #+#    #+#             */
/*   Updated: 2025/07/27 17:40:51 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_strjoin_free(char *s1, char *s2)
{
    char *joined;
    
    joined = ft_strjoin(s1, s2);
    free(s1);
    free(s2);
    return joined;
}
static int init_dolar(t_dolar *dolar)
{
    dolar->i = 0;
    dolar->start = 0;
    dolar->result = ft_strdup("");
    if (dolar->result == NULL)
        return (1);
    dolar->tmp = NULL;
    dolar->var_name = NULL;
    dolar->var_value = NULL;
    dolar->in_single_quote = 0;
    dolar->in_double_quote = 0;
    return (0);
}

// static int process_quotes(t_dolar *dolar, char *str)
// {
//     if (str[dolar->i] == '\'' && !dolar->in_double_quote)
//     {
//         dolar->in_single_quote = !dolar->in_single_quote;
//         dolar->result = ft_strjoin_free(dolar->result, ft_substr(str, dolar->i, 1));
//         if (dolar->result ==  NULL)
//             return (1);
//         dolar->i++;
//     }
//     else if (str[dolar->i] == '"' && !dolar->in_single_quote)
//     {
//         dolar->in_double_quote = !dolar->in_double_quote;
//         dolar->result = ft_strjoin_free(dolar->result, ft_substr(str, dolar->i, 1));
//         if (dolar->result ==  NULL)
//             return (1);
//         dolar->i++;
//     }
//     return (0);
// }

// static int process_dollar(t_dolar *dolar, char *str)
// {
//     if (!ft_isalnum(str[dolar->i + 1]))
//     {
        
//     }
//     return 0;
//     dolar->start = ++dolar->i;
//     while (str[dolar->i] && (ft_isalnum(str[dolar->i]) || str[dolar->i] == '_'))
//         dolar->i++;
//     dolar->var_name = ft_substr(str, dolar->start, dolar->i - dolar->start);
//     if (dolar->var_name == NULL)
//         return (2);
//     dolar->var_value = getenv(dolar->var_name);
//     free(dolar->var_name);
//     if (dolar->var_value)
//     {
//         dolar->result = ft_strjoin_free(dolar->result, ft_strdup(dolar->var_value));
//         if (dolar->result == NULL)
//             return (2);   
//     }
//     return 1;
// }

// char *checking_dolar(char *str)
// {
//     t_dolar dolar;

//     if (init_dolar(&dolar) == 1)
//         return (NULL);
//     while (str[dolar.i])
//     {
//         if ((str[dolar.i] == '\'' || str[dolar.i] == '"') && 
//             ((str[dolar.i] == '\'' && !dolar.in_double_quote) || 
//              (str[dolar.i] == '"' && !dolar.in_single_quote)))
//         {
//             if (process_quotes(&dolar, str) == 1)
//                 return (NULL);
//         }
//         else if (str[dolar.i] == '$' && !dolar.in_single_quote)
//         {
//             dolar.retu = process_dollar(&dolar, str);
//             if (dolar.retu == 0)
//                 return str;
//             else if (dolar.retu == 2)
//                 return (NULL);
//         }
//         else
//         {
//             dolar.result = ft_strjoin_free(dolar.result, ft_substr(str, dolar.i, 1));
//             if (dolar.result == NULL)
//                 return (NULL);
//             dolar.i++;
//         }
//     }
//     return dolar.result;
// }

char *checking_dolar(char *str)
{
    t_dolar dolar;

    init_dolar(&dolar);
    while (str[dolar.i])
    {
        if (str[dolar.i] == '\'' && !dolar.in_double_quote)
        {
            dolar.in_single_quote = !dolar.in_single_quote;
            dolar.tmp = ft_substr(str, dolar.i, 1);
            dolar.result = ft_strjoin_free(dolar.result, dolar.tmp);
            dolar.i++;
        }
        else if (str[dolar.i] == '"' && !dolar.in_single_quote)
        {
            dolar.in_double_quote = !dolar.in_double_quote;
            dolar.tmp = ft_substr(str, dolar.i, 1);
            dolar.result = ft_strjoin_free(dolar.result, dolar.tmp);
            dolar.i++;
        }
        else if (str[dolar.i] == '$' && !dolar.in_single_quote && dolar.in_double_quote)
        {
            if(!ft_isalnum(str[dolar.i + 1]))
            {
                dolar.tmp = ft_substr(str, dolar.i, 1);
                dolar.result = ft_strjoin_free(dolar.result, dolar.tmp);
                dolar.i++;
                continue;
            }
            dolar.start = ++dolar.i;
            while (str[dolar.i] && (ft_isalnum(str[dolar.i]) || str[dolar.i] == '_'))
                dolar.i++;
            dolar.var_name = ft_substr(str, dolar.start, dolar.i - dolar.start);
            dolar.var_value = getenv(dolar.var_name);
            free(dolar.var_name);
            if (dolar.var_value)
                dolar.result = ft_strjoin_free(dolar.result, ft_strdup(dolar.var_value));
        }
        else
        {
            dolar.tmp = ft_substr(str, dolar.i, 1);
            dolar.result = ft_strjoin_free(dolar.result, dolar.tmp);
            dolar.i++;
        }
    }
    return (dolar.result);
}
