/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:38:20 by aoussama          #+#    #+#             */
/*   Updated: 2025/07/31 04:48:04 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void init_qouts(t_qout *strc)
{
    strc->i = 0;
    strc->in_quote = 0;
    strc->quote_char = 0;
    strc->result = ft_strdup("");
    strc->tmp = NULL;
}
char *skip_single_qout(char *str)
{
    t_qout qout;

    init_qouts(&qout);
    while (str[qout.i])
    {
        if (str[qout.i] == '\'' && qout.in_quote == 0)
        {
            qout.in_quote = 1;
            qout.quote_char = '\'';
            qout.i++;
            continue;
        }
        if (str[qout.i] == '\'' && qout.in_quote == 1)
        {
            qout.in_quote = 0;
            qout.quote_char = 0;
            qout.i++;
            continue;
        }
        if (str[qout.i] == '$' && str[qout.i + 1] == '\'' )
        {
            qout.i++;
            continue;
        }
        char *tmp = ft_substr(str, qout.i, 1);
        char *new_res = ft_strjoin(qout.result, tmp);
        qout.result = new_res;
        qout.i++;
    }
    return qout.result;
}
char *extract_quoted_substring(char *str, int *index, char quote_char)
{
    int start = (*index)++;

        while (str[*index] && str[*index] != quote_char)
            (*index)++;
        if (str[*index] == quote_char)
            (*index)++;
    if (quote_char == '\'')
        return skip_single_qout(ft_substr(str, start, *index - start));
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
            result = ft_strjoin(result, helper);
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
                        result = ft_strjoin(result, first);
                        ft_lstadd_back(&tmp, fill_node(ft_strdup(result), T_IDENTIFIER, 1));
                        result = ft_strdup("");
                    }
                    if (env_val[sp])
                    {
                        ft_lstadd_back(&tmp, fill_node(result, T_IDENTIFIER, 0));   
                        join_lists(&tmp, split_cmd(env_val + sp,1));
                        result = ft_strdup("");
                    }
                }
                else
                {
                    
                    result = ft_strjoin(result, ft_strdup(env_val));
                }
            }
        }
        else if (str[i] == '$' && str[i + 1] == '\'')
        {
            i++;
            helper = extract_quoted_substring(str, &i, str[i]);
            result = ft_strjoin(result, helper);
        }
        else
        {
            result = ft_strjoin(result, ft_substr(str, i, 1));
            i++;
        }
    }
    if (result && *result)
        ft_lstadd_back(&tmp, fill_node(result, T_IDENTIFIER, 0));
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
                ft_lstadd_back(&tmp, fill_node(ft_strdup(current->content), current->type, current->remove_qoute));
                current = current->next;
                ft_lstadd_back(&tmp, fill_node(ft_strdup(current->content), current->type, current->remove_qoute));
                current = current->next;
                continue;
            }
        }
        if (present_dolar(current->content) == 0)
            ft_lstadd_back(&tmp, fill_node(skip_single_qout(ft_strdup(current->content)), current->type, current->remove_qoute));
        else
        {
            t_list *processed = process_node_content2(current->content);
            join_lists(&tmp, processed);
        }
        current = current->next;
    }
    return (tmp);
}
