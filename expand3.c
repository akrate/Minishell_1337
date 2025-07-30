/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:38:20 by aoussama          #+#    #+#             */
/*   Updated: 2025/07/30 14:56:31 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char *extract_quoted_substring(char *str, int *index, char quote_char)
{
    int start = (*index)++;

        while (str[*index] && str[*index] != quote_char)
            (*index)++;
        if (str[*index] == quote_char)
            (*index)++;
        
    return ft_substr(str, start, *index - start);
}
int present_dolar(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\'')
        {
            i++;
            while (str[i] != '\'' && str[i])
                i++; 
        }
        if (str[i] == '"')
        {
            i++;
            while (str[i] != '"' && str[i])
                i++;
        }
        if(str[i] == '$')
        {
            if (ft_isalpha(str[i + 1]) == 1 || str[i + 1] == '_')
                return (1);
        }
        i++;
    }
    return (0);
}

int check_space(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == ' ')
        {
            return (1);
        }
        i++;
    }
    return (0);
}
void join_lists(t_list **a, t_list *b)
{
    if (!*a)
    {
        *a = b;
        return;
    }

    t_list *last = *a;
    while (last->next)
        last = last->next;
    last->next = b;
}

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
                        result = ft_strdup("");
                    }
                    if (env_val[sp])
                        join_lists(&tmp, split_cmd(env_val + sp,1));
                }
                else
                {
                    
                    result = ft_strjoin_free(skip_qouts(result,0), ft_strdup(env_val));
                }
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
            if (current->next != NULL)
            {
                ft_lstadd_back(&tmp, fill_node(ft_strdup(current->content), current->type, 0));
                current = current->next;
                ft_lstadd_back(&tmp, fill_node(ft_strdup(current->content), current->type, 0));
                current = current->next;
                continue;
            }
        }
        if (present_dolar(current->content) == 0)
            ft_lstadd_back(&tmp, fill_node(ft_strdup(current->content), current->type, 0));
        else
        {
            t_list *processed = process_node_content2(current->content);
            join_lists(&tmp, processed);
        }
        current = current->next;
    }
    return (tmp);
}
