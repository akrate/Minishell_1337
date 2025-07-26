/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:55:00 by aoussama          #+#    #+#             */
/*   Updated: 2025/07/26 21:58:46 by aoussama         ###   ########.fr       */
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
t_list *chr_meta(char *str,int *i)
{
    if (str[*i] == '<')
    {
        if (str[(*i) + 1] == '<')
        {
            if (is_meta(str[(*i) + 2]))
                return (write (1,"parse error\n",12),NULL);
            return ((*i) += 2,fill_node(ft_strdup("<<"),T_DLESS,1));
        }
        else
            return ((*i)++,fill_node(ft_strdup("<"),T_LESS,1));
    }else if (str[*i] == '>')
    {
        if (str[(*i) + 1] == '>')
        {
            if (is_meta(str[(*i) + 2]))
                return (write (1,"parse error\n",12),NULL);
            return ((*i) += 2,fill_node(ft_strdup(">>"),T_DGREAT,1));
        }
        else
            return ((*i)++,fill_node(ft_strdup(">"),T_GREAT,1));
    }else if (str[*i] == '|')
        return ((*i)++,fill_node(ft_strdup("|"),T_PIPE,1));
    return (NULL);
}
t_list *split_cmd(char *str)
{
    int i;
    int start;
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
        while (str[i] && str[i] != ' ' && is_meta(str[i]) != 1)
            get_pos(str,&i);
        if (is_meta(str[i]))
        {
            if (ft_lstadd_back(&head,chr_meta(str,&i)) == 1)   
                 return (ft_lstclear(&head), NULL);
        }
        else
        {   
            if(ft_lstadd_back(&head,fill_node(ft_substr(str,start,i - start),T_IDENTIFIER,1)) == 1)
             return (ft_lstclear(&head), NULL); 
        }
    }
    return (head);
}

void paring_cmd(char *cmd)
{
    t_list *args;
    t_list *tmp;
    int flag;
    args = split_cmd(cmd);
    if (args == NULL)
    {
        printf("Error: in malloc");
        return;
    }
    flag = 0;
    if (checking_cmd(&args) == 1)
    return ;
    convert_dolar(&args);
    tmp = args;
    while (tmp)
    {
        if (tmp->type == T_DLESS)
            flag = 2;
        // if (flag == 0)  
            // tmp->content = checking_dolar(tmp->content);
        if (tmp->content == NULL)
            ft_lstclear(&args);
        tmp->content = skip_qouts(tmp->content,tmp->remove_qoute);
        printf("[%s]-\n", (char *)tmp->content);
        if (flag != 0)
            flag--;
        tmp = tmp->next;
    }
}
