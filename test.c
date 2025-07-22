/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:36:21 by aoussama          #+#    #+#             */
/*   Updated: 2025/07/22 19:12:22 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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


void free_split(char **tmp)
{
    int i = 0;
    if (!tmp)
        return;
    while (tmp[i])
        free(tmp[i++]);
    free(tmp);
}

t_list *create_list(char *str,int flag)
{
    char **tmp;
    t_list *list;
    int j;
    int i;
    tmp = ft_split(str,' ');
    if (tmp == NULL)
        return (NULL);
    i = flag;
    list = NULL;
    while (tmp[i])
    {
        if (is_meta(tmp[i][0]))
        {
            
            j = 0;
            if (ft_lstadd_back(&list,chr_meta(tmp[i],&j)) == 1)
            {
                ft_lstclear(&list);
                free_split(tmp);
                return (NULL);
            }
        }
        else
        {
            if(ft_lstadd_back(&list,fill_node(ft_substr(tmp[i],0,ft_strlen(tmp[i])),T_IDENTIFIER,0)) == 1)
            {
                ft_lstclear(&list);
                free_split(tmp);

                return (NULL);
            }
        }
        i++;
    }
    free_split(tmp);
    return (list);
}
char *get_first_word(char *str)
{
    char **tmp;
    char *first;
    tmp = ft_split(str,' ');
    int i;
    
    i = 0;
    first = ft_strdup(tmp[0]);
    while (tmp[i])
    {
        free(tmp[i]);
        i++;
    }
    free(tmp);
    return (first);
}
void convert_dolar(t_list **list)
{
    int i;
    char *result;
    char *str;
    char *str1;
    t_list *tmp;
    t_list *helper;
    char *var_value;
    int start;
    char *to_add;
    int flag;

    tmp = *list;
    while (tmp)
    {
        i = 0;
        result = ft_strdup("");
        str = ft_strdup(tmp->content);
        start = 0;
        flag = 0;
        while (str[i])
        {
            if (str[i] == '"')
            {
                start = i++;
                while (str[i] && str[i] != '"')
                    i++;
                str1 = ft_substr(str, start, i - start + 1);
                result = ft_strjoin_free(result, str1);
            }
            else if (str[i] == '\'')
            {
                start = i++;
                while (str[i] && str[i] != '\'')
                    i++;
                str1 = ft_substr(str, start, i - start + 1);
                result = ft_strjoin_free(result, str1);
            }
            else if (str[i] == '$')
            {
                if (str[i + 1] == '$')
                {
                    start = i;
                    while (str[i] == '$')
                        i++;
                    i--;
                    str1 = ft_substr(str, start, i - start);
                    result = ft_strjoin_free(result, str1);
                }
                if (i > 0)
                {
                    free(tmp->content);
                    tmp->content = ft_substr(str, 0, i);
                }
                else
                    flag = 1;
                start = ++i;
                if (str[i] == '"')
                {
                    i++;
                    while (str[i] != '"' && str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
                        i++;
                    str1 = ft_substr(str, start, i - start + 1);
                    result = ft_strjoin_free(result, str1);
                    i++;
                    continue;
                }
                else
                {
                    if (ft_isdigit(str[i]) == 1)
                    {
                        i++;
                    }
                    else{
                        
                        while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
                            i++;
                    }
                }
                str1 = skip_qouts(ft_substr(str, start, i - start),1);
                // printf("str1 ===>%s\n",str1);
                var_value = getenv(str1);
                // printf("var_value ===>%s\n",var_value);

                free(str1);
                if (var_value && check_space(var_value))
                {
                    if (flag == 1)
                    {
                        free(tmp->content);
                        tmp->content = get_first_word(var_value);
                    }
                    helper = tmp->next;
                    tmp->next = create_list(var_value,flag);

                    if (str[i] != '\0')
                        ft_lstadd_back(&tmp->next, fill_node(ft_strdup(str + i), T_IDENTIFIER,1));/// dakchi li b9a mn node 
                    join_lists(&tmp->next, helper);
                    break;
                }
                else
                {
                    if (var_value)
                        to_add = ft_strdup(var_value);
                    else
                        to_add = ft_strdup("");
                                    
                    result = ft_strjoin_free(result, to_add);
                    result = ft_strjoin_free(result,ft_strdup(str + i));
                }
                break;
            }
            else
            {
                str1 = ft_substr(str, i, 1);
                result = ft_strjoin_free(result, str1);
            }
            i++;
        }
        if (result && *result)
        {
            
            free(tmp->content);
            tmp->content = result;
        }
        else
            free(result);
        tmp = tmp->next;
        free(str);
    }
}
