/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dolar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:37:05 by aoussama          #+#    #+#             */
/*   Updated: 2025/07/30 15:26:24 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
            dolar.result = ft_strjoin(dolar.result, dolar.tmp);
            dolar.i++;
        }
        else if (str[dolar.i] == '"' && !dolar.in_single_quote)
        {
            dolar.in_double_quote = !dolar.in_double_quote;
            dolar.tmp = ft_substr(str, dolar.i, 1);
            dolar.result = ft_strjoin(dolar.result, dolar.tmp);
            dolar.i++;
        }
        else if (str[dolar.i] == '$' && !dolar.in_single_quote && dolar.in_double_quote)
        {
            if(!ft_isalnum(str[dolar.i + 1]))
            {
                dolar.tmp = ft_substr(str, dolar.i, 1);
                dolar.result = ft_strjoin(dolar.result, dolar.tmp);
                dolar.i++;
                continue;
            }
            dolar.start = ++dolar.i;
            while (str[dolar.i] && (ft_isalnum(str[dolar.i]) || str[dolar.i] == '_'))
                dolar.i++;
            dolar.var_name = ft_substr(str, dolar.start, dolar.i - dolar.start);
            dolar.var_value = getenv(dolar.var_name);
            if (dolar.var_value)
                dolar.result = ft_strjoin(dolar.result, ft_strdup(dolar.var_value));
        }
        else
        {
            dolar.tmp = ft_substr(str, dolar.i, 1);
            dolar.result = ft_strjoin(dolar.result, dolar.tmp);
            dolar.i++;
        }
    }
    return (dolar.result);
}
