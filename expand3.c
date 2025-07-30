/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:38:20 by aoussama          #+#    #+#             */
/*   Updated: 2025/07/30 11:55:16 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *process_node_content2(char *str)
{
    int i = 0;
    int start;
    int sp;
    char *result = ft_strdup("");
    char *helper;
    t_list *tmp = NULL;

    while (str[i])
    {
        if (str[i] == '"' || str[i] == '\'')
        {
            helper = extract_quoted_substring(str, &i, str[i]);
            result = ft_strjoin_free(result, helper);
        }
        else if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
        {
            start = ++i;
            while (ft_isalnum(str[i]) || str[i] == '_')
                i++;
            char *env_name = ft_substr(str, start, i - start);
            char *env_val = getenv(env_name);
            free(env_name);
            if (env_val)
            {
                if (check_space(env_val))
                {
                    sp = 0;
                    while (env_val[sp] && env_val[sp] != ' ' && is_meta(env_val[sp]) == 0)
                        sp++;
                    if (sp > 0)
                    {   
                        char *first = ft_substr(env_val, 0, sp);
                        result = ft_strjoin_free(result, first);
                        ft_lstadd_back(&tmp, fill_node(ft_strdup(result), T_IDENTIFIER, 1));
                        free(result);
                        result = ft_strdup("");
                    }
                    if (env_val[sp])
                        join_lists(&tmp, split_cmd(env_val + sp,1));
                }
                else
                    result = ft_strjoin_free(result, ft_strdup(env_val));
            }
        }
        else
        {
            result = ft_strjoin_free(result, ft_substr(str, i, 1));
            i++;
        }
    }
    if (result && *result)
        ft_lstadd_back(&tmp, fill_node(result, T_IDENTIFIER, 1));
    else
        free(result);
    return tmp;
}


t_list *convert_dolar2(t_list **list)
{
    t_list *tmp = NULL;
    t_list *current = *list;

    while (current)
    {
        if (current->type == T_DLESS)
        {
            if (current->next != NULL && current->next->next != NULL)
                current = current->next->next;

        }
        if (present_dolar(current->content) == 0)
        {
            ft_lstadd_back(&tmp, fill_node(ft_strdup(current->content), current->type, 0));
        }
        else
        {
            t_list *processed = process_node_content2(current->content);
            join_lists(&tmp, processed);
        }
        current = current->next;
    }
    return (tmp);
}
