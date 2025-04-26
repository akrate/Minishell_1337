/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:55:00 by aoussama          #+#    #+#             */
/*   Updated: 2025/04/26 17:42:00 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void get_pos(char *str,int *i)
{
    char c;
    if (str[*i] == '\'' || str[*i] == '"')
    {
        c = str[*i];
        (*i)++;
        while (str[*i] && str[*i] != c)
            (*i)++;
        if (str[*i] == c)
            (*i)++;
    }else{
        while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != ' ' && !is_meta(str[*i]))
            (*i)++;
    }
}
char *chr_meta(char *str,int *i)
{
    if (str[*i] == '<')
    {
        if (str[(*i) + 1] == '<')
        {
            if (str[(*i) + 2] == '<')
                return (write (1,"parse error near `>'\n",21),NULL);
            (*i) += 2;
            return (ft_strdup("<<"));
        }
        else{
            (*i)++;
            return (ft_strdup("<"));
        }
    }else if (str[*i] == '>')
    {
        if (str[(*i) + 1] == '>')
        {
            if (str[(*i) + 2] == '>')
                return (write (1,"parse error near `<'\n",21),NULL);
            (*i) += 2;
            return (ft_strdup(">>"));
        }
        else
        {
            (*i)++;   
            return (ft_strdup(">"));
        }
    }else if (str[*i] == '|')
    {
        (*i)++;
        return (ft_strdup("|"));
    }
}
t_list *split_cmd(char *str)
{
    int i;
    int start;
    char *meta;
    t_list *head = NULL;
    if (!str)
        return (NULL);
    i = 0;
    while (str[i] == ' ')
            i++;
    while (str[i])
    {
        while (str[i] == ' ')
            i++;
        start = i;
        while (str[i] && str[i] != ' ' && !is_meta(str[i]))
            get_pos(str,&i);
        if (is_meta(str[i]))
        {
            meta = chr_meta(str,&i);
            if (!meta)
                return (ft_lstclear(&head), NULL);
            ft_lstadd_back(&head,ft_lstnew(meta)); 
        }
        ft_lstadd_back(&head,ft_lstnew(ft_substr(str,start,i - start)));
    }
    return (head);
}
void paring_cmd(char *cmd)
{
    t_list *args = split_cmd(cmd);
    
    t_list *tmp = args;
    if(!tmp)
        write (1,"error",5);
    while (tmp)
    {
        printf("arg: %s\n", (char *)tmp->content);
        tmp = tmp->next;
    }
}
